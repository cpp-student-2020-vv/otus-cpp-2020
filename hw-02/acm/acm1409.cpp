#include <iostream>

/**
 * @brief task 1409
 * https://acm.timus.ru/problem.aspx?space=1&num=1409&locale=ru
 */
void task_1409(int a, int b, int& out_a, int& out_b) {
  long sum = a + b - 1;
  out_a = sum - a;
  out_b = sum - b;
}

void task_1409_io_wrapper(std::istream& in = std::cin,
                          std::ostream& out = std::cout) {
  int a, b;
  int out1, out2;
  in >> a >> b;
  task_1409(a, b, out1, out2);
  out << out1 << " " << out2 << std::endl;
}

#ifdef ONLINE_JUDGE

int main() {
  task_1409_io_wrapper();
  return 0;
}

#endif
