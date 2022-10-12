#ifndef FIFO_H
#define FIFO_H

// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THIS FILE.

#include <stdio.h>
#include <iostream>
#include <queue>

#include "generic_error.h"

using std::deque;
using std::cout;

////////////////////////////////////////////////////////////
// my_fifo_t


template <class T> class my_fifo_t {
 public:
  void enqueue(T);
  T dequeue();
  T edequeue();

  void tenqueue(int time, T);
  T tdequeue(int time);

  // tdequeue(int *time) always dequeues, setting *time to be the time associated with the element dequeued
  T tdequeue(int *time);

  // compatibility
  void push_front(T);
  void tpush_front(int time, T);

  void push_back(T);
  void pop();
  T front();
  bool space_p();
  int space();
  bool full_p();
  bool empty();
  bool tempty(int time);
  int  size ();
  void print();

  int get_head();
  int get_tail();
  int next(int cur);
  T   sel(int cur);
  void erase(int cur);

  T   sel_offset(int cur);
  void erase_offset(int cur);

  my_fifo_t(char *name, int size);
  my_fifo_t(int size);
  my_fifo_t();
  
  void init(char *name, int size);
  void init(int size);
  void init(char *_name, int size, T empty);
  void init(int size, T empty);
  void init_time(char *_name, int size, T empty);


  inline unsigned int get_max_size() { return max_size; };

 private:
  T *els;
  int *times;
  T empty_value;
  int head;
  int tail;
  unsigned int num;
  unsigned int max_size;
  bool wraparound_p;
  char *name;
};

template <class T> my_fifo_t<T>::my_fifo_t(int size) {
  max_size = size;
  num = 0;
  els = new T [size];
  head = tail = 0;
  name = NULL;
}

// same as constructor
template <class T> my_fifo_t<T>::my_fifo_t(char *_name, int size) {
  max_size = size;
  num = 0;
  els = new T [size];
  head = tail = 0;
  name = _name;
}

// same as constructor
template <class T> void my_fifo_t<T>::init(int size) {
  max_size = size;
  num = 0;
  els = new T [size];
  head = tail = 0;
  name = NULL;
}

// same as constructor
template <class T> void my_fifo_t<T>::init(int size, T empty) {
  max_size = size;
  num = 0;
  els = new T [size];
  head = tail = 0;
  empty_value = empty;
  name = NULL;
}

// same as constructor
template <class T> void my_fifo_t<T>::init(char *_name, int size, T empty) {
  init(size, empty);
  name = _name;
}

// same as constructor
template <class T> void my_fifo_t<T>::init(char *_name, int size) {
  init(size);
  name = _name;
}

// same as constructor
template <class T> void my_fifo_t<T>::init_time(char *_name, int size, T empty) {
  name = _name;
  max_size = size;
  num = 0;
  els = new T [size];
  times = new int [size];
  empty_value = empty;
  head = tail = 0;
}

template <class T> my_fifo_t<T>::my_fifo_t() {
  num = 0;
  max_size = 0;
  els = NULL;
  head = tail = 0;
}

template <class T> void my_fifo_t<T>::print() {
  cout << ":my_fifo_t: num = " << size() << ", max_size = " << max_size << "\n";
}

template <class T>  inline void my_fifo_t<T>::push_back(T value) {
  char *_func_name = (char *)"my_fifo_t::push_back";

  if (num >= max_size) {
    cout << "num = " << num << ", max_size = " << max_size << "\n";
    if (name == NULL) name = (char *)"undefined";
    ERROR_ARGS(("attempting to push into full fifo! (%s)", name));
  } else {
    num++;
    els[tail++] = value;
    tail %= max_size;
  }
}

template <class T>  inline void my_fifo_t<T>::push_front(T value) {
  static char *_func_name = "my_fifo_t::push";

  if (num >= max_size) {
    cout << "num = " << num << ", max_size = " << max_size << "\n";
    ERROR_ARGS(("attempting to push into full fifo (%s)!", name));
  } else {
    num++;
    if (head == 0) {
      head = max_size - 1;
    } else {
      head--;
    }
    els[head] = value;
  }
}

template <class T>  inline void my_fifo_t<T>::tpush_front(int time, T value) {
  static char *_func_name = "my_fifo_t::push";

  if (num >= max_size) {
    cout << "num = " << num << ", max_size = " << max_size << "\n";
    ERROR_ARGS(("attempting to push into full fifo (%s)!", name));
  } else {
    num++;
    if (head == 0) {
      head = max_size - 1;
    } else {
      head--;
    }
    els[head] = value;
    times[head] = time;
  }
}

template <class T>  void my_fifo_t<T>::pop() {
  static char *_func_name = "my_fifo_t::pop";

  if (num == 0) {
    ERROR_ARGS(("attempting to pop empty fifo (%s)", name));
  } else {
    num--;
    head = (head + 1) % max_size;
  }
}

template <class T>  T my_fifo_t<T>::front() {
  static char *_func_name = "my_fifo_t::front";

  if (num == 0) 
    ERROR_ARGS(("front of empty fifo (%s)", name));
  return(els[head]);
}

template <class T> T my_fifo_t<T>::dequeue() {
  static char *_func_name = "my_fifo_t::dequeue";
  T r = els[head];

  if (num == 0) {
    ERROR_ARGS(("attempting to dequeue from empty fifo (%s)", name));
  } else {
    num--;
    head = (head + 1) % max_size;
  }
  return(r);
}

template <class T> T my_fifo_t<T>::edequeue() {
  // static char *_func_name = "my_fifo_t::edequeue";
  T r = els[head];

  if (num == 0) {
    return (empty_value);
  } else {
    num--;
    head = (head + 1) % max_size;
  }
  return(r);
}

// time dequeue
template <class T>  T my_fifo_t<T>::tdequeue(int cur_time) {
  //  static char *_func_name = "my_fifo_t::dequeue";
  if ((num == 0) || (times[head] > cur_time)) {
    return(empty_value);
  } else {
    T r = els[head];
    num--;
    head = (head + 1) % max_size;
    return(r);
  }
}

// *time dequeue
template <class T>  T my_fifo_t<T>::tdequeue(int *time) {
  static char *_func_name = "my_fifo_t::dequeue";
  T r = els[head];
  *time = time[head];
  num--;
  head = (head + 1) % max_size;
  return(r);
}

template <class T>  void my_fifo_t<T>::enqueue(T value) {
  push_back(value);
}

template <class T>  void my_fifo_t<T>::tenqueue(int t, T value) {
  times[tail] = t;
  push_back(value);
}

template <class T> inline bool my_fifo_t<T>::space_p() {
  return (num < max_size);
}

template <class T> inline bool my_fifo_t<T>::full_p() {
  return !(space_p());
}

template <class T> inline bool my_fifo_t<T>::empty() {
  return (num == 0);
}

template <class T> inline bool my_fifo_t<T>::tempty(int cur_time) {
  return ((num == 0) || (times[head] > cur_time));
}

template <class T> inline int my_fifo_t<T>::size() {
  return (num);
}

template <class T> inline int my_fifo_t<T>::space() {
  return (max_size - num);
}

template <class T> inline int my_fifo_t<T>::get_head() {
  wraparound_p = false;
  return (head);
}

template <class T> inline int my_fifo_t<T>::get_tail() {
  if (num == max_size) 
    return(-1);
  else
    return (tail);
}

template <class T> inline int my_fifo_t<T>::next(int cur) {
  if (cur == tail) {
    if (wraparound_p) 
      return(-1);
    else {
      wraparound_p = true;
    }
  }
  return((cur + 1) % max_size);
}

template <class T> inline T my_fifo_t<T>::sel(int cur) { // no error checking
  return(els[cur]);
}

template <class T> inline void my_fifo_t<T>::erase(int cur) { 
  int next = (cur + 1) % max_size;
  while (next != tail) {
    els[cur] = els[next];
    cur = next;
    next = (next + 1) % max_size;
  }
  num--;
  if (tail == 0) 
    tail = (max_size - 1);
  else
    tail--;
}

template <class T> inline T my_fifo_t<T>::sel_offset(int i) { // no error checking
  int cur = (head + i) % max_size;
  return(els[cur]);
}

template <class T> inline void my_fifo_t<T>::erase_offset(int i) { 
  int cur = (i + head) % max_size;
  int next = (cur + 1) % max_size;
  while (next != tail) {
    els[cur] = els[next];
    cur = next;
    next = (next + 1) % max_size;
  }
  num--;
  if (tail == 0) 
    tail = (max_size - 1);
  else
    tail--;
}

typedef my_fifo_t <int> ififo_t;
typedef my_fifo_t <char> cfifo_t;
  
#endif
