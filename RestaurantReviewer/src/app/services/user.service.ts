import { Injectable, EventEmitter } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import * as Constants from '../constants.export';
import { Observable } from 'rxjs';
import { User } from '../entities/user/user.model';
import { catchError } from 'rxjs/operators';
import { throwError } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class UserService {
  public currentUserType: string;
  public currentUserEmail: string;
  public currentUserName: string;

  editUsersEvent = new EventEmitter<any>();

  constructor(private http: HttpClient) { }

  public login(email: string, password: string): Observable<any> {
    const body = {};
    body[Constants.kParamEmail] = email;
    body[Constants.kParamPassword] = password;

    return this.http
      .post(`${Constants.kLoginUrl}`, JSON.stringify(body))
      .pipe(catchError(errorResponse => {
        const genericMessage = 'An unknown error has occured !';
        if (!errorResponse.error || !errorResponse.error.errorMessage) {
          return throwError(genericMessage);
        }
        return throwError(errorResponse.error.errorMessage);
      }));
  }

  public registerUser(email: string, name: string, password: string, isOwner: boolean): Observable<any> {
    const body = {};
    body[Constants.kParamEmail] = email;
    body[Constants.kParamName] = name;
    body[Constants.kParamPassword] = password;
    body[Constants.kParamIsOwner] = isOwner;

    return this.http
      .post(`${Constants.kRegisterUrl}`, JSON.stringify(body))
      .pipe(catchError(errorResponse => {
        const genericMessage = 'An unknown error has occured !';
        if (!errorResponse.error || !errorResponse.error.errorMessage) {
          return throwError(genericMessage);
        }
        return throwError(errorResponse.error.errorMessage);
      }));
  }

  public deleteUser(email: string) {
    const body = {};
    body[Constants.kParamEmail] = email;

    return this.http.post(`${Constants.kDeleteUserUrl}`, JSON.stringify(body));
  }

  public editUser(email: string, newUserData: User) {
    const body = {};
    body[Constants.kParamEmail] = email;
    body[Constants.kParamUser] = newUserData.toJson();

    return this.http.post(`${Constants.kEditUserUrl}`, JSON.stringify(body));
  }

  public userList(): Observable<any> {
    return this.http.get(`${Constants.kGetUsers}`);
  }

  public autoLogin(): boolean {
    const userData: {
      name: string;
      email: string;
      password: string;
      userType: string;
    } = JSON.parse(localStorage.getItem('userData'));

    if (!userData) {
      return false;
    }

    this.updateCurrentUserData(userData.userType, userData.email, userData.name);
    return true;
  }

  public updateCurrentUserData(currentUserType: string, currentUserEmail: string, currentUserName: string) {
    this.currentUserType = currentUserType;
    this.currentUserEmail = currentUserEmail;
    this.currentUserName = currentUserName;
  }

  public resetData() {
    this.currentUserType = '';
    this.currentUserEmail = '';
    this.currentUserName = '';

  }
}
