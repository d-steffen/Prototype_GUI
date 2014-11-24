#ifndef TEXT_FILE_H_
#define TEXT_FILE_H_

#include <fstream>
#include <cstring>
#include <string>
#include <QString>

class NACdialog;

class LogFile
{
private:
	std::ofstream log;
	NACdialog* _UI;

public:

	LogFile(NACdialog* UI)
	{
		_UI = UI;
	}

	//int moveTo();

	void append(std::string n);
	void append(QString n);

	void clear();

	void write(std::string n);
	void write(QString n);
};
#endif
