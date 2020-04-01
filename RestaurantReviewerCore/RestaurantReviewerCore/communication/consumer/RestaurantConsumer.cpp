#include "RestaurantConsumer.h"

#include "../manager/RestaurantManager.h"
#include "../entities/Restaurant.h"
#include "../../utils/Constants.h"

#include <qmetaobject.h>

using namespace toptal::utils;
using namespace toptal::entities;
using namespace toptal::manager;
using namespace toptal::communication::consumer;

RestaurantConsumer::RestaurantConsumer(std::shared_ptr<QHttpServer>& httpServer)
{
    httpServer->route(kApiRestaurantAdd, [&](const QHttpServerRequest& request)
        {
            return handleAdd(request);
        });
    httpServer->route(kFetchAllRestaurantsUrl, [&](const QHttpServerRequest& request)
        {
            return handleAll(request);
        });
    httpServer->route(kFetchRestaurantForUserUrl, [&](const QHttpServerRequest& request)
        {
            return handleFetchForUser(request);
        });
    httpServer->route(kFetchOneRestaurantsUrl, [&](const QHttpServerRequest& request)
        {
            return handleFetchOne(request);
        });
    httpServer->route(kAddReviewUrl, [&](const QHttpServerRequest& request)
        {
            return handleAddReview(request);
        });
    httpServer->route(kUpdateReviewUrl, [&](const QHttpServerRequest& request)
        {
            return handleUpdateReview(request);
        });
    httpServer->route(kEditReviewUrl, [&](const QHttpServerRequest& request)
        {
            return handleEditReview(request);
        });
    httpServer->route(kDeleteReviewUrl, [&](const QHttpServerRequest& request)
        {
            return handleDeleteReview(request);
        });
    httpServer->route(kDeleteRestaurantUrl, [&](const QHttpServerRequest& request)
        {
            return handleDelete(request);
        });
    httpServer->route(kDeleteRestaurantsForUserUrl, [&](const QHttpServerRequest& request)
        {
            return handleDeleteAllForUser(request);
        });
    httpServer->route(kEditRestaurantUrl, [&](const QHttpServerRequest& request)
        {
            return handleEdit(request);
        });
    httpServer->route(kFetchAllReviewsUrl, [&](const QHttpServerRequest& request)
        {
            return handleAllReviews(request);
        });
}

std::unique_ptr<RestaurantConsumer> RestaurantConsumer::makePtr(std::shared_ptr<QHttpServer> httpServer)
{
	return std::make_unique<RestaurantConsumer>(httpServer);
}

QHttpServerResponse RestaurantConsumer::handleAdd(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        Restaurant restaurant;
        restaurant.fromJsonObject(body);

        if (RestaurantManager::instance()->restaurantExists(restaurant.name()))
        {
            std::exception ex("A restaurant with given name already exists !");
            throw ex;
        }

        if (!RestaurantManager::instance()->addRestaurant(restaurant))
        {
            // error
        }

    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply["errorMessage"] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleAll(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonArray revArray;

    try
    {
        RestaurantList rstList = RestaurantManager::instance()->getAll();

        for (const Restaurant& rst : rstList)
        {
            revArray.push_back(rst.toJsonObject());
        }
    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
    }

    QJsonDocument doc(revArray);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleFetchForUser(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonArray revArray;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QString userEmail = body[kEmail].toString();

        RestaurantList rstList = RestaurantManager::instance()->getAllForUser(userEmail);

        for (const Restaurant& rst : rstList)
        {
            revArray.push_back(rst.toJsonObject());
        }
    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
    }

    QJsonDocument doc(revArray);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleFetchOne(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QString restaurantName = body[kName].toString();

        Restaurant dbRst = RestaurantManager::instance()->getOne(restaurantName);

        jsonReply = dbRst.toJsonObject();
    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleAddReview(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QJsonObject restaurantJson = body[kRestaurant].toObject();
        QJsonObject reviewJson = body[kReview].toObject();

        Restaurant restaurant;
        restaurant.fromJsonObject(restaurantJson);

        Review review;
        review.fromJsonObject(reviewJson);


        if (!RestaurantManager::instance()->addReview(restaurant, review))
        {
            // error
        }

    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleUpdateReview(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QJsonObject restaurantJson = body[kRestaurant].toObject();
        QJsonObject reviewJson = body[kReview].toObject();

        Restaurant restaurant;
        restaurant.fromJsonObject(restaurantJson);

        Review review;
        review.fromJsonObject(reviewJson);


        if (!RestaurantManager::instance()->updateReview(restaurant, review))
        {
            // error
        }
    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleEditReview(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QJsonObject restaurantJson = body[kRestaurant].toObject();
        QJsonObject oldReviewJson = body[kOldReview].toObject();
        QJsonObject newReviewJson = body[kNewReview].toObject();


        Restaurant restaurant;
        restaurant.fromJsonObject(restaurantJson);

        Review oldReview;
        oldReview.fromJsonObject(oldReviewJson);

        Review newReview;
        newReview.fromJsonObject(newReviewJson);

        if (!RestaurantManager::instance()->editReview(restaurant, oldReview, newReview))
        {
            // error
        }
    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleDelete(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QString restName = body[kName].toString();

        if (!RestaurantManager::instance()->deleteRestaurant(restName))
        {
            // error
        }

    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleDeleteAllForUser(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QString userEmail = body[kEmail].toString();

        if (!RestaurantManager::instance()->deleteAllForUser(userEmail))
        {
            // error
        }

    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleEdit(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {

        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QString origRestName = body[kOriginalName].toString();
        QString newRestName = body[kName].toString();
        QString newImagePath = body[kImagePath].toString();

        if (RestaurantManager::instance()->restaurantExists(newRestName))
        {
            std::exception ex("A restaurant with given name already exists !");
            throw ex;
        }

        if (!RestaurantManager::instance()->editRestaurant(origRestName, newRestName, newImagePath))
        {
            // error
        }

    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply["errorMessage"] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleDeleteReview(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QJsonObject restaurantJson = body[kRestaurant].toObject();
        QJsonObject reviewJson = body[kReview].toObject();

        Restaurant restaurant;
        restaurant.fromJsonObject(restaurantJson);

        Review review;
        review.fromJsonObject(reviewJson);

        if (!RestaurantManager::instance()->deleteReview(restaurant, review))
        {
            // error
        }
    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse RestaurantConsumer::handleAllReviews(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonArray revArray;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        Restaurant restaurant;
        restaurant.fromJsonObject(body[kRestaurant].toObject());

        std::vector<Review> reviewList = {};

         if (!RestaurantManager::instance()->getAllReviews(restaurant, reviewList))
         {
             // error
         }

        for (const Review& review: reviewList)
        {
            revArray.push_back(review.toJsonObject());
        }
    }
    catch (const std::exception & ex)
    {
        returnCode = QHttpServerResponder::StatusCode::InternalServerError;
    }

    QJsonDocument doc(revArray);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}
