#include <algorithm>
#include <iostream>
#include <string>

/**
 * @brief https://acm.timus.ru/problem.aspx?space=1&num=1877
 * acceptance:
 * https://acm.timus.ru/status.aspx?space=1&num=1877&author=312959
 *
 * @param code1 first code
 * @param code2 second code
 * @return true if code could be guessed by thief
 * @return false otherwise
 */
bool task_1877(int code1, int code2) {
  //   // brute-force
  //   bool found = false;
  //   int candidates[] = {code1, code2};
  //   int upper_bound = std::max(code1, code2);
  //   for (int probe = 0; probe <= upper_bound && !found; ++probe) {
  //     found = (probe == candidates[probe % 2]);
  //   }
  //   return found;
  return (code1 % 2) == 0 || (code2 % 2) == 1;
}

void task_1877_io_wrapper(std::istream& in = std::cin,
                          std::ostream& out = std::cout) {
  std::string str_code1, str_code2;
  std::getline(in, str_code1);
  std::getline(in, str_code2);

  int code1 = std::stoi(str_code1);
  int code2 = std::stoi(str_code2);

  bool result = task_1877(code1, code2);

  out << (result ? "yes" : "no") << std::endl;
}

#ifdef ONLINE_JUDGE

int main() {
  task_1877_io_wrapper();
  return 0;
}

#endif
