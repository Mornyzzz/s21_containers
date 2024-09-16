
#ifndef S21_AVL_TREE_H
#define S21_AVL_TREE_H

#include <iostream>

template <typename key, typename value>
class avl_tree {
 protected:
  struct tree_node;

 public:
  class iter;
  class const_iter;

  avl_tree();
  avl_tree(const avl_tree& other);
  avl_tree(avl_tree&& other) noexcept;
  ~avl_tree();
  avl_tree& operator=(avl_tree&& other) noexcept;
  avl_tree& operator=(const avl_tree& other);
  class iter {
   public:
    iter();
    iter(tree_node* node, tree_node* past_node = nullptr);
    iter& operator++();
    iter operator++(int);
    iter& operator--();
    iter operator--(int);
    value& operator*();
    bool operator==(const iter& iter1);
    friend class avl_tree<key, value>;
    bool operator!=(const iter& iter1);

   protected:
    tree_node* iter_node;
    tree_node* iter_past_node;
    tree_node* forward(tree_node* node);
    tree_node* back(tree_node* node);
  };
  class const_iter {
   public:
    const_iter() : iter(){};
    const value& operator*() const { return iter::operator*(); };
  };
  iter begin();
  iter end();
  bool empty();
  size_t size();
  size_t max_size();
  void clear();
  std::pair<iter, bool> insert(const key& tree_key);
  void erase(iter pos);
  void swap(avl_tree& other);
  void merge(avl_tree& other);
  bool contains(const key& tree_key);

 protected:
  iter find(const key& tree_key);
  struct tree_node {
    tree_node(key tree_key, value tree_value);
    tree_node(key tree_key, value tree_value, tree_node* tree_parent);
    friend class avl_tree<key, value>;
    key key_;
    value value_;
    tree_node* left = nullptr;
    tree_node* right = nullptr;
    tree_node* parent = nullptr;
    int height = 0;
  };
  tree_node* root_;

  void free_node(tree_node* node);
  tree_node* copy_tree(tree_node* node, tree_node* parent);

  static tree_node* get_min(tree_node* node);
  static tree_node* get_max(tree_node* node);

  void swap_value(tree_node* a, tree_node* b);
  void rotate_right(tree_node* node);
  void rotate_left(tree_node* node);
  void balance(tree_node* node);
  int get_balance(tree_node* node);
  int get_height(tree_node* node);
  void set_height(tree_node* node);

  bool insert_recursive(tree_node* node, const key& tree_key, value tree_value);
  tree_node* delete_recursive(tree_node* node, key tree_key);
  size_t size_recursive(tree_node* node);
  tree_node* find_recursive(tree_node* node, const key& tree_key);
};

#include "s21_avl_tree.tpp"
#endif
