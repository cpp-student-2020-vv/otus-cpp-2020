#include <iostream>

/**
 * @brief task 1264
 * https://acm.timus.ru/problem.aspx?space=1&num=1264
 *
 * @param n array size
 * @param m fn value range
 * @return number of code lines
 */
int task_1264(int n, int m) { return n * (m + 1); }

void task_1264_io_wrapper(std::istream& in = std::cin,
                          std::ostream& out = std::cout) {
  int n, m;
  in >> n >> m;
  int line_count = task_1264(n, m);
  out << line_count << std::endl;
}

#ifdef ONLINE_JUDGE

int main() {
  task_1264_io_wrapper();
  return 0;
}

#endif
