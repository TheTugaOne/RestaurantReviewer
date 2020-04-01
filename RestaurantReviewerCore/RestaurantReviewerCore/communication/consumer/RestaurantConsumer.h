#ifndef RESTAURANTCONSUMER_H
#define RESTAURANTCONSUMER_H

#include "IConsumer.h"

namespace toptal
{
namespace communication
{
namespace consumer
{

class RestaurantConsumer : public IConsumer
{
public:
	RestaurantConsumer() = default;
	RestaurantConsumer(std::shared_ptr<QHttpServer>& httpServer);

	static std::unique_ptr<RestaurantConsumer> makePtr(std::shared_ptr<QHttpServer> httpServer);

private:
	QHttpServerResponse handleAdd(const QHttpServerRequest& request);
	QHttpServerResponse handleAll(const QHttpServerRequest& request);
	QHttpServerResponse handleFetchForUser(const QHttpServerRequest& request);
	QHttpServerResponse handleFetchOne(const QHttpServerRequest& request);
	QHttpServerResponse handleAddReview(const QHttpServerRequest& request);
	QHttpServerResponse handleUpdateReview(const QHttpServerRequest& request);
	QHttpServerResponse handleEditReview(const QHttpServerRequest& request);
	QHttpServerResponse handleDelete(const QHttpServerRequest& request);
	QHttpServerResponse handleDeleteAllForUser(const QHttpServerRequest& request);
	QHttpServerResponse handleEdit(const QHttpServerRequest& request);
	QHttpServerResponse handleDeleteReview(const QHttpServerRequest& request);
	QHttpServerResponse handleAllReviews(const QHttpServerRequest& request);

}; // class RestaurantConsumer

using RestaurantConsumerPtr = std::unique_ptr<RestaurantConsumer>;

} } } // toptal::communication::consumer

#endif // RESTAURANTCONSUMER_H