#include <algorithm>
#include <iostream>
#include <map>

#include "custom_allocator.hpp"
#include "custom_forward_list.hpp"
#include "factorial.hpp"

constexpr static std::size_t ALLOCATE_SIZE = 10;

using namespace otus_cpp::hw02::math;
using namespace otus_cpp::hw02::allocator;
using namespace otus_cpp::hw02;
using pair_allocator =
    custom_allocator<std::pair<const int, int>, ALLOCATE_SIZE>;

template <typename C>
void fill_map_like_container(C& instance, const size_t count = 10) {
  for (int i = 0; i < count; ++i) {
    instance[i] = factorial(i);
  }
}

template <typename C>
void fill_list_like_container(C& instance, const size_t count) {
  for (int i = count - 1; i >= 0; --i) {
    instance.push_front(i);
  }
}

template <typename I>
void print_container_item(const I& item, std::ostream& out);

template <typename C>
void print_container(const char* prefix, const C& container,
                     std::ostream& out = std::cout) {
  out << prefix << std::endl;
  // std::for_each(container.cbegin(), container.cend(),
  //               [&out](std::pair<const typename C::key_type, typename
  //               C::mapped_type> item) {
  //                 out << item.first << " " << item.second << std::endl;
  //               });
  for (const auto& item : container) {
    print_container_item(item, out);
  }
}

template <typename I>
inline void print_container_item(const I& item, std::ostream& out) {
  out << item << std::endl;
}

template <>
inline void print_container_item(const std::pair<const int, int>& item,
                                 std::ostream& out) {
  out << item.first << " " << item.second << std::endl;
}

void main_logic_unsafe() {
  std::map<int, int> map = {};
  fill_map_like_container(map);

  std::cout << "main::Filling map with custom allocator...\n";
  std::map<int, int, std::less<int>, pair_allocator> allocated_map{};
  fill_map_like_container(allocated_map);
  std::cout << "main::allocated_map.len=" << allocated_map.size() << std::endl;
  print_container("main::map with custom allocator content:", allocated_map);

  std::cout << "main::filling custom list with default allocator...\n";
  custom_forward_list<int> custom_list = {};
  fill_list_like_container(custom_list, 10);
  print_container("main::custom_list content:", custom_list);

  std::cout << "main::filling custom list with custom allocator...\n";
  custom_forward_list<int, custom_allocator<int, ALLOCATE_SIZE, 2>>
      custom_list_custom_allocator = {};
  fill_list_like_container(custom_list_custom_allocator, 10);
  print_container("main::custom_list with custom allocator content:",
                  custom_list_custom_allocator);
}

int main(int, char**) {
  try {
    main_logic_unsafe();
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}