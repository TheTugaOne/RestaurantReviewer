export class User {
    public name: string;
    public email: string;
    public password: string;
    public userType: string;

    constructor(name: string = '', email: string = '', password: string = '', userType: string = '') {
        this.name = name;
        this.email = email;
        this.password = password;
        this.userType = userType;
    }

    fromJson(jsonRev) {
        this.name = jsonRev['name'];
        this.email = jsonRev['email'];
        this.password = jsonRev['password'];
        this.userType = jsonRev['date'];
    }

    toJson() {
        const review = {} as any;

        review.name = this.name;
        review.email = this.email;
        review.password = this.password;
        review.userType = this.userType;

        return review;
    }
}