#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>


using namespace std;

boost::mutex mutex;       // mutex variable
boost::condition cond;    // condition variable
static bool queue_ready;  // queue state

template<typename T>
class BlockingQueue
{
public:
	explicit BlockingQueue(const vector<T>& buf) : buffer(buf)
	{}
	void insert(T elem) 
	{

	}
	void remove()
	{

	}
private:
	vector<T> buffer;
};


int main() 
{
	return 0;
}