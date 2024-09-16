#pragma once
#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "s21_containers.h"

namespace s21 {

template <typename T>
class Queue : public abstract_container<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue() : abstract_container<T>() {}
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q);
  ~Queue();
  Queue<T> &operator=(Queue &s);

  const_reference front();
  const_reference back();

  void push(const_reference data_);
  void pop();
  void swap(Queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21
#include "s21_queue.tpp"
#endif  // S21_QUEUE_H
