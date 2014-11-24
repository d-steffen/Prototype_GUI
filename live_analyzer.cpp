#include <cstdint>
#include <fstream>
#include <ctime>
#include <queue>
#include <list>
#include <iostream>

#include "live_analyzer.h"
#include "text_file.h"
#include "data_format.h"
#include "tree_format.h"

#include <QString>

// includes for ROOT tree:
#include <cmath>
#include <limits>
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TMultiGraph.h"


#define TIME_FORMAT "%Y%m%d_%H%M%S"
//#define shapesPerSec 3


liveAnalyzer::liveAnalyzer(std::queue<uint32_t, std::list<uint32_t> > *FIFO, QSemaphore *freeSpace, QSemaphore *usedSpace, TH1F *_spec, TH2I *_heatMap, TMultiGraph *_scope, QMutex *oszi, QMutex *buffer)
{
	_FIFO = FIFO;
	_freeSpace = freeSpace;
	_usedSpace = usedSpace;
	_oszi = oszi;
	_buffer = buffer;

	scope = _scope;
	heatMap = _heatMap;
	spec = _spec;

	channelNumber.lock();
	channelNo = 0;
	channelNumber.unlock();
}

void liveAnalyzer::stop()
{
	mutex.lock();
	reading = false;
	mutex.unlock();
	//emit writeConsole("Stop rootThread");

	return;
}

void liveAnalyzer::adoptChannelNumber(QString item)
{
	if(item == "All channels")
	{
		channelNumber.lock();
		channelNo = 0;
		channelNumber.unlock();
		//emit writeConsole(QString::number(channelNo));
	}
	else
	{
		channelNumber.lock();
		channelNo = QChar(item[item.size()-1]).digitValue();
		channelNumber.unlock();
		//emit writeConsole(QString::number(channelNo));
	}
}

bool liveAnalyzer::valueOfBool(bool reading)
{
	bool value = false;
	bool empty = false;
	_buffer->lock();
	empty = _FIFO->empty();
	_buffer->unlock();
	if(reading or !empty)
		value = true;
	return value;
}

void liveAnalyzer::run()
{
	LogFile *Log = new LogFile((NACdialog*)this);

	// for filename with time stamp:
	std::ofstream file;
	QString rawfile;
	QString treename;
	QString filename;
	struct tm *timeinfo;
	char buffer[16];
	time_t rawtime;

	mutex.lock();
	reading = true;
	mutex.unlock();

	bool time_out = false;
	int scopeCount = 0;

	float x=0, y=0;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,16,TIME_FORMAT,timeinfo);
	rawfile = "../rawfiles/" + QString(buffer) + ".dat";
	treename = "../forest/" + QString(buffer) + ".root";
	filename = QString(buffer);
	emit adoptCurrentFile(treename);

	Log->append("Measurement " + filename + ":");
	emit writeConsole("   Read raw data into " + rawfile);
	emit writeConsole("   Save online analyzed data in " + treename);

	file.open(rawfile.toUtf8().constData(), std::ios::binary | std::ios::out | std::ios::app);
	TFile *treefile = new TFile(treename.toUtf8().constData(), "RECREATE");

	event_t *event = new event_t;
	event->eventSize = 0;
	event->channelNo = 0;
	event->timetag = 0;
	event->samples = 0;
	event->pedestal = 0;
	event->sigma_noise = 0;
	event->maximum = 0;

	TTree *tree = new TTree("tree", "PENeLOPE_Data");
	tree->Branch("channelNo", &event->channelNo, "channelNo/I");
	tree->Branch("timestamp", &event->timetag, "timestamp/I");
	tree->Branch("sampleNo", &event->samples, "sampleNo/I");
	tree->Branch("samples", event->smpl, "samples[sampleNo]/I");
	tree->Branch("pedestal",&event->pedestal,"pedestal/I");
	tree->Branch("sigma_noise", &event->sigma_noise, "sigma_noise/I");
	tree->Branch("maximum", &event->maximum, "maximum/I");

	header_0 *header0;
	header_1 *header1;
	header_2 *header2;
	header_3 *header3;
	data_word *word;
	trailer *trailer_0;

	timespec start;
	clock_gettime(CLOCK_REALTIME, &start);
	timespec stop;

	if (file.is_open())
	{
		while(valueOfBool(reading))
		{
			if(!_usedSpace->tryAcquire(1, 1000))  ///////////////////// read header0
			{
				emit writeConsole("   Time out: No entries in Buffer FIFO. Try again!");
				//emit writeConsole(QString("reading = %1").arg(reading));
				//emit writeConsole(QString("FIFO empty? %1").arg(_FIFO->empty()));
				continue;
			}
			_buffer->lock();
			uint32_t temp = _FIFO->front();
			_buffer->unlock();
			file.write((char*)&temp,4);
			header0 = (header_0*)&temp;
			_buffer->lock();
			_FIFO->pop();
			_buffer->unlock();
			_freeSpace->release(1);
			if (header0->start != 0x00000000)
			{
				Log->append(QString("   Not expected data word (expected: header0)"));
				emit writeConsole("   Startcode not found!");
				continue;
			}

			if(!_usedSpace->tryAcquire(1, 4000))	///////////////////// read header1
			{
				emit writeConsole("   Time out: Incomplete event (expected: header1). Search for new header0.");
				Log->append(QString("   Time out: Incomplete event. Search for new header0."));
				continue;
			}
			_buffer->lock();
			temp = _FIFO->front();
			_buffer->unlock();
			file.write((char*)&temp,4);
			header1 = (header_1*)&temp;
			event->channelNo = header1->channelNo;
			//emit writeConsole(QString("channel no: %1").arg(event->channelNo));
			event->eventSize = header1->no_words;
			//emit writeConsole(QString("event size: %1").arg(event->eventSize));
			event->samples = (header1->no_words - 5)*2;
			//emit writeConsole(QString("event samples: %1").arg(event->samples));
			_buffer->lock();
			_FIFO->pop();
			_buffer->unlock();
			_freeSpace->release();

			if(!_usedSpace->tryAcquire(1, 4000))  ///////////////////// read header2
			{
				emit writeConsole("   Time out: Incomplete event (expected: header2). Search for new header0.");
				Log->append(QString("   Time out: Incomplete event. Search for new header0."));
				continue;
			}
			_buffer->lock();
			temp = _FIFO->front();
			_buffer->unlock();
			file.write((char*)&temp,4);
			header2 = (header_2*)&temp;
			event->pedestal = header2->pedestal;
			event->sigma_noise = sqrt(header2->sigma_noise);
			//emit writeConsole(QString("pedestal: %1").arg(event->sigma_noise));
			_buffer->lock();
			_FIFO->pop();
			_buffer->unlock();
			_freeSpace->release();

			if(!_usedSpace->tryAcquire(1, 4000))	///////////////////// read header3
			{
				emit writeConsole("   Time out: Incomplete event (expected: header3). Search for new header0.");
				Log->append(QString("   Time out: Incomplete event. Search for new header0."));
				continue;
			}
			_buffer->lock();
			temp = _FIFO->front();
			_buffer->unlock();
			file.write((char*)&temp,4);
			header3 = (header_3*)&temp;
			event->timetag = header3->timestamp;
//			max_time = event->timetag;
			//emit writeConsole(QString("timestamp: %1").arg(event->timetag));
			_buffer->lock();
			_FIFO->pop();
			_buffer->unlock();
			_freeSpace->release();


			for (int sample_i = 0; sample_i < event->samples; sample_i += 2)
			{
				if(!_usedSpace->tryAcquire(1, 2000))	///////////////////// read data words
				{
					emit writeConsole(QString("   Time out: Incomplete event (expected: data word #%1). Search for new header0.").arg(sample_i/2));
					//Log->append(QString("   Time out: Incomplete event. Search for new data word."));
					time_out = true;
					break;
				}
				_buffer->lock();
				temp = _FIFO->front();
				_buffer->unlock();
				file.write((char*)&temp,4);
				word = (data_word*)&temp;
				_buffer->lock();
				_FIFO->pop();
				_buffer->unlock();
				_freeSpace->release();
				event->smpl[sample_i] = word->data0;
				//emit writeConsole(QString(" %1").arg(event->smpl[sample_i]));
				event->smpl[sample_i+1] = word->data1;
				//emit writeConsole(QString(" %1").arg(event->smpl[sample_i+1]));
			}
			if(time_out == true)
			{
				time_out =false;
				continue;
			}

			if(!_usedSpace->tryAcquire(1, 4000))	///////////////////// read trailer
			{
				emit writeConsole("   Time out: Incomplete event (expected: trailer). Search for new header0.");
				Log->append(QString("   Time out: Incomplete event. Search for new header0."));
				continue;
			}
			_buffer->lock();
			temp = _FIFO->front();
			_buffer->unlock();
			file.write((char*)&temp,4);
			trailer_0 = (trailer*)&temp;
			//emit writeConsole(QString("trailer: %1").arg(temp));
			_buffer->lock();
			_FIFO->pop();
			_buffer->unlock();
			_freeSpace->release();
			if (trailer_0->trail == 0xFFFFFFFF)
			{
				_oszi->lock();
				if(scopeCount < scope->GetListOfGraphs()->GetSize())
					((TGraph*)scope->GetListOfGraphs()->At(scopeCount))->Set(event->samples);

				event->maximum = std::numeric_limits<int>::min();
				for(int smpl_i = 0; smpl_i < event->samples;smpl_i++)
				{
					event->maximum = std::max(event->maximum, event->smpl[smpl_i]);
					channelNumber.lock();
					if(scopeCount < scope->GetListOfGraphs()->GetSize() && (channelNo == 0 || event->channelNo == channelNo))
						((TGraph*)scope->GetListOfGraphs()->At(scopeCount))->SetPoint(smpl_i+1, smpl_i, event->smpl[smpl_i]);
					channelNumber.unlock();
				}

				if(scopeCount < scope->GetListOfGraphs()->GetSize())
					scopeCount++;
				_oszi->unlock();

				//emit writeConsole("   Trailer found->Fill tree!");
				tree->Fill();
				if(event->channelNo==1){x=1.5;y=3.5;}
				if(event->channelNo==2){x=1.5;y=2.5;}
				if(event->channelNo==3){x=1.5;y=1.5;}
				if(event->channelNo==4){x=2.5;y=3.5;}
				if(event->channelNo==5){x=2.5;y=2.5;}
				if(event->channelNo==6){x=2.5;y=1.5;}
				if(event->channelNo==7){x=3.5;y=3.5;}
				if(event->channelNo==8){x=3.5;y=2.5;}
				if(event->channelNo==9){x=3.5;y=1.5;}
				heatMap->Fill(x,y);
			}
			else
			{
				Log->append(QString("   Not expected data word (expected: trailer)"));
				emit writeConsole("   Trailer not found");
			}

			clock_gettime(CLOCK_REALTIME, &stop);
			double timediff = stop.tv_sec*1e9 + stop.tv_nsec - start.tv_sec*1e9 - start.tv_nsec;
			if (timediff > 1e9)
			{
				spec->Reset();
				//treefile->Write("",TObject::kOverwrite);
				for(int i = 0; i < tree->GetEntries(); i++)
				{
					tree->GetEntry(i);
					channelNumber.lock();
					if(channelNo == 0)
						spec->Fill(event->maximum);
					else if(event->channelNo == channelNo)
						spec->Fill(event->maximum);
					channelNumber.unlock();
				}
				emit updateHistos(spec, heatMap, scope);
				//emit writeConsole(QString("   update histograms"));
				heatMap->Reset();
				clock_gettime(CLOCK_REALTIME, &start);
				scopeCount = 0;
			}
		}
	}
	else emit writeConsole("   Unable to open rawfile!");

	emit writeConsole("   Buffers on PC are empty!");

	spec->Reset();
	//treefile->Write("",TObject::kOverwrite);
	if(tree->GetEntries() != 0){
		std::cout << "tree: " << tree << std::endl;
		for(int i = 0; i < tree->GetEntries(); i++)
		{
			tree->GetEntry(i);
			channelNumber.lock();
			if(channelNo == 0)
				spec->Fill(event->maximum);
			else if(event->channelNo == channelNo)
				spec->Fill(event->maximum);
			channelNumber.unlock();
		}
		emit updateHistos(spec, heatMap, scope);
		//emit writeConsole(QString("   update histograms"));
	}


	spec->Reset();
	//treefile->Write("",TObject::kOverwrite);
	for(int i = 0; i < tree->GetEntries(); i++)
	{
		tree->GetEntry(i);
		spec->Fill(event->maximum);
	}

	mutex.lock();
	reading = true;
	mutex.unlock();

	file.close();
	if(!file.is_open()) emit writeConsole("   Binary file closed!");

	treefile->Write();
	treefile->Close();
	delete event;
	delete treefile;

	emit finished();
	return;
}

