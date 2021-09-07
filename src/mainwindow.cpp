#include "mainwindow.h"
#include "serial.h"

#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	this->setGeometry(100,100,1000,500); // Set window size to be 1000x500

	qDebug() << "MainWindow";
	Serial serial;

	// Device select dropdown
	dropdown = new QComboBox(this);
	dropdown->setGeometry(10,50,200,30);

	// Populate list with available ports
	dropdown->addItems(serial.FindAllSerialPorts());
	qDebug() << "list has " << dropdown->count() << " things";

	// Start button
	start_button = new QPushButton("Add Item", this);
	QObject::connect(start_button, &QPushButton::clicked, this, &MainWindow::addAnItem);
	start_button->setGeometry(10, 10, 80, 30);

}
