import { Component, OnInit } from '@angular/core';
import { MatDialogRef } from '@angular/material/dialog';
import { Restaurant } from 'src/app/entities/restaurant/restaurant.model';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-add-restaurant',
  templateUrl: './add-restaurant.component.html',
  styleUrls: ['./add-restaurant.component.css']
})
export class AddRestaurantComponent {
  public restaurant: Restaurant = new Restaurant();

  constructor(public dialogRef: MatDialogRef<AddRestaurantComponent>) { }

  public onCreate() {
    this.dialogRef.close(this.restaurant);
  }

  public onCancel() {
    this.dialogRef.close();
  }

}
