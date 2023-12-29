//
// Created by shecannotsee on 23-12-29.
//
#include <mock_thread.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "global_test_set.h"

TEST(t1_thread, join) {
  // start mock
  mock_thread m_thread;

  // The following code is derived from: https://en.cppreference.com/w/cpp/thread/thread/join
  auto foo = []() {
    std::cout << RED_COLOR << "mock failed\n" << RESET_COLOR;
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };
  auto bar = []() {
    std::cout << RED_COLOR << "mock failed\n" << RESET_COLOR;
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };

  std::cout << "starting first helper...\n";
  std::thread helper1(foo);

  std::cout << "starting second helper...\n";
  std::thread helper2(bar);

  std::cout << "waiting for helpers to finish..." << std::endl;
  helper1.join();
  helper2.join();

  std::cout << "done!\n";
}
