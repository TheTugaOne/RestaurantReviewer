#include "Constants.h"


namespace toptal
{
namespace utils
{
// System
const QString kDirSeparator = "\\";
const QString kSQLiteDbName = "TopTal.sqlite";
const QString kDataFolderName = "TopTal";
const QString kLogsFolder = "Logs";

// Rest Api
const int kPort = 8080;

const QString kApiLogin = "/user/login";
const QString kApiRegister = "/user/register";
const QString kGetUsers = "/user/all";
const QString kDeleteUser = "/user/delete";
const QString kEditUser = "/user/edit";

const QString kApiRestaurantAdd = "/restaurant/add";
const QString kAddReviewUrl = "/restaurant/add-review";
const QString kUpdateReviewUrl = "/restaurant/update-review";
const QString kFetchAllRestaurantsUrl = "/restaurant/all";
const QString kFetchOneRestaurantsUrl = "/restaurant/one";
const QString kDeleteRestaurantUrl = "/restaurant/delete";
const QString kDeleteRestaurantsForUserUrl = "/restaurant/delete/user";
const QString kEditRestaurantUrl = "/restaurant/edit";
const QString kFetchRestaurantForUserUrl = "/restaurant/fetch-for-user";
const QString kEditReviewUrl = "/restaurant/review/edit";
const QString kDeleteReviewUrl = "/restaurant/review/delete";
const QString kFetchAllReviewsUrl = "/restaurant/review/all";

// Http request body params
const QString kName = "name";
const QString kOriginalName = "original-name";
const QString kUser = "user";
const QString kEmail = "email";
const QString kPassword = "password";
const QString kIsOwner = "is-owner";
const QString kUserType = "usertype";
const QString kImagePath = "imagePath";
const QString kOwnerEmail = "ownerEmail";
const QString kRestaurant = "restaurant";
const QString kReview = "review";
const QString kReviews = "reviews";
const QString kOldReview = "old-review";
const QString kNewReview = "new-review";
const QString kRating = "rating";
const QString kCreatorName = "creatorName";
const QString kComment = "comment";
const QString kDate = "date";
const QString kReply = "reply";


} } // toptal::utils