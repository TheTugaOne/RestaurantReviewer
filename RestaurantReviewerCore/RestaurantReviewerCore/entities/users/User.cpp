#include "User.h"
#include "../../utils/Constants.h"


using namespace toptal::utils;
using namespace toptal::entities::users;

User::User()
{
	_name.clear();
	_email.clear();
	_password.clear();
	_userType = UserType::eReviewer;
}

User::User(const User& other)
{
	_name = other._name;
	_email = other._email;
	_password = other._password;
	_userType = other._userType;
}

User& User::operator=(const User& other)
{
	_name = other._name;
	_email = other._email;
	_password = other._password;
	_userType = other._userType;

	return *this;
}

QJsonObject User::toJsonObject() const
{
	QJsonObject userObj;
	userObj[kName] = _name;
	userObj[kEmail] = _email;
	userObj[kPassword] = _password;
	userObj[kUserType] = usertypeToString(_userType);

	return userObj;
}

void User::fromJsonObject(const QJsonObject& body)
{
	_name = body[kName].toString();
	_email = body[kEmail].toString();
	_password = body[kPassword].toString();
	_userType = stringToUsertype(body[kUserType].toString());
}

bool User::isValid()
{
	return !_name.isEmpty() && !_email.isEmpty() && !_password.isEmpty();
}

QString User::usertypeToString(const UserType& type) const
{
	switch (type)
	{
	case UserType::eReviewer:
		return "Reviewer";
	case UserType::eOwner:
		return "Owner";
	case UserType::eAdmin:
		return "Admin";
	default:
		return "";
	}
}

UserType User::stringToUsertype(const QString& string)
{
	if (string == "Reviewer")
		return UserType::eReviewer;
	if (string == "Owner")
		return UserType::eOwner;
	if (string == "Admin")
		return UserType::eAdmin;
}
