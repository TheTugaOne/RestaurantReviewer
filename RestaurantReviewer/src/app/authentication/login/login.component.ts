import { Component, OnInit, OnDestroy } from '@angular/core';
import { Router, RouterModule } from '@angular/router';

import { UserService } from 'src/app/services/user.service';
import { take } from 'rxjs/operators/'
import { pipe, Subscription } from 'rxjs';
import { StarRatingComponent } from 'ng-starrating';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent{

  email: string;
  password: string;

  error: string = null;

  isLoading = false;

  private loginSub: Subscription;

  constructor(private router: Router,
    private userService: UserService) { }

  public onLogin() {
    this.isLoading = true;

    this.loginSub = this.userService.login(this.email, this.password).subscribe(response => {
      localStorage.setItem('userData', JSON.stringify({ name: response['name'], email: this.email, userType: response['usertype'] }));
      this.userService.updateCurrentUserData(response['usertype'], this.email, response['name']);
      this.router.navigate(['/home']);
      this.isLoading = false;
    },
      errorMessage => {
        this.error = errorMessage;
        this.isLoading = false;
      }
    );
  }

  public onRegister() {
    this.router.navigate(['/register']);
  }

}
