#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/shared_ptr.hpp>
// #include <stdlib.h>

/*
* Steps :
* 1. Create a shared pointer for a common resource : a vector, to which shared-pointers from 
*    producer and consumer exists.
* 2. Create two threads, one each for a producer and a consumer, implement unique and shared locking
*    mechanisms for writing and reading to/from the vector.  
*/

boost::shared_mutex mutex;  // to be applicable with shared_lock(s)


template<typename T>
class Producer
{
public:
  explicit Producer(boost::shared_ptr<std::vector<T>> buf):
    pres(boost::shared_ptr<std::vector<T>>(buf))
  {}
  explicit Producer():
    pres(boost::shared_ptr<std::vector<T>>(new std::vector<T>(10)))
  {}
  void run() 
  {
    for (int i=0; i < 15; ++i) {
      // need to write into the buffer, hence an exclusive unique_lock
      boost::unique_lock<boost::shared_mutex> lock{mutex};
      if (pres->size() >= pres->capacity()) { 
        std::cout << "clearing the buffer\n";
        pres->clear();
      }
      else {
        int n = rand() % 100;
        std::cout << "number pushed " << n << "\n";
        pres->push_back(n);
      }
      lock.unlock();
      wait(1);  // wait for a second to be sure of the write-operation
    }
  }

private:
  boost::shared_ptr<std::vector<T>> pres;  // resource queue
  void wait(int seconds)
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
  }
};


template<typename T>
class Consumer
{
public:
  explicit Consumer(boost::shared_ptr<std::vector<T>> buf):
    pres(boost::shared_ptr<std::vector<T>>(buf))
  {}
  explicit Consumer():
    pres(boost::shared_ptr<std::vector<T>>(new std::vector<T>(10)))
  {}
  void run()
  {
    for (int i=0; i<20; ++i) {
      wait(1);  
      // only reads from the resource, hence a shared_lock
      boost::shared_lock<boost::shared_mutex> lock{mutex};
      std::cout << "last element " << pres->back() << "\n";
    }
  }
private:
  boost::shared_ptr<std::vector<T>> pres;
  void wait(int seconds)
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
  }
};


int main() 
{
  boost::shared_ptr<std::vector<int>> buf(new std::vector<int>(20));
  Producer<int> pi(buf);
  Consumer<int> ci(buf);
  boost::thread* pt = new boost::thread(boost::bind(&Producer<int>::run, &pi));
  boost::thread* ct = new boost::thread(boost::bind(&Consumer<int>::run, &ci));
  pt->join();
  ct->join();
  return 0;
}
