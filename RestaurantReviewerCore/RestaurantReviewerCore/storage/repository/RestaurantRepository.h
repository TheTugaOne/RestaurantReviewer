#ifndef RESTAURANTREPOSITORY_H
#define RESTAURANTREPOSITORY_H

#include <memory>
#include <QtSql/qsqldatabase.h>
#include "../sqlite/SQLite.h"
#include "../entities/Restaurant.h"

namespace toptal
{
namespace storage
{
namespace repository
{

class RestaurantRepository
{
public:
								RestaurantRepository(sqlite::SQLitePtr sqlDb);


	bool						addRestaurant(const entities::Restaurant& restaurant);
	bool						addReview(const entities::Restaurant& restaurant, const entities::Review& review);
	bool						updateReview(const entities::Restaurant& restaurant, const entities::Review& review);
	bool						editReview(const entities::Restaurant& restaurant, const entities::Review& oldReview, const entities::Review& newReview);
	bool						deleteRestaurant(const QString& restaurantName);
	bool						deleteAllForUser(const QString& userEmail);
	bool						editRestaurant(const QString& originalRestName, const QString& newRestName, const QString& imagePath);
	bool						deleteReview(const entities::Restaurant& restaurant, const entities::Review& review);
	bool						getAllReviews(const entities::Restaurant& restaurant, std::vector<entities::Review>& outReviews);
	bool						restaurantExists(const QString& restaurantName);

	bool						getOne(const QString& restaurantName, entities::Restaurant& outRest);
	entities::RestaurantList	getAll();
	entities::RestaurantList	getAllForUser(const QString& userEmail);

	static std::unique_ptr<RestaurantRepository> makePtr(sqlite::SQLitePtr sqlDb);
private:

	utils::SqlColumns			restaurantToColumns(const entities::Restaurant& restaurant);
	entities::RestaurantList	entriesToRestaurantList(const std::vector<QStringList>& entries);

private:
	toptal::storage::sqlite::SQLitePtr _sqlite;

}; // class RestaurantRepository

using RestaurantRepositoryPtr = std::unique_ptr<RestaurantRepository>;

} } } // toptal::storage::repository

#endif // RESTAURANTREPOSITORY_H