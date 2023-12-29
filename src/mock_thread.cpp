//
// Created by shecannotsee on 23-12-29.
//

#include "mock_thread.h"
#include "cpp-stub/addr_pri.h"

#include <thread>

#include "class_support.h"
#include "std_thread_support.h"

mock_thread::mock_thread() noexcept {
  // ctor
  stub_.set(pthread_create, mock::thread::pthread_create);
  stub_.set(ADDR(std::thread, _M_start_thread), mock::thread::_M_start_thread_mock);
  // dtor
  auto std_thread_d  = mock::get_dtor_addr<std::thread>();
  auto mock_thread_d = mock::get_dtor_addr<mock::thread>();
  stub_.set(std_thread_d, mock_thread_d);
  // join
  stub_.set(ADDR(std::thread, join), mock::thread::join);
  // detach
  stub_.set(ADDR(std::thread, detach), mock::thread::detach);
}
