#pragma once
#include <iostream>

namespace otus_cpp::unit1::task1 {
/**
 * @brief Запрос версии патча из состава триплета версии продукта в нотации
 * SemVer(major, minor, patch)
 *
 * @return int версия патча продукта
 */
int version();

/**
 * @brief Выводит версию продукта и базовое приветствие в переданный выходной
 * поток.
 *
 * @param os выходной поток для приветствия, по умолчанию std::cout.
 */
void greet_with_version(std::ostream& os = std::cout);
}  // namespace otus_cpp::unit1::task1
