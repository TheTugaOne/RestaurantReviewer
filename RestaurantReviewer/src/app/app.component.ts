import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { UserService } from './services/user.service';
import { RestaurantService } from './services/restaurant.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'RestaurantReviewer';

  constructor(public router: Router,
    public userService: UserService,
    public restaurantService: RestaurantService) { }

  public onLogout() {
    // reset current session data
    this.restaurantService.resetData();
    this.userService.resetData();
    localStorage.clear();
    this.router.navigate(['/login']);
  }

  public onAddRestaurant() {
    this.restaurantService.addRestaurantEvent.emit();
  }

  public onEditUsers() {
    this.userService.editUsersEvent.emit();
  }

}
