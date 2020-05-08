#include "Consumer.h"

#include <iostream>
#include <cassert>

Consumer::Consumer(DataObserver d)
	: data_(d)
{
}

// Each thread consumes items from the buffer generated number of times: [1,10].
// Consumers will wait if the buffer is empty or if the number of the items in the buffer
// are not divisible by 5.
// In the case when there aren't any producers (they all finished their work), but there
// are still consumers, the laters will wait 1min and will return from the function.
void Consumer::consume(cus id)
{
	assert(!data_.expired());

	using namespace std::chrono_literals;
	auto ptr = data_.lock();
	cus cc = generateNumber(10);
	for (int i = 0; i < cc; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::unique_lock<std::mutex> lock(ptr->mutex_);
		if (!ptr->isNotEmpty_.wait_until(lock, std::chrono::system_clock::now() + 1min, [ptr]() {
			return !(ptr->buffer_.empty() || ptr->buffer_.size() % 5 != 0);
			})) {
			std::cerr << "Consumer " << id << " has waited for too long. Canceling its execution!" << std::endl;
			return;
		}
		int item = consumeItem();
		ptr->buffer_.pop_back();
		ptr->isNotFull_.notify_one();
		std::cout << "Count " << cc << ":\tConsumer " << id << ":\t Consumed  " << item
			<< ":\t Remaining Items " << ptr->buffer_.size() << std::endl;
	}
}

int Consumer::consumeItem() const
{
	assert(!data_.expired());
	return data_.lock()->buffer_.back();
}