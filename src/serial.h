#ifndef SERIAL_H
#define SERIAL_H

#include <QStringList>

class Serial
{
	public:
		Serial();
		QStringList FindAllSerialPorts();
};

#endif // SERIAL_H
