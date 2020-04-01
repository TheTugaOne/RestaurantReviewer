#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QJsonDocument>

namespace toptal
{
namespace entities
{
/*!
*	\class	ISerializable.
*	\brief	Interface that must be implemented by classes that offer serialization.
*/
class ISerializable
{
public:
	ISerializable() = default;
	ISerializable(const ISerializable&) = delete;
	ISerializable& operator=(const ISerializable&) = delete;

protected:
	virtual QJsonObject toJsonObject() const = 0;
	virtual void		fromJsonObject(const QJsonObject& body) = 0;
}; // class ISerializable

} } // toptal::entities

#endif // ISERIALIZABLE_H