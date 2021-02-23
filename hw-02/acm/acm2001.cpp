#include <iostream>
#include <vector>

using namespace std;

void task_2001(vector<int>& a, vector<int>& b, int& out_a, int& out_b) {
  out_b = b[0] - b[1];
  out_a = a[0] - a[2];
}

void task_2001_io_wrapper(std::istream& in = std::cin,
                          std::ostream& out = std::cout) {
  vector<int> a, b;
  int out_a, out_b;
  for (int i = 0; i < 3; ++i) {
    int a_probe, b_probe;
    in >> a_probe >> b_probe;
    a.emplace_back(a_probe);
    b.emplace_back(b_probe);
  }

  task_2001(a, b, out_a, out_b);

  out << out_a << " " << out_b << std::endl;
}

#ifdef ONLINE_JUDGE

int main() {
  task_2001_io_wrapper();
  return 0;
}

#endif
