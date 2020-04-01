import { Component, OnInit } from '@angular/core';
import { Review } from 'src/app/entities/review/review.model';
import { MatDialogRef } from '@angular/material/dialog';

@Component({
  selector: 'app-edit-review',
  templateUrl: './edit-review.component.html',
  styleUrls: ['./edit-review.component.css']
})
export class EditReviewComponent {

  public newReview: Review = new Review();

  constructor(public dialogRef: MatDialogRef<EditReviewComponent>) { }

  public onConfirm() {
    this.dialogRef.close(this.newReview);
  }

  public onCancel() {
    this.dialogRef.close();
  }

}
