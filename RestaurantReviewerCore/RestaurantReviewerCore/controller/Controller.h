#ifndef RESTAURANTREVIEWERCONTROLLER_H
#define RESTAURANTREVIEWERCONTROLLER_H

#include <QObject>
#include <QtHttpServer/QtHttpServer>

#include <list>

#include "../communication/consumer/IConsumer.h";

namespace toptal
{
namespace controller
{

class Controller: public QObject
{
	Q_OBJECT
public:
	Controller() = default;

	void init();
private:
	std::shared_ptr<QHttpServer> _httpServer;
	std::list<communication::consumer::IConsumerPtr> _consumerList;

}; // class Controller

} } // toptal::controller

#endif // RESTAURANTREVIEWERCONTROLLER_H