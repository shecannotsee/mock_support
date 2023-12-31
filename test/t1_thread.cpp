//
// Created by shecannotsee on 23-12-29.
//

#include "global_test_set.h"
#include <mock_thread.h>

#include <chrono>
#include <iostream>
#include <thread>

TEST(t1_thread, join) {
  // start mock
  mock_thread<std::thread, mock::thread> m_thread;

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
  SUCCEED();
}

TEST(t1_thread, join1) {
  // start mock
  mock_thread<std::thread, mock::thread> m_thread;

  auto independentThread = []() {
    std::cout << RED_COLOR << "mock failed.\n" << RESET_COLOR;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << RED_COLOR << "mock failed.\n" << RESET_COLOR;
  };
  std::cout << GREEN_COLOR << "step1, next run detach.\n" << RESET_COLOR;
  std::thread t(independentThread);
  t.detach();
  std::cout << GREEN_COLOR << "step2.\n" << RESET_COLOR;
}
