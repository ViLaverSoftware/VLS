#include <VLS/Properties/Temp.h>

#include <iostream>

namespace VLS::Properties {
Temp::Temp() {
  std::cout
      << "Prevents VLS::Properties library from being a interface library...";
}
}  // namespace VLS::Properties
