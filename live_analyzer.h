#ifndef LIVE_ANALYZER_H_
#define LIVE_ANALYZER_H_

#include <cstdint>
#include <queue>
#include <list>

#include <QObject>
#include <QThread>
#include <QString>
#include <QSemaphore>
#include <QMutex>

#include "TH1.h"
#include "TH2.h"
#include "TMultiGraph.h"

#define shapesPerSec 20

class liveAnalyzer : public QThread
{
	Q_OBJECT

public:
	liveAnalyzer(std::queue<uint32_t, std::list<uint32_t> > *FIFO, QSemaphore *freeSpace, QSemaphore *usedSpace, TH1F *_spec, TH2I *_heatMap, TMultiGraph *_scope, QMutex *oszi, QMutex *buffer);
	TH1F *spec;
	TH2I *heatMap;
	TMultiGraph *scope;

public slots:
	void run();
	void stop();
	void adoptChannelNumber(QString item);
	bool valueOfBool(bool reading);

signals:
	void writeConsole(QString line);
	void finished();
	void updateHistos(TH1F *spec, TH2I *heatMap, TMultiGraph *scope);
	void adoptCurrentFile(QString file);

private:
	std::queue<uint32_t, std::list<uint32_t> > *_FIFO;
	QSemaphore *_freeSpace;
	QSemaphore *_usedSpace;
	QMutex mutex;
	QMutex channelNumber;
	QMutex *_oszi;
	QMutex *_buffer;
	volatile bool reading;
	volatile int channelNo;

};

#endif
