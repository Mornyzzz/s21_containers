#pragma once
#ifndef S21_STACK_H
#define S21_STACK_H

#include "s21_containers.h"

namespace s21 {
template <typename T>
class Stack : public abstract_container<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack() : abstract_container<T>() {}
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  Stack<T> &operator=(Stack &s);

  const_reference top();

  void push(const_reference data_);
  void pop();
  void swap(Stack &other);

  template <typename... Args>
  void insert_many_front(Args &&...args);
};
}  // namespace s21
#include "s21_stack.tpp"
#endif  // S21_STACK_H
