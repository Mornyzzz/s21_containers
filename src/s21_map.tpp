

#include "s21_map.h"

namespace s21 {
template <typename key, typename t>
map<key, t>::map(const std::initializer_list<std::pair<const key, t>> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename key, typename t>
map<key, t> &map<key, t>::operator=(map &&other) noexcept {
  if (this != &other) {
    avl_tree<key, t>::operator=(std::move(other));
  }
  return *this;
}

template <typename key, typename t>
map<key, t> &map<key, t>::operator=(const map &other) {
  if (this != &other) {
    avl_tree<key, t>::operator=(other);
  }
  return *this;
}

template <typename key, typename t>
std::pair<typename map<key, t>::map_iter, bool> map<key, t>::insert(
    const std::pair<const key, t> &map_value) {
  return insert(map_value.first, map_value.second);
}

template <typename key, typename t>
std::pair<typename map<key, t>::map_iter, bool> map<key, t>::insert(
    const key &map_key, const t &obj) {
  std::pair<map_iter, bool> return_value;
  if (avl_tree<key, t>::root_ == nullptr) {
    avl_tree<key, t>::root_ =
        new typename avl_tree<key, t>::tree_node(map_key, obj);
    return_value.first = map_iter(avl_tree<key, t>::root_);
    return_value.second = true;
  } else {
    bool check_insert = avl_tree<key, t>::insert_recursive(
        avl_tree<key, t>::root_, map_key, obj);
    return_value.first = find(map_key);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename key, typename t>
std::pair<const key, t> map<key, t>::map_iter::operator*() {
  if (avl_tree<key, t>::iter::iter_node == nullptr) {
    static std::pair<const key, t> fake_value{};
    return fake_value;
  }
  std::pair<const key, t> pr =
      std::make_pair(avl_tree<key, t>::iter::iter_node->key_,
                     avl_tree<key, t>::iter::iter_node->value_);
  std::pair<const key, t> &ref = pr;
  return ref;
}

template <typename key, typename t>
t &map<key, t>::map_iter::return_value() {
  if (avl_tree<key, t>::iter::iter_node == nullptr) {
    static t fake_value{};
    return fake_value;
  }
  return avl_tree<key, t>::iter::iter_node->value_;
}

template <typename key, typename t>
typename map<key, t>::map_iter map<key, t>::find(const key &map_key) {
  typename avl_tree<key, t>::tree_node *node =
      avl_tree<key, t>::find_recursive(avl_tree<key, t>::root_, map_key);
  return map_iter(node);
}

template <typename key, typename t>
std::pair<typename map<key, t>::map_iter, bool> map<key, t>::insert_or_assign(
    const key &map_key, const t &obj) {
  auto it = find(map_key);
  if (it != this->end()) {
    erase(it);
    auto pr = insert(map_key, obj);
    pr.second = false;
    return pr;
  }
  return insert(map_key, obj);
}

template <typename key, typename t>
template <class... args>
s21::vector<std::pair<typename map<key, t>::map_iter, bool>>
map<key, t>::insert_many(args &&...args_) {
  s21::vector<std::pair<typename map<key, t>::map_iter, bool>> vector_;
  for (const auto &arg : {args_...}) {
    vector_.push_back(insert(arg));
  }
  return vector_;
}

template <typename key, typename t>
t &map<key, t>::at(const key &map_key) {
  auto map_iter1 = find(map_key);
  if (map_iter1 == nullptr)
    throw std::out_of_range(
        "container does not have an element with the specified key");
  return map_iter1.return_value();
}

template <typename key, typename t>
t &map<key, t>::operator[](const key &map_key) {
  auto map_iter1 = find(map_key);
  if (map_iter1 == nullptr) {
    auto pr = insert(std::make_pair(map_key, t()));
    map_iter1 = pr.first;
  }
  return map_iter1.return_value();
}

template <typename key, typename t>
typename map<key, t>::map_iter map<key, t>::begin() {
  return map<key, t>::map_iter(
      avl_tree<key, t>::get_min(avl_tree<key, t>::root_));
}

template <typename key, typename t>
typename map<key, t>::map_iter map<key, t>::end() {
  if (avl_tree<key, t>::root_ == nullptr) return begin();

  typename avl_tree<key, t>::tree_node *last_node =
      avl_tree<key, t>::get_max(avl_tree<key, t>::root_);
  map_iter test(nullptr, last_node);
  return test;
}

template <typename key, typename t>
typename map<key, t>::const_map_iter map<key, t>::cbegin() const {
  return map<key, t>::const_map_iter(
      avl_tree<key, t>::get_min(avl_tree<key, t>::root_));
}

template <typename key, typename t>
typename map<key, t>::const_map_iter map<key, t>::cend() const {
  if (avl_tree<key, t>::root_ == nullptr) return cbegin();

  typename avl_tree<key, t>::tree_node *last_node =
      avl_tree<key, t>::get_max(avl_tree<key, t>::root_);
  const_map_iter test(nullptr, last_node);
  return test;
}

template <typename key, typename t>
void map<key, t>::merge(map &other) {
  map const_tree(other);
  map_iter const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    auto map_key = (*const_it).first;
    auto obj = (*const_it).second;
    std::pair<map_iter, bool> pr = insert(map_key, obj);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename key, typename t>
void map<key, t>::erase(map::map_iter pos) {
  if (avl_tree<key, t>::root_ == nullptr || pos.iter_node == nullptr) return;
  avl_tree<key, t>::root_ =
      avl_tree<key, t>::delete_recursive(avl_tree<key, t>::root_, (*pos).first);
}
}  // namespace s21
