#ifndef _BOUNDED_BUFFER_PRODUCER_H_
#define _BOUNDED_BUFFER_PRODUCER_H_

#include "Utility.h"

/*
 * @class Producer
 * @brief Produces item to the buffer
 **/
class Producer
{
	DataObserver data_;

public:
	/*
	 * @brief Producer constructor
	 * @param d Observer for the data to operate on
	 **/
	explicit Producer(DataObserver d);

	/*
	 * @brief Produces items to the buffer
	 * @param id Thread id
	 **/
	void produce(cus id);

private:
	int produceItem() const;
};

#endif // _BOUNDED_BUFFER_PRODUCER_