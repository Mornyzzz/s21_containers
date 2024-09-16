#include "s21_queue.h"
#include "s21_stack.h"

namespace s21 {
template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items) : Stack() {
  for (auto &i : items) this->push(i);
}

template <typename T>
Stack<T>::Stack(const Stack &s) : Stack() {
  Node<value_type> *current = s.head_;
  Stack<value_type> temp;
  while (current != nullptr) {
    temp.push(current->data_);
    current = current->pNext_;
  }
  while (!temp.empty()) {
    this->push(temp.top());
    temp.pop();
  }
}

template <typename T>
Stack<T>::Stack(Stack &&s) : Stack<T>(s) {
  if (this->head_ == s.head_)
    throw std::invalid_argument("Stack argument too large.");
  s.~Stack();
}

template <typename T>
Stack<T>::~Stack() {
  while (this->m_size) {
    this->pop();
  }
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack &s) {
  if (this->head_) {
    this->~Stack();
  }
  Node<value_type> *current = s.head_;
  Stack<value_type> temp;
  while (current != nullptr) {
    temp.push(current->data_);
    current = current->pNext_;
  }
  while (!temp.empty()) {
    this->push(temp.top());
    temp.pop();
  }
  return *this;
}

template <typename T>
const T &Stack<T>::top() {
  return this->head_->data_;
}

template <typename T>
void Stack<T>::push(const_reference data_) {
  this->head_ = new Node<value_type>(data_, this->head_);
  (this->m_size)++;
}

template <typename T>
void Stack<T>::pop() {
  Node<value_type> *current = this->head_;
  this->head_ = this->head_->pNext_;
  if (current != nullptr) delete current;
  (this->m_size)--;
}

template <typename T>
void Stack<T>::swap(Stack &other) {
  Stack<T> temp(*this);
  *this = other;
  other = temp;
}

template <typename T>
template <typename... Args>
void Stack<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

}  // namespace s21
