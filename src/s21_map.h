
#ifndef S21_MAP_H
#define S21_MAP_H

#include "s21_avl_tree.h"
#include "s21_vector.h"
namespace s21 {
template <typename key, typename t>
class map : public avl_tree<key, t> {
 public:
  class map_iter;
  class const_map_iter;
  map() : avl_tree<key, t>(){};
  map(std::initializer_list<std::pair<const key, t>> const &items);
  map(const map &other) : avl_tree<key, t>(other){};
  map(map &&other) noexcept : avl_tree<key, t>(std::move(other)){};
  map &operator=(map &&other) noexcept;
  map &operator=(const map &other);
  ~map() = default;

  map_iter begin();
  map_iter end();
  const_map_iter cbegin() const;
  const_map_iter cend() const;
  void merge(map &other);

  class map_iter : public avl_tree<key, t>::iter {
   public:
    friend class map;
    map_iter() : avl_tree<key, t>::iter(){};
    map_iter(typename avl_tree<key, t>::tree_node *node,
             typename avl_tree<key, t>::tree_node *past_node = nullptr)
        : avl_tree<key, t>::iter(node, past_node = nullptr){};
    std::pair<const key, t> operator*();

   protected:
    t &return_value();
  };

  class const_map_iter : public map_iter {
   public:
    friend class map;
    const_map_iter() : map_iter(){};
    const_map_iter(typename avl_tree<key, t>::tree_node *node,
                   typename avl_tree<key, t>::tree_node *past_node = nullptr)
        : map_iter(node, past_node = nullptr){};
    const std::pair<const key, t> &operator*() const {
      return map_iter::operator*();
    };
  };
  t &at(const key &map_key);
  t &operator[](const key &map_key);
  std::pair<map_iter, bool> insert(const std::pair<const key, t> &map_value);
  std::pair<map_iter, bool> insert(const key &map_key, const t &obj);
  std::pair<map_iter, bool> insert_or_assign(const key &map_key, const t &obj);
  template <class... args>
  s21::vector<std::pair<map_iter, bool>> insert_many(args &&...args_);
  void erase(map_iter pos);

 private:
  map_iter find(const key &tree_key);
};

}  // namespace s21
#include "s21_map.tpp"
#endif
