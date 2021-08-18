#include <QApplication>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char **argv)
{
	QApplication app (argc, argv);

	// Give the window an icon
	QIcon icon(":/files/assets/icon.png");
	app.setWindowIcon(icon);

	// Show the main window
	MainWindow window;
	window.show();

	// Start the application
	return app.exec();
}
