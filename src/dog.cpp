#include "dog.h"

dog::dog(std::string dog_name, int dog_age) {
  this->dog_name = dog_name;
  this->dog_age  = dog_age;
  std::cout << "dog_name: " << dog_name << "\ndog_age: " << dog_age << "\n";
}

dog::~dog() { std::cout << "\nthis is a destructor"; }