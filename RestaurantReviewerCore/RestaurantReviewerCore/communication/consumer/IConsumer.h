/*!
 *	\file IConsumer.h
 *	\date 19 January 2018
 *	\brief Interface for Consumer.
 */

#ifndef PROCESSING_CONSUMER_I_CONSUMER_H
#define PROCESSING_CONSUMER_I_CONSUMER_H

#include <memory>
#include <QtHttpServer/QtHttpServer>


namespace toptal
{
namespace communication
{
namespace consumer
{
/*!
	*	\class Consumer
	*	\brief Interface for Message Dispatcher.
	*/
class IConsumer
{
public:
	IConsumer(const IConsumer&) = delete;
	IConsumer& operator=(const IConsumer&) = delete;

	explicit			IConsumer() = default;
	virtual				~IConsumer() = default;

}; // class IConsumer

using IConsumerPtr = std::unique_ptr<IConsumer>;

} } } // namespace sai::communication::consumer

#endif // PROCESSING_CONSUMER_I_CONSUMER_H
