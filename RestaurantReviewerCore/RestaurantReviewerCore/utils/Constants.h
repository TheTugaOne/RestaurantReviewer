#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

#include <QString>

namespace toptal
{
namespace utils
{
// System
extern const QString kDirSeparator;
extern const QString kSQLiteDbName;
extern const QString kDataFolderName;
extern const QString kLogsFolder;

// Rest Api
extern const int kPort;

extern const QString kApiLogin;
extern const QString kApiRegister;
extern const QString kGetUsers;
extern const QString kDeleteUser;
extern const QString kEditUser;

extern const QString kApiRestaurantAdd;
extern const QString kAddReviewUrl;
extern const QString kUpdateReviewUrl;
extern const QString kFetchAllRestaurantsUrl;
extern const QString kFetchOneRestaurantsUrl;
extern const QString kDeleteRestaurantUrl;
extern const QString kDeleteRestaurantsForUserUrl;
extern const QString kEditRestaurantUrl;
extern const QString kFetchRestaurantForUserUrl;
extern const QString kEditReviewUrl;
extern const QString kDeleteReviewUrl;
extern const QString kFetchAllReviewsUrl;

// Http request body params
extern const QString kName;
extern const QString kOriginalName;
extern const QString kUser;
extern const QString kEmail;
extern const QString kPassword;
extern const QString kIsOwner;
extern const QString kUserType;
extern const QString kImagePath;
extern const QString kOwnerEmail;
extern const QString kRestaurant;
extern const QString kReview;
extern const QString kReviews;
extern const QString kOldReview;
extern const QString kNewReview;
extern const QString kRating;
extern const QString kCreatorName;
extern const QString kComment;
extern const QString kDate;
extern const QString kReply;

// SQL
struct SqlColumn
{
	QString		name;
	QString		value;

	SqlColumn(const QString& otherName = "", const QString& otherValue = "")
	{
		name = otherName;
		value = otherValue;
	}
};

using SqlColumns = std::vector<SqlColumn>;

} } // toptal::constants

#endif // CONSTANTS_H