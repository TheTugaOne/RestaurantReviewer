import { Component, OnInit } from '@angular/core';
import { Restaurant } from './restaurant.model';
import { ActivatedRoute } from '@angular/router';
import { RestaurantService } from 'src/app/services/restaurant.service';
import { Review } from '../review/review.model';
import { UserService } from 'src/app/services/user.service';
import { take } from 'rxjs/operators/'
import { pipe, Subscription, Observable } from 'rxjs';
import { MatDialog } from '@angular/material/dialog';
import { EditReviewComponent } from 'src/app/dialogs/edit-review/edit-review.component';

@Component({
  selector: 'app-restaurant',
  templateUrl: './restaurant.component.html',
  styleUrls: ['./restaurant.component.css']
})
export class RestaurantComponent implements OnInit {

  public restaurant = new Restaurant();
  public bestReview: Review = new Review();
  public worstReview: Review = new Review();
  public alreadyReviewed = false;

  constructor(private route: ActivatedRoute,
              private dialog: MatDialog,
              private restaurantService: RestaurantService,
              public userService: UserService) { }

  ngOnInit(): void {
    this.worstReview.rating = 6; // add a maximum rating so the worst review can comepare against this
    this.route.params.subscribe(res => {
      this.initRestaurant(res.id);
    });
  }

  private initRestaurant(id: any) {
    const restaurant = this.restaurantService.getRestaurant(id).name;

    this.restaurantService.fetchRestaurant(restaurant).subscribe(response => {
      this.restaurant.fromJson(response);
      this.calculateBestWorstReview();
      this.alreadyReviewed = this.userAlreadyReviewed();
    });
  }

  public onSubmitReview(reviewRating: number, reviewComment: string) {
    let newRv = new Review();

    newRv.comment = reviewComment;
    newRv.rating = reviewRating;
    newRv.creatorName = this.userService.currentUserName;
    newRv.date = '';

    const today = new Date();
    const date = today.getFullYear() + '-' + (today.getMonth() + 1) + '-' + today.getDate();
    const time = today.getHours() + ':' + today.getMinutes() + ':' + today.getSeconds();
    newRv.date = date + ' ' + time;

    this.restaurantService.addReview(this.restaurant, newRv).pipe(take(1)).subscribe(() => {
      alert('Thank you for your feedback! It will be visible to everyone as soon as the owner of the restaurant aproves it !')
      this.restaurant.reviews.push(newRv);
      this.alreadyReviewed = this.userAlreadyReviewed();
    });
  }

  public onReviewAccepted(review) {
    this.restaurantService.updateReview(this.restaurant, review).subscribe(() => {
      this.refreshReviews();
    });
  }

  public showReview(reply: string): boolean {
    if (this.userService.currentUserType === 'Reviewer' && !reply) {
      return false;
    }

    return true;
  }

  public onEditReview(index) {
    const originalReview: Review = this.restaurant.reviews[index];

    const dialogRef = this.dialog.open(EditReviewComponent);

    dialogRef.afterClosed().subscribe(newReview => {
      if (newReview) {
        if (!newReview.rating) {
          newReview.rating = originalReview.rating;
        }
        if (!newReview.comment) {
          newReview.comment = originalReview.comment;
        }
        if (!newReview.reply) {
          newReview.reply = originalReview.reply;
        }
        newReview.date = originalReview.date;
        newReview.creatorName = originalReview.creatorName;

        this.restaurantService.editReview(this.restaurant, originalReview, newReview).subscribe(() => {
          this.refreshReviews();
        });
      }
    });
  }

  public onDeleteReview(index) {
    this.restaurantService.deleteReview(this.restaurant, this.restaurant.reviews[index]).subscribe(() => {
      this.refreshReviews();
    });
  }

  private refreshReviews() {
    this.restaurantService.fetchReviews(this.restaurant).subscribe(response => {
      this.restaurant.reviews = new Array<Review>();
      this.restaurant.reviewsFromJson(response);
      this.calculateBestWorstReview();
    });
  }

  private calculateBestWorstReview() {
    this.worstReview = new Review();
    this.worstReview.rating = 6;
    this.bestReview = new Review();

    this.restaurant.reviews.forEach(review => {
      if (review.rating <= this.worstReview.rating) {
        this.worstReview = review;
      }

      if (review.rating >= this.bestReview.rating) {
        this.bestReview = review;
      }
    });
  }

  public userAlreadyReviewed() {
    const index = this.restaurant.reviews.findIndex(review => review.creatorName === this.userService.currentUserName);

    if (index === -1) {
      return false;

    }
    return true;
  }

}
