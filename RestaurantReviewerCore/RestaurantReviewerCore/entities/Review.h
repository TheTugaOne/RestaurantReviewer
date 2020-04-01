#ifndef REVIEW_H
#define REVIEW_H

#include "ISerializable.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace toptal
{
namespace entities
{
class Review: public ISerializable
{
public:
				Review();
				Review(const Review& second);
	Review&		operator=(const Review& second);
	bool		operator==(const Review& second);

	QJsonObject toJsonObject() const override;
	void		fromJsonObject(const QJsonObject& body) override;

	bool		compareForReply(const Review& second);

private:
	int _rating;
	QString _creatorName;
	QString _comment;
	QString _date;
	QString _reply;

}; // class Review

} } // toptal::entities

#endif // REVIEW_H