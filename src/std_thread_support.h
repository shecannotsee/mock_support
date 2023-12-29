//
// Created by shecannotsee on 23-12-29.
//

#ifndef STD_THREAD_SUPPORT_H
#define STD_THREAD_SUPPORT_H
#include <thread>

namespace mock {

class thread {
 private:
  // c++ 14 add remove_cvref
  template <typename T>
  struct remove_cvref {
    typedef typename std::remove_reference<T>::type type;
  };
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 2097.  packaged_task constructors should be constrained
  // 3039. Unnecessary decay in thread and packaged_task
  template <typename Tp>
  using not_same = std::__not_<std::is_same<remove_cvref<Tp>, thread>>;  // c++ 14 can use std::remove_cvref

 public:
  thread() {
    printf("thread_mock_c success!(default)\n");
  }

  template <typename Callable, typename... Args, typename = std::_Require<not_same<Callable>>>
  explicit thread(Callable &&f, Args &&...args) {
    printf("thread_mock_c success!(function)\n");
  }

  ~thread() {
    printf("thread_mock_d success!\n");
  }

  static void join() {
  }

  static void detach() {
  }

  static int pthread_create_mock(pthread_t *__restrict __newthread,
                                 const pthread_attr_t *__restrict __attr,
                                 void *(*__start_routine)(void *),
                                 void *__restrict __arg) {
    static int ret = 1;
    return ret;
  }

  static void _M_start_thread_mock(std::unique_ptr<std::thread::_State>, void (*)()) {
  }

};  // class thread_mock

}  // namespace mock

#endif  // STD_THREAD_SUPPORT_H
