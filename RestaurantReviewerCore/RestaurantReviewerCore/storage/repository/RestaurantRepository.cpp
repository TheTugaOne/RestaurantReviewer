#include "RestaurantRepository.h"

using namespace toptal::utils;
using namespace toptal::entities;
using namespace toptal::storage::sqlite;
using namespace toptal::storage::repository;

static const QString kTableName = "Restaurants";

// Do not use Constants.h for this! it is not initialized before static kColoumns
const SqlColumns kColumns =
{
	{"name", ""},
	{"ownerEmail", ""},
	{"reviews", ""},
	{"imagePath", ""}
};

RestaurantRepository::RestaurantRepository(SQLitePtr sqlDb) :
	_sqlite(sqlDb)
{
	assert(_sqlite);

	if (!_sqlite->tableExists(kTableName))
	{
		_sqlite->createTable(kTableName, kColumns);
	}
}


bool RestaurantRepository::addRestaurant(const Restaurant& restaurant)
{
	SqlColumns columns = restaurantToColumns(restaurant);

	if (!_sqlite->insert(kTableName, columns))
		return false;

	return true;
}

bool RestaurantRepository::addReview(const Restaurant& restaurant, const Review& review)
{
	Restaurant tmpRst = restaurant;
	tmpRst.addReview(review);

	SqlColumns columnsToBeUpdated = { { kReviews, tmpRst.jsonReviews() } };
	SqlColumns whereCriteria = { { kName, tmpRst.name() } };

	if (!_sqlite->update(kTableName, columnsToBeUpdated, whereCriteria))
		return false;

	return true;
}

bool RestaurantRepository::updateReview(const Restaurant& restaurant, const Review& review)
{
	Restaurant tmpRst = restaurant;
	std::vector<Review>& reviews = tmpRst.reviews();

	// Update the review that needs to be replaced
	for (Review& rev : reviews)
	{
		if (rev.compareForReply(review))
		{
			rev = review;
			break;
		}
	}

	tmpRst.setReviews(reviews);

	SqlColumns columnsToBeUpdated = { { kReviews, tmpRst.jsonReviews() } };
	SqlColumns whereCriteria = { { kName, tmpRst.name() } };

	if (!_sqlite->update(kTableName, columnsToBeUpdated, whereCriteria))
		return false;

	return true;
}

bool RestaurantRepository::editReview(const Restaurant& restaurant, const Review& oldReview, const Review& newReview)
{
	Restaurant tmpRst = restaurant;
	std::vector<Review> reviews = tmpRst.reviews();

	// Update the review that needs to be replaced
	for (Review& rev : reviews)
	{
		if (rev == oldReview)
		{
			rev = newReview;
			break;
		}
	}

	tmpRst.setReviews(reviews);

	SqlColumns columnsToBeUpdated = { { kReviews, tmpRst.jsonReviews() } };
	SqlColumns whereCriteria = { { kName, tmpRst.name() } };

	if (!_sqlite->update(kTableName, columnsToBeUpdated, whereCriteria))
		return false;

	return true;
}

bool RestaurantRepository::deleteRestaurant(const QString& restaurantName)
{
	SqlColumns whereCriteria = { { kName, restaurantName } };

	if (!_sqlite->deleteByColumns(kTableName, whereCriteria))
		return false;

	return true;
}

bool RestaurantRepository::deleteAllForUser(const QString& userEmail)
{
	SqlColumns whereCriteria = { { kOwnerEmail, userEmail } };

	if (!_sqlite->deleteByColumns(kTableName, whereCriteria))
		return false;

	return false;
}

bool RestaurantRepository::editRestaurant(const QString& originalRestName, const QString& newRestName, const QString& imagePath)
{
	SqlColumns columnsToBeUpdated = { { kName, newRestName }, { kImagePath, imagePath } };
	SqlColumns whereCriteria = { { kName, originalRestName } };

	if (!_sqlite->update(kTableName, columnsToBeUpdated, whereCriteria))
		return false;

	return true;
}

bool RestaurantRepository::deleteReview(const Restaurant& restaurant, const Review& review)
{
	Restaurant tmpRst = restaurant;
	std::vector<Review>& reviews = tmpRst.reviews();

	// Update the review that needs to be replaced
	for (int i = 0; i < reviews.size(); ++i)
	{
		if (reviews[i] == review)
		{
			reviews.erase(reviews.begin() + i);
			break;
		}
	}

	tmpRst.setReviews(reviews);

	SqlColumns columnsToBeUpdated = { { kReviews, tmpRst.jsonReviews() } };
	SqlColumns whereCriteria = { { kName, tmpRst.name() } };

	if (!_sqlite->update(kTableName, columnsToBeUpdated, whereCriteria))
		return false;

	return true;
}

bool RestaurantRepository::getAllReviews(const Restaurant& restaurant, std::vector<Review>& outReviews)
{
	SqlColumn column(kName, restaurant.name());

	std::vector<QStringList> records;

	if (!_sqlite->getByColumn(kTableName, column, records))
		return false;

	if (records.size() == 0)
		return false;

	Restaurant tmpRst; // use the restaurant object to parse the json reviews
	tmpRst.setReviews(records[0][2]);

	outReviews = tmpRst.reviews();

	return true;
}

bool RestaurantRepository::restaurantExists(const QString& restaurantName)
{
	SqlColumn emailColumn = { kName, restaurantName };
	std::vector<QStringList> records;

	if (!_sqlite->getByColumn(kTableName, emailColumn, records))
		return false;

	if (records.size() == 0)
		return false; // user doesn't exist

	return true;
}

bool RestaurantRepository::getOne(const QString& restaurantName, Restaurant& outRest)
{
	SqlColumn column(kName, restaurantName);

	std::vector<QStringList> records;

	if (!_sqlite->getByColumn(kTableName, column, records))
		return false;

	if (records.size() == 0)
		return false;

	// should be just 1 entry, restaurant names are unique
	RestaurantList rstList = entriesToRestaurantList(records);

	outRest = rstList[0];

	return true;
}

RestaurantList RestaurantRepository::getAll()
{
	std::vector<QStringList> records;

	_sqlite->getAll(kTableName, records);

	return entriesToRestaurantList(records);
}

RestaurantList RestaurantRepository::getAllForUser(const QString& userEmail)
{
	SqlColumns columns = { { kOwnerEmail, userEmail } };
	std::vector<QStringList> records;

	_sqlite->getByColumns(kTableName, columns, records);

	return entriesToRestaurantList(records);
}

SqlColumns RestaurantRepository::restaurantToColumns(const Restaurant& restaurant)
{
	SqlColumns columns;
	columns =
	{
		{ kName, restaurant.name() },
		{ kOwnerEmail, restaurant.ownerEmail() },
		{ kReviews, restaurant.jsonReviews() },
		{ kImagePath, restaurant.imagePath() },
	};

	return columns;
}

RestaurantList RestaurantRepository::entriesToRestaurantList(const std::vector<QStringList>& entries)
{
	RestaurantList rstList;
	for (const QStringList& entry : entries)
	{
		Restaurant restaurant;
		restaurant.setName(entry[0]);
		restaurant.setOwnerEmail(entry[1]);
		restaurant.setReviews(entry[2]); // use json string to create reviews
		restaurant.setImagePath(entry[3]);

		rstList.push_back(restaurant);
	}

	return rstList;
}

std::unique_ptr<RestaurantRepository> RestaurantRepository::makePtr(SQLitePtr sqlDb)
{
	return std::make_unique<RestaurantRepository>(sqlDb);
}