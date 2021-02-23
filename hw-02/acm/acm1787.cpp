#include <iostream>
#include <numeric>
#include <vector>

/**
 * @brief task 1787
 * https://acm.timus.ru/problem.aspx?space=1&num=1787
 *
 * @param tpm  average throughput (cars per minute)
 * @param m minutes count (already passed), m === arrivals.size()
 * @param arrivals arrivals per each minute up to "m"
 * @return int queue size
 */
int task_1787(int tpm, int m, std::vector<int>& arrivals) {
  int accumulated_queue = 0;
  for (auto a : arrivals) {
    accumulated_queue += a;
    accumulated_queue = (accumulated_queue - tpm > 0) 
        ? accumulated_queue - tpm 
        : 0;
  }
  return accumulated_queue;
}

void task_1787_io_wrapper(std::istream& in = std::cin,
                          std::ostream& out = std::cout) {
  int tpm, minutes;
  in >> tpm >> minutes;
  std::vector<int> arrivals(minutes);
  for (int i = 0; i < minutes; i++) {
    int buf;
    in >> buf;
    arrivals.emplace_back(buf);
  }

  int queue_size = task_1787(tpm, minutes, arrivals);
  out << queue_size << std::endl;
}

#ifdef ONLINE_JUDGE

int main() {
  task_1787_io_wrapper();
  return 0;
}

#endif
