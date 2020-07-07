#include "SkinnyList.h"

#include <iostream>
#include <string>
#include <vector>

// This prints an array of strings, followed by a newline.
void print_array(const std::string* items, int count) {
  for(int i = 0; i < count; ++i) {
    std::cout << items[i] << ' ';
  }

  std::cout << '\n';
}

// This prints a list of strings, followed by a newline.
void print_list(const SkinnyList* list) {
  for(int i = 0; i < list->count(); ++i) {
    std::cout << list->lookup(i) << ' ';
  }

  std::cout << '\n';
}


// This function will print an error and kill the program if
// it encounters and unexpected data in the list.
void assert_equal(const SkinnyList* list, const std::string* expected, int count) {
  if(list->count() != count) {
    std::cout << "ERROR: Incorrect list count!\n";
    std::cout << "  Expected: " << count << '\n';
    std::cout << "    Actual: " << list->count() << '\n';
    std::exit(1);
  }

  for(int i = 0; i < count; ++i) {
    if(list->lookup(i) != expected[i]) {
      std::cout << "ERROR: Incorrect list data!\n";
      std::cout << "  Expected: ";
      print_array(expected, count);
      std::cout << "    Actual: ";
      print_list(list);
      std::exit(1);
    }
  }
}

// This main function is full of tests.
// Run it to make sure SkinnyList works as expected!
int main() {
  // Make a new list...
  SkinnyList* list = new SkinnyList();

  // Test inserting at head...
  list->insert(0, "c");
  list->insert(0, "b");
  list->insert(0, "a");
  std::string test1[] = {"a", "b", "c"};
  assert_equal(list, test1, 3);

  // Test inserting at tail...
  list->insert(3, "d");
  list->insert(4, "e");
  list->insert(5, "f");
  std::string test2[] = {"a", "b", "c", "d", "e", "f"};
  assert_equal(list, test2, 6);

  // Test inserting in the middle...
  list->insert(2, "!");
  list->insert(5, "?");
  std::string test3[] = {"a", "b", "!", "c", "d", "?", "e", "f"};
  assert_equal(list, test3, 8);

  // Test removing the head...
  list->remove(0);
  std::string test4[] = {"b", "!", "c", "d", "?", "e", "f"};
  assert_equal(list, test4, 7);

  // Test removing the tail...
  list->remove(6);
  std::string test5[] = {"b", "!", "c", "d", "?", "e"};
  assert_equal(list, test5, 6);

  // Test removing in the middle...
  list->remove(4);
  list->remove(1);
  std::string test6[] = {"b", "c", "d", "e"};
  assert_equal(list, test6, 4);

  // Test removing everything...
  list->remove(2);
  list->remove(2);
  list->remove(0);
  list->remove(0);
  std::string test7[] = {};
  assert_equal(list, test7, 0);

  // All done - clean up!
  std::cout << "All tests passed!\n";
  delete list;
}
