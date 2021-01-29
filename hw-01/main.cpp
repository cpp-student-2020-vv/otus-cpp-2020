#include <cstdio>

#include "ip_filter_controller.h"
#include "ver.h"

namespace otus_cpp::unit1::task2 {
std::unique_ptr<Ip_filter_controller> build_composition_root() {
  return std::make_unique<Ip_filter_controller>(
      std::make_unique<Ip_input_adapter>(),
      std::make_unique<Ip_filter_logic<Ip4_dto>>());
}
}  // namespace otus_cpp::unit1::task2

int main(int, char**) {
  // std::printf("ip_filter version: %d\n", otus_cpp::unit1::task2::version());
  // return 0;
  try {
    auto pController = otus_cpp::unit1::task2::build_composition_root();
    pController->run();
  } catch (std::logic_error const& err) {
    std::cerr << "Error happened: " << err.what() << std::endl;
    return -1;
  }
  return 0;
}
