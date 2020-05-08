#include "Consumer.h"

#include <iostream>
#include <cassert>

Consumer::Consumer(std::weak_ptr<Data> d)
	: data_(d)
{
}

void Consumer::consume(const unsigned short id)
{
	assert(!data_.expired());

	{
		auto ptr = data_.lock();
		const int cc = consumeCount();
		for (int i = 0; i < cc; ++i) {
			std::unique_lock<std::mutex> lock(ptr->mutex_);
			ptr->isNotEmpty.wait(lock, [&ptr]() { return !(ptr->buffer_.empty() || (ptr->buffer_.size() % 4 == 0)); });
			std::cout << "Count " << cc << ":\t";
			int item = consumeItem();
			ptr->buffer_.pop_back();
			ptr->isNotFull.notify_one();
			std::cout << "Consumer " << id << ":\t Consumed  " << item
				<< ":\t Remaining Items " << ptr->buffer_.size() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}

int Consumer::consumeItem() const
{
	assert(!data_.expired());
	return data_.lock()->buffer_.back();
}

int Consumer::consumeCount() const
{
	int i = 0;
	srand((unsigned int)&i);
	return (rand() % 10) + 1;
}