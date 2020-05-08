#include "Utility.h"

int generateNumber(int c)
{
	const auto now = std::chrono::system_clock::now();
	srand((unsigned)now.time_since_epoch().count());
	return (rand() % c) + 1;
}