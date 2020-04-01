import { Injectable, EventEmitter } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import * as Constants from '../constants.export';

import { Restaurant } from '../entities/restaurant/restaurant.model'
import { Review } from '../entities/review/review.model';
import { catchError } from 'rxjs/operators';
import { throwError } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class RestaurantService {

  public restaurantList: Restaurant[] = [];

  addRestaurantEvent = new EventEmitter<any>();

  constructor(private http: HttpClient) { }


  public fetchAll() {
    this.http.get(`${Constants.kFetchAllRestaurantsUrl}`).subscribe(response => {
      this.restaurantList = this.restaurantsFromJson(response);
    });
  }

  public fetchAllForUser(userEmail: string) {
    const body = {};
    body[Constants.kParamEmail] = userEmail;

    return this.http.post(`${Constants.KFetchRestaurantForUserUrl}`, JSON.stringify(body)).subscribe(response => {
      this.restaurantList = this.restaurantsFromJson(response);
    });
  }

  public fetchRestaurant(restaurantName: string) {
    const body = {};
    body[Constants.kParamName] = restaurantName;

    return this.http.post(`${Constants.kFetchRestaurantUrl}`, JSON.stringify(body));
  }

  public addRestaurant(newRestaurant: Restaurant) {
    return this.http
      .post(`${Constants.kAddRestaurantUrl}`, JSON.stringify(newRestaurant))
      .pipe(catchError(errorResponse => {
        const genericMessage = 'An unknown error has occured !';
        if (!errorResponse.error || !errorResponse.error.errorMessage) {
          return throwError(genericMessage);
        }
        return throwError(errorResponse.error.errorMessage);
      }));
  }

  public addReview(restaurant: Restaurant, review: Review) {
    const body = {};
    body[Constants.kRestaurant] = restaurant.toJson();
    body[Constants.kReview] = review.toJson();

    return this.http.post(`${Constants.kAddReviewUrl}`, JSON.stringify(body));
  }

  public updateReview(restaurant: Restaurant, review: Review) {
    const body = {};
    body[Constants.kRestaurant] = restaurant.toJson();
    body[Constants.kReview] = review.toJson();

    return this.http.post(`${Constants.kUpdateReviewUrl}`, JSON.stringify(body));
  }

  public editReview(restaurant: Restaurant, oldReview: Review, newReview: Review) {
    const body = {};
    body[Constants.kRestaurant] = restaurant.toJson();
    body[Constants.kParamNewReview] = newReview.toJson();
    body[Constants.kParamOldReview] = oldReview.toJson();

    return this.http.post(`${Constants.kEditReviewUrl}`, JSON.stringify(body));
  }

  public deleteRestaurant(restaurantName: string) {
    const body = {};
    body[Constants.kParamName] = restaurantName;

    return this.http.post(`${Constants.kDeleteRestaurantUrl}`, JSON.stringify(body));
  }

  public deleteAllRestaurantsForUser(userEmail: string) {
    const body = {};
    body[Constants.kParamEmail] = userEmail;

    return this.http.post(`${Constants.kDeleteRestaurantsForUserUrl}`, JSON.stringify(body));
  }

  public editRestaurant(originalRestaurantName: string, newName: string, newImagePath: string) {
    const body = {};
    body[Constants.kParamOriginalName] = originalRestaurantName;
    body[Constants.kParamName] = newName;
    body[Constants.kParamImagePath] = newImagePath;

    return this.http
      .post(`${Constants.kEditRestaurantUrl}`, JSON.stringify(body))
      .pipe(catchError(errorResponse => {
        const genericMessage = 'An unknown error has occured !';
        if (!errorResponse.error || !errorResponse.error.errorMessage) {
          return throwError(genericMessage);
        }
        return throwError(errorResponse.error.errorMessage);
      }));
  }

  public deleteReview(restaurant: Restaurant, review: Review) {
    const body = {};
    body[Constants.kRestaurant] = restaurant.toJson();
    body[Constants.kReview] = review.toJson();

    return this.http.post(`${Constants.kDeleteReviewUrl}`, JSON.stringify(body));
  }

  public fetchReviews(restaurant: Restaurant) {
    const body = {};
    body[Constants.kRestaurant] = restaurant.toJson();

    return this.http.post(`${Constants.kFetchAllReviewsUrl}`, JSON.stringify(body));
  }

  public getRestaurant(id: any) {
    return this.restaurantList[id];
  }

  private restaurantsFromJson(response: any) {
    var restList: Restaurant[] = [];

    response.forEach((value) => {
      const newRst = new Restaurant();
      newRst.fromJson(value);
      restList.push(newRst);
    });

    return restList;
  }


  public resetData() {
    this.restaurantList = [];
  }

}
