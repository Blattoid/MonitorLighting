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

	// Device select dropdown
	dropdown = new QComboBox(this);
	dropdown->setGeometry(10,10,200,30);

	// Populate dropdown with available ports
	MainWindow::refreshPortList();

	// Start button
	refreshBtn = new QPushButton("Refresh", this);
	QObject::connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshPortList);
	refreshBtn->setGeometry(220, 10, 80, 30);

}

void MainWindow::refreshPortList() {
	// Populate dropdown with available ports
	dropdown->clear();
	dropdown->addItems(serial.FindAllSerialPorts());
	qDebug() << "list has " << dropdown->count() << " things";
}
