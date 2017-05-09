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

class Producer
{
public:
  explicit Producer(boost::shared_ptr<std::vector<int>> buf):
    res(boost::shared_ptr<std::vector<int>>(buf))
  {}
  explicit Producer():
    res(boost::shared_ptr<std::vector<int>>(new std::vector<int>(10)))
  {}

  void run() 
  {
    for (int i=0; i < 100; ++i) {
      produce();
    }
  }

private:
  boost::shared_ptr<std::vector<int>> res;  // resource queue
  void wait(int seconds)
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
  }
  void produce() 
  {
    if (res->size() >= res->capacity()) { 
      std::cout << "capacity overflow.. clearing the buffer\n";
      res->clear();

    }
    else {
      int n = rand() % 100;
      std::cout << "number pushed " << n << "\n";
      res->push_back(n);
    }
    wait(2);
  }
};

class Consumer
{
private:
  boost::shared_ptr<std::vector<int>> cres;
};

int main() 
{
  boost::shared_ptr<std::vector<int>> buf(new std::vector<int>(20));
  Producer p(buf);
  boost::thread* pt = new boost::thread(boost::bind(&Producer::run, &p));
  // boost::thread* ct = new boost::thread(boost::bind(&Consumer::run, &c));
  pt->join();
  return 0;
}
