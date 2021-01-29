#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace otus_cpp::unit1::task2 {
using Ip4_dto = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;

static Ip4_dto build_ip4_dto(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  return std::make_tuple(a, b, c, d);
}

static Ip4_dto build_ip4_dto(const std::string& address_str) {
  std::vector<uint8_t> parts;
  std::istringstream ss(address_str);
  for (std::string octet; std::getline(ss, octet, '.');) {
    parts.emplace_back(static_cast<uint8_t>(std::stoul(octet)));
  }
  return build_ip4_dto(parts[0], parts[1], parts[2], parts[3]);
}

std::ostream& operator<<(std::ostream& os, Ip4_dto a) {
  os << std::dec << static_cast<int>(std::get<0>(a)) << "."
     << static_cast<int>(std::get<1>(a)) << "."
     << static_cast<int>(std::get<2>(a)) << "."
     << static_cast<int>(std::get<3>(a));
  return os;
}
}  // namespace otus_cpp::unit1::task2