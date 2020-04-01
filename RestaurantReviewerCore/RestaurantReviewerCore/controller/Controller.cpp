#include "Controller.h"

#include <QtSql/qsqldatabase.h>

#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/Logs.h"

#include "../manager/UserManager.h"
#include "../manager/RestaurantManager.h"

#include "../communication/consumer/UserConsumer.h"
#include "../communication/consumer/RestaurantConsumer.h"

#include "../storage/repository/UserRepository.h"
#include "../storage/repository/RestaurantRepository.h"

#include "../storage/sqlite/SQLite.h"


using namespace toptal::utils;
using namespace toptal::controller;
using namespace toptal::manager;
using namespace toptal::storage::sqlite;
using namespace toptal::storage::repository;
using namespace toptal::communication::consumer;

void Controller::init()
{
	// Set up qt logging
	toptal::utils::initLogging();

	// Create public folder if it doesn't exist
	Utils::instance().initPublicFolder();

	// create and init db
	const QString databaseName = Utils::instance().dataDirectory() + kDirSeparator + kDataFolderName 
									+ kDirSeparator + kSQLiteDbName;
	SQLitePtr sqliteDb = SQLite::makePtr(databaseName);

	// Create repositories
	UserRepositoryPtr userRepository = UserRepository::makePtr(sqliteDb);
	RestaurantRepositoryPtr restaurantRepository = RestaurantRepository::makePtr(sqliteDb);

	// Init managers
	UserManager::instance()->init(userRepository);
	RestaurantManager::instance()->init(restaurantRepository);

	// Init http communication
	_httpServer = std::make_shared<QHttpServer>();
	_consumerList.emplace_back(UserConsumer::makePtr(_httpServer));
	_consumerList.emplace_back(RestaurantConsumer::makePtr(_httpServer));

	_httpServer->listen(QHostAddress::Any, kPort);
}
