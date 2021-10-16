#include <QApplication>
#include "WMainWindow.h"


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	WMainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
