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
  std::cout << BLUE_COLOR << "Member functions start!\n" << RESET_COLOR;
  test_target.lock();
  test_target.unlock();
  test_target.try_lock();
  test_target.native_handle();
  std::cout << BLUE_COLOR << "Member functions done!\n" << RESET_COLOR;
  SUCCEED();
}

TEST(t2_mutex, timed_mutex) {
  mock_timed_mutex mock_timed_mutex_turn_on;

  std::timed_mutex test_target;
  std::cout << BLUE_COLOR << "Member functions start!\n" << RESET_COLOR;
  test_target.lock();
  test_target.try_lock();
  // try_lock_for
  {
    const auto timeout = std::chrono::milliseconds(200);
    test_target.try_lock_for(timeout);
  }
  // try_lock_until
  {
    const auto now     = std::chrono::system_clock::now();
    const auto timeout = now + std::chrono::seconds(10);
    test_target.try_lock_until(timeout);
  }
  test_target.unlock();
  test_target.native_handle();
  std::cout << BLUE_COLOR << "Member functions done!\n" << RESET_COLOR;
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
  // mock_unique_lock_with_mutex mock_unique_lock_with_mutex_turn_on;
  {
    std::mutex test_mutex;
    std::unique_lock<std::mutex> test_target(test_mutex);
    std::cout << BLUE_COLOR << "Member functions start!\n" << RESET_COLOR;
    test_target.lock();
    test_target.try_lock();
    test_target.unlock();
    std::cout << PURPLE_COLOR << "Swap start!\n" << RESET_COLOR;
    {
      std::unique_lock<std::mutex> swap_target(test_mutex);
      test_target.swap(swap_target);
    }
    std::cout << PURPLE_COLOR << "Swap done.\n" << RESET_COLOR;
    test_target.release();
    test_target.owns_lock();
    test_target.mutex();
    std::cout << BLUE_COLOR << "Member functions done.\n" << RESET_COLOR;
  }
  SUCCEED();
}

TEST(t2_mutex, unique_lock_with_timed_mutex) {
  mock_unique_lock<std::timed_mutex, mock::timed_mutex> mock_unique_lock_turn_on;
  {
    std::timed_mutex test_mutex;
    std::unique_lock<std::timed_mutex> test_target(test_mutex);
    std::cout << BLUE_COLOR << "Member functions start!\n" << RESET_COLOR;
    test_target.lock();
    test_target.try_lock();
    // try_lock_for
    {
      const auto timeout = std::chrono::milliseconds(200);
      test_target.try_lock_for(timeout);
    }
    // try_lock_until
    {
      const auto now     = std::chrono::system_clock::now();
      const auto timeout = now + std::chrono::seconds(10);
      test_target.try_lock_until(timeout);
    }
    test_target.unlock();
    std::cout << PURPLE_COLOR << "Swap start!\n" << RESET_COLOR;
    {
      std::unique_lock<std::timed_mutex> swap_target(test_mutex);
      test_target.swap(swap_target);
    }
    std::cout << PURPLE_COLOR << "Swap done.\n" << RESET_COLOR;
    test_target.release();
    test_target.owns_lock();
    test_target.mutex();
    std::cout << BLUE_COLOR << "Member functions done.\n" << RESET_COLOR;
  }
  SUCCEED();
}

TEST(t2_mutex, condition_variable) {
  SUCCEED();
}