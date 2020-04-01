import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { MatInputModule } from '@angular/material/input';
import { MatButtonModule } from '@angular/material/button';
import { MatMenuModule } from '@angular/material/menu';
import { MatIconModule } from '@angular/material/icon';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatCardModule } from '@angular/material/card'
import { MatCheckboxModule } from '@angular/material/checkbox';
import { FormsModule } from '@angular/forms';
import { MatDialogModule } from '@angular/material/dialog';
import { MatRadioModule } from '@angular/material/radio';
import { MatSelectModule } from '@angular/material/select';
import { MatSliderModule } from '@angular/material/slider';
import { MatTooltipModule } from '@angular/material/tooltip';

import { HttpClientModule } from '@angular/common/http';

import { FlexLayoutModule } from '@angular/flex-layout';

import { RatingModule } from 'ng-starrating';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { LoginComponent } from './authentication/login/login.component';
import { RegisterComponent } from './authentication/register/register.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { HomeComponent } from './home/home.component';
import { RestaurantComponent } from './entities/restaurant/restaurant.component';
import { UserService } from './services/user.service';
import { AddRestaurantComponent } from './dialogs/add-restaurant-component/add-restaurant.component';
import { ReviewComponent } from './entities/review/review.component';
import { EditRestaurantComponent } from './dialogs/edit-restaurant/edit-restaurant.component';
import { EditUsersComponent } from './dialogs/edit-users/edit-users.component';
import { UserComponent } from './entities/user/user.component';
import { EditReviewComponent } from './dialogs/edit-review/edit-review.component';
import { LoadingSpinnerComponent } from './utility/loading-spinner/loading-spinner.component';

@NgModule({
  declarations: [
    AppComponent,
    LoginComponent,
    RegisterComponent,
    HomeComponent,
    RestaurantComponent,
    AddRestaurantComponent,
    ReviewComponent,
    EditRestaurantComponent,
    EditUsersComponent,
    UserComponent,
    EditReviewComponent,
    LoadingSpinnerComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    BrowserAnimationsModule,
    MatInputModule,
    MatButtonModule,
    FlexLayoutModule,
    FormsModule,
    MatMenuModule,
    MatIconModule,
    MatCheckboxModule,
    MatToolbarModule,
    MatCardModule,
    HttpClientModule,
    MatDialogModule,
    MatRadioModule,
    MatSelectModule,
    RatingModule,
    MatSliderModule,
    MatTooltipModule
  ],
  providers: [UserService],
  bootstrap: [AppComponent]
})
export class AppModule { }
