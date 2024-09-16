

#include "s21_set.h"
#include "s21_vector.h"

namespace s21 {

template <typename key>
set<key>::set(const std::initializer_list<key> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    avl_tree<key, key>::insert(*i);
  }
}

template <typename key>
set<key> &set<key>::operator=(set &&other) noexcept {
  if (this != &other) {
    avl_tree<key, key>::operator=(std::move(other));
  }
  return *this;
}

template <typename key>
set<key> &set<key>::operator=(const set &other) {
  if (this != &other) {
    avl_tree<key, key>::operator=(other);
  }
  return *this;
}

template <typename key>
template <class... args>
s21::vector<std::pair<typename avl_tree<key, key>::iter, bool>>
set<key>::insert_many(args &&...args_) {
  s21::vector<std::pair<typename avl_tree<key, key>::iter, bool>> vector_;
  for (const auto &arg : {args_...}) {
    vector_.push_back(avl_tree<key, key>::insert(arg));
  }
  return vector_;
}

}  // namespace s21
