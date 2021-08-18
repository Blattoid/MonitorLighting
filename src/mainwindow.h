#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QComboBox;
class QPushButton;

class MainWindow : public QWidget
{
	public:
		explicit MainWindow(QWidget *parent = 0);
	private:
		QComboBox *dropdown;
		QPushButton *start_button;
		QPushButton *quit_button;
		void addAnItem();
		int cockCount = 0;
};

#endif // WINDOW_H
