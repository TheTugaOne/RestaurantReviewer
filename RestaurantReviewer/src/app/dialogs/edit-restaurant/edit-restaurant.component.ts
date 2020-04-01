import { Component, OnInit } from '@angular/core';
import { Restaurant } from 'src/app/entities/restaurant/restaurant.model';
import { MatDialogRef } from '@angular/material/dialog';

@Component({
  selector: 'app-edit-restaurant',
  templateUrl: './edit-restaurant.component.html',
  styleUrls: ['./edit-restaurant.component.css']
})
export class EditRestaurantComponent {
  public name: string = '';
  public imagePath: string = '';

  constructor(public dialogRef: MatDialogRef<EditRestaurantComponent>) { }

  public onConfirm() {
    this.dialogRef.close({ name: this.name, imagePath: this.imagePath });
  }

  public onCancel() {
    this.dialogRef.close();
  }

}
