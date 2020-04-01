#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <memory>

#include "../storage/repository/RestaurantRepository.h"
#include "../entities/Restaurant.h"

namespace toptal
{
namespace manager
{

class RestaurantManager
{
public:
	static std::shared_ptr<RestaurantManager> instance();

								RestaurantManager(const RestaurantManager&) = delete;
	RestaurantManager			operator=(const RestaurantManager&) = delete;

	void						init(storage::repository::RestaurantRepositoryPtr& restaurantRepository);

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

	entities::Restaurant		getOne(const QString& resturantName);
	entities::RestaurantList	getAll();
	entities::RestaurantList	getAllForUser(const QString& userEmail);
private:
							RestaurantManager(storage::repository::RestaurantRepositoryPtr& restaurantRepository);

private:
	static std::shared_ptr<RestaurantManager>	 _instance;			//!< The only instance of RestaurantManager.
	storage::repository::RestaurantRepositoryPtr _restaurantRepository;

}; // class RestaurantManager

using RestaurantManagerPtr = std::shared_ptr<RestaurantManager>;

} } // topotal::manager

#endif // RESTAURANTMANAGER_H