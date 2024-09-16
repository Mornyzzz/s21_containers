

#include <sys/sysctl.h>
#include <sys/types.h>

#include "s21_avl_tree.h"

template <typename key, typename value>
avl_tree<key, value>::avl_tree() : root_(nullptr) {}

template <typename key, typename value>
avl_tree<key, value>::avl_tree(const avl_tree &other) {
  root_ = copy_tree(other.root_, nullptr);
}

template <typename key, typename value>
avl_tree<key, value>::avl_tree(avl_tree &&other) noexcept {
  root_ = other.root_;
  other.root_ = nullptr;
}

template <typename key, typename value>
avl_tree<key, value>::~avl_tree() {
  clear();
}

template <typename key, typename value>
avl_tree<key, value> &avl_tree<key, value>::operator=(
    avl_tree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename key, typename value>
avl_tree<key, value> &avl_tree<key, value>::operator=(const avl_tree &other) {
  if (this != &other) {
    avl_tree temp(other);
    free_node(root_);
    *this = std::move(temp);
  }
  return *this;
}

template <typename key, typename value>
typename avl_tree<key, value>::iter avl_tree<key, value>::begin() {
  return avl_tree::iter(get_min(root_));
}

template <typename key, typename value>
typename avl_tree<key, value>::iter avl_tree<key, value>::end() {
  iter result;
  if (root_ == nullptr)
    result = begin();
  else {
    tree_node *last_node = get_max(root_);
    iter test(nullptr, last_node);
    result = test;
  }
  return result;
}

template <typename key, typename value>
bool avl_tree<key, value>::empty() {
  return root_ == nullptr;
}

template <typename key, typename value>
size_t avl_tree<key, value>::size() {
  return size_recursive(root_);
}

template <typename key, typename value>
size_t avl_tree<key, value>::max_size() {
  return std::numeric_limits<size_t>::max() /
         sizeof(typename avl_tree<key, value>::tree_node);
}

template <typename key, typename value>
void avl_tree<key, value>::clear() {
  if (root_ != nullptr) free_node(root_);
  root_ = nullptr;
}

template <typename key, typename value>
std::pair<typename avl_tree<key, value>::iter, bool>
avl_tree<key, value>::insert(const key &tree_key) {
  std::pair<iter, bool> return_value;
  if (root_ == nullptr) {
    root_ = new tree_node(tree_key, tree_key);
    return_value.first = iter(root_);
    return_value.second = true;
  } else {
    bool check_insert = insert_recursive(root_, tree_key, tree_key);
    return_value.first = find(tree_key);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename key, typename value>
void avl_tree<key, value>::erase(iter pos) {
  if (root_ != nullptr && pos.iter_node != nullptr)
    root_ = delete_recursive(root_, *pos);
}

template <typename key, typename value>
void avl_tree<key, value>::swap(avl_tree &other) {
  std::swap(root_, other.root_);
}

template <typename key, typename value>
void avl_tree<key, value>::merge(avl_tree &other) {
  avl_tree const_tree(other);
  iter const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    std::pair<iter, bool> pr = insert(*const_it);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename key, typename value>
typename avl_tree<key, value>::iter avl_tree<key, value>::find(
    const key &tree_key) {
  tree_node *exact_node = find_recursive(root_, tree_key);
  return iter(exact_node);
}

template <typename key, typename value>
bool avl_tree<key, value>::contains(const key &tree_key) {
  tree_node *contain_node = find_recursive(root_, tree_key);
  return !(contain_node == nullptr);
}

template <typename key, typename value>
typename avl_tree<key, value>::tree_node *avl_tree<key, value>::iter::forward(
    avl_tree::tree_node *node) {
  tree_node *res = nullptr;
  if (node->right != nullptr) {
    res = get_min(node->right);
  } else {
    tree_node *parent_ = node->parent;
    while (parent_ != nullptr && node == parent_->right) {
      node = parent_;
      parent_ = parent_->parent;
    }
    res = parent_;
  }
  return res;
}

template <typename key, typename value>
typename avl_tree<key, value>::tree_node *avl_tree<key, value>::iter::back(
    avl_tree::tree_node *node) {
  tree_node *res = nullptr;
  if (node->left != nullptr) {
    res = get_max(node->left);
  } else {
    tree_node *parent_ = node->parent;
    while (parent_ != nullptr && node == parent_->left) {
      node = parent_;
      parent_ = node->parent;
    }
  }
  return res;
}

template <typename key, typename value>
avl_tree<key, value>::iter::iter()
    : iter_node(nullptr), iter_past_node(nullptr) {}

template <typename key, typename value>
avl_tree<key, value>::iter::iter(avl_tree::tree_node *node,
                                 avl_tree::tree_node *past_node)
    : iter_node(node), iter_past_node(past_node) {}

template <typename key, typename value>
typename avl_tree<key, value>::iter &avl_tree<key, value>::iter::operator++() {
  tree_node *tmp;
  if (iter_node != nullptr) {
    tmp = get_max(iter_node);
  }
  iter_node = forward(iter_node);
  if (iter_node == nullptr) {
    iter_past_node = tmp;
  }
  return *this;
}

template <typename key, typename value>
typename avl_tree<key, value>::iter avl_tree<key, value>::iter::operator++(
    int) {
  iter temp = *this;
  operator++();
  return temp;
}

template <typename key, typename value>
typename avl_tree<key, value>::iter &avl_tree<key, value>::iter::operator--() {
  if (iter_node == nullptr && iter_past_node != nullptr) {
    *this = iter_past_node;
    return *this;
  }
  iter_node = back(iter_node);
  return *this;
}

template <typename key, typename value>
typename avl_tree<key, value>::iter avl_tree<key, value>::iter::operator--(
    int) {
  iter temp = *this;
  operator--();
  return temp;
}

template <typename key, typename value>
value &avl_tree<key, value>::iter::operator*() {
  if (iter_node == nullptr) {
    static value fake_value{};
    return fake_value;
  }
  return iter_node->key_;
}

template <typename key, typename value>
bool avl_tree<key, value>::iter::operator==(const avl_tree::iter &iter1) {
  return iter_node == iter1.iter_node;
}

template <typename key, typename value>
bool avl_tree<key, value>::iter::operator!=(const avl_tree::iter &iter1) {
  return !(*this == iter1);
}

template <typename key, typename value>
avl_tree<key, value>::tree_node::tree_node(key tree_key, value tree_value)
    : key_(tree_key), value_(tree_value) {}

template <typename key, typename value>
avl_tree<key, value>::tree_node::tree_node(key tree_key, value tree_value,
                                           tree_node *node)
    : key_(tree_key), value_(tree_value), parent(node) {}

template <typename key, typename value>
typename avl_tree<key, value>::tree_node *avl_tree<key, value>::copy_tree(
    avl_tree::tree_node *node, avl_tree::tree_node *parent) {
  if (node == nullptr) return nullptr;
  tree_node *new_node = new tree_node(node->key_, node->value_, parent);
  new_node->left = copy_tree(node->left, new_node);
  new_node->right = copy_tree(node->right, new_node);
  return new_node;
}

template <typename key, typename value>
void avl_tree<key, value>::free_node(tree_node *node) {
  if (node == nullptr) return;
  free_node(node->left);
  free_node(node->right);
  delete node;
}

template <typename key, typename value>
int avl_tree<key, value>::get_height(avl_tree::tree_node *node) {
  return node == nullptr ? -1 : node->height;
}

template <typename key, typename value>
int avl_tree<key, value>::get_balance(avl_tree::tree_node *node) {
  return node == nullptr ? 0 : get_height(node->right) - get_height(node->left);
}

template <typename key, typename value>
void avl_tree<key, value>::set_height(avl_tree::tree_node *node) {
  node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
}

template <typename key, typename value>
void avl_tree<key, value>::swap_value(avl_tree::tree_node *a,
                                      avl_tree::tree_node *b) {
  std::swap(a->key_, b->key_);
  std::swap(a->value_, b->value_);
}

template <typename key, typename value>
void avl_tree<key, value>::rotate_right(avl_tree::tree_node *node) {
  tree_node *new_left = node->left->left;
  tree_node *new_rightright = node->right;
  tree_node *new_rightleft = node->left->right;

  swap_value(node, node->left);
  node->right = node->left;

  node->left = new_left;
  if (node->left) {
    node->left->parent = node;
  }

  node->right->left = new_rightleft;
  if (node->right->left) {
    node->right->left->parent = node->right;
  }

  node->right->right = new_rightright;
  if (node->right->right) {
    node->right->right->parent = node->right;
  }

  set_height(node->right);
  set_height(node);
}

template <typename key, typename value>
void avl_tree<key, value>::rotate_left(avl_tree::tree_node *node) {
  tree_node *new_right = node->right->right;
  tree_node *new_leftleft = node->left;
  tree_node *new_leftright = node->right->left;

  swap_value(node, node->right);
  node->left = node->right;

  node->right = new_right;
  if (node->right) {
    node->right->parent = node;
  }

  node->left->right = new_leftright;
  if (node->left->right) {
    node->left->right->parent = node->left;
  }

  node->left->left = new_leftleft;
  if (node->left->left) {
    node->left->left->parent = node->left;
  }

  set_height(node->left);
  set_height(node);
}

template <typename key, typename value>
void avl_tree<key, value>::balance(tree_node *node) {
  int balance = get_balance(node);
  if (balance == -2) {
    if (get_balance(node->left) == 1) rotate_left(node->left);
    rotate_right(node);
  } else if (balance == 2) {
    if (get_balance(node->right) == -1) rotate_right(node->right);
    rotate_left(node);
  }
}

template <typename key, typename value>
typename avl_tree<key, value>::tree_node *avl_tree<key, value>::get_min(
    avl_tree::tree_node *node) {
  if (node == nullptr) return nullptr;
  if (node->left == nullptr) return node;
  return get_min(node->left);
}

template <typename key, typename value>
typename avl_tree<key, value>::tree_node *avl_tree<key, value>::get_max(
    avl_tree::tree_node *node) {
  if (node == nullptr) return nullptr;
  if (node->right == nullptr) return node;
  return get_max(node->right);
}

template <typename key, typename value>
size_t avl_tree<key, value>::size_recursive(avl_tree::tree_node *node) {
  if (node == nullptr) return 0;
  size_t leftsize = size_recursive(node->left);
  size_t rightsize = size_recursive(node->right);
  return 1 + leftsize + rightsize;
}

template <typename key, typename value>
bool avl_tree<key, value>::insert_recursive(avl_tree::tree_node *node,
                                            const key &tree_key,
                                            value tree_value) {
  bool check_insert = false;
  if (tree_key < node->key_) {
    if (node->left == nullptr) {
      node->left = new tree_node(tree_key, tree_value, node);
      check_insert = true;
    } else {
      check_insert = insert_recursive(node->left, tree_key, tree_value);
    }
  } else if (tree_key > node->key_) {
    if (node->right == nullptr) {
      node->right = new tree_node(tree_key, tree_value, node);
      check_insert = true;
    } else {
      check_insert = insert_recursive(node->right, tree_key, tree_value);
    }
  } else if (tree_key == node->key_) {
    return check_insert;
  }
  set_height(node);
  balance(node);
  return check_insert;
}

template <typename key, typename value>
typename avl_tree<key, value>::tree_node *
avl_tree<key, value>::delete_recursive(avl_tree::tree_node *node,
                                       key tree_key) {
  if (node == nullptr) return nullptr;
  if (tree_key < node->key_) {
    node->left = delete_recursive(node->left, tree_key);
  } else if (tree_key > node->key_) {
    node->right = delete_recursive(node->right, tree_key);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      tree_node *node_right = node->right;
      tree_node *node_left = node->left;
      tree_node *node_parent = node->parent;
      delete node;
      if (node_left == nullptr) {
        node = node_right;
      } else {
        node = node_left;
      }
      if (node != nullptr) node->parent = node_parent;
    } else {
      tree_node *min_in_right = get_min(node->right);
      node->key_ = min_in_right->key_;
      node->value_ = min_in_right->value_;
      node->right = delete_recursive(node->right, min_in_right->key_);
    }
  }
  if (node != nullptr) {
    set_height(node);
    balance(node);
  }
  return node;
}

template <typename key, typename value>
typename avl_tree<key, value>::tree_node *avl_tree<key, value>::find_recursive(
    avl_tree::tree_node *node, const key &tree_key) {
  if (node == nullptr || node->key_ == tree_key) return node;
  if (tree_key > node->key_) {
    return find_recursive(node->right, tree_key);
  } else {
    return find_recursive(node->left, tree_key);
  }
}
