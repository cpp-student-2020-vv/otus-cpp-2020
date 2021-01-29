#pragma once

#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

namespace otus_cpp::unit1::task2 {

/**
 * @brief Класс-адаптер входного потока, разбирает входные строки до строк
 * адреса (не преобразовывая их в TAddress).
 */
class Ip_input_adapter {
 public:
  /**
   * @brief Конструктор @c ip_input_adapter .
   *
   * @param in входной поток с данными (по умолчанию @c std::cin )
   */
  Ip_input_adapter(std::istream& in = std::cin) : input(in) {}

  /**
   * @brief Возвращает признак конца потока.
   *
   * @return true
   * @return false
   */
  bool eof() const { return input.eof(); }

  /**
   * @brief Получить следующую строку с адресом и вернуть флаг успешности
   * операции.
   *
   * @param str_address  выходной аргумент для хранения следующего адреса.
   * @return true если не достигнут конец потока (операция успешна, @p
   * str_address содержит данные)
   * @return false если достигнут конец потока (@p str_address НЕ содержит
   * полезных данных)
   */
  bool get_next_str_address(std::string& str_address) {
    std::string line;
    if (get_next_line(line)) {
      str_address = extract_address(line);
      return true;
    }
    return false;
  }

  /**
   * @brief Валидировать корректность строки входного потока
   * (str \t str \t str).
   * В случае некорректных данных возбуждается исключение
   * @c std::logic_error .
   *
   * @param line очередная входная строка.
   */
  static void validate_line(const std::string& line) {
    if (line.empty()) {
      throw std::logic_error("invalid argument: Input string is empty!");
    }
    auto line_regex = get_line_regex();
    std::smatch base_match;
    if (!std::regex_match(line, base_match, line_regex)) {
      throw std::logic_error("invalid argument: Input string [" + line +
                             "] does not match regex!");
    }
    if (base_match.size() != 4) {
      throw std::logic_error(
          "invalid argument: Input string does not match regex (match "
          "size!=4)!");
    }
  }

  /**
   * @brief Частично валидировать корректность IPv4 адреса (проверяется только
   * структура d.d.d.d без контроля переполнения). В случае некорректных данных
   * возбуждается исключение
   * @c std::logic_error .
   *
   * @param address_str строка с IPv4 адресом
   */
  static void validate_address_str(const std::string& address_str) {
    auto address_regex = get_addr_regex();
    if (!std::regex_match(address_str, address_regex)) {
      throw std::logic_error("invalid argument: Address string [" +
                             address_str + "] does not match regex!");
    }
  }

 private:
  bool get_next_line(std::string& line) {
    if (std::getline(input, line)) {
      validate_line(line);
      return true;
    }
    return false;
  }

  std::string extract_address(std::string& line) {
    auto line_regex = get_line_regex();
    std::smatch base_match;
    std::regex_match(line, base_match, line_regex);
    std::string address_str = base_match[1].str();
    validate_address_str(address_str);
    return address_str;
  }

  static const std::regex& get_line_regex() {
    static const std::regex line_regex(
        "(\\d+\\.\\d+\\.\\d+\\.\\d+)\t(.*)\t(.*)");
    return line_regex;
  }

  static const std::regex& get_addr_regex() {
    static const std::regex addr_regex("\\d+\\.\\d+\\.\\d+\\.\\d+");
    return addr_regex;
  }

  std::istream& input;
};
}  // namespace otus_cpp::unit1::task2
