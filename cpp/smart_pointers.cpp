#include <iostream>
#include <string.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>


template<typename T>
class C
{
public:
  template<class Y>
  explicit C(boost::shared_ptr<Y> pg):pg_(pg)
  {}
  long count() const {
    return pg_.use_count;
  }
private:
  boost::shared_ptr<T> pg_;
};

class A
{
public:
  explicit A(boost::shared_ptr<int> pi, int a=10):age(a),pi_(pi)
  {}
  long count() const {
    return pi_.use_count();
  }
private:
  int age;
  boost::shared_ptr<int> pi_;
};

class B
{
public:
  explicit B(boost::shared_ptr<int> pi, int a=20):degree(a),pi_(pi)
  {}
  long count() const {
    return pi_.use_count();
  }
private:
  int degree;
  boost::shared_ptr<int> pi_;
};

int main() 
{
  // scoped pointer
  boost::scoped_ptr<std::string> pstr(new std::string("Hlosas"));
  if (pstr) std::cout << *pstr << "\n";

  // shared pointer
  boost::shared_ptr<int> pi(new int(30));
  A a1(pi,10);
  B b1(pi,20);
  C<int> c1(pi);
  std::cout << "number of pointers " << a1.count() << "\n";
  return 0;
}