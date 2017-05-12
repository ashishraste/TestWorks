#include <iostream>
#include <boost/thread.hpp>
#include "snippets/blocking_queue.h"

using namespace std;

template<typename T>
void BlockingQueue<T>::insert(T elem) 
{
	while (buffer.size() == buffer.capacity()) 
		cond.wait(mutex);
	boost::unique_lock<boost::mutex> lock(mutex);
	buffer.push_back(elem);
	cond.notify_all();
}

template<typename T>
T BlockingQueue<T>::remove()
{
	boost::unique_lock<boost::mutex> lock{mutex};
	while (buffer.size() == 0)
		cond.wait(mutex);
	T elem = buffer.front();
	buffer.erase(buffer.begin());
	return elem;
}

int main() 
{
	vector<int> integers(10);
	BlockingQueue<int> queue(integers);
	return 0;
}