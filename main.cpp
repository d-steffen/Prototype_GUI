#include <QtGui/QApplication>

#include "NACdialog.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	NACdialog *Window = new NACdialog;
	Window->show();
	
	return app.exec();
}
