//
// Created by shecannotsee on 23-12-29.
//

#ifndef MOCK_MUTEX_H
#define MOCK_MUTEX_H

#include "class_support.h"
#include "cpp-stub/stub.h"
#include "std_mutex_support.h"

// The usage is as follows:
//   mock_mutex<std::mutex, mock::mutex> m_mutex;
template <typename T1, typename T2>
class mock_mutex {
 public:
  mock_mutex() {
    // ctor
    // dtor
    auto std_mutex_d  = mock::get_dtor_addr<T1>();
    auto mock_mutex_d = mock::get_dtor_addr<T2>();
    stub_.set(std_mutex_d, mock_mutex_d);
    // lock
    stub_.set(ADDR(std::mutex, lock), mock::mutex::lock);
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
//   mock_condition_variable<std::condition_variable, mock::condition_variable> m_condition_variable;
template <typename T1, typename T2>
class mock_condition_variable {
 public:
  mock_condition_variable() {
    // ctor
    auto std_cv_ctor  = mock::get_ctor_addr<T1>();
    auto mock_cv_ctor = mock::get_ctor_addr<T2>();
    stub_.set(std_cv_ctor, mock_cv_ctor);
    // dtor
    auto std_cv_d  = mock::get_dtor_addr<T1>();
    auto mock_cv_d = mock::get_dtor_addr<T2>();
    stub_.set(std_cv_d, mock_cv_d);
    // notify_one
    stub_.set(ADDR(std::condition_variable, notify_one), mock::condition_variable::notify_one);
    // notify_all
    stub_.set(ADDR(std::condition_variable, notify_all), mock::condition_variable::notify_all);
    // wait
    stub_.set((void(std::condition_variable::*)(mock::condition_variable))ADDR(std::condition_variable, wait),
              mock::condition_variable::wait);

    // native_handle
    stub_.set(ADDR(std::condition_variable, native_handle), mock::condition_variable::native_handle);
  }

  ~mock_condition_variable() = default;

 private:
  Stub stub_;
};

#endif  // MOCK_MUTEX_H
