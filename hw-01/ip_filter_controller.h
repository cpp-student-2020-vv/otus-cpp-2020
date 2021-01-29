#pragma once

#include <memory>

#include "ip_filter_dto.h"
#include "ip_filter_logic.h"
#include "ip_input_adapter.h"

namespace otus_cpp::unit1::task2 {
/**
 * @brief Класс реализует общую оркестрацию компонентов (аналог MVC-controller).
 */
class Ip_filter_controller {
 public:
  /**
   * @brief Конструктор контроллера логики. Реализует DI через параметры
   * конструктора.
   *
   * @param pInput адаптер входного потока, обернутый @c unique_ptr
   * @param pLogic экземпляр бизнес логики фильтра, обернутый @c unique_ptr
   */
  Ip_filter_controller(std::unique_ptr<Ip_input_adapter> pInput,
                       std::unique_ptr<Ip_filter_logic<Ip4_dto>> pLogic)
      : input(std::move(pInput)), logic(std::move(pLogic)) {}

  /**
   * @brief Основной цикл работы.
   */
  void run() {
    for (std::string address_str; input->get_next_str_address(address_str);) {
      logic->add(build_ip4_dto(address_str));
    }

    logic->sort_reversed_lex();

    logic->report_all();
    logic->report_first_eq_one();
    logic->report_first_46_second_70();
    logic->report_any_eq_46();
  }

 private:
  std::unique_ptr<Ip_input_adapter> input;
  std::unique_ptr<Ip_filter_logic<Ip4_dto>> logic;
};
}  // namespace otus_cpp::unit1::task2