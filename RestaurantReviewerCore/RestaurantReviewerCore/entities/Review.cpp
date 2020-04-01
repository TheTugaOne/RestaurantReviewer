#include "Review.h"
#include "../../utils/Constants.h"

using namespace toptal::entities;
using namespace toptal::utils;

Review::Review()
{
	_rating = 0;
	_creatorName = "";
	_comment = "";
	_date = "";
	_reply = "";
}

Review::Review(const Review& second)
{
	_rating = second._rating;
	_creatorName = second._creatorName;
	_comment = second._comment;
	_date = second._date;
	_reply = second._reply;
}

Review& Review::operator=(const Review& second)
{
	_rating = second._rating;
	_creatorName = second._creatorName;
	_comment = second._comment;
	_date = second._date;
	_reply = second._reply;

	return *this;
}

bool Review::operator==(const Review& second)
{
	return _rating == second._rating
		&& _creatorName == second._creatorName
		&& _comment == second._comment
		&& _date == second._date
		&& _reply == second._reply;
}

QJsonObject Review::toJsonObject() const
{
	QJsonObject review;

	review[kRating] = _rating;
	review[kCreatorName] = _creatorName;
	review[kComment] = _comment;
	review[kDate] = _date;
	review[kReply] = _reply;

	return review;
}

void Review::fromJsonObject(const QJsonObject& body)
{
	_rating = body[kRating].toInt();
	_creatorName = body[kCreatorName].toString();
	_comment = body[kComment].toString();
	_date = body[kDate].toString();
	_reply = body[kReply].toString();
}

bool Review::compareForReply(const Review& second)
{
	return _rating == second._rating
		&& _creatorName == second._creatorName
		&& _comment == second._comment
		&& _date == second._date;
}
