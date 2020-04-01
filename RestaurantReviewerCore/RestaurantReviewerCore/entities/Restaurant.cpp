#include "Restaurant.h"
#include "../../utils/Constants.h"

#include <QJsonArray>

using namespace toptal::utils;
using namespace toptal::entities;

Restaurant::Restaurant()
{
	_name.clear();
	_ownerEmail.clear();
	_imagePath.clear();
	_reviews.clear();
}

Restaurant::Restaurant(const Restaurant& second)
{
	_name = second.name();
	_ownerEmail = second.ownerEmail();
	_imagePath = second.imagePath();
	_reviews = second.reviews();
}

Restaurant& Restaurant::operator=(const Restaurant& second)
{
	_name = second._name;
	_ownerEmail = second._ownerEmail;
	_imagePath = second._imagePath;
	_reviews = second._reviews;

	return *this;
}

QJsonObject Restaurant::toJsonObject() const
{
	QJsonObject rstObj;

	rstObj[kName] = _name;
	rstObj[kOwnerEmail] = _ownerEmail;
	rstObj[kImagePath] = _imagePath;
	rstObj[kReviews] = jsonReviews();

	return rstObj;
}

void Restaurant::fromJsonObject(const QJsonObject& body)
{
	_name = body[kName].toString();
	_imagePath = body[kImagePath].toString();
	_ownerEmail = body[kOwnerEmail].toString();

	QJsonArray reviewArray = body[kReviews].toArray();
	for (const QJsonValue& value : reviewArray)
	{
		Review review;
		review.fromJsonObject(value.toObject());
		_reviews.push_back(review);
	}
}

void Restaurant::setReviews(const QString& jsonReviews)
{
	QJsonDocument doc = QJsonDocument::fromJson(jsonReviews.toUtf8());
	QJsonArray revArray = doc.array();

	for (const QJsonValue& value : revArray)
	{
		Review review;
		review.fromJsonObject(value.toObject());
		_reviews.push_back(review);
	}
}

void Restaurant::setReviews(const std::vector<Review>& reviews)
{
	_reviews = reviews;
}

QString Restaurant::jsonReviews() const
{
	QJsonArray data;
	QJsonDocument doc;

	for (const Review& review : _reviews)
	{
		QJsonObject jsonReview = review.toJsonObject();
		data.push_back(jsonReview);
	}

	doc.setArray(data);
	return doc.toJson();
}
