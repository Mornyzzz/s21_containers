#include <gtest/gtest.h>

#include <list>
#include <queue>
#include <stack>

#include "tests_entry.h"

using std::cout;
using std::endl;
using std::list;
using std::queue;
using std::stack;

// list
TEST(Test_s21_list, s21_list_test_list) {
  s21::List<int> s21_list_1;
  list<int> std_list_1;
  int y = 0;
  for (auto &i : std_list_1) {
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_list_param) {
  s21::List<int> s21_list_1(5);
  list<int> std_list_1(5);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_copy) {
  s21::List<int> s21_list_1{10, 5, 15, 13};
  s21::List<int> s21_list_2(std::move(s21_list_1));
  list<int> std_list_1{10, 5, 15, 13};
  list<int> std_list_2(std::move(std_list_1));

  auto y = s21_list_2.begin();
  for (auto &&i : std_list_2) {
    // cout << "std_list: " << i << " "
    //      << "List: " << *y << endl;
    ASSERT_EQ(i, *y);
    y++;
  }

  auto x = std_list_2.begin();
  for (auto &&i : s21_list_2) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, *x);
    x++;
  }
}

/*TEST(Test_s21_list, s21_list_copy_2) {
  ASSERT_THROW(s21::List<int> s21_list_2(std::move(s21_list_2)),
               std::invalid_argument);
}*/

TEST(Test_s21_list, s21_list_test_list_construct_copy) {
  s21::List<int> s21_list_1{10, 5, 15, 13};
  s21::List<int> s21_list_2(s21_list_1);

  list<int> std_list_1{10, 5, 15, 13};
  list<int> std_list_2(std_list_1);

  int y = 0;
  for (auto &i : std_list_2) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_2[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_sort_1) {
  s21::List<int> s21_list_1{10, 5, 15, 13};
  list<int> std_list_1{10, 5, 15, 13};
  s21_list_1.sort();
  std_list_1.sort();
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_marge_1) {
  s21::List<int> s21_list_1{1, 2, 3, 4};
  s21::List<int> s21_list_2{1, 2, 3, 4};
  s21_list_1.merge(s21_list_2);
  list<int> std_list_1{1, 2, 3, 4};
  list<int> std_list_2{1, 2, 3, 4};
  std_list_1.merge(std_list_2);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
  int x = 0;
  for (auto &i : std_list_2) {
    // cout << "std_list: " << i << " "
    //      << "List: " << s21_list_2[x++] << endl;
    ASSERT_EQ(i, s21_list_2[x++]);
  }
}

TEST(Test_s21_list, s21_list_test_marge_2) {
  s21::List<int> s21_list_1{1, 2, 3, 4};
  s21::List<int> s21_list_2{5, 6};
  s21_list_1.merge(s21_list_2);
  list<int> std_list_1{1, 2, 3, 4};
  list<int> std_list_2{5, 6};
  std_list_1.merge(std_list_2);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
  int x = 0;
  for (auto &i : std_list_2) {
    // cout << "std_list: " << i << " "
    //      << "List: " << s21_list_2[x++] << endl;
    ASSERT_EQ(i, s21_list_2[x++]);
  }
}

TEST(Test_s21_list, s21_list_test_marge_3) {
  s21::List<int> s21_list_1{1, 2};
  s21::List<int> s21_list_2{3, 4, 5, 6};
  s21_list_1.merge(s21_list_2);
  list<int> std_list_1{1, 2};
  list<int> std_list_2{3, 4, 5, 6};
  std_list_1.merge(std_list_2);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
  int x = 0;
  for (auto &i : std_list_2) {
    // cout << "std_list: " << i << " "
    //      << "List: " << s21_list_2[x++] << endl;
    ASSERT_EQ(i, s21_list_2[x++]);
  }
}

TEST(Test_s21_list, s21_list_test_insert_1) {
  s21::List<int> s21_list_1{10, 5, 15, 13};
  list<int> std_list_1{10, 5, 15, 13};
  s21::Iterator<int> it = s21_list_1.begin();
  ++it;
  auto s21_result = s21_list_1.insert(it, 111111);

  auto x = std_list_1.begin();
  ++x;
  auto std_result = std_list_1.insert(x, 111111);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
  // cout << "\n" << "std_list: " << *std_result << " " << "List: " <<
  // *s21_result << endl;
  ASSERT_EQ(*s21_result, *std_result);
}

TEST(Test_s21_list, s21_list_test_insert_2) {
  s21::List<int> s21_list_1{10, 5, 15, 13};
  auto y = s21_list_1.begin();
  ++y;
  auto s21_result = s21_list_1.insert(y, 111111);
  ++y;
  s21_list_1.insert(y, 999);

  list<int> std_list_1{10, 5, 15, 13};
  auto x = std_list_1.begin();
  ++x;
  auto std_result = std_list_1.insert(x, 111111);
  ++x;
  std_list_1.insert(x, 999);

  int j = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " "
    //      << "List: " << s21_list_1[j++] << endl;
    ASSERT_EQ(i, s21_list_1[j++]);
  }
  // cout << "\n" << "std_list: " << *std_result << " " << "List: " <<
  // *s21_result << endl;
  ASSERT_EQ(*s21_result, *std_result);
}

TEST(Test_s21_list, s21_list_test_erase_1) {
  s21::List<int> s21_list_1{10, 5, 15, 13};
  list<int> std_list_1{10, 5, 15, 13};
  s21_list_1.erase(s21_list_1.begin());
  std_list_1.erase(std_list_1.begin());
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_swap_1) {
  s21::List<int> s21_list_1{1, 2, 3, 4};
  s21::List<int> s21_list_2{5, 6, 7, 8};
  s21_list_1.swap(s21_list_2);
  list<int> std_list_1{1, 2, 3, 4};
  list<int> std_list_2{5, 6, 7, 8};
  std_list_1.swap(std_list_2);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_swap_2) {
  s21::List<int> s21_list_1{1, 2};
  s21::List<int> s21_list_2{3, 4, 5, 6};
  s21_list_1.swap(s21_list_2);
  list<int> std_list_1{1, 2};
  list<int> std_list_2{3, 4, 5, 6};
  std_list_1.swap(std_list_2);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_swap_3) {
  s21::List<int> s21_list_1{1, 2, 3, 4};
  s21::List<int> s21_list_2{5, 6};
  s21_list_1.swap(s21_list_2);
  list<int> std_list_1{1, 2, 3, 4};
  list<int> std_list_2{5, 6};
  std_list_1.swap(std_list_2);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_unique_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  s21_list_1.unique();
  std_list_1.unique();
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_reverse_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  s21_list_1.reverse();
  std_list_1.reverse();
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_reverse_2) {
  s21::List<int> s21_list_1{10};
  list<int> std_list_1{10};
  s21_list_1.reverse();
  std_list_1.reverse();
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " << s21_list_1[y++] <<
    // endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_empty_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  ASSERT_EQ(std_list_1.empty(), s21_list_1.empty());
}

TEST(Test_s21_list, s21_list_test_empty_2) {
  s21::List<int> s21_list_1;
  list<int> std_list_1;
  ASSERT_EQ(std_list_1.empty(), s21_list_1.empty());
}

TEST(Test_s21_list, s21_list_test_get_size_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  ASSERT_EQ(std_list_1.size(), s21_list_1.get_size());
}

/*TEST(Test_s21_list, s21_list_test_max_size_1) {
  s21::List<char> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<char> std_list_1{10, 10, 5, 5, 15, 13, 13};
  ASSERT_EQ(std_list_1.max_size(), s21_list_1.max_size());
  // cout << "std_list MAX_SIZE: " << std_list_1.max_size() << " " <<
  // "List MAX_SIZE: " << s21_list_1.max_size() << endl;
}
*/
TEST(Test_s21_list, s21_list_test_push_back_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  s21_list_1.push_back(777);
  std_list_1.push_back(777);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " <<
    // s21_list_1[y++] << endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_push_front_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  s21_list_1.push_front(777);
  s21_list_1.push_front(666);

  std_list_1.push_front(777);
  std_list_1.push_front(666);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " <<
    // s21_list_1[y++] << endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_push_front_2) {
  s21::List<int> s21_list_1;
  list<int> std_list_1;
  s21_list_1.push_front(11);
  s21_list_1.push_front(22);
  s21_list_1.push_front(33);

  std_list_1.push_front(11);
  std_list_1.push_front(22);
  std_list_1.push_front(33);
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " <<
    // s21_list_1[y++] << endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_pop_back_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  s21_list_1.pop_back();
  std_list_1.pop_back();
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " <<
    // s21_list_1[y++] << endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_pop_front_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  s21_list_1.pop_front();
  std_list_1.pop_front();
  int y = 0;
  for (auto &i : std_list_1) {
    // cout << "std_list: " << i << " " << "List: " <<
    // s21_list_1[y++] << endl;
    ASSERT_EQ(i, s21_list_1[y++]);
  }
}

TEST(Test_s21_list, s21_list_test_front_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  // cout << "std_list: " << std_list_1.front() << " " <<
  // "List: " << s21_list_1.front() << endl;
  ASSERT_EQ(std_list_1.front(), s21_list_1.front());
}

TEST(Test_s21_list, s21_list_test_back_1) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13, 13};
  // cout << "std_list: " << std_list_1.back() << " " <<
  // "List: " << s21_list_1.back() << endl;
  ASSERT_EQ(std_list_1.back(), s21_list_1.back());
}

TEST(Test_s21_list, s21_list_test_begin_end) {
  s21::List<int> s21_list_1{10, 10, 5, 5, 15, 13};
  list<int> std_list_1{10, 10, 5, 5, 15, 13};
  auto y = std_list_1.begin();
  for (auto &i : s21_list_1) {
    ASSERT_EQ(i, *y);
    y++;
  }
}

TEST(Test_s21_list, s21_list_test_splice) {
  s21::List<int> s21_list_1{10, 9, 5, 6, 15, 7};
  s21::List<int> s21_list_2{4, 7, 2, 6};

  auto i = s21_list_1.begin();
  s21_list_1.splice(++i, s21_list_2);

  list<int> std_list_1{10, 9, 5, 6, 15, 7};
  list<int> std_list_2{4, 7, 2, 6};

  auto y = std_list_1.begin();
  std_list_1.splice(++y, std_list_2);

  int count = 0;
  for (auto &n : std_list_1) {
    // cout << "std_list: " << n << " "
    //      << "List: " << s21_list_1[count++] << endl;
    ASSERT_EQ(n, s21_list_1[count++]);
  }
}

TEST(Test_s21_list, s21_list_test_operator_minus_minus) {
  s21::List<int> s21_list_1{10, 9, 5, 5, 15, 13, 8};
  list<int> std_list_1{10, 9, 5, 5, 15, 13, 8};
  auto y = std_list_1.end();
  for (auto i = s21_list_1.end(); i != s21_list_1.begin(); i--) {
    // cout << "std_list: " << *y << " " << "List: " << *i << endl;
    if (i != s21_list_1.end()) {
      ASSERT_EQ(*i, *y);
    }
    y--;
  }
}

TEST(Test_s21_list, Insert_Many) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  s21::List<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(Test_s21_list, Insert_Many_Back) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  s21::List<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  our_it = our_list.end();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(Test_s21_list, Insert_Many_Front) {
  s21::List<int> our_list = {1, 2, 3, 4, 5};
  s21::List<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

// stack

TEST(Test_s21_stack, s21_stack_test_stack_1) {
  s21::Stack<int> s21_stack_1;
  for (size_t i = 0; i < 10; i++) s21_stack_1.push(i);

  stack<int> std_stack_1;
  for (size_t i = 0; i < 10; i++) std_stack_1.push(i);

  while (!std_stack_1.empty()) {
    ASSERT_EQ(std_stack_1.top(), s21_stack_1.top());
    // cout << "std_stack: " << std_stack_1.top() << " " << "Stack: " <<
    // s21_stack_1.top() << endl;
    std_stack_1.pop();
    s21_stack_1.pop();
  }
}

TEST(Test_s21_stack, s21_stack_test_stack_2) {
  s21::Stack<int> s21_stack_1{1, 2, 3, 4, 5};

  for (size_t i = 5; !s21_stack_1.empty(); i--) {
    ASSERT_EQ(i, (size_t)s21_stack_1.top());
    // cout << "std_stack: " << std_stack_1.top() << " " << "Stack: " <<
    // s21_stack_1.top() << endl;
    s21_stack_1.pop();
  }
}

TEST(Test_s21_stack, s21_stack_copy) {
  s21::Stack<int> s21_stack_1{5, 4, 3, 2, 1};
  s21::Stack<int> s21_stack_2(std::move(s21_stack_1));

  for (int i = 1; !s21_stack_2.empty(); i++) {
    ASSERT_EQ(i, s21_stack_2.top());
    // cout << "std_stack: " << std_stack_2.top() << " "
    //      << "Stack: " << s21_stack_2.top() << endl;
    s21_stack_2.pop();
  }
}

/*TEST(Test_s21_stack, s21_stack_copy_2) {
  ASSERT_THROW(s21::Stack<int> s21_stack_2(std::move(s21_stack_2)),
               std::invalid_argument);
}*/

TEST(Test_s21_stack, s21_stack_test_operator_1) {
  s21::Stack<int> s21_stack_1;
  s21::Stack<int> s21_stack_2;
  for (size_t i = 0; i < 10; i++) s21_stack_1.push(i);
  s21_stack_2 = s21_stack_1;
  stack<int> std_stack_1;
  stack<int> std_stack_2;
  for (size_t i = 0; i < 10; i++) std_stack_1.push(i);
  std_stack_2 = std_stack_1;

  for (size_t i = s21_stack_1.get_size(); i > 0; i--) {
    // cout << "std_stack: " << std_stack_2.top() << " " << "Stack: " <<
    // s21_stack_2.top() << endl;
    ASSERT_EQ(std_stack_1.top(), s21_stack_1.top());
    std_stack_2.pop();
    s21_stack_2.pop();
  }
}

TEST(Test_s21_stack, s21_stack_test_swap) {
  s21::Stack<int> s21_stack_1;
  s21::Stack<int> s21_stack_2;
  for (int i = 0, y = 10; i < 10; i++, y--) {
    s21_stack_1.push(i);
    s21_stack_2.push(y);
  }
  s21_stack_1.swap(s21_stack_2);

  stack<int> std_stack_1;
  stack<int> std_stack_2;
  for (int i = 0, y = 10; i < 10; i++, y--) {
    std_stack_1.push(i);
    std_stack_2.push(y);
  }
  std_stack_1.swap(std_stack_2);

  //  for (size_t i = s21_stack_2.get_size(); i > 0; i--) {
  //    ASSERT_EQ(std_stack_2.top(), s21_stack_2.top());
  //    // cout << "std_stack 2: " << std_stack_2.top() << " " <<
  //    // "Stack 2: " << s21_stack_2.top() << endl;
  //    std_stack_2.pop();
  //    s21_stack_2.pop();
  //  }
  //  // cout << endl;

  for (size_t i = s21_stack_1.get_size(); i > 0; i--) {
    ASSERT_EQ(std_stack_1.top(), s21_stack_1.top());
    // cout << "std_stack 1: " << std_stack_1.top() << " " <<
    // "Stack 1: " << s21_stack_1.top() << endl;
    std_stack_1.pop();
    s21_stack_1.pop();
  }
}

TEST(Test_s21_stack, s21_stack_test_operator_eq_1) {
  s21::Stack<int> s21_stack_1{1, 2, 3, 4, 5, 6, 7};

  stack<int> std_stack_1;
  for (size_t i = 0; i < 8; i++) std_stack_1.push(i);

  // cout << std_stack_1.empty() << " " << s21_stack_1.empty() << endl;
  ASSERT_EQ(std_stack_1.empty(), s21_stack_1.empty());
}

TEST(Test_s21_stack, s21_stack_test_empty_2) {
  s21::Stack<int> s21_stack_1;
  s21::Stack<int> s21_stack_2;
  ASSERT_EQ(!s21_stack_1.empty(), !s21_stack_2.empty());
}

TEST(Test_s21_stack, s21_stack_test_size) {
  s21::Stack<int> s21_stack_1;
  stack<int> std_stack_1;
  ASSERT_EQ(std_stack_1.size(), s21_stack_1.get_size());
}

TEST(Test_s21_stack, s21_stack_BIG_STACK) {
  s21::Stack<int> s21_stack_1;
  stack<int> std_stack_1;
  int rand_count = 0;
  for (size_t i = 0; i < 1000; i++) {
    rand_count = std::rand() % 10000;
    s21_stack_1.push(rand_count);
    std_stack_1.push(rand_count);
  }
  for (size_t i = s21_stack_1.get_size(); i > 0; i--) {
    // cout << "std_stack 1: " << std_stack_1.top() << " " <<
    // "Stack 1: " << s21_stack_1.top() << endl;
    ASSERT_EQ(std_stack_1.top(), s21_stack_1.top());
    std_stack_1.pop();
    s21_stack_1.pop();
  }
}

TEST(Test_s21_stack, InsertManyFront) {
  s21::Stack<int> our_stack_int;
  our_stack_int.insert_many_front(1, 2, 3);
  EXPECT_EQ(our_stack_int.top(), 3);
}

// queue

TEST(Test_s21_queue, s21_queue_test_queue_1) {
  s21::Queue<int> s21_queue_1;
  for (size_t i = 0; i < 10; i++) s21_queue_1.push(i);

  queue<int> std_queue_1;
  for (size_t i = 0; i < 10; i++) std_queue_1.push(i);

  while (!std_queue_1.empty()) {
    ASSERT_EQ(std_queue_1.front(), s21_queue_1.front());
    // cout << "std_queue: " << std_queue_1.front() << " " <<
    // "Queue: " << s21_queue_1.front() << endl;
    std_queue_1.pop();
    s21_queue_1.pop();
  }
  ASSERT_EQ(std_queue_1.size(), s21_queue_1.get_size());
}

TEST(Test_s21_queue, s21_queue_test_queue_2) {
  s21::Queue<int> s21_queue_1{5, 4, 3, 2, 1};

  for (size_t i = 5; !s21_queue_1.empty(); i--) {
    ASSERT_EQ(i, (size_t)s21_queue_1.front());
    // cout << "std_stack: " << s21_queue_1.front() << " " <<
    // "Stack: " << s21_queue_1.front() << endl;
    s21_queue_1.pop();
  }
}

TEST(Test_s21_queue, s21_queue_copy) {
  s21::Queue<int> s21_queue_1{5, 4, 3, 2, 1};
  s21::Queue<int> s21_queue_2(std::move(s21_queue_1));

  queue<int> std_queue_1;
  for (int i = 0; i < 5; i++) std_queue_1.push(i);
  queue<int> std_queue_2(std::move(std_queue_1));

  for (int i = 5; !s21_queue_2.empty(); i--) {
    ASSERT_EQ(i, s21_queue_2.front());
    // cout << "std_queue: " << std_queue_2.top() << " "
    //      << "Queue: " << s21_queue_2.top() << endl;
    s21_queue_2.pop();
  }
}

/*TEST(Test_s21_queue, s21_queue_copy_2) {
  ASSERT_THROW(s21::Queue<int> s21_queue_2(std::move(s21_queue_2)),
               std::invalid_argument);
}*/

TEST(Test_s21_queue, s21_queue_test_operator_1) {
  s21::Queue<int> s21_queue_1;
  s21::Queue<int> s21_queue_2;
  for (size_t i = 0; i < 10; i++) s21_queue_1.push(i);
  s21_queue_2 = s21_queue_1;

  queue<int> std_queue_1;
  queue<int> std_queue_2;
  for (size_t i = 0; i < 10; i++) std_queue_1.push(i);
  std_queue_2 = std_queue_1;

  for (size_t i = s21_queue_1.get_size(); i > 0; i--) {
    // cout << "std_queue: " << std_queue_1.front() << " " <<
    // "Queue: " << s21_queue_1.front() << endl;
    ASSERT_EQ(std_queue_1.front(), s21_queue_1.front());
    std_queue_1.pop();
    s21_queue_1.pop();
  }

  for (size_t i = s21_queue_2.get_size(); i > 0; i--) {
    // cout << "std_queue: " << std_queue_2.front() << " " <<
    // "Queue: " << s21_queue_2.front() << endl;
    ASSERT_EQ(std_queue_2.front(), s21_queue_2.front());
    std_queue_2.pop();
    s21_queue_2.pop();
  }
  ASSERT_EQ(std_queue_1.size(), s21_queue_1.get_size());
}

TEST(Test_s21_queue, s21_queue_test_swap) {
  s21::Queue<int> s21_queue_1;
  s21::Queue<int> s21_queue_2;
  for (int i = 0, y = 10; i < 10; i++, y--) {
    s21_queue_1.push(i);
    s21_queue_2.push(y);
  }
  s21_queue_1.swap(s21_queue_2);

  queue<int> std_queue_1;
  queue<int> std_queue_2;
  for (int i = 0, y = 10; i < 10; i++, y--) {
    std_queue_1.push(i);
    std_queue_2.push(y);
  }
  std_queue_1.swap(std_queue_2);

  for (size_t i = s21_queue_2.get_size(); i > 0; i--) {
    ASSERT_EQ(std_queue_2.front(), s21_queue_2.front());
    // cout << "std_queue 2: " << std_queue_2.front() << " " <<
    // "Queue 2: " << s21_queue_2.front() << endl;
    std_queue_2.pop();
    s21_queue_2.pop();
  }
  // cout << endl;

  for (size_t i = s21_queue_1.get_size(); i > 0; i--) {
    ASSERT_EQ(std_queue_1.front(), s21_queue_1.front());
    // cout << "std_queue_1: " << std_queue_1.front() << " " <<
    // "Queue 1: " << s21_queue_1.front() << endl;
    std_queue_1.pop();
    s21_queue_1.pop();
  }
  ASSERT_EQ(std_queue_1.size(), s21_queue_1.get_size());
}

TEST(Test_s21_queue, s21_queue_test_empty_1) {
  s21::Queue<int> s21_queue_1{1, 2, 3, 4, 5, 6, 7};

  queue<int> std_queue_1;
  for (size_t i = 0; i < 8; i++) std_queue_1.push(i);

  // cout << std_queue_1.empty() << " " << s21_queue_1.empty() << endl;
  ASSERT_EQ(std_queue_1.empty(), s21_queue_1.empty());
}

TEST(Test_s21_queue, s21_queue_test_empty_2) {
  s21::Queue<int> s21_queue_1;
  s21::Queue<int> s21_queue_2;
  ASSERT_EQ(!s21_queue_1.empty(), !s21_queue_2.empty());
}

TEST(Test_s21_queue, s21_queue_test_size) {
  s21::Queue<int> s21_queue_1;
  queue<int> std_queue_1;
  ASSERT_EQ(std_queue_1.size(), s21_queue_1.get_size());
}

TEST(Test_s21_queue, InsertManyBack) {
  s21::Queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}
