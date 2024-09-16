

#include "s21_multiset.h"
#include "s21_vector.h"

namespace s21 {

template <typename key>
multiset<key> &multiset<key>::operator=(multiset &&other) noexcept {
  if (this != &other) {
    set<key>::operator=(std::move(other));
  }
  return *this;
}

template <typename key>
bool multiset<key>::insert_recursive(
    typename avl_tree<key, key>::tree_node *node, const key &value) {
  bool check_insert = false;
  if (value <= node->key_) {
    if (node->left == nullptr) {
      node->left =
          new typename avl_tree<key, key>::tree_node(value, value, node);
      check_insert = true;
    } else {
      check_insert = insert_recursive(node->left, value);
    }
  } else if (value >= node->key_) {
    if (node->right == nullptr) {
      node->right =
          new typename avl_tree<key, key>::tree_node(value, value, node);
      check_insert = true;
    } else {
      check_insert = insert_recursive(node->right, value);
    }
  } else if (value == node->key_) {
    return check_insert;
  }
  this->set_height(node);
  this->balance(node);
  return check_insert;
}

template <typename key>
std::pair<typename multiset<key>::iter, bool> multiset<key>::insert(
    const key &value) noexcept {
  std::pair<typename set<key>::iter, bool> return_value;
  if (avl_tree<key, key>::root_ == nullptr) {
    avl_tree<key, key>::root_ =
        new typename avl_tree<key, key>::tree_node(value, value);
    return_value.first = typename set<key>::iter(avl_tree<key, key>::root_);
    return_value.second = true;
  } else {
    bool check_insert = insert_recursive(avl_tree<key, key>::root_, value);
    return_value.first = this->find(value);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename key>
template <class... args>
s21::vector<std::pair<typename avl_tree<key, key>::iter, bool>>
multiset<key>::insert_many(args &&...args_) {
  s21::vector<std::pair<typename avl_tree<key, key>::iter, bool>> vector_;
  for (const auto &arg : {args_...}) {
    vector_.push_back(avl_tree<key, key>::insert(arg));
  }
  return vector_;
}

}  // namespace s21
