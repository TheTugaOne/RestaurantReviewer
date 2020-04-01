#include "UserConsumer.h"

#include "../manager/UserManager.h"
#include "../entities/users/User.h"
#include "../../utils/Constants.h"

#include <thread>
#include <chrono>

#include <QCryptographicHash>

using namespace toptal::utils;
using namespace toptal::entities::users;
using namespace toptal::manager;
using namespace toptal::communication::consumer;

UserConsumer::UserConsumer(std::shared_ptr<QHttpServer>& httpServer)
{
    httpServer->route(kApiLogin, [&](const QHttpServerRequest& request) 
        {
            return handleLogin(request);
        });
    httpServer->route(kApiRegister, [&](const QHttpServerRequest& request)
        {
            return handleRegister(request);
        });
    httpServer->route(kGetUsers, [&](const QHttpServerRequest& request)
        {
            return handleGetAll(request);
        });
    httpServer->route(kDeleteUser, [&](const QHttpServerRequest& request)
        {
            return handleDelete(request);
        });
    httpServer->route(kEditUser, [&](const QHttpServerRequest& request)
        {
            return handleEdit(request);
        });
}

std::unique_ptr<UserConsumer> UserConsumer::makePtr(std::shared_ptr<QHttpServer> httpServer)
{
	return std::make_unique<UserConsumer>(httpServer);
}

QHttpServerResponse UserConsumer::handleLogin(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;
    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();
        QString email = body[kEmail].toString();
        QString password = body[kPassword].toString();

        if (email.isEmpty() || password.isEmpty())
            throw "Invalid parameters";

        QByteArray hash = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5);
        QString encryptedPassword = QString::fromStdString(hash.toStdString());

        if (password == "admin")
            encryptedPassword = password;

        User outUser;

        if (!UserManager::instance()->login(email, encryptedPassword, outUser))
        {
            returnCode = QHttpServerResponder::StatusCode::Unauthorized;
            std::exception ex("Username or password wrong !");
            throw ex;
        }

        if (outUser.isValid())
        {
            jsonReply = outUser.toJsonObject();
        }
    }
    catch (const std::exception & ex)
    {
        if (returnCode == QHttpServerResponder::StatusCode::Ok)
            returnCode = QHttpServerResponder::StatusCode::InternalServerError;

        jsonReply["errorMessage"] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse UserConsumer::handleRegister(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();
        QString name = body[kName].toString();
        QString email = body[kEmail].toString();
        QString password = body[kPassword].toString();
        bool isOwner = body[kIsOwner].toBool();

        if (UserManager::instance()->userExists(email))
        {
            std::exception ex("User with given email already exists !");
            throw ex;
        }

        QByteArray hash = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5);
        QString encryptedPassword = QString::fromStdString(hash.toStdString());

        QString userType = "Reviewer";
        if (isOwner)
            userType = "Owner";

        if (! UserManager::instance()->registerUser(email, name, encryptedPassword, userType))
        {
            std::exception ex("Failed to register user !");
            throw ex;
        }

    }
    catch (const std::exception & ex)
    {
        if (returnCode == QHttpServerResponder::StatusCode::Ok)
            returnCode = QHttpServerResponder::StatusCode::InternalServerError;

        jsonReply["errorMessage"] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse UserConsumer::handleGetAll(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonArray revArray;

    try
    {
        UserList usrLst;

        if (!UserManager::instance()->getAll(usrLst))
        {
            // error
        }

        for (const User& user: usrLst)
        {
            revArray.push_back(user.toJsonObject());
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

QHttpServerResponse UserConsumer::handleDelete(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QString email = body[kEmail].toString();

        if (!UserManager::instance()->deleteUser(email))
        {
            // error
        }

    }
    catch (const std::exception & ex)
    {
        if (returnCode == QHttpServerResponder::StatusCode::Ok)
            returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

QHttpServerResponse UserConsumer::handleEdit(const QHttpServerRequest& request)
{
    QHttpServerResponder::StatusCode returnCode = QHttpServerResponder::StatusCode::Ok;
    QJsonObject jsonReply;

    try
    {
        QJsonDocument document = QJsonDocument::fromJson(request.body());
        QJsonObject body = document.object();

        QString email = body[kEmail].toString();

        User newUsr;
        newUsr.fromJsonObject(body[kUser].toObject());

        if (!UserManager::instance()->editUser(email, newUsr))
        {
            // error
        }
    }
    catch (const std::exception & ex)
    {
        if (returnCode == QHttpServerResponder::StatusCode::Ok)
            returnCode = QHttpServerResponder::StatusCode::InternalServerError;
        jsonReply[""] = QString(ex.what());
    }

    QJsonDocument doc(jsonReply);

    QHttpServerResponse resp(QByteArray(), doc.toJson(), returnCode);
    resp.addHeader("Access-Control-Allow-Origin", "*"); // Pass cors

    return resp;
}

