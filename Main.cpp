#include "Consumer.h"
#include "Producer.h"
#include "Utility.h"

#include <algorithm>
#include <array>
#include <thread>
#include <vector>

static cus numOfProducers = 5;
static cus numOfConsumers = 5;

int main(int argc, char* argv[])
{
	std::array<std::thread, numOfProducers + numOfConsumers> workers;
	std::shared_ptr<Data> data(std::make_shared<Data>());

	Producer p(data);
	us i = 0;
	for (; i < numOfProducers; ++i) {
		workers[i] = std::thread(&Producer::produce, &p, i + 1);
	}

	Consumer c(data);
	for (; i < numOfProducers + numOfConsumers; ++i) {
		workers[i] = std::thread(&Consumer::consume, &c, i + 1);
	}

	std::for_each(workers.begin(), workers.end(), [](auto& w) { w.join(); });

	return 0;
}