#include <iostream>

/**
 * @brief this is a doggo class
 *
 */
class dog {
 public:
  dog(std::string dog_name, int dog_age);
  ~dog();

 private:
  std::string dog_name;
  int dog_age;
};