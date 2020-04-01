import { Review } from '../review/review.model'
import { kParamNewReview } from 'src/app/constants.export';


export class Restaurant {
    public name: string;
    public ownerEmail: string;
    public reviews: Array<Review>;
    public imagePath: string;

    constructor(name: string = '', imagePath: string = '') {
        this.name = name;
        this.imagePath = imagePath;
    }

    fromJson(jsonNode) {
        this.name = jsonNode["name"];
        this.ownerEmail = jsonNode["ownerEmail"];
        this.imagePath = jsonNode["imagePath"];

        this.reviews = [];

        var json = JSON.parse(jsonNode['reviews']);
        for (var i = 0; i < json.length; i++) {
            let newRv = new Review();
            newRv.fromJson(json[i]);

            if (newRv) {
                this.reviews.push(newRv);
            }
        }
    }

    toJson() {
        const restaurant = {} as Restaurant;

        restaurant.name = this.name;
        restaurant.ownerEmail = this.ownerEmail;
        restaurant.reviews = new Array<Review>();
        for (const review of this.reviews) {
            restaurant.reviews.push(review);
        }
        restaurant.imagePath = this.imagePath;

        return restaurant;
    }

    reviewsFromJson(reviewArray: any) {
        for (const review of reviewArray) {
            let newRv = new Review();
            newRv.fromJson(review);

            if (newRv) {
                this.reviews.push(newRv);
            }
        }
    }

}