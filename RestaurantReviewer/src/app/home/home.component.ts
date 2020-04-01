import { Component, OnInit, ElementRef, OnDestroy } from '@angular/core';
import { MatDialog } from '@angular/material/dialog';
import { Restaurant } from '../entities/restaurant/restaurant.model';
import { AddRestaurantComponent } from '../dialogs/add-restaurant-component/add-restaurant.component';
import { RestaurantService } from '../services/restaurant.service';
import { UserService } from '../services/user.service';
import { take } from 'rxjs/operators/'
import { pipe, Subscription } from 'rxjs';
import { EditRestaurantComponent } from '../dialogs/edit-restaurant/edit-restaurant.component';
import { EditUsersComponent } from '../dialogs/edit-users/edit-users.component';
import { User } from '../entities/user/user.model';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
  providers: [MatDialog],
})
export class HomeComponent implements OnInit, OnDestroy {

  private addRestaurantSubscription: Subscription;
  private editUsersSubscription: Subscription;

  public filterRestaurantsValue = 0;

  public error: string = null;

  constructor(private dialog: MatDialog,
    public restaurantService: RestaurantService,
    public userService: UserService) { }

  ngOnInit() {
    this.userService.autoLogin();

    this.addRestaurantSubscription = this.restaurantService.addRestaurantEvent.subscribe(() => {
      this.onAddRestaurant();
    });

    this.editUsersSubscription = this.userService.editUsersEvent.subscribe(() => {
      this.onEditUsers();
    });


    this.loadRestaurants();
  }

  private onAddRestaurant() {
    const dialogRef = this.dialog.open(AddRestaurantComponent);

    dialogRef.afterClosed().subscribe((newRestaurant: Restaurant) => {
      if (newRestaurant) {
        newRestaurant.ownerEmail = this.userService.currentUserEmail;
        this.restaurantService.addRestaurant(newRestaurant).subscribe(response => {
          this.restaurantService.fetchAllForUser(this.userService.currentUserEmail);
        },
          errorMessage => {
            alert(errorMessage);
          });
      }
    });
  }

  ngOnDestroy() {
    if (this.addRestaurantSubscription) {
      this.addRestaurantSubscription.unsubscribe();
    }

    if (this.editUsersSubscription) {
      this.editUsersSubscription.unsubscribe();
    }
  }

  private loadRestaurants() {
    if (this.userService.currentUserType === 'Owner') {
      this.restaurantService.fetchAllForUser(this.userService.currentUserEmail);
    }
    else {
      this.restaurantService.fetchAll();
    }
  }

  public onEditRestaurant(index) {
    const originalRestaurant = this.restaurantService.getRestaurant(index);
    const dialogRef = this.dialog.open(EditRestaurantComponent);

    dialogRef.afterClosed().subscribe(data => {
      if (data) {
        this.restaurantService.editRestaurant(originalRestaurant.name, data.name, data.imagePath).subscribe(() => {
          this.loadRestaurants();
        },
          errorMessage => {
            alert(errorMessage);
          });
      }
    });
  }

  public onDeleteRestaurant(index) {
    if (confirm('Are you sure you want to delete this restaurant ?')) {
      const originalRestaurant = this.restaurantService.getRestaurant(index);

      this.restaurantService.deleteRestaurant(originalRestaurant.name).subscribe(() => {
        this.loadRestaurants();
      });
    }
  }

  public restaurantAverageRating(index) {
    const restaurant = this.restaurantService.getRestaurant(index);

    let totalRating = 0;
    let acceptedReviews = 0;

    for (const review of restaurant.reviews) {
      if (review.reply) {
        totalRating += review.rating;
        acceptedReviews++;
      }
    }

    if (acceptedReviews === 0) {
      return 0;
    }

    return totalRating / acceptedReviews;
  }

  public numberOfReviews(index) {
    const restaurant = this.restaurantService.getRestaurant(index);
    let acceptedReviews = 0;

    for (const review of restaurant.reviews) {
      if (review.reply) {
        acceptedReviews++;
      }
    }

    return acceptedReviews;
  }

  public hasPendingReview(index) {
    const restaurant = this.restaurantService.getRestaurant(index);

    for (const review of restaurant.reviews) {
      if (!review.reply) {
        return true;
      }
    }

    return false;
  }

  private onEditUsers() {
    let Users: Array<User> = [];

    this.userService.userList().subscribe((response) => {
      Users = response;

      // dont show admin in the user list
      const adminIndex = Users.findIndex(user => user.email === 'admin');
      if (adminIndex !== -1) {
        Users.splice(adminIndex, 1);
      }

      const dialogRef = this.dialog.open(EditUsersComponent,
        {
          data: Users
        });

      dialogRef.afterClosed().subscribe((response) => {
        if (response) {
          if (response.userAction === 'delete') {
            if (confirm('Are you sure you want to delete this user ? The restaurants created by him will be deleted as well !')) {
              this.userService.deleteUser(response.oldUser.email).subscribe(() => {
                this.restaurantService.deleteAllRestaurantsForUser(response.oldUser.email).subscribe(() => {
                  this.restaurantService.fetchAll();
                });
              });
            }
          } else { // edit user
            if (!response.newUser.name) {
              response.newUser.name = response.oldUser.name;
            }
            if (!response.newUser.email) {
              response.newUser.email = response.oldUser.email;
            }
            if (!response.newUser.userType) {
              response.newUser.userType = response.oldUser.userType;
            }

            this.userService.editUser(response.oldUser.email, response.newUser).subscribe();
          }
        }
      });
    });
  }

}
