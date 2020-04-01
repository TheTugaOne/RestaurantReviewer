export class Review {
    public rating: number; // out of 5
    public creatorName: string; // user who created the review
    public comment: string; // user comment
    public date: string; // the date when this review was made
    public reply: string; // reply given by the owner of the restaurant once he accepts the review

    constructor(rating: number = 0, creatorName: string = '', comment: string = '', date: string = '', reply: string = '') {
        this.rating = rating;
        this.creatorName = creatorName;
        this.comment = comment;
        this.date = date;
        this.reply = reply;
    }

    fromJson(jsonRev) {
        this.rating = Number(jsonRev['rating']);
        this.creatorName = jsonRev['creatorName'];
        this.comment = jsonRev['comment'];
        this.date = jsonRev['date'];
        this.reply = jsonRev['reply'];
    }

    toJson() {
        const review = {} as any;

        review.rating = this.rating;
        review.creatorName = this.creatorName;
        review.comment = this.comment;
        review.date = this.date;
        review.reply = this.reply;

        return review;
    }

    public compareForReply(second: Review): boolean {
        return this.rating === second.rating
            && this.creatorName === second.creatorName
            && this.comment === second.comment
            && this.date === second.date;
    }

}