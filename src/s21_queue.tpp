#include "s21_queue.h"

namespace s21 {
template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const &items) : Queue() {
  for (auto &i : items) {
    this->push(i);
  }
}

template <typename T>
Queue<T>::Queue(const Queue &q) : Queue() {
  Node<value_type> *current = q.head_;
  while (current != nullptr) {
    this->push(current->data_);
    current = current->pNext_;
  }
}

template <typename T>
Queue<T>::Queue(Queue &&q) : Queue<T>(q) {
  if (this->head_ == q.head_)
    throw std::invalid_argument("Queue argument too large.");
  q.~Queue();
}

template <typename T>
Queue<T>::~Queue() {
  while (this->m_size) {
    this->pop();
  }
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue &q) {
  if (this->head_) {
    this->~Queue();
  }
  Node<value_type> *current = q.head_;
  while (current != nullptr) {
    this->push(current->data_);
    current = current->pNext_;
  }
  return *this;
}

template <typename T>
const T &Queue<T>::front() {
  return this->head_->data_;
}

template <typename T>
const T &Queue<T>::back() {
  if (this->head_ == nullptr) {
    return this->head_->data_;
  } else {
    Node<value_type> *current = this->head_;
    while (current->pNext_ != nullptr) {
      current = current->pNext_;
    }
    return current->data_;
  }
}

template <typename T>
void Queue<T>::push(const_reference data_) {
  if (this->head_ == nullptr) {
    this->head_ = new Node<value_type>(data_);
  } else {
    Node<value_type> *current = this->head_;
    while (current->pNext_ != nullptr) {
      current = current->pNext_;
    }
    current->pNext_ = new Node<value_type>(data_);
  }
  (this->m_size)++;
}

template <typename T>
void Queue<T>::pop() {
  Node<value_type> *current = this->head_;
  this->head_ = this->head_->pNext_;
  if (current != nullptr) delete current;
  (this->m_size)--;
}

template <typename T>
void Queue<T>::swap(Queue &other) {
  Queue<T> temp(*this);
  *this = other;
  other = temp;
}

template <typename T>
template <typename... Args>
void Queue<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}
}  // namespace s21
