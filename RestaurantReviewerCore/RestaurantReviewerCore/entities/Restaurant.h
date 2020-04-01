#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <QJsonDocument>
#include <QJsonObject>

#include "ISerializable.h"
#include "Review.h"

namespace toptal
{
namespace entities
{

class Restaurant: public ISerializable
{
public:
								Restaurant();
								Restaurant(const Restaurant& second);
	Restaurant&					operator=(const Restaurant& second);

	inline QString				name() const { return _name; };
	inline void					setName(const QString& name) { _name = name; };

	inline QString				ownerEmail() const { return _ownerEmail; };
	inline void					setOwnerEmail(const QString& email) { _ownerEmail = email; };

	inline QString				imagePath() const { return _imagePath; };
	inline void					setImagePath(const QString& imagePath) { _imagePath = imagePath; };
	
	inline std::vector<Review> reviews() const { return _reviews; };
	inline void				   addReview(const Review& review) { _reviews.push_back(review); };
	void					   setReviews(const QString& jsonReviews);
	void					   setReviews(const std::vector<Review>& reviews);

	QString						jsonReviews() const;

	QJsonObject					toJsonObject() const override;
	void						fromJsonObject(const QJsonObject& body) override;

private:
	QString _name;
	QString _ownerEmail;
	std::vector<Review> _reviews;
	QString _imagePath;

}; // class Restaurant

using RestaurantList = std::vector<Restaurant>;

} } // toptal::entities

#endif // RESTAURANT_H
