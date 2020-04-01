#ifndef LOGS_H
#define LOGS_H

#define LOGSIZE 1024 * 100
#define LOGFILES 5

#include <QObject>
#include <QString>
#include <QDebug>
#include <QDate>
#include <QTime>

namespace toptal
{
namespace utils
{

	bool initLogging();
	void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);


} } // toptal::utils

#endif // LOGS_H