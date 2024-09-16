#pragma once
#ifndef s21_ABSTRACT_CLASS_H
#define s21_ABSTRACT_CLASS_H
#define MAX_SIZE_LIST 384307168202282325

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {

template <typename T>
class Node {
 public:
  Node *pNext_;
  Node *pBack_;
  T data_;
  explicit Node(T data_ = T(), Node *pNext_ = nullptr, Node *pBack_ = nullptr) {
    this->data_ = data_;
    this->pNext_ = pNext_;
    this->pBack_ = pBack_;
  }
};

template <typename T>
class ConstIterator {
 public:
  Node<T> *ptr_;
  ConstIterator() : ptr_(0) {}
  ConstIterator(Node<T> *curr) : ptr_(curr) {}
  T &operator*() { return this->ptr_->data_; }
};

template <typename T>
class Iterator : public ConstIterator<T> {
 public:
  Iterator() : ConstIterator<T>() {}
  Iterator(Node<T> *curr) : ConstIterator<T>(curr) {}
  bool operator==(const Iterator &other);
  bool operator!=(const Iterator &other);
  Iterator &operator++();
  Iterator &operator++(int);
  Iterator &operator--();
  Iterator &operator--(int);
};

template <typename T>
class abstract_container {
 protected:
  size_t m_size;
  Node<T> *head_;
  Node<T> *tail_;

 public:
  abstract_container() : m_size(0), head_(nullptr), tail_(nullptr) {}
  size_t max_size() { return std::numeric_limits<size_t>::max() / (sizeof(T)); }
  bool empty() { return this->m_size <= 0; }
  size_t get_size() { return this->m_size; }
};

}  // namespace s21

#endif  // s21_ABSTRACT_CLASS_H
