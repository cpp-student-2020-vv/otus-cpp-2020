#pragma once

#include <forward_list>

namespace otus_cpp::hw02 {

struct node_base {
  node_base() = default;
  node_base* next{nullptr};
};

template <typename V>
struct node : public node_base {
  template <typename... Args>
  node(Args&&... args) : node_base{}, value(std::forward<Args>(args)...) {}

  V value;
};

template <typename T>
struct custom_fwd_lst_iter;

template <typename T>
struct const_custom_fwd_lst_iter;

template <typename T, class Allocator = std::allocator<T>>
class custom_forward_list {
  static_assert(std::is_same<T, typename Allocator::value_type>::value,
                "Element type for container and allocator should be the same!");

  using Node = node<T>;
  using Allocator_Node = typename Allocator::template rebind<Node>::other;

 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using allocator_type = Allocator;

  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  using iterator = custom_fwd_lst_iter<T>;
  using const_iterator = const_custom_fwd_lst_iter<T>;

  custom_forward_list() = default;

  custom_forward_list(const custom_forward_list& other) {
    copy(std::cbegin(other), std::cend(other));
  }

  custom_forward_list(custom_forward_list&& other)
      : allocator_{std::forward<Allocator_Node>(other.allocator_)} {
    head_.next = other.head_.next;
    other.head_.next = nullptr;
  }

  ~custom_forward_list() { clear(); };

  custom_forward_list& operator=(const custom_forward_list& other) {
    clear();
    copy(std::cbegin(other), std::cend(other));
  }

  custom_forward_list& operator=(custom_forward_list&& other) {
    clear();
    head_.next = other.head_.next;
    other.head_.next = nullptr;
    allocator_ = std::move(other.allocator_);
  }

  bool operator==(const custom_forward_list& other) const {
    return std::equal(std::cbegin(*this), std::cend(*this), std::cbegin(other),
                      std::cend(other));
  }

  bool operator!=(const custom_forward_list& other) const {
    return !this->operator==(other);
  }

  void push_front(const T& value) {
    Node* node = allocator_.allocate(1);
    allocator_.construct(node, value);
    node->next = head_.next;
    head_.next = node;
  }

  void push_front(T&& value) {
    Node* node = allocator_.allocate(1);
    allocator_.construct(node, std::forward<T>(value));
    node->next = head_.next;
    head_.next = node;
  }

  void pop_front() {
    Node* node = static_cast<Node*>(head_.next);
    head_.next = node->next;
    allocator_.destroy(node);
    allocator_.deallocate(node, 1);
  }

  reference front() { return static_cast<Node*>(head_.next)->value; }

  const_reference front() const {
    return static_cast<Node*>(head_.next)->value;
  }

  bool empty() const { return (nullptr == head_.next) ? true : false; }

  size_type size() const noexcept {
    return std::distance(std::cbegin(*this), std::cend(*this));
  }

  void clear() noexcept {
    while (nullptr != head_.next) {
      pop_front();
    }
  }

  iterator begin() noexcept { return iterator{head_.next}; }

  const_iterator begin() const noexcept { return const_iterator{head_.next}; }

  iterator end() noexcept { return iterator{nullptr}; }

  const_iterator end() const noexcept { return const_iterator{nullptr}; }

  const_iterator cbegin() const noexcept { return const_iterator{head_.next}; }

  const_iterator cend() const noexcept { return const_iterator{nullptr}; }

 private:
  void copy(const_iterator first, const_iterator last) {
    auto size = std::distance(first, last);
    while (0 < size) {
      auto first_copy = first;
      for (decltype(size) i = 0; i < size - 1; ++first_copy, ++i)
        ;
      push_front(*first_copy);
      --size;
    }
  }

  node_base head_;
  Allocator_Node allocator_;
};

template <typename T>
struct custom_fwd_lst_iter {
  using Self = custom_fwd_lst_iter<T>;
  using Node = node<T>;

  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using difference_type = ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  explicit custom_fwd_lst_iter(node_base* node) : node_{node} {}

  reference operator*() const { return static_cast<Node*>(node_)->value; }

  pointer operator->() const { return &static_cast<Node*>(node_)->value; }

  Self& operator++() {
    node_ = node_->next;
    return *this;
  }

  Self operator++(int) {
    Self tmp{node_};
    node_ = node_->next;
    return tmp;
  }

  node_base* node_{nullptr};
};

template <typename T>
bool operator==(const custom_fwd_lst_iter<T>& lhs,
                const custom_fwd_lst_iter<T>& rhs) {
  return lhs.node == rhs.node;
}

template <typename T>
bool operator!=(const custom_fwd_lst_iter<T>& lhs,
                const custom_fwd_lst_iter<T>& rhs) {
  return lhs.node != rhs.node;
}

template <typename T>
struct const_custom_fwd_lst_iter {
  using Self = const_custom_fwd_lst_iter<T>;
  using Node = const node<T>;

  using value_type = T;
  using pointer = const T*;
  using reference = const T&;
  using difference_type = ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  explicit const_custom_fwd_lst_iter(const node_base* node) : node_{node} {}

  reference operator*() const { return static_cast<Node*>(node_)->value; }

  pointer operator->() const { return &static_cast<Node*>(node_)->value; }

  Self& operator++() {
    node_ = node_->next;
    return *this;
  }

  Self operator++(int) {
    Self tmp{node_};
    node_ = node_->next;
    return tmp;
  }

  const node_base* node_{nullptr};
};

template <typename T>
bool operator==(const const_custom_fwd_lst_iter<T>& lhs,
                const const_custom_fwd_lst_iter<T>& rhs) {
  return lhs.node_ == rhs.node_;
}

template <typename T>
bool operator!=(const const_custom_fwd_lst_iter<T>& lhs,
                const const_custom_fwd_lst_iter<T>& rhs) {
  return lhs.node_ != rhs.node_;
}

}  // namespace otus_cpp::hw02