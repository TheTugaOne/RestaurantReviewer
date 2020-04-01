// This file contains API constants that must match the ones defined in Core.

export const kServerAddress = 'http://192.168.1.5:8080';

export const kParamUser = 'user';
export const kParamEmail = 'email';
export const kParamName = 'name';
export const kParamOriginalName = 'original-name';
export const kParamPassword = 'password';
export const kParamImagePath = 'imagePath';
export const kParamIsOwner = "is-owner";
export const kParamOldReview = "old-review";
export const kParamNewReview = "new-review";

export const kRestaurant = 'restaurant';
export const kReview = 'review';

export const kLoginUrl = kServerAddress + '/user/login';
export const kRegisterUrl = kServerAddress + '/user/register';
export const kGetUsers = kServerAddress + '/user/all';
export const kDeleteUserUrl = kServerAddress + '/user/delete';
export const kEditUserUrl = kServerAddress + '/user/edit';


export const kAddRestaurantUrl = kServerAddress + '/restaurant/add';
export const kAddReviewUrl = kServerAddress + '/restaurant/add-review';
export const kUpdateReviewUrl = kServerAddress + '/restaurant/update-review';
export const kFetchAllRestaurantsUrl = kServerAddress + '/restaurant/all';
export const kFetchRestaurantUrl = kServerAddress + '/restaurant/one';
export const kDeleteRestaurantUrl = kServerAddress + '/restaurant/delete';
export const kDeleteRestaurantsForUserUrl = kServerAddress + '/restaurant/delete/user';
export const kEditRestaurantUrl = kServerAddress + '/restaurant/edit';
export const KFetchRestaurantForUserUrl = kServerAddress + '/restaurant/fetch-for-user';
export const kEditReviewUrl = kServerAddress + '/restaurant/review/edit';
export const kDeleteReviewUrl = kServerAddress + '/restaurant/review/delete';
export const kFetchAllReviewsUrl = kServerAddress + '/restaurant/review/all';

