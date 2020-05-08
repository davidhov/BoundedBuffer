#ifndef _BOUNDED_BUFFER_UTILItY_H_
#define	_BOUNDED_BUFFER_UTILItY_H_

#include <chrono>
#include <memory>
#include <mutex>
#include <vector>

using us = unsigned short;
using cus = const us;

static cus maxNumOfItems = 100;

/*
 * @struct Data
 * @brief Represents data to be seen from both Producer and Consumer classes
 **/
struct Data
{
	/*
	 * @brief Data constructor
	 **/
	Data()
	{
		buffer_.reserve(maxNumOfItems);
	}
	std::vector<int> buffer_;
	// Mutex for mutual exclusion when accessing buffer
	std::mutex mutex_;

	// Condition variable for waiting a consumer to free space in the buffer
	std::condition_variable isNotFull_;

	// Condition variable for waiting a producer to fill empty buffer
	// Also checks if buffer's size is divisible by 5
	// Note: If there aren't any producers left this waits until the given time (1m)
	// and the thread returns from the function
	std::condition_variable isNotEmpty_;
};

using DataObserver = std::weak_ptr<Data>;

/*
 * @brief Generates a number between [1,c]
 * @param c Upper limit of a generated number
 **/
int generateNumber(int c);

#endif // _BOUNDED_BUFFER_UTILItY_H_