//
// Created by shecannotsee on 23-12-29.
//

#ifndef MOCK_THREAD_H
#define MOCK_THREAD_H

#include "cpp-stub/stub.h"

class mock_thread {
public:
  mock_thread() noexcept;
  ~mock_thread() = default;
private:
  Stub stub_;
};

#endif //MOCK_THREAD_H
