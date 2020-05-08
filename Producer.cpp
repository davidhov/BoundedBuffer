#include "Producer.h"

#include <iostream>
#include <cassert>
#include <chrono>
#include <mutex>

Producer::Producer(DataObserver d)
	: data_(d)
{
}

// Produces items between range [1,100] and pushes those in the buffer.
// Each thread pushes items from [1,100] arbitrary number of times 
// generated in the range [1, 10].
// Procuders will be blocked and wait for the condition when the buffer is full. 
// One of the consumers will wake up any producer.

void Producer::produce(cus id)
{
	assert(!data_.expired());
	auto ptr = data_.lock();
	cus pc = generateNumber(10);
	for (int i = 0; i < pc; ++i) {
		int item = produceItem();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::unique_lock<std::mutex> lock(ptr->mutex_);
		ptr->isNotFull_.wait(lock, [ptr]() { return ptr->buffer_.size() != maxNumOfItems; });
		ptr->buffer_.push_back(item);
		ptr->isNotEmpty_.notify_one();
		std::cout << "Count " << pc << ":\tProducer " << id << ":\t Generated " << item
			<< ":\t Existing Items  " << ptr->buffer_.size() << std::endl;
	}
}

int Producer::produceItem() const
{
	return generateNumber(100);
}
