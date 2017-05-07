#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * @brief     Demonstrates the usage of copy constructor and copy assignment operator.
 */
class A 
{
public:
  explicit A(int deg, int a=10) {
    degree = new int;
    *degree = deg;
    age = a;
  }
  A(){}

  // copy constructor, age overridden :)
  // take note of how a new memory is allocated for the degree-pointer,
  // useful when the stack memories are released during program-termination,
  // helps in not having an invalid pointer for other objects created via first A object.
  A(const A& a) {  
    age = a.age+10;
    degree = new int;
    *degree = *(a.degree);
  }
  // copy assignment operator
  A& operator=(const A& a) {
    age = a.age;
    degree = new int;
    *degree = *(a.degree);
    return *this;
  }
  // deletes the degree pointer
  ~A() {
    delete(degree);
    age = 0;
  }
  int getDegree() {
    return *degree;
  }
  int getAge() {
    return age;
  }
private:   
  int age;
  int* degree;
};

int main() {
  A a1(25,10);
  A a2(a1);  // calls copy constructor
  A a3;      // calls copy assignment operator
  a3 = a1;
  cout << a3.getDegree() << "\n";
  return 0;
}