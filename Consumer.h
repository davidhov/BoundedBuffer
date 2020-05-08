#ifndef _BOUNDED_BUFFER_CONSUMER_H_
#define _BOUNDED_BUFFER_CONSUMER_H_

#include "Data.h"

class Consumer
{
	std::weak_ptr<Data> data_;

public:
	explicit Consumer(std::weak_ptr<Data> d);
	void consume(const unsigned short id);

private:
	int consumeItem() const;
	int consumeCount() const;
};

#endif // _BOUNDED_BUFFER_CONSUMER_H_