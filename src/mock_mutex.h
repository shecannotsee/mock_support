//
// Created by shecannotsee on 23-12-29.
//

#ifndef MOCK_MUTEX_H
#define MOCK_MUTEX_H

#include <mutex>

#include "class_support.h"
#include "cpp-stub/stub.h"
#include "std_mutex_support.h"

// The usage is as follows:
//   mock_mutex mock_mutex_turn_on;
class mock_mutex {
 public:
  mock_mutex() {
    // lock
    stub_.set(ADDR(std::mutex, lock), mock::mutex::lock);
    // unlock
    stub_.set(ADDR(std::mutex, unlock), mock::mutex::unlock);
    // try_lock
    stub_.set(ADDR(std::mutex, try_lock), mock::mutex::try_lock);
    // native_handle
    stub_.set(ADDR(std::mutex, native_handle), mock::mutex::native_handle);
  }

  ~mock_mutex() = default;

 private:
  Stub stub_;
};

// The usage is as follows:
//   mock_timed_mutex mock_timed_mutex_turn_on;
class mock_timed_mutex {
 public:
  mock_timed_mutex() {
    // lock
    stub_.set(ADDR(std::timed_mutex, lock), mock::timed_mutex::lock);
    // try_lock
    stub_.set(ADDR(std::timed_mutex, try_lock), mock::timed_mutex::try_lock);
    // try_lock_for
    stub_.set((bool(std::timed_mutex::*)(const std::chrono::milliseconds&))ADDR(std::timed_mutex, try_lock_for),
              mock::timed_mutex::try_lock_for);
    // try_lock_until
    stub_.set(
        (bool(std::timed_mutex::*)(const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>&))
            ADDR(std::timed_mutex, try_lock_until),
        mock::timed_mutex::try_lock_until);
    // unlock
    stub_.set(ADDR(std::timed_mutex, unlock), mock::timed_mutex::unlock);
    // native_handle
    stub_.set(ADDR(std::timed_mutex, native_handle), mock::timed_mutex::native_handle);
  }

  ~mock_timed_mutex() = default;

 private:
  Stub stub_;
};

// The usage is as follows:
//   lock_guard mock_lock_guard_turn_on;
class mock_lock_guard {
 public:
  mock_lock_guard() {
    // mock mutex is complete
    // lock
    stub_.set(ADDR(std::mutex, lock), mock::mutex::lock);
    // unlock
    stub_.set(ADDR(std::mutex, unlock), mock::mutex::unlock);
    // try_lock
    stub_.set(ADDR(std::mutex, try_lock), mock::mutex::try_lock);
    // native_handle
    stub_.set(ADDR(std::mutex, native_handle), mock::mutex::native_handle);
  }

  ~mock_lock_guard() = default;

 private:
  Stub stub_;
};

// The usage is as follows:
//   mock_unique_lock<std::mutex, mock::mutex> mock_unique_lock_turn_on;
// or:
//    mock_unique_lock<std::timed_mutex, mock::timed_mutex> mock_unique_lock_turn_on;
template <typename std_mutex_type, typename mock_mutex_type>
class mock_unique_lock {
 public:
  mock_unique_lock() {
    // type check
    static_assert(
        (std::is_same<std_mutex_type, std::mutex>::value && std::is_same<mock_mutex_type, mock::mutex>::value) ||
            (std::is_same<std_mutex_type, std::timed_mutex>::value &&
             std::is_same<mock_mutex_type, mock::timed_mutex>::value),
        "mock_unique_lock only accepts the following types "
        "mock_unique_lock<std::mutex, mock::mutex> or "
        "mock_unique_lock<std::timed_mutex, mock::timed_mutex>");

    if (std::is_same<std_mutex_type, std::mutex>::value) {
      // mock mutex
      // lock
      stub_.set(ADDR(std::mutex, lock), mock::mutex::lock);
      // unlock
      stub_.set(ADDR(std::mutex, unlock), mock::mutex::unlock);
      // try_lock
      stub_.set(ADDR(std::mutex, try_lock), mock::mutex::try_lock);
      // native_handle
      stub_.set(ADDR(std::mutex, native_handle), mock::mutex::native_handle);

      // unique_lock
      // lock
      stub_.set(ADDR(std::unique_lock<std::mutex>, lock), mock::unique_lock<std::mutex>::lock);
      // try_lock
      stub_.set(ADDR(std::unique_lock<std::mutex>, try_lock), mock::unique_lock<std::mutex>::try_lock);
      // try_lock_until: Not supported, because std::mutex doesn't have a member function try_lock_until
      // try_lock_for: Not supported, because std::mutex doesn't have a member function try_lock_for
      // unlock
      stub_.set(ADDR(std::unique_lock<std::mutex>, unlock), mock::unique_lock<std::mutex>::unlock);
      // swap
      stub_.set(ADDR(std::unique_lock<std::mutex>, swap), mock::unique_lock<std::mutex>::swap);
      // release
      stub_.set(ADDR(std::unique_lock<std::mutex>, release), mock::unique_lock<std::mutex>::release);
      // owns_lock
      stub_.set(ADDR(std::unique_lock<std::mutex>, owns_lock), mock::unique_lock<std::mutex>::owns_lock);
      // mutex
      stub_.set(ADDR(std::unique_lock<std::mutex>, mutex), mock::unique_lock<std::mutex>::mutex);

    } else if (std::is_same<std_mutex_type, std::timed_mutex>::value) {
      // mock timed_mutex
      // lock
      stub_.set(ADDR(std::timed_mutex, lock), mock::timed_mutex::lock);
      // try_lock
      stub_.set(ADDR(std::timed_mutex, try_lock), mock::timed_mutex::try_lock);
      // try_lock_for
      stub_.set((bool(std::timed_mutex::*)(const std::chrono::milliseconds&))ADDR(std::timed_mutex, try_lock_for),
                mock::timed_mutex::try_lock_for);
      // try_lock_until
      stub_.set((bool(std::timed_mutex::*)(
                    const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>&))
                    ADDR(std::timed_mutex, try_lock_until),
                mock::timed_mutex::try_lock_until);
      // unlock
      stub_.set(ADDR(std::timed_mutex, unlock), mock::timed_mutex::unlock);
      // native_handle
      stub_.set(ADDR(std::timed_mutex, native_handle), mock::timed_mutex::native_handle);

      // unique_lock
      // lock
      stub_.set(ADDR(std::unique_lock<std::timed_mutex>, lock), mock::unique_lock<std::timed_mutex>::lock);
      // try_lock
      stub_.set(ADDR(std::unique_lock<std::timed_mutex>, try_lock), mock::unique_lock<std::timed_mutex>::try_lock);
      // try_lock_until
      stub_.set((bool(std::unique_lock<std::timed_mutex>::*)(
                    const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>&))
                    ADDR(std::unique_lock<std::timed_mutex>, try_lock_until),
                mock::unique_lock<std::timed_mutex>::try_lock_until);
      // try_lock_for
      stub_.set((bool(std::unique_lock<std::timed_mutex>::*)(const std::chrono::milliseconds&))ADDR(
                    std::unique_lock<std::timed_mutex>, try_lock_for),
                mock::unique_lock<std::timed_mutex>::try_lock_for);
      // unlock
      stub_.set(ADDR(std::unique_lock<std::timed_mutex>, unlock), mock::unique_lock<std::timed_mutex>::unlock);
      // swap
      stub_.set(ADDR(std::unique_lock<std::timed_mutex>, swap), mock::unique_lock<std::timed_mutex>::swap);
      // release
      stub_.set(ADDR(std::unique_lock<std::timed_mutex>, release), mock::unique_lock<std::timed_mutex>::release);
      // owns_lock
      stub_.set(ADDR(std::unique_lock<std::timed_mutex>, owns_lock), mock::unique_lock<std::timed_mutex>::owns_lock);
      // mutex
      stub_.set(ADDR(std::unique_lock<std::timed_mutex>, mutex), mock::unique_lock<std::timed_mutex>::mutex);
    }
  }

  ~mock_unique_lock() = default;

 private:
  Stub stub_;
};

// The usage is as follows:
//   mock_condition_variable mock_condition_variable_turn_on;
class mock_condition_variable {
 public:
  mock_condition_variable() {
    // notify_one
    stub_.set(ADDR(std::condition_variable, notify_one), mock::condition_variable::notify_one);
    // notify_all
    stub_.set(ADDR(std::condition_variable, notify_all), mock::condition_variable::notify_all);
    // wait
    stub_.set((void(std::condition_variable::*)(std::unique_lock<std::mutex>&))ADDR(std::condition_variable, wait),
              mock::condition_variable::wait);

    stub_.set((void(std::condition_variable::*)(std::unique_lock<std::mutex>&, std::function<bool()>))ADDR(
                  std::condition_variable, wait),
              mock::condition_variable::wait_mutex_f);
    // wait_until
    stub_.set((std::cv_status(std::condition_variable::*)(
                  std::unique_lock<std::mutex>&,
                  const std::chrono::time_point<std::chrono::system_clock>&))ADDR(std::condition_variable, wait_until),
              mock::condition_variable::wait_until_t1);
    stub_.set((std::cv_status(std::condition_variable::*)(
                  std::unique_lock<std::mutex>&,
                  const std::chrono::time_point<std::chrono::steady_clock>&))ADDR(std::condition_variable, wait_until),
              mock::condition_variable::wait_until_t2);
    stub_.set((bool(std::condition_variable::*)(std::unique_lock<std::mutex>&,
                                                const std::chrono::time_point<std::chrono::system_clock>&,
                                                std::function<bool()>))ADDR(std::condition_variable, wait_until),
              mock::condition_variable::wait_until_t3_system_clock);
    stub_.set((bool(std::condition_variable::*)(std::unique_lock<std::mutex>&,
                                                const std::chrono::time_point<std::chrono::steady_clock>&,
                                                std::function<bool()>))ADDR(std::condition_variable, wait_until),
              mock::condition_variable::wait_until_t3_steady_clock);
    // wait_for
    stub_.set((std::cv_status(std::condition_variable::*)(
                  std::unique_lock<std::mutex>&,
                  const std::chrono::duration<int64_t, std::milli>&))ADDR(std::condition_variable, wait_for),
              mock::condition_variable::wait_for_t2);
    stub_.set((bool(std::condition_variable::*)(std::unique_lock<std::mutex>&,
                                                const std::chrono::duration<int64_t, std::milli>&,
                                                std::function<bool()>))ADDR(std::condition_variable, wait_for),
              mock::condition_variable::wait_for_t3);
    // native_handle
    stub_.set(ADDR(std::condition_variable, native_handle), mock::condition_variable::native_handle);
  }

  ~mock_condition_variable() = default;

 private:
  Stub stub_;
};

#endif  // MOCK_MUTEX_H
