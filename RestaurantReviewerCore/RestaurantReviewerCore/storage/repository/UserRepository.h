#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <memory>
#include "../sqlite/SQLite.h"
#include "../entities/users/User.h"


namespace toptal
{
namespace storage
{
namespace repository
{

class UserRepository
{
public:
					UserRepository(sqlite::SQLitePtr sqlDb);
					UserRepository(const UserRepository&) = delete;
	UserRepository	operator=(const UserRepository&) = delete;

	bool			login(const QString& email, const QString& password, entities::users::User& outUser);
	bool			registerUser(const QString& email, const QString& name, const QString& password, const QString& userType);
	bool			userExists(const QString& email);
	bool			getAll(entities::users::UserList& outUsrList);
	bool			getOne(const QString& email, entities::users::User& outUser);
	bool			deleteUser(const QString& email);
	bool			editUser(const QString& email, const entities::users::User& newUsr);

	static std::unique_ptr<UserRepository> makePtr(sqlite::SQLitePtr sqlDb);

private:
	entities::users::UserList	entriesToUserList(const std::vector<QStringList>& entries);

private:
	toptal::storage::sqlite::SQLitePtr _sqlite;

}; // class UserRepository

using UserRepositoryPtr = std::unique_ptr<UserRepository>;

} } } // toptal::storage::repository

#endif // USERREPOSITORY_H