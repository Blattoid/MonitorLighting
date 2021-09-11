#ifndef WINDOW_H
#define WINDOW_H

#include "serial.h"
#include <QWidget>

class QComboBox;
class QPushButton;

class MainWindow : public QWidget
{
	public:
		explicit MainWindow(QWidget *parent = 0);
	private:
		Serial serial;

		QComboBox *dropdown;
		QPushButton *refreshBtn;

		void refreshPortList();
};

#endif // WINDOW_H
