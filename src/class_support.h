//
// Created by shecannotsee on 23-12-29.
//
//

#ifndef CLASS_SUPPORT_H
#define CLASS_SUPPORT_H

namespace mock {

template <class T>
void* get_ctor_addr(bool start = true) {
  // the start vairable must be true, or the compiler will optimize out.
  if (start) {
    goto Start;
  }
  Call_Constructor:
    // This line of code will not be executed.
    // The purpose of the code is to allow the compiler to generate the assembly code that calls the constructor.
    T();
  Start:
    // The address of the line of code T() obtained by assembly
    char* p = (char*)&&Call_Constructor;  // https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
  // CALL rel32
  void* ret = 0;
  char pos;
  char call = 0xe8;
  do {
    pos = *p;
    if (pos == call) {
      ret = p + 5 + (*(int*)(p + 1));
    }
  } while (!ret && (++p));

  return ret;
}

template <class T>
void* get_dtor_addr(bool start = true) {
  // the start vairable must be true, or the compiler will optimize out.
  if (start) {
    goto Start;
  }
  // This line of code will not be executed.
  // The purpose of the code is to allow the compiler to generate the assembly code that calls the constructor.
  {
    T();
    Call_dtor:
        ;;
  }
  Start:
    // The address of the line of code T() obtained by assembly
    char* p = (char*)&&Call_dtor;  // https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
  // CALL rel32
  void* ret = 0;
  char pos;
  char call = 0xe8;
  do {
    pos = *p;
    if (pos == call) {
      ret = p + 5 + (*(int*)(p + 1));
    }
  } while (!ret && (--p));
  return ret;
}

}// namespace mock

#endif  // CLASS_SUPPORT_H
