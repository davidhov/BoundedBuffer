#include "Producer.h"

#include <iostream>
#include <cassert>
#include <chrono>
#include <mutex>

Producer::Producer(std::weak_ptr<Data> d)
	: data_(d)
{
}

void Producer::produce(const unsigned short id)
{
	assert(!data_.expired());
	{
		auto ptr = data_.lock();
		const int pc = produceCount();
		for (int i = 0; i < pc; ++i) {
			int item = produceItem();
			std::unique_lock<std::mutex> lock(ptr->mutex_);
			ptr->isNotFull.wait(lock, [&ptr]() { return ptr->buffer_.capacity() - ptr->buffer_.size() != 0; });
			std::cout << "Count " << pc << ":\t";
			ptr->buffer_.push_back(item);
			ptr->isNotEmpty.notify_one();
			std::cout << "Producer " << id << ":\t Generated " << item
				<< ":\t Existing Items  " << ptr->buffer_.size() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
}

int Producer::produceItem() const
{
	return produceCount(10);
}

int Producer::produceCount(int c) const
{
	int i = 0;
	srand((unsigned int)&i);
	return (rand() % (10 * c)) + 1;
}
