#include "Consumer.h"
#include "Data.h"
#include "Producer.h"

#include <algorithm>
#include <array>
#include <thread>
#include <vector>

using us = unsigned short;
using cus = const us;

static cus numOfProducers = 5;
static cus numOfConsumers = 5;
static cus numOfItems = 100;

int main(int argc, char* argv[])
{
	std::array<std::thread, numOfProducers + numOfConsumers> workers;
	std::shared_ptr<Data> data(std::make_shared<Data>(numOfItems));

	Producer p(data);
	for (us i = 0; i < numOfProducers; ++i) {
		workers[i] = std::thread(&Producer::produce, &p, i + 1);
	}

	Consumer c(data);
	for (us i = numOfProducers; i < numOfProducers + numOfConsumers; ++i) {
		workers[i] = std::thread(&Consumer::consume, &c, i + 1);
	}

	std::for_each(workers.begin(), workers.end(), [](auto& w) { w.join(); });

	return 0;
}