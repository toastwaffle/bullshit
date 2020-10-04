#include "bs.pb.h"

#include <iostream>

int main() {
  bs::demo demo;
  demo.set_text("Hello, World!\n");
  std::cout << demo.DebugString();
}
