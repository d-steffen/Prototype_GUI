#ifndef READOUT_H_
#define READOUT_H_

#include <queue>
#include <list>
#include <cstdint>

#include <QString>
#include <QThread>
#include <QSemaphore>
#include <QMutex>


class readoutThread : public QThread
{
	Q_OBJECT

private:
	volatile bool stopped;
	bool reading;
	timespec stopsignaltime;
	std::queue<uint32_t, std::list<uint32_t> > *_FIFO;
	QSemaphore *_freeSpace;
	QSemaphore *_usedSpace;
	QMutex *_buffer;
	QMutex mutex;

public:
	readoutThread(std::queue<uint32_t, std::list<uint32_t> > *FIFO, QSemaphore *freeSpace, QSemaphore *usedSpace, QMutex *buffer)
	{
		mutex.lock();
		stopped = false;
		mutex.unlock();
		_FIFO = FIFO;
		_freeSpace = freeSpace;
		_usedSpace =usedSpace;
		_buffer = buffer;
	}
	void stop();
	void createTree(QString filename);
	void run();
	QString filename;

signals:
	void writeConsole(QString line);
	void updateStatusBars(int reads, int data, int words, int bufferSize);
	void done();
};

#endif
