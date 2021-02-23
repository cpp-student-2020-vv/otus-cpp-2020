#pragma once

#include <iostream>
#include <memory>
#include <new>
#include <vector>

namespace otus_cpp::hw02::allocator {

class bad_alloc_out_of_space : std::bad_alloc {
 public:
  const char *what() const noexcept override {
    return "custom_allocator(): out of registered space!";
  }
};

class bad_alloc_not_implemented : std::bad_alloc {
 public:
  const char *what() const noexcept override {
    return "custom_allocator(): method is not implemented yet!";
  }
};

template <typename T, std::size_t N = 10, int Trace_id = 1>
struct custom_allocator {
  static_assert(N > 0, "Container size should be non-zero!");

  using value_type = T;

  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;

  template <typename U>
  struct rebind {
    using other = custom_allocator<U, N, Trace_id>;
  };

  custom_allocator() = default;

  // custom_allocator() {
  //   used_size_ = 0;
  //   data_ = std::make_unique<std::vector<T>>(N);
  // }

  ~custom_allocator() = default;

  template <typename U>
  custom_allocator(const custom_allocator<U, N, Trace_id> &) {}

  pointer allocate(std::size_t n) {
    std::cout << "custom_allocator(" << Trace_id
              << ")::try to allocate: [n = " << n << "]" << std::endl;

    if (n != 1)
      throw std::invalid_argument(
          "custom_allocator cannot allocate by size anything except n==1!");
    if (used_size_ + n > N) throw bad_alloc_out_of_space();

    ++used_size_;
    pointer p = data_.data() + used_size_ - 1;
    return p;
  }

  void deallocate(T *p, std::size_t n) {
    std::cout << "custom_allocator(" << Trace_id
              << ")::try to deallocate: [p = " << p << ", n  = " << n << "] "
              << std::endl;

    // std::free(p);
  }

  template <typename U, typename... Args>
  void construct(U *p, Args &&... args) {
    std::cout << "custom_allocator(" << Trace_id << ")::construct" << std::endl;

    new (p) U(std::forward<Args>(args)...);
  };

  void destroy(T *p) {
    std::cout << "custom_allocator(" << Trace_id << ")::destroy" << std::endl;

    p->~T();
  }

 private:
  // std::unique_ptr<std::vector<T>> data_;
  std::vector<T> data_{N};
  size_t used_size_{0};
};

}  // namespace otus_cpp::hw02::allocator
