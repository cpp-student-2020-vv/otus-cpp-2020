#include <algorithm>
#include <iostream>
#include <map>

#include "custom_allocator.hpp"
#include "factorial.hpp"

using namespace otus_cpp::hw02::math;
using namespace otus_cpp::hw02::allocator;
using pair_allocator = custom_allocator<std::pair<const int, int>, 10>;

template <typename C>
void fill_map_like_container(C& instance) {
  for (int i; i < 10; ++i) {
    instance[i] = factorial(i);
  }
}

template <typename C>
void print_map_like_container(const C& container,
                              std::ostream& out = std::cout) {
  // std::for_each(container.cbegin(), container.cend(),
  //               [&out](std::pair<const typename C::key_type, typename
  //               C::mapped_type> item) {
  //                 out << item.first << " " << item.second << std::endl;
  //               });
  for (const auto& item : container) {
    out << item.first << " " << item.second << std::endl;
  }
}

void main_logic_unsafe() {
  std::map<int, int> map = {};
  fill_map_like_container(map);

  std::map<int, int, std::less<int>, pair_allocator> allocated_map{};
  std::cout << "main::Filling allocated map...\n";
  fill_map_like_container(allocated_map);
  std::cout << "main::allocated_map.len=" << allocated_map.size() << std::endl;

  std::cout << "allocated_map content:" << std::endl;
  print_map_like_container<decltype(allocated_map)>(allocated_map);
}

int main(int, char**) {
  try {
    main_logic_unsafe();
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}