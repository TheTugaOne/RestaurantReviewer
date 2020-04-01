import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { UserService } from 'src/app/services/user.service';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit {

  name: string;
  email: string;
  password: string;

  error: string = null;

  isOwnerAccountChecked: false;

  constructor(private router: Router,
    private userService: UserService) { }

  ngOnInit(): void {
  }

  public onRegister() {
    this.userService.registerUser(this.email, this.name, this.password, this.isOwnerAccountChecked).subscribe(response => {
      // do something with error
      this.router.navigate(['/login']);
    },
      errorMessage => {
        this.error = errorMessage;
      }
  );
  }

  public onCancelRegistration() {
    this.router.navigate(['/login']);
  }

}
