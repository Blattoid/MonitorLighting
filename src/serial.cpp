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

		// Does it exist?
		if (lstat(path, &info) < 0){
			qDebug() << "fucky wucky uwu";
			continue;
		}

		qDebug() << QString::fromStdString(entry.path()) << " " << QString::number(info.st_dev);
		output.append(QString::fromStdString(entry.path()));
	}

	output.sort(); // Be tidy
	return output;
}
