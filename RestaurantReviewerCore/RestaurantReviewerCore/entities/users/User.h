#ifndef USER_H
#define USER_H

#include <vector>

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "../ISerializable.h"
namespace toptal
{
namespace entities
{
namespace users
{

enum class UserType
{
	eReviewer,
	eOwner,
	eAdmin
};

/*!
*	\class	ISerializable.
*	\brief	Interface that must be implemented by classes that offer serialization.
*/
class User: public ISerializable
{
public:
						User();
						User(const User& other);
	User&				operator=(const User& other);

	QJsonObject			toJsonObject() const override;
	void				fromJsonObject(const QJsonObject& body) override;

	bool				isValid();

	inline QString		name() const { return _name; };
	inline void			setName(const QString& name) { _name = name; };

	inline QString		email() const { return _email; };
	inline void			setEmail(const QString& email) { _email = email; };

	inline QString		password() const { return _password; };
	inline void			setPassword(const QString& password) { _password = password; };

	inline UserType		userType() const { return _userType; };
	inline QString		stringUserType() const{ return usertypeToString(_userType); };
	inline void			setUserType(const QString& userType) { _userType = stringToUsertype(userType); };


private:
	QString usertypeToString(const UserType& type) const;
	UserType stringToUsertype(const QString& string);

private:
	QString _name;
	QString _email;
	QString _password;
	UserType _userType;

}; // class User

using UserList = std::vector<User>;

} } } // toptal::entities::users

#endif // USER_H