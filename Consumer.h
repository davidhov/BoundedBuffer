#ifndef _BOUNDED_BUFFER_CONSUMER_H_
#define _BOUNDED_BUFFER_CONSUMER_H_

#include "Utility.h"

/*
 * @class Consumer
 * @brief Consume item from the buffer
 **/
class Consumer
{
	DataObserver data_;

public:
	/*
	 * @brief Consumer constructor
	 * @param d Observer for the data to operate on
	 **/
	explicit Consumer(DataObserver d);

	/*
	 * @brief Consumes items from the buffer
	 * @param id Thread id
	 **/
	void consume(cus id);

private:
	int consumeItem() const;
};

#endif // _BOUNDED_BUFFER_CONSUMER_H_