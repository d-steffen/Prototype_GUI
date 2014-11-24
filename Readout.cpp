#include <cstdint>
#include <queue>
#include <list>
#include <QString>

#include <uhal/uhal.hpp>
#include <uhal/log/log.hpp>
#include <uhal/log/exception.hpp>

#include "Readout.h"
#include "text_file.h"
#include "live_analyzer.h"

// includes for ROOT tree:
#include <cmath>
#include <limits>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "TH1.h"

#include "data_format.h"
#include "tree_format.h"

using namespace uhal;


void readoutThread::stop(){
	mutex.lock();
	stopped = true;
	mutex.unlock();
	clock_gettime(CLOCK_REALTIME, &stopsignaltime);
	emit writeConsole("Closing readout connection...");

	// connecting to the Hardware IP endpoint:
	struct FatalLevel afatal;
	//struct DebugLevel adebug;
	uhal::setLogLevelTo(afatal);
	ConnectionManager manager ( "file://connections.xml" );
	HwInterface hw=manager.getDevice ( "bp.udp.0" );

	hw.getNode("CONTROLS.data_saving").write(0);
	hw.dispatch();
}


void readoutThread::run(){

	emit writeConsole("Start Measurement");
	emit writeConsole("   Connect to Network Access Controller");

	try{
		// connecting to the Hardware IP endpoint:
		struct FatalLevel afatal;
		//struct DebugLevel adebug;
		uhal::setLogLevelTo(afatal);
		ConnectionManager manager ( "file://connections.xml" );
		HwInterface hw=manager.getDevice ( "bp.udp.0" );

		// defining Log-file:
		LogFile *Log = new LogFile((NACdialog*)this);

		// disable data acquisition
		hw.getNode("CONTROLS.data_saving").write(0);
		hw.dispatch();

		// reset channel_buffer_fifo and data_fifo on FPGA-stage 1 and ll_fifo on FPGA-stage 2:
		hw.getNode("CONTROLS.fifo_reset").write(1);
		hw.dispatch();

		// reset ipbus fifos and registers:
		hw.getNode("RST").write(1);
		hw.dispatch();

		struct timespec req = {0};
		req.tv_sec = 0;
		req.tv_nsec = 200;
		nanosleep(&req, (struct timespec *)NULL);

		hw.getNode("CONTROLS.fifo_reset").write(0);
		hw.dispatch();

		emit writeConsole("   START saving data from SDU...");
		emit writeConsole("");

		reading = true;

		hw.getNode("CONTROLS.data_saving").write(1);
		hw.dispatch();
		timespec start;
		clock_gettime(CLOCK_REALTIME, &start);
		timespec stop;
		double tc = 0, bc = 0;


		while(reading)
		{
			ValWord<uint32_t> wordCnt = hw.getNode("FLAGS.WORD_CNT").read();
			hw.dispatch();

			ValVector<uint32_t> vec;
			if (wordCnt.value() > 0)
			{
				vec = hw.getNode("DATA").readBlock(wordCnt.value());
				hw.dispatch();
				if (!vec.valid()){
					emit writeConsole("   Invalid data");
					Log->append(QString("   Readout of invalid data!"));
				}
				for (unsigned int i = 0; i<vec.size(); i++)
				{
					_freeSpace->acquire();
					_buffer->lock();
					_FIFO->push(vec[i]);
					_buffer->unlock();
					_usedSpace->release();
				}
			}

			tc+=1;
			bc += (vec.size()*4);
			clock_gettime(CLOCK_REALTIME, &stop);
			double timediff = stop.tv_sec*1e9 + stop.tv_nsec - start.tv_sec*1e9 - start.tv_nsec;
			if (timediff > 1e9)
			{
				//emit writeConsole(QString("%1 reads/s (%2 KB/s)").arg(tc/timediff*1e9).arg(bc/timediff*1e6));
				//emit writeConsole(QString::number(wordCnt.value()) + " words in buffer");
				int FIFOsize = 0;
				_buffer->lock();
				FIFOsize = _FIFO->size();
				_buffer->unlock();
				emit updateStatusBars(static_cast<int>(tc/timediff*1e9), static_cast<int>(bc/timediff*1e6), wordCnt.value(), FIFOsize);
				tc = 0;
				bc = 0;
				clock_gettime(CLOCK_REALTIME, &start);
			}

			if(stopped==true)
			{
				timespec now;
				clock_gettime(CLOCK_REALTIME, &now);
				double timediff = now.tv_sec*1e9 + now.tv_nsec - stopsignaltime.tv_sec*1e9 - stopsignaltime.tv_nsec;
				if (timediff > 1e9)
					reading = false;
			}
		}

		mutex.lock();
		stopped = false;
		mutex.unlock();
		reading = true;

		emit updateStatusBars(0, 0, 0, 0);

		hw.getNode("CONTROLS.fifo_reset").write(1);
		hw.dispatch();

		emit writeConsole("Buffers on NAC reseted!");

		emit done();//createTree(filename);
	}
	catch(const exception::exception& e){
		emit writeConsole("No NAC available in network.");
	}
	return;
}


void readoutThread::createTree(QString filename){

	std::ifstream rawdata;

	int histno = 0;
	int max_time = 0;


	event_t * event = new event_t;

	event->eventSize = 0;
	event->channelNo = 0;
	event->timetag = 0;
	event->samples = 0;
	event->pedestal = 0;
	event->sigma_noise = 0;
	event->maximum = 0;

	QString rawfile;
	QString treename;
	rawfile = "../rawfiles/" + filename + ".dat";
	treename = "../forest/" + filename + ".root";

	TFile * treefile = new TFile(treename.toUtf8().constData(), "RECREATE");
	TTree * tree = new TTree("tree", "PENeLOPE_Data");

	tree->Branch("channelNo", &event->channelNo, "channelNo/I");
	tree->Branch("timestamp", &event->timetag, "timestamp/I");
	tree->Branch("sampleNo", &event->samples, "sampleNo/I");
	tree->Branch("samples", event->smpl, "samples[sampleNo]/I");
	tree->Branch("pedestal",&event->pedestal,"pedestal/I");
	tree->Branch("sigma_noise", &event->sigma_noise, "sigma_noise/I");
	tree->Branch("maximum", &event->maximum, "maximum/I");

	emit writeConsole("Converting " + rawfile + " to " + treename);

	TH1F *spec = new TH1F("spec", "Proton Spectrum", 512, 0, 2048);

	header_0 header0;
	header_1 header1;
	header_2 header2;
	header_3 header3;
	data_word word;
	trailer trailer_0;

	//begin reading file:

	rawdata.open(rawfile.toUtf8().constData(), std::ios::in | std::ios::binary);

	if (rawdata.is_open())
	{
		while(!rawdata.eof())
		{
			rawdata.read((char*)&header0, sizeof(header0));
			if (rawdata && header0.start != 0x00000000)
			{
				emit writeConsole("Startcode not found!");
				continue;
			}
			rawdata.read((char*)&header1, sizeof(header1));
			rawdata.read((char*)&header2, sizeof(header2));
			rawdata.read((char*)&header3, sizeof(header3));
			if (!rawdata){
				emit writeConsole("End of file...");
				break;
			}
			event->channelNo = header1.channelNo;
			//emit writeConsole(QString("channel no: %1").arg(event->channelNo));
			event->eventSize = header1.no_words;
			//emit writeConsole(QString("event size: %1").arg(event->eventSize));
			event->samples = (header1.no_words - 5)*2;
			//emit writeConsole(QString("event samples: %1").arg(event->samples));
			event->timetag = header3.timestamp;
			max_time = event->timetag;
			//emit writeConsole(QString("timestamp: %1").arg(event->timetag));
			event->pedestal = header2.pedestal;
			event->sigma_noise = sqrt(header2.sigma_noise);
			//emit writeConsole(QString("pedestal: %1").arg(event->sigma_noise));

			for (int sample_i = 0; sample_i < event->samples; sample_i += 2)
			{
				rawdata.read((char*)&word, sizeof(data_word));
				//if (!rawdata){
				//	emit write Console("End of file...");
				//	break;
				//}
				event->smpl[sample_i] = word.data0;
				//emit writeConsole(QString(" %1").arg(event->smpl[sample_i]));
				event->smpl[sample_i+1] = word.data1;
				//emit writeConsole(QString(" %1").arg(event->smpl[sample_i+1]));
			}

			rawdata.read((char*)&trailer_0, sizeof(trailer_0));
			if (rawdata && trailer_0.trail == 0xFFFFFFFF)
			{
				std::ostringstream ostr;
				ostr << histno;

				TH1F *hist = new TH1F(ostr.str().c_str(),"Signal Shape", event->samples, 0, event->samples);
				event->maximum = std::numeric_limits<int>::min();
				for(int smpl_i = 0; smpl_i < event->samples;smpl_i++)
				{
					event->maximum = std::max(event->maximum, event->smpl[smpl_i]);
					hist->Fill(smpl_i, event->smpl[smpl_i]);
				}
				spec->Fill(event->maximum);

				histno++;

				tree->Fill();
			}
			else if (!rawdata)
				emit writeConsole("End of file...");
			else
				emit writeConsole("Trailer not found");

		}; //end while(!rawdata.eof())

		rawdata.close();

	}; //end if(rawdata.is_open())

	treefile->Write();
	treefile->Close();
	delete event;
	delete treefile;

	emit writeConsole("Conversion done!");

	emit done();

return;
}
