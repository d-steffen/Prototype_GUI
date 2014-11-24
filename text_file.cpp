#include "text_file.h"

#include <fstream>
#include <cstring>
#include <string>

#include <QScrollBar>
#include <QString>

#include "NACdialog.h"

void LogFile::append(std::string n){
		log.open("log.txt", std::ios::out | std::ios::app);
		std::string line;
		std::string nline;
		nline = "\n";
		line = n+nline;
		log.write(line.c_str(), strlen(line.c_str()));
		log.close();
		return;
	}

void LogFile::append(QString n){
		log.open("log.txt", std::ios::out | std::ios::app);
		std::string line;
		std::string nline;
		nline = "\n";
		line = n.toUtf8().constData() + nline;
		log.write(line.c_str(), strlen(line.c_str()));
		log.close();
		return;
	}

void LogFile::clear(){
		log.open("log.txt", std::ios::out | std::ios::trunc);
		log.close();
		_UI->Console->clear();
		return;
	}

void LogFile::write(std::string n){
		QScrollBar *TerminalSlider = _UI->Console->verticalScrollBar(); // needed for scrolling behavior of "Console"
		int SliderPosition = TerminalSlider->value();
		bool comparator = (SliderPosition == TerminalSlider->maximum());

		_UI->Console->append(n.c_str());
		_UI->Console->repaint();
		if (comparator){
			TerminalSlider->setValue(TerminalSlider->maximum());
		}
		else{
			TerminalSlider->setValue(SliderPosition);
		}

		return;
	}

void LogFile::write(QString n){
		QScrollBar *TerminalSlider = _UI->Console->verticalScrollBar(); // needed for scrolling behavior of "Console"
		int SliderPosition = TerminalSlider->value();
		bool comparator = (SliderPosition == TerminalSlider->maximum());

		_UI->Console->append(n);
		_UI->Console->repaint();
		if (comparator){
			TerminalSlider->setValue(TerminalSlider->maximum());
		}
		else{
			TerminalSlider->setValue(SliderPosition);
		}

		return;
	}
