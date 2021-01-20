#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

#include "ip_filter_dto.h"

namespace otus_cpp::unit1::task2 {

template <typename TAddress>
class Ip_filter_logic {
 public:
  using value_type = TAddress;

  /**
   * @brief Конструктор Ip_filter_logic.
   *
   * @param out Выходной поток для отчетов (по умолчанию @c std::cout)
   */
  Ip_filter_logic(std::ostream& out = std::cout) : report_stream(out) {}

  /**
   * @brief Добавить адрес в коллекцию фильтра.
   *
   * @param address Адрес
   */
  void add(const TAddress&& address) {
    addresses.emplace_back(std::move(address));
    is_sorted = false;
  }

  /**
   * @brief Отсортировать накопленные адреса в обратном лексикографическом
   * порядке.
   */
  void sort_reversed_lex() {
    std::sort(addresses.begin(), addresses.end(),
              [](auto a, auto b) { return b < a; });
    is_sorted = true;
  }

  /**
   * @brief Вывести полный список адресов после сортировки. Одна строка - один
   * адрес.
   */
  void report_all() {
    ensure_sorted();
    for (const auto& a : addresses) {
      print(a);
    }
  }

  /**
   * @brief Вывести список адресов, первый байт которых равен 1.
   */
  void report_first_eq_one() {
    auto predicate = [](const TAddress& a) { return std::get<0>(a) == 1; };
    report_by_predicate(predicate);
  }

  /**
   * @brief Вывести список адресов, первый байт которых равен 46, а второй 70.
   */
  void report_first_46_second_70() {
    auto predicate = [](const TAddress& a) {
      return std::get<0>(a) == 46 && std::get<1>(a) == 70;
    };
    report_by_predicate(predicate);
  }

  /**
   * @brief Вывести список адресов, любой байт которых равен 46.
   */
  void report_any_eq_46() {
    ensure_sorted();

    auto predicate = [](const TAddress& a) {
      return std::get<0>(a) == 46 || std::get<1>(a) == 46 ||
             std::get<2>(a) == 46 || std::get<3>(a) == 46;
    };
    for (const auto& a : addresses) {
      if (predicate(a)) {
        print(a);
      }
    }
  };

 private:
  template <class UnaryPredicate>
  void report_by_predicate(UnaryPredicate predicate) {
    ensure_sorted();
    auto rangeStart = std::find_if(begin(addresses), end(addresses), predicate);
    if (rangeStart == end(addresses)) {
      return;  // no items with this predicate
    }

    auto rangeEnd = std::find_if_not(rangeStart, end(addresses), predicate);

    std::for_each(rangeStart, rangeEnd, [this](auto& a) { this->print(a); });
  }

  void ensure_sorted() {
    if (!is_sorted) {
      throw std::logic_error(
          "Invalid state: sort_reversed_lex() was not called yet!");
    }
  }

  void print(const TAddress& a) { report_stream << a << std::endl; }

  std::ostream& report_stream;
  bool is_sorted{false};
  std::vector<TAddress> addresses{};
};
}  // namespace otus_cpp::unit1::task2