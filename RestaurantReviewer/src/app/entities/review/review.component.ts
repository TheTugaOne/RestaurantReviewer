import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Review } from './review.model';
import { UserService } from 'src/app/services/user.service';

@Component({
  selector: 'app-review',
  templateUrl: './review.component.html',
  styleUrls: ['./review.component.css']
})
export class ReviewComponent implements OnInit {
  @Output() reviewAccepted = new EventEmitter<Review>();
  @Input() review: Review;

  constructor(public userService: UserService) { }

  ngOnInit(): void {
  }

  onAcceptReview(reply: string) {
    this.review.reply = reply;
    this.reviewAccepted.emit(this.review);
  }
}
