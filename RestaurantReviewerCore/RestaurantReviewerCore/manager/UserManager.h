#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <memory>

#include "../storage/repository/UserRepository.h"
#include "../entities/users/User.h"

namespace toptal
{
namespace manager
{

class UserManager
{
public:
	static std::shared_ptr<UserManager> instance();


							UserManager(const UserManager&) = delete;
							
	UserManager				operator=(const UserManager&) = delete;

	void					init(storage::repository::UserRepositoryPtr& userRepository);

	bool					login(const QString& email, const QString& password, entities::users::User& outUser);
	bool					registerUser(const QString& name, const QString& email, const QString& password, const QString& userType);
	bool					userExists(const QString& email);
	bool					getAll(entities::users::UserList& outUsrList);
	
	bool					deleteUser(const QString& email);
	bool					editUser(const QString& email, const entities::users::User& newUsr);

private:
							UserManager(storage::repository::UserRepositoryPtr& userRepository);
	bool					getOne(const QString& email, entities::users::User& outUser);

private:
	static std::shared_ptr<UserManager>		_instance; //!< The only instance of UserManager.
	storage::repository::UserRepositoryPtr	_userRepository;

}; // class UserManager

using UserManagerPtr = std::shared_ptr<UserManager>;

} } // toptal::manager

#endif // USERMANAGER_H
