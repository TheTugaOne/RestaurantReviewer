#ifndef USERCONSUMER_H
#define USERCONSUMER_H

#include "IConsumer.h"

namespace toptal
{
namespace communication
{
namespace consumer
{

class UserConsumer: public IConsumer
{
public:
	UserConsumer() = default;
	UserConsumer(std::shared_ptr<QHttpServer>& httpServer);

	static std::unique_ptr<UserConsumer> makePtr(std::shared_ptr<QHttpServer> httpServer);

private:
	QHttpServerResponse handleLogin(const QHttpServerRequest& request);
	QHttpServerResponse handleRegister(const QHttpServerRequest& request);
	QHttpServerResponse handleGetAll(const QHttpServerRequest& request);
	QHttpServerResponse handleDelete(const QHttpServerRequest& request);
	QHttpServerResponse handleEdit(const QHttpServerRequest& request);


}; // class UserConsumer

using AuthenticationConsumerPtr = std::unique_ptr<UserConsumer>;

} } } // toptal::communication::consumer

#endif // AUTHENTICATIONCONSUMER_H