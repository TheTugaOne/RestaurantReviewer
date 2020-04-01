#include "RestaurantManager.h"

#include <assert.h>

using namespace toptal::manager;
using namespace toptal::entities;
using namespace toptal::storage::repository;

RestaurantManagerPtr RestaurantManager::_instance = nullptr;

RestaurantManager::RestaurantManager(RestaurantRepositoryPtr& restaurantRepository):
	_restaurantRepository(std::move(restaurantRepository))
{
}

RestaurantManagerPtr RestaurantManager::instance()
{
	assert(_instance);

	return _instance;
}

void RestaurantManager::init(RestaurantRepositoryPtr& restaurantRepository)
{
	assert(restaurantRepository);

	if (_instance)
	{
		// Someone has already called init
		return;
	}

	_instance.reset(new RestaurantManager(restaurantRepository));
}

bool RestaurantManager::addRestaurant(const Restaurant& restaurant)
{
	return _restaurantRepository->addRestaurant(restaurant);
}

bool RestaurantManager::addReview(const Restaurant& restaurant, const Review& review)
{
	return _restaurantRepository->addReview(restaurant, review);
}

bool RestaurantManager::updateReview(const Restaurant& restaurant, const Review& review)
{
	return _restaurantRepository->updateReview(restaurant, review);
}

bool RestaurantManager::editReview(const Restaurant& restaurant, const Review& oldReview, const Review& newReview)
{
	return _restaurantRepository->editReview(restaurant, oldReview, newReview);
}

bool RestaurantManager::deleteRestaurant(const QString& restaurantName)
{
	return _restaurantRepository->deleteRestaurant(restaurantName);
}

bool RestaurantManager::deleteAllForUser(const QString& userEmail)
{
	return _restaurantRepository->deleteAllForUser(userEmail);;
}

bool RestaurantManager::editRestaurant(const QString& originalRestName, const QString& newRestName, const QString& imagePath)
{
	return _restaurantRepository->editRestaurant(originalRestName, newRestName, imagePath);
}

bool RestaurantManager::deleteReview(const Restaurant& restaurant, const Review& review)
{
	return _restaurantRepository->deleteReview(restaurant, review);
}

bool RestaurantManager::getAllReviews(const Restaurant& restaurant, std::vector<Review>& outReviews)
{
	return _restaurantRepository->getAllReviews(restaurant, outReviews);
}

bool RestaurantManager::restaurantExists(const QString& restaurantName)
{
	return _restaurantRepository->restaurantExists(restaurantName);;
}


Restaurant RestaurantManager::getOne(const QString& resturantName)
{
	Restaurant outRst;

	_restaurantRepository->getOne(resturantName, outRst);

	return outRst;
}

RestaurantList RestaurantManager::getAll()
{
	return _restaurantRepository->getAll();
}

RestaurantList RestaurantManager::getAllForUser(const QString& userEmail)
{
	return _restaurantRepository->getAllForUser(userEmail);
}

