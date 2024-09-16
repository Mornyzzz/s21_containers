
#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "s21_avl_tree.h"
#include "s21_set.h"
#include "s21_vector.h"
namespace s21 {

template <typename key>
class multiset : public set<key> {
 public:
  multiset() : set<key>() {}
  multiset(std::initializer_list<key> const &items) : set<key>(items) {}
  multiset(const multiset &s) : set<key>(s){};
  multiset(multiset &&s) noexcept : set<key>(std::move(s)){};
  ~multiset() = default;

  multiset &operator=(multiset &&other) noexcept;

  bool insert_recursive(typename avl_tree<key, key>::tree_node *node,
                        const key &tree_key);
  std::pair<typename multiset<key>::iter, bool> insert(
      const key &value) noexcept;

  template <class... args>
  s21::vector<std::pair<typename avl_tree<key, key>::iter, bool>> insert_many(
      args &&...args_);
};

}  // namespace s21
#include "s21_multiset.tpp"
#endif
