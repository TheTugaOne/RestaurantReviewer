import { Component, Inject } from '@angular/core';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { User } from 'src/app/entities/user/user.model';

@Component({
  selector: 'app-edit-users',
  templateUrl: './edit-users.component.html',
  styleUrls: ['./edit-users.component.css']
})
export class EditUsersComponent {
  users: Array<User> = [];
  selectedUser: User = new User();
  newUser: User = new User();
  userAction: any;

  constructor(public dialogRef: MatDialogRef<EditUsersComponent>,
    @Inject(MAT_DIALOG_DATA) public data: Array<User>) {
    if (data) {
      this.users = data;
    }
  }

  public onConfirm() {
    this.dialogRef.close({ oldUser: this.selectedUser, newUser: this.newUser, userAction: this.userAction });
  }

  public onCancel() {
    this.dialogRef.close();
  }

}
