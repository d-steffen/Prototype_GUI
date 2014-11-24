#ifndef NACDIALOG_H
#define NACDIALOG_H

#include <QMainWindow>
#include <QSemaphore>
#include <QString>
#include <QMutex>
#include "ui_NACdialog.h"
#include "Readout.h"
#include "live_analyzer.h"
#include "text_file.h"
#include "TH1.h"
#include "TH2.h"
#include "TMultiGraph.h"

#define shapesPerSec 20

class NACdialog : public QMainWindow, public Ui::UI_NACdialog
{
	Q_OBJECT

	public:
		NACdialog(QWidget *parent = 0);

	private slots:
		void on_StartButton_toggled();
		void on_ResetButton_toggled();
		void on_ApplyButton_clicked();
		void writeConsole(QString line);
		void roThread_updateStatusBars(int reads, int data, int words, int bufferSize);
		void rootThread_finished();
		void rootThread_updateHistos(TH1F *spec, TH2I* heatMap, TMultiGraph* scope);
		void postAnalysis();
		void adoptCurrentFile(QString file);

	private:
		int nmb_of_smpls_per_event;
		void ApplySettings(int nmb_of_smpls, int reg_length, int factor);
		readoutThread* roThread;
		liveAnalyzer *rootThread;
		LogFile* Log;
		// create FIFO Buffer and Semaphores for readoutThread and rootThread:
		QSemaphore *freeSpace;
		QSemaphore *usedSpace;
		QMutex oszi;
		QMutex buffer;
		std::queue<uint32_t, std::list<uint32_t> > FIFO;
		QString currentFile;
		TH1F *spec;
		TH2I *heatMap;
		TMultiGraph *scope;
};

#endif
