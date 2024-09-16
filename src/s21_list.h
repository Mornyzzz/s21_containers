#pragma once
#ifndef S21_LIST_H
#define S21_LIST_H

#include "s21_containers.h"

namespace s21 {
template <typename T>
class List : public abstract_container<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = Iterator<T>;
  using const_iterator = ConstIterator<T>;
  using size_type = size_t;

  List() : abstract_container<T>(){};
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &other);
  List(List &&other);
  ~List();
  List<T> &operator=(const List &l);
  reference operator[](const int index);

  const_reference front();
  const_reference back();

  iterator begin() { return this->head_; }
  iterator end() { return this->tail_; }

  size_type max_size() { return MAX_SIZE_LIST; }
  void set_copy(Node<T> *other, Node<T> *end);

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos, List other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);
};

}  // namespace s21
#include "s21_list.tpp"
#endif  // S21_LIST_H
