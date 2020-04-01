#include <QtCore/QCoreApplication>
#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>

#include <QtHttpServer/QtHttpServer>
#include "controller/Controller.h"
#include <gtest/gtest.h>

#include <qdebug.h>

using namespace toptal::controller;


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

    toptal::controller::Controller controller;
    controller.init();

	return a.exec();
}

