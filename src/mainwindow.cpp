#include "mainwindow.h"
//#include "serial.h"

#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	qDebug() << "MainWindow";

	// Device select dropdown
	dropdown = new QComboBox(this);
	dropdown->setGeometry(10,50,150,30);

	// Populate list with example text
	/*
	QStringList items;
	for (char x=1; x<=10; x++) {
		items << QString("item").append(QString::number(x));
		qDebug() << items.count();
	}
	qDebug() << "before: " << dropdown->count();
	dropdown->clear();
	dropdown->addItems(items);
	qDebug() << "after: " << dropdown->count();
	*/

	// Start button
	start_button = new QPushButton("Add Item", this);
	/*QObject::connect(start_button, &QPushButton::clicked, this, &MainWindow::addAnItem);
	start_button->setGeometry(10, 10, 80, 30);
	*/
}

/*
void MainWindow::addAnItem() {
	dropdown->addItem(QString("Item ").append(QString::number(dropdown->count()+1)));
}
*/
