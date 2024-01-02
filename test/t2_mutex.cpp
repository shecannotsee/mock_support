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
  using mutex_type = std::mutex;
  mock_condition_variable mock_condition_variable_turn_on;
  std::condition_variable cv;
  mutex_type test_mutex;
  std::unique_lock<mutex_type> test_u_l(test_mutex);
  {
    std::cout << BLUE_COLOR << "Member functions start!\n" << RESET_COLOR;
    cv.notify_one();
    cv.notify_all();
    // wait
    {
      // p1
      cv.wait(test_u_l);
      // p2
      const std::function<bool()> function = [] {
        std::cout << RED_COLOR << "Mock failed\n" << RESET_COLOR;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return false;
      };
      cv.wait(test_u_l, function);
    }
    // wait_until
    {
      std::cout << PURPLE_COLOR << "wait_until\n" << RESET_COLOR;
      // t1
      {
        auto timeout = std::chrono::system_clock::now() + std::chrono::milliseconds(200);
        auto ret     = cv.wait_until(test_u_l, timeout);
        EXPECT_EQ(ret, std::cv_status::timeout);
      }
      // t2
      {
        auto timeout = std::chrono::steady_clock::now() + std::chrono::seconds(1);
        cv.wait_until(test_u_l, timeout);
      }
      // t3: system_clock
      {
        std::function<bool()> check_function = []() {
          std::cout << RED_COLOR << "Mock failed\n" << RESET_COLOR;
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
          return false;
        };
        auto timeout = std::chrono::system_clock::now() + std::chrono::seconds(5);
        cv.wait_until(test_u_l, timeout, check_function);
      }
      // t3: steady_clock
      {
        std::function<bool()> check_function = []() {
          std::cout << RED_COLOR << "Mock failed\n" << RESET_COLOR;
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
          return false;
        };
        auto timeout = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        cv.wait_until(test_u_l, timeout, check_function);
      }
    }
    // wait_for
    {
      std::cout << PURPLE_COLOR << "wait_for\n" << RESET_COLOR;
      // t2
      { cv.wait_for(test_u_l, std::chrono::milliseconds(200)); }
      // t3
      {
        const std::function<bool()> function = [] {
          std::cout << RED_COLOR << "Mock failed\n" << RESET_COLOR;
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
          return false;
        };
        cv.wait_for(test_u_l, std::chrono::milliseconds(200), function);
      }
    }
    cv.native_handle();
    std::cout << BLUE_COLOR << "Member functions done.\n" << RESET_COLOR;
  }
  SUCCEED();
}
