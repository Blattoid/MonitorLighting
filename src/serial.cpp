#include "serial.h"
#include <QDebug>
#include <strings.h>
#include <filesystem>
#include <sys/stat.h>

Serial::Serial() {
	// Constructor stuff can go here if needed
}

QStringList Serial::FindAllSerialPorts() {
	QStringList output;

	struct stat info;
	for (const auto& entry : std::filesystem::directory_iterator("/sys/class/tty"))	{
		// Append "/device" to the path
		char path[35];
		strcpy(path, entry.path().c_str());
		strcat(path, "/device");

		// Skip if /device doesn't exist
		if (lstat(path, &info) < 0) continue;

		// Append path to list
		qDebug() << QString::fromStdString(entry.path()) << " " << QString::number(info.st_dev);
		output.append(QString::fromStdString(entry.path()));
	}

	output.sort(); // Be tidy
	return output;
}
