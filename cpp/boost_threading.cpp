#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void delayGuy()
{
  for (int i=0; i<5; ++i)
  {
    wait(i);
    std::cout << "delayed by " << i << '\n';
  }
}

void chatterGuy()
{
	for (int i=0; i<=2; ++i) std::cout << "I'm catbug :) \n";
}

void boringCompanyGuy()
{
	std::cout << "I'll help humanity \n";
}

int main()
{
  boost::shared_ptr<boost::thread> t1(new boost::thread(boost::bind(&delayGuy)));
  boost::thread t2{chatterGuy};
  boost::thread* t3 = new boost::thread(&boringCompanyGuy);  // or via boost::thread(boost::bind(&boringCompanyGuy));
  t1->join();
  t2.join();
  t3->join();
  return 0;
}