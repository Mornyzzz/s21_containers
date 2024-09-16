
#ifndef S21_SET_H
#define S21_SET_H

#include "s21_avl_tree.h"
#include "s21_vector.h"
namespace s21 {

template <typename key>
class set : public avl_tree<key, key> {
 public:
  set() : avl_tree<key, key>(){};
  set(std::initializer_list<key> const &items);
  set(const set &other) : avl_tree<key, key>(other){};
  set(set &&other) noexcept : avl_tree<key, key>(std::move(other)){};
  set &operator=(set &&other) noexcept;
  set &operator=(const set &other);
  ~set() = default;

  typename avl_tree<key, key>::iter find(const key &set_key) {
    return avl_tree<key, key>::find(set_key);
  };
  template <class... args>
  s21::vector<std::pair<typename avl_tree<key, key>::iter, bool>> insert_many(
      args &&...args_);
};

}  // namespace s21
#include "s21_set.tpp"
#endif
