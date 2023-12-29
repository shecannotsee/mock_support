//
// Created by shecannotsee on 23-12-29.
//

#ifndef MOCK_THREAD_H
#define MOCK_THREAD_H

#include "cpp-stub/stub.h"

#include <thread>
#include "class_support.h"
#include "std_thread_support.h"

// The usage is as follows:
//   mock_thread<std::thread, mock::thread> m_thread;
template <typename T1, typename T2>
class mock_thread {
public:
  mock_thread() {
    // ctor
    stub_.set(pthread_create, mock::thread::pthread_create);
    stub_.set(ADDR(std::thread, _M_start_thread), mock::thread::_M_start_thread_mock);
    // dtor
    auto std_thread_d  = mock::get_dtor_addr<T1>();
    auto mock_thread_d = mock::get_dtor_addr<T2>();
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

#endif //MOCK_THREAD_H
