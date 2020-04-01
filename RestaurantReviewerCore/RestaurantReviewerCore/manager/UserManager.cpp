#include "UserManager.h"

#include <assert.h>
#include "../entities/users/User.h"

using namespace toptal::manager;
using namespace toptal::entities::users;
using namespace toptal::storage::repository;

UserManagerPtr UserManager::_instance = nullptr;

UserManager::UserManager(UserRepositoryPtr& userRepository) :
	_userRepository(std::move(userRepository))
{
}

UserManagerPtr UserManager::instance()
{
	assert(_instance);

	return _instance;
}

void UserManager::init(UserRepositoryPtr& userRepository)
{
	assert(userRepository);

	if (_instance)
	{
		// Someone has already called init
		return;
	}

	_instance.reset(new UserManager(userRepository));
}

bool UserManager::login(const QString& email, const QString& password, User& outUser)
{
	return _userRepository->login(email, password, outUser);;
}

bool UserManager::registerUser(const QString& email, const QString& name, const QString& password, const QString& userType)
{
	return _userRepository->registerUser(email, name, password, userType);
}

bool UserManager::userExists(const QString& email)
{
	return _userRepository->userExists(email);
}

bool UserManager::getAll(UserList& outUsrList)
{
	return _userRepository->getAll(outUsrList);
}

bool UserManager::getOne(const QString& email, User& outUser)
{
	return _userRepository->getOne(email, outUser);
}

bool UserManager::deleteUser(const QString& email)
{
	return _userRepository->deleteUser(email);
}

bool UserManager::editUser(const QString& email, const User& newUsr)
{
	User tmpUser;
	if (!getOne(email, tmpUser))
		return false;

	QString encryptedPassword = tmpUser.password();
	tmpUser = newUsr;
	tmpUser.setPassword(encryptedPassword);

	return _userRepository->editUser(email, tmpUser);
}

