#include "Logs.h"
#include "Utils.h"
#include "Constants.h"
#include <QDir>

using namespace toptal::utils;

static QString logFileName;
void deleteOldLogs(const QString& logsFolder);
void initLogFileName(const QString& logsFolder);

bool toptal::utils::initLogging()
{
	const QString logsFolder = Utils::instance().dataDirectory() + kDirSeparator + kDataFolderName + kDirSeparator + kLogsFolder;

	QDir dir(logsFolder);

	if (!dir.exists())
	{
		if (!QDir().mkdir(logsFolder))
			return false;
	}

	deleteOldLogs(logsFolder);
	initLogFileName(logsFolder);

	QFile outFile(logFileName);
	if (outFile.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		qInstallMessageHandler(messageHandler);
		return true;
	}
	else
	{
		return false;
	}


	return true;
}

void toptal::utils::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QFile outFile(logFileName);
	int size = outFile.size();

	const QString logsFolder = Utils::instance().dataDirectory() + kDirSeparator + kDataFolderName + kDirSeparator + kLogsFolder;
	if (size > LOGSIZE)
	{
		deleteOldLogs(logsFolder);
		initLogFileName(logsFolder);
	}

	QFile outF(logFileName);
	outF.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream ts(&outF);

	QString logMsg = logFileName = QString("TIME - %1-%2 :" + msg)
		.arg(QDate::currentDate().toString("yyyy_MM_DD"))
		.arg(QTime::currentTime().toString("hh_mm_ss"));

	ts << logMsg << endl;
}

void deleteOldLogs(const QString& logsFolder)
{
	QDir dir;
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	dir.setSorting(QDir::Time | QDir::Reversed);
	dir.setPath(logsFolder);

	QFileInfoList lst = dir.entryInfoList();
	if (lst.size() <= LOGFILES)
	{
		return; // no need to delete files
	}
	else
	{
		for (int i = 0; i < (lst.size() - LOGFILES); ++i)
		{
			QString path = lst.at(i).absoluteFilePath();
			QFile file(path);
			file.remove();
		}
	}
}

void initLogFileName(const QString& logsFolder)
{
	logFileName = QString(logsFolder + kDirSeparator + "log_%1_%2.txt")
		.arg(QDate::currentDate().toString("yyyy_MM_DD"))
		.arg(QTime::currentTime().toString("hh_mm_ss"));
}

