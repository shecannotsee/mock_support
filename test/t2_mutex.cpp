//
// Created by shecannotsee on 23-12-29.
//
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "global_test_set.h"

TEST(t2_mutex, mutex) {

  // code from: https://zh.cppreference.com/w/cpp/thread/mutex
  static std::map<std::string, std::string> g_pages;
  static std::mutex g_pages_mutex;

  auto save_page = [&](const std::string &url) {
    // 模拟长页面读取
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
  };

  std::thread t1(save_page, "http://foo");
  std::thread t2(save_page, "http://bar");
  t1.join();
  t2.join();

  // 现在访问g_pages是安全的，因为线程t1/t2生命周期已结束
  for (const auto &pair : g_pages) {
    std::cout << pair.first << " => " << pair.second << '\n';
  }
}

TEST(t2_mutex, condition_variable) {
  // code from: https://zh.cppreference.com/w/cpp/thread/condition_variable
  static std::mutex m;
  static std::condition_variable cv;
  static std::string data;
  static bool ready     = false;
  static bool processed = false;

  auto worker_thread = [&]() {
    // 等待直至 main() 发送数据
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return ready; });

    // 等待后，我们占有锁。
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // 发送数据回 main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
    // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
    lk.unlock();
    cv.notify_one();
  };

  std::thread worker(worker_thread);

  data = "Example data";
  // 发送数据到 worker 线程
  {
    std::lock_guard<std::mutex> lk(m);
    ready = true;
    std::cout << "main() signals data ready for processing\n";
  }
  cv.notify_one();

  // 等候 worker
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return processed;});
  }
  std::cout << "Back in main(), data = " << data << '\n';

  worker.join();
}