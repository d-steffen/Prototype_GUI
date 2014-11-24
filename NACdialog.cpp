#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
#include <list>
#include <cstdint>

#include <QtGui>
#include <QObject>
#include <QApplication>
#include <QSemaphore>
#include <QString>
#include <QThread>

#include <uhal/uhal.hpp>
#include <uhal/log/log.hpp>
#include <uhal/log/exception.hpp>

#include "NACdialog.h"
#include "Readout.h"
#include "text_file.h"
#include "live_analyzer.h"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TStyle.h"

using namespace uhal;

NACdialog::NACdialog(QWidget *parent):QMainWindow(parent)
{
	setupUi(this);

	currentFile = "empty";

	// create the three diagrams for the TQtWidgets:
	spec = new TH1F("spec", "Proton Spectrum", 512, 0, 2048);
	spec->GetXaxis()->SetTitle("ADC channel");
	spec->GetXaxis()->CenterTitle();
	spec->GetYaxis()->SetTitle("counts");
	spec->GetYaxis()->CenterTitle();

	heatMap = new TH2I("heatMap", "", 5, 0, 5, 5, 0, 5);
	heatMap->GetXaxis()->SetTitle("x");
	heatMap->GetXaxis()->SetBinLabel(1, "");
	heatMap->GetYaxis()->SetTitle("y");
	heatMap->GetYaxis()->SetBinLabel(1, "");

	scope = new TMultiGraph();
	for(int i = 0; i < shapesPerSec; i++)
	{
		TGraph *shape = new TGraph();
		shape->SetLineColor(kBlue);
		shape->SetLineWidth(2);
		scope->Add(shape);
	}
	scope->SetTitle("Signal Shapes");

	// clear the log-file and the Console with every opening of the GUI:
	Log = new LogFile((NACdialog*)this);
	Log->clear();

	// initialize QSemaphores:
	freeSpace = new QSemaphore(progressBarPCBuffer->maximum());
	usedSpace = new QSemaphore(0);

	// create readoutThread and rootThread:
	// readoutThread -> Trolltech official documentation, rootThread -> http://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
	rootThread = new liveAnalyzer(&FIFO, freeSpace, usedSpace, spec, heatMap, scope, &oszi, &buffer);
	//liveAnalyzer* rootAnalyzer = new liveAnalyzer(&FIFO, freeSpace, usedSpace);
	//rootAnalyzer->moveToThread(rootThread);
	roThread = new readoutThread(&FIFO, freeSpace, usedSpace, &buffer);

	// connect signals for rootThread:
	//connect(rootThread, SIGNAL(started()), rootAnalyzer, SLOT(process()));
	//connect(rootAnalyzer, SIGNAL(finished()), rootThread, SLOT(quit()));

	// connect signals for functionality of GUI:
	connect(rootThread, SIGNAL(writeConsole(QString)), this, SLOT(writeConsole(QString)));
	connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(roThread, SIGNAL(writeConsole(QString)), this, SLOT(writeConsole(QString)));
	connect(roThread, SIGNAL(updateStatusBars(int, int, int, int)), this, SLOT(roThread_updateStatusBars(int, int, int, int)));
	connect(roThread, SIGNAL(done()), rootThread, SLOT(stop()));
	connect(rootThread, SIGNAL(finished()), this, SLOT(rootThread_finished()));
	connect(rootThread, SIGNAL(updateHistos(TH1F*, TH2I*, TMultiGraph*)), this, SLOT(rootThread_updateHistos(TH1F*, TH2I*, TMultiGraph*)));
	connect(ComboBox, SIGNAL(currentIndexChanged(QString)), rootThread, SLOT(adoptChannelNumber(QString)));
	connect(ComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(postAnalysis()));
	connect(rootThread, SIGNAL(adoptCurrentFile(QString)), this, SLOT(adoptCurrentFile(QString)));

	// make sure that displayed settings are applied:
	ApplySettings(NumberSpinBox->value(), ConsecutiveSpinBox->value(), FactorSpinBox->value());

}


void NACdialog::on_StartButton_toggled()
{
	// Disable Reset- and Apply-Button while Data is taken
	ResetButton->setDisabled(StartButton->isChecked());
	ApplyButton->setDisabled(StartButton->isChecked());
	
	if(StartButton->isChecked()){
		Console->clear();

		roThread->start();
		rootThread->start();
	}
	else{
		roThread->stop();
		//rootThread->stop();
		StartButton->setDisabled(true);
	}
}


void NACdialog::on_ResetButton_toggled()
{
	StartButton->setDisabled(ResetButton->isChecked());
	ApplyButton->setDisabled(ResetButton->isChecked());

	if(ResetButton->isChecked()){
		Console->clear();
		Log->write(QString("Connecting to Network Access Controller (NAC)..."));

		// connecting to the Hardware IP endpoint:
		struct FatalLevel afatal;
		//struct DebugLevel adebug;
		uhal::setLogLevelTo(afatal);
		ConnectionManager manager ( "file://connections.xml" );
		HwInterface hw=manager.getDevice ( "bp.udp.0" );

		Log->write(QString("Connection established!"));
		Log->write(QString("Reset Signal Detection Units (SDUs) ..."));

		hw.getNode("CONTROLS.RESET").write(1);
		hw.dispatch();

		struct timespec req = {0};
		req.tv_sec = 1;
		req.tv_nsec = 0;
		nanosleep(&req, (struct timespec *)NULL);

		hw.getNode("CONTROLS.RESET").write(0);
		hw.dispatch();

		Log->write(QString("SDUs successfully reseted and NAC ready!"));
		Log->append(QString("############ Signal Detection Units reseted ############"));

		NumberSpinBox->setValue(50);
		ConsecutiveSpinBox->setValue(2);
		FactorSpinBox->setValue(4);
		Log->write(QString(""));
		Log->write(QString("Apply reseted setting:"));
		ApplySettings(NumberSpinBox->value(), ConsecutiveSpinBox->value(), FactorSpinBox->value());

		ResetButton->setChecked(false);
	}
}

void NACdialog::on_ApplyButton_clicked()
{
	Console->clear();
	ApplySettings(NumberSpinBox->value(), ConsecutiveSpinBox->value(), FactorSpinBox->value());
}

void NACdialog::ApplySettings(int nmb_of_smpls, int reg_length, int factor)
{
	Log->write(QString("Connecting to Network Access Controller (NAC)..."));

	// connecting to the Hardware IP endpoint:
	struct FatalLevel afatal;
	//struct DebugLevel adebug;
	uhal::setLogLevelTo(afatal);
	ConnectionManager manager ( "file://connections.xml" );
	HwInterface hw=manager.getDevice ( "bp.udp.0" );

	//Log->write(QString("Connection established!"));
	Log->write(QString("Apply settings:"));
	Log->append(QString("New Settings applied:"));

	nmb_of_smpls_per_event = nmb_of_smpls;
	std::ostringstream convert;
	convert.str("");
	convert << nmb_of_smpls;
	std::string output = "   Number of collected samples per event: " + convert.str();
	Log->write(output);
	Log->append(output);
	hw.getNode("CONTROLS.nmb_of_smpls").write(nmb_of_smpls);

	convert.str("");
	convert << reg_length;
	output = "   Number of consecutive samples for trigger decision: " + convert.str();
	Log->write(output);
	Log->append(output);
	hw.getNode("CONTROLS.reg_length").write(reg_length);

	convert.str("");
	convert << factor;
	output = "   Multiplication factor for signal detection: " + convert.str();
	Log->write(output);
	Log->append(output);
	hw.getNode("CONTROLS.factor").write(factor);

	hw.getNode("CONTROLS.fifo_reset").write(1);

	try{
		hw.dispatch();

		Log->write(QString("Settings applied and NAC ready..."));

	}
	catch(const exception::exception& e){
		Log->write(QString("No NAC available in network."));
	}

	return;
}

void NACdialog::writeConsole(QString line)
{
	Log->write(line);
	return;
}

void NACdialog::roThread_updateStatusBars(int reads, int data, int words, int bufferSize)
{
	progressBarReads->setValue(reads);
	progressBarData->setValue(data);
	progressBarBuffer->setValue(words);
	progressBarPCBuffer->setValue(bufferSize);
	return;
}

void NACdialog::rootThread_finished()
{
	StartButton->setDisabled(false);
	ComboBox->setCurrentIndex(0);
	return;
}

void NACdialog::rootThread_updateHistos(TH1F *spec, TH2I *heatMap, TMultiGraph *scope)
{
	CanvasSpectrum->GetCanvas()->cd();
	CanvasSpectrum->Erase();
	gStyle->SetOptStat(11);
	spec->Draw();
	int x[2], y[2];
	x[0]=0; x[1]=1000; y[0]=0; y[1]=0;
	TGraph *gr = new TGraph(2, x, y);
	gr->SetLineWidth(1);
	gr->Draw("L");
	CanvasSpectrum->Refresh();

	CanvasHeatMap->GetCanvas()->cd();
	CanvasHeatMap->GetCanvas()->SetGrid();
	CanvasHeatMap->Erase();
	gStyle->SetOptStat(0);
	heatMap->Draw("COLZ");
	CanvasHeatMap->Refresh();

	CanvasScope->Erase();
	CanvasScope->GetCanvas()->cd();
	gStyle->SetOptStat(0);
	oszi.lock();
	scope->SetTitle("Signal Shapes");
	scope->Draw("A");
	scope->GetYaxis()->SetRangeUser(-600,1200);
	oszi.unlock();
	CanvasScope->Refresh();

	return;
}

void NACdialog::postAnalysis()
{
	if(!StartButton->isChecked())
	{
		if(currentFile != "empty"){
			TFile *file = new TFile(currentFile.toUtf8().constData(), "READ");
			TH1F *spectrum = new TH1F("spectrum", "Proton Spectrum", 512, 0, 2048);
			TTree *tree;
			file->GetObject("tree", tree);

			int maximum = 0;
			int channelNo = 0;
			tree->SetBranchAddress("maximum", &maximum);
			tree->SetBranchAddress("channelNo", &channelNo);

			for(int i = 0; i < tree->GetEntries(); i++){
				tree->GetEntry(i);
				if(ComboBox->currentIndex() == 0)
					spectrum->Fill(maximum);
				else if(channelNo == ComboBox->currentIndex())
					spectrum->Fill(maximum);
			}
			CanvasSpectrum->GetCanvas()->cd();
			CanvasSpectrum->Erase();
			gStyle->SetOptStat(11);
			gStyle->SetOptFit(0111);
			int x[2], y[2];
			x[0]=0; x[1]=1000; y[0]=0; y[1]=0;
			TGraph *gr = new TGraph(2, x, y);
			gr->SetLineWidth(1);
			spectrum->Draw();
			gr->Draw("L");
			CanvasSpectrum->Refresh();

			CanvasScope->Refresh();
		}
		else Log->write(QString("No file yet to be analyzed."));
		//delete file;
		return;
	}
}

void NACdialog::adoptCurrentFile(QString file)
{
	currentFile = file;
	return;
}
