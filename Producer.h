#ifndef _BOUNDED_BUFFER_PRODUCER_H_
#define _BOUNDED_BUFFER_PRODUCER_H_

#include "Data.h"

class Producer
{
	std::weak_ptr<Data> data_;

public:
	explicit Producer(std::weak_ptr<Data> d);
	void produce(const unsigned short id);

private:
	int produceItem() const;
	int produceCount(int = 1) const;
};

#endif // _BOUNDED_BUFFER_PRODUCER_