// Created by shecannotsee on
#include <iostream>
#include "global_test_set.h"
#include "test_example.h"
// test_suite
// easy_test
// logic_test

int main() {
  std::cout << YELLOW_COLOR << "Start test " << RESET_COLOR << std::endl;
  constexpr bool easy_test = false;
  constexpr bool test_suite = true;
  if (easy_test) {

  }

  if (test_suite) {
    testing::InitGoogleTest();

    if (RUN_ALL_TESTS() == 0) {
      std::cout << GREEN_COLOR << "Pass the test." << RESET_COLOR << std::endl;
    } else {
      std::cout << RED_COLOR << "Failed the test." << RESET_COLOR << std::endl;
    }
  }

  return 0;
}
