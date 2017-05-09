#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/shared_ptr.hpp>
#include <stdlib.h>


/*
* Steps :
* 1. Create a shared pointer for the integers-resource.
* 2. Create two threads, one each for a producer and a consumer,
*    implement locking mechanisms for accessing the shared resource.*    
*/

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
    for (int i=0; i < 100; ++i) {
      produce();
    }
  }

private:
  boost::shared_ptr<std::vector<T>> pres;  // resource queue
  void wait(int seconds)
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
  }
  void produce() 
  {
    if (pres->size() >= pres->capacity()) { 
      std::cout << "capacity overflow.. clearing the buffer\n";
      pres->clear();

    }
    else {
      int n = rand() % 100;
      std::cout << "number pushed " << n << "\n";
      pres->push_back(n);
    }
    wait(2);
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
private:
  boost::shared_ptr<std::vector<T>> pres;
  void run()
  {
    while (1) {
      consume();
    }
  }
  void consume()
  {
    if (!pres->size()) {
      std::cout << pres->pop_back() << "\n";
    }
  }
};


int main() 
{
  boost::shared_ptr<std::vector<int>> buf(new std::vector<int>(20));
  Producer<int> p(buf);
  boost::thread* pt = new boost::thread(boost::bind(&Producer<int>::run, &p));
  // boost::thread* ct = new boost::thread(boost::bind(&Consumer::run, &c));
  pt->join();
  return 0;
}
