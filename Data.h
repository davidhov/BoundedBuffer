#ifndef _BOUNDED_BUFFER_DATA_H_
#define	_BOUNDED_BUFFER_DATA_H_

#include <mutex>
#include <vector>

struct Data
{
	Data(size_t n)
	{
		buffer_.reserve(n);
	}
	std::vector<int> buffer_;
	std::mutex mutex_;
	std::condition_variable isNotFull;
	std::condition_variable isNotEmpty;
};

#endif // _BOUNDED_BUFFER_DATA_H_