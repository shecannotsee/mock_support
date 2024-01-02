//
// Created by shecannotsee on 23-12-29.
//

#ifndef MOCK_THREAD_H
#define MOCK_THREAD_H

#include <thread>

#include "class_support.h"
#include "cpp-stub/stub.h"
#include "std_thread_support.h"

// The usage is as follows:
//   mock_thread<std::thread, mock::thread> m_thread;
template <typename std_thread_type, typename mock_thread_type>
class mock_thread {
 public:
  mock_thread() {
    // type check
    static_assert(
        std::is_same<std_thread_type, std::thread>::value || std::is_same<mock_thread_type, mock::thread>::value,
        "mock_thread only accepts the following types mock_thread<std::thread, mock::thread>");
    // ctor
    stub_.set(pthread_create, mock::thread::pthread_create);
    stub_.set(ADDR(std::thread, _M_start_thread), mock::thread::_M_start_thread_mock);
    // dtor
    auto std_thread_d  = mock::get_dtor_addr<std_thread_type>();
    auto mock_thread_d = mock::get_dtor_addr<mock_thread_type>();
    stub_.set(std_thread_d, mock_thread_d);
    // join
    stub_.set(ADDR(std::thread, join), mock::thread::join);
    // detach
    stub_.set(ADDR(std::thread, detach), mock::thread::detach);
  }

  ~mock_thread() = default;

 private:
  Stub stub_;
};

#endif  // MOCK_THREAD_H
