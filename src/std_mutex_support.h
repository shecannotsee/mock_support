//
// Created by shecannotsee on 23-12-29.
//

#ifndef STD_MUTEX_SUPPORT_H
#define STD_MUTEX_SUPPORT_H

#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>

namespace mock {

constexpr bool start_mock_print_mutex = true;

class mutex /* : private mutex_base */ {
 public:
  typedef struct pthread_internal_list {
    struct pthread_internal_list* __prev;
    struct pthread_internal_list* __next;
  } pthread_list_t;
  struct pthread_mutex_s {
    int __lock;
    unsigned int __count;
    int __owner;
#ifdef __x86_64__
    unsigned int __nusers;
#endif
    /* KIND must stay at this position in the structure to maintain
       binary compatibility with static initializers.  */
    int __kind;
#ifdef __x86_64__
    short __spins;
    short __elision;
    pthread_list_t __list;
#define __PTHREAD_MUTEX_HAVE_PREV 1
#else
    unsigned int __nusers;
    __extension__ union {
      struct {
        short __espins;
        short __eelision;
#define __spins __elision_data.__espins
#define __elision __elision_data.__eelision
      } __elision_data;
      __pthread_slist_t __list;
    };
#define __PTHREAD_MUTEX_HAVE_PREV 0
#endif
  };
  typedef union {
    struct pthread_mutex_s __data;
    char __size[40];
    long int __align;
  } pthread_mutex_t;
  typedef pthread_mutex_t gthread_mutex_t;
  typedef gthread_mutex_t native_type;
  typedef native_type* native_handle_type;

 public:
  mutex() {
    if (start_mock_print_mutex) {
      printf("mock std::mutex::mutex() success!\n");
    }
  }
  ~mutex() {
    if (start_mock_print_mutex) {
      printf("mock std::mutex::~mutex() success!\n");
    }
  }

  mutex(const mutex&)            = delete;
  mutex& operator=(const mutex&) = delete;

  static void lock() {
    if (start_mock_print_mutex) {
      printf("mock std::mutex::lock() success!\n");
    }
  }

  static bool try_lock() {
    if (start_mock_print_mutex) {
      printf("mock std::mutex::try_lock()->bool success!\n");
    }
  }

  static void unlock() {
    if (start_mock_print_mutex) {
      printf("mock std::mutex::unlock() success!\n");
    }
  }

  static native_handle_type native_handle() {
    if (start_mock_print_mutex) {
      printf("mock std::mutex::native_handle() success!\n");
    }
    return nullptr;
  }
};  // class mutex

class timed_mutex {
 public:
  timed_mutex() {
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::timed_mutex() success!\n");
    }
  }
  ~timed_mutex() {
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::~timed_mutex() success!\n");
    }
  }

  timed_mutex(const timed_mutex&)            = delete;
  timed_mutex& operator=(const timed_mutex&) = delete;

  static void lock() {
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::lock() success!\n");
    }
  }

  static bool try_lock() {
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::try_lock()->bool success!\n");
    }
    return true;
  }

  static bool try_lock_for(void* obj, const std::chrono::milliseconds&) {
    ::mock::timed_mutex* o = (::mock::timed_mutex*)obj;
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::try_lock_for()->bool success!\n");
    }
    return true;
  }

  static bool try_lock_until(void* obj,
                             const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>&) {
    ::mock::timed_mutex* o = (::mock::timed_mutex*)obj;
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::try_lock_until()->bool success!\n");
    }
    return true;
  }

  static void unlock() {
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::unlock() success!\n");
    }
  }

  static ::mock::mutex::native_handle_type native_handle() noexcept {
    if (start_mock_print_mutex) {
      printf("mock std::timed_mutex::native_handle() success!\n");
    }
    return nullptr;
  }
};

template <typename mutex_type>
class unique_lock {
 private:
  struct defer_lock_t {
    explicit defer_lock_t() = default;
  };
  struct try_to_lock_t {
    explicit try_to_lock_t() = default;
  };
  struct adopt_lock_t {
    explicit adopt_lock_t() = default;
  };
  template <typename _Tp>
  inline _GLIBCXX_CONSTEXPR _Tp* addressof(_Tp& __r) _GLIBCXX_NOEXCEPT {
    return __builtin_addressof(__r);
  }

 public:
  unique_lock() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::unique_lock() success!\n");
    }
  }

  explicit unique_lock(mutex_type& m) {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::unique_lock(mutex_type& m) success!\n");
    }
  }

  unique_lock(mutex_type& __m, defer_lock_t) {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::unique_lock(mutex_type& __m, defer_lock_t) success!\n");
    }
  }

  unique_lock(mutex_type& m, try_to_lock_t) {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::unique_lock(mutex_type& m, try_to_lock_t) success!\n");
    }
  }

  unique_lock(mutex_type& m, adopt_lock_t) {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::unique_lock(mutex_type& m, adopt_lock_t) success!\n");
    }
  }

  template <typename _Clock, typename _Duration>
  unique_lock(mutex_type& m, const std::chrono::time_point<_Clock, _Duration>& atime) {
    if (start_mock_print_mutex) {
      printf(
          "mock std::unique_lock::unique_lock(mutex_type& m, const std::chrono::time_point<_Clock, _Duration>& atime) "
          "success!\n");
    }
  }

  template <typename _Rep, typename _Period>
  unique_lock(mutex_type& m, const std::chrono::duration<_Rep, _Period>& rtime) {
    if (start_mock_print_mutex) {
      printf(
          "mock std::unique_lock::unique_lock(mutex_type& m, const std::chrono::duration<_Rep, _Period>& rtime) "
          "success!\n");
    }
  }

  ~unique_lock() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::~unique_lock() success!\n");
    }
  }

  unique_lock(const unique_lock&)            = delete;
  unique_lock& operator=(const unique_lock&) = delete;

  unique_lock(unique_lock&& __u) noexcept {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::ctor::move success!\n");
    }
  }

  unique_lock& operator=(unique_lock&& __u) noexcept {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::=::movce success!\n");
    }
    return *this;
  }

  static void lock() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::lock success!\n");
    }
  }

  static bool try_lock() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::try_lock success!\n");
    }
    return true;
  }

  static bool try_lock_for(void* obj, const std::chrono::milliseconds&) {
    ::mock::unique_lock<std::timed_mutex>* o = (::mock::unique_lock<std::timed_mutex>*)obj;
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::try_lock_for()->bool success!\n");
    }
    return true;
  }

  static bool try_lock_until(void* obj,
                             const std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>&) {
    ::mock::unique_lock<std::timed_mutex>* o = (::mock::unique_lock<std::timed_mutex>*)obj;
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::try_lock_until()->bool success!\n");
    }
    return true;
  }

  static void unlock() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::unlock() success!\n");
    }
  }

  static void swap(unique_lock& u) noexcept {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::swap(...) success!\n");
    }
  }

  static mutex_type* release() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::release() success!\n");
    }
    return nullptr;
  }

  static bool owns_lock() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::owns_lock() success!\n");
    }
    return true;
  }

  explicit operator bool() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::operator bool() success!\n");
    }
    return true;
  }

  static mutex_type* mutex() {
    if (start_mock_print_mutex) {
      printf("mock std::unique_lock::mutex() success!\n");
    }
    return nullptr;
  }
};  // class unique_lock

class condition_variable {
 public:
  condition_variable() {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::condition_variable() success!\n");
    }
  }
  ~condition_variable() {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::~condition_variable() success!\n");
    }
  }

  condition_variable(const condition_variable&)            = delete;
  condition_variable& operator=(const condition_variable&) = delete;

  static void notify_one() {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::notify_one() success!\n");
    }
  }

  static void notify_all() {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::notify_all() success!\n");
    }
  }

  static void wait(void* obj, std::unique_lock<std::mutex>& lock) {
    ::mock::condition_variable* o = (::mock::condition_variable*)obj;
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait(unique_lock<mutex>) success!\n");
    }
  }
  static void wait_mutex_f(void* obj, std::unique_lock<std::mutex>& lock, std::function<bool()> p) {
    ::mock::condition_variable* o = (::mock::condition_variable*)obj;
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait(unique_lock<mutex>, function) success!\n");
    }
  }

  template <typename Duration>
  static std::cv_status wait_until(std::unique_lock<std::mutex>& lock,
                                   const std::chrono::time_point<__clock_t, Duration>& atime) {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait_until(...1) success!\n");
    }
    return std::cv_status::timeout;
    return std::cv_status::no_timeout;
  }

  template <typename Clock, typename Duration>
  static std::cv_status wait_until(std::unique_lock<std::mutex>& lock,
                                   const std::chrono::time_point<Clock, Duration>& atime) {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait_until(...2) success!\n");
    }
    return std::cv_status::timeout;
    return std::cv_status::no_timeout;
  }

  template <typename Clock, typename Duration, typename Predicate>
  static bool wait_until(std::unique_lock<std::mutex>& lock,
                         const std::chrono::time_point<Clock, Duration>& atime,
                         Predicate p) {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait_until(...3) success!\n");
    }
    return true;
  }

  template <typename Rep, typename Period>
  static std::cv_status wait_for(std::unique_lock<std::mutex>& lock, const std::chrono::duration<Rep, Period>& rtime) {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait_for(...1) success!\n");
    }
    return std::cv_status::timeout;
    return std::cv_status::no_timeout;
  }

  template <typename Rep, typename Period, typename Predicate>
  static bool wait_for(std::unique_lock<std::mutex>& lock,
                       const std::chrono::duration<Rep, Period>& rtime,
                       Predicate p) {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait_for(...2) success!\n");
    }
    return true;
  }

  static ::mock::mutex::native_handle_type native_handle() {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::native_handle() success!\n");
    }
    return nullptr;
  }

 private:
  template <typename Dur>
  static std::cv_status wait_until_impl(unique_lock<mutex>& lock,
                                        const std::chrono::time_point<__clock_t, Dur>& atime) {
    if (start_mock_print_mutex) {
      printf("mock std::condition_variable::wait_until_impl(...) success!\n");
    }
    return std::cv_status::timeout;
    return std::cv_status::no_timeout;
  }
};

}  // namespace mock

#endif  // STD_MUTEX_SUPPORT_H
