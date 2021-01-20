#include "lib.h"

#include "version.h"

namespace otus_cpp::unit1::task1 {

int version() { return PROJECT_VERSION_PATCH; }

void greet_with_version(std::ostream& os) {
  os << "Version: " << version() << std::endl;
  os << "Hello, World!" << std::endl;
}

}  // namespace otus_cpp::unit1::task1
