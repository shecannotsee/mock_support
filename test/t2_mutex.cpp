//
// Created by shecannotsee on 23-12-29.
//
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "global_test_set.h"
#include "mock_mutex.h"
#include "mock_thread.h"

TEST(t2_mutex, mutex) {
  mock_mutex mock_mutex_turn_on;

  std::mutex test_target;
  test_target.lock();
  test_target.unlock();
  test_target.try_lock();
  test_target.native_handle();
  SUCCEED();
}

TEST(t2_mutex, lock_guard) {
  mock_lock_guard mock_lock_guard_turn_on;

  {
    std::mutex test_target;
    std::lock_guard<std::mutex> lg(test_target);
  }
  SUCCEED();
}

TEST(t2_mutex, unique_lock_with_mutex) {
  mock_unique_lock<std::mutex, mock::mutex> mock_unique_lock_turn_on;
  {
    std::mutex test_target;
    std::unique_lock<std::mutex> ul(test_target);
    std::cout << BLUE_COLOR << "Member functions start!\n" << RESET_COLOR;
    ul.lock();
    ul.try_lock();
    ul.unlock();
    std::cout << PURPLE_COLOR << "Swap start!\n" << RESET_COLOR;
    {
      std::unique_lock<std::mutex> swap_target(test_target);
      ul.swap(swap_target);
    }
    std::cout << PURPLE_COLOR << "Swap done.\n" << RESET_COLOR;
    ul.release();
    ul.owns_lock();
    ul.mutex();
    std::cout << BLUE_COLOR << "Member functions done.\n" << RESET_COLOR;
  }
  SUCCEED();
}

TEST(t2_mutex, condition_variable) {
  SUCCEED();
  return;
}