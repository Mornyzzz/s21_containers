#include "s21_list.h"

namespace s21 {

template <typename T>
bool Iterator<T>::operator==(const Iterator<T> &other) {
  return this->ptr_->data_ == other.ptr_->data_;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T> &other) {
  return this->ptr_->data_ != other.ptr_->data_;
}

template <typename T>
Iterator<T> &Iterator<T>::operator++() {
  if (this->ptr_->pNext_ != nullptr) this->ptr_ = this->ptr_->pNext_;
  return *this;
}

template <typename T>
Iterator<T> &Iterator<T>::operator--() {
  if (this->ptr_->pBack_ != nullptr) this->ptr_ = this->ptr_->pBack_;
  return *this;
}

template <typename T>
Iterator<T> &Iterator<T>::operator++(int) {
  this->operator++();
  return *this;
}

template <typename T>
Iterator<T> &Iterator<T>::operator--(int) {
  this->operator--();
  return *this;
}

template <typename T>
List<T>::List(size_type n) : List() {
  while (n--) this->push_back(0);
}

template <typename T>
List<T>::List(const List &other) : List() {
  Node<value_type> *current = other.head_;
  while (current != other.tail_) {
    this->push_back(current->data_);
    current = current->pNext_;
  }
}

template <typename T>
List<T>::List(List &&other) : List<T>(other) {
  if (this->head_ == other.head_)
    throw std::invalid_argument("List argument too large.");
  other.clear();
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items) : List() {
  for (auto &i : items) {
    this->push_back(i);
  }
}

template <typename T>
List<T>::~List() {
  this->clear();
}

template <typename T>
void List<T>::push_back(const_reference value) {
  if (this->head_ == nullptr && this->tail_ == nullptr) {
    this->head_ = new Node<T>(value);
    this->tail_ = new Node<T>;
    this->head_->pNext_ = this->tail_;
    this->tail_->pNext_ = nullptr;
  } else {
    Node<T> *current = this->head_;
    while (current->pNext_ != this->tail_) {
      current = current->pNext_;
    }
    Node<T> *temp = current;
    current->pNext_ = new Node<T>(value);
    current = current->pNext_;
    current->pBack_ = temp;
    this->tail_->pBack_ = current;
    current->pNext_ = this->tail_;
  }
  (this->m_size)++;
}

template <typename T>
void List<T>::push_front(const_reference value) {
  if (this->head_ == nullptr && this->tail_ == nullptr) {
    this->head_ = new Node<value_type>(value, this->head_);
    this->tail_ = new Node<T>;
    this->head_->pNext_ = this->tail_;
    this->tail_->pBack_ = this->head_;
    this->tail_->pNext_ = nullptr;
  } else {
    this->head_ = new Node<value_type>(value, this->head_);
  }
  (this->m_size)++;
}

template <typename T>
void List<T>::pop_back() {
  if (this->head_ == nullptr) {
    return;
  }
  Iterator<T> last = Iterator<T>(this->head_);
  while (last.ptr_->pNext_ != nullptr) {
    ++last;
  }
  this->erase(--last);
}

template <typename T>
void List<T>::pop_front() {
  Node<value_type> *current = this->head_;
  this->head_ = this->head_->pNext_;
  if (current) delete current;
  (this->m_size)--;
}

template <typename T>
T &List<T>::operator[](const int index) {
  int counter = 0;
  Node<value_type> *current = this->head_;
  while (current != nullptr) {
    if (counter == index) {
      return current->data_;
    }
    current = current->pNext_;
    counter++;
  }
  return this->head_->data_;
}

template <typename T>
List<T> &List<T>::operator=(const List &l) {
  if (this->head_) {
    this->clear();
  }
  this->set_copy(l.head_, l.tail_);
  return *this;
}

template <typename T>
void List<T>::set_copy(Node<T> *other, Node<T> *end) {
  if (other != end) {
    this->push_back(other->data_);
    this->set_copy(other->pNext_, end);
  }
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  size_t index = 0;
  Node<T> *current = this->head_;
  for (auto i = this->begin(); i != this->end(); ++i, index++) {
    if (pos == i) break;
  }
  if (index == 0) {
    push_front(value);
  } else {
    for (size_t y = 0; y < index - 1; y++) {
      current = current->pNext_;
    }
    current->pNext_ = new Node<value_type>(value, current->pNext_);
    (this->m_size)++;
  }
  Iterator<T> result;
  result.ptr_ = current->pNext_;
  return result;
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (pos == Iterator<T>(this->head_)) {
    pop_front();
  } else {
    Node<value_type> *current = this->head_;
    while (current->data_ != pos.ptr_->data_) {
      current = current->pNext_;
    }
    Node<value_type> *to_delete = current->pNext_;
    current->pNext_ = to_delete->pNext_;
    if (to_delete != nullptr) delete to_delete;
    (this->m_size)--;
  }
}

template <typename T>
void List<T>::swap(List &other) {
  List<T> temp(*this);
  *this = other;
  other = temp;
}

template <typename T>
void List<T>::reverse() {
  List<T> temp;
  for (auto &&i : *this) {
    temp.push_front(i);
  }
  *this = temp;
}

template <typename T>
void List<T>::sort() {
  List<T> temp_list;
  temp_list = *this;
  T temp;
  for (size_t i = 0; i < this->m_size - 1; i++) {
    for (size_t j = 0; j < this->m_size - i - 1; j++) {
      if (temp_list[j] > temp_list[j + 1]) {
        temp = temp_list[j];
        temp_list[j] = temp_list[j + 1];
        temp_list[j + 1] = temp;
      }
    }
  }
  *this = temp_list;
}

template <typename T>
void List<T>::merge(List &other) {
  this->set_copy(other.head_, other.tail_);
  this->sort();
}

template <typename T>
void List<T>::unique() {
  Node<value_type> *current = this->head_;
  List<T> temp;
  T temp_data = 0;
  while (current != this->tail_) {
    if (temp_data != current->data_) {
      temp.push_back(current->data_);
      temp_data = current->data_;
    }
    current = current->pNext_;
  }
  *this = temp;
}

template <typename T>
void List<T>::splice(const_iterator pos, List other) {
  iterator temp_iter(pos.ptr_);
  for (auto &&i : *this) {
    if (i == *pos) {
      for (auto &&y : other) {
        this->insert(temp_iter, y);
      }
      break;
    }
  }
}

template <typename T>
void List<T>::clear() {
  while (this->m_size) {
    this->pop_front();
  }
  if (this->tail_ != nullptr) {
    if (this->tail_ != nullptr) delete this->tail_;
  }
  this->tail_ = nullptr;
  this->head_ = nullptr;
}

template <typename T>
const T &List<T>::front() {
  return this->head_->data_;
}

template <typename T>
const T &List<T>::back() {
  if (this->head_ == nullptr) {
    return this->head_->data_;
  } else {
    Node<value_type> *current = this->head_;
    while (current->pNext_ != this->tail_) {
      current = current->pNext_;
    }
    return current->data_;
  }
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  Node<T> *pos_node = pos.ptr_;
  Iterator it(pos_node);

  for (const auto &arg : {args...}) {
    insert(it, arg);
  }
  return it;
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_front(arg);
  }
}

}  // namespace s21
