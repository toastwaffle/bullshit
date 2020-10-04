#include "commands/init.h"

#include <filesystem>
#include <iostream>

namespace bs {

namespace commands {

namespace fs = std::filesystem;

int Init() {
  if (fs::exists(".bs")) {
    std::cerr << "Cannot initialise new repository: .bs already exists.\n";
    return EXIT_FAILURE;
  }
  if (!fs::create_directory(".bs")) {
    std::cerr << "Failed to create .bs directory.\n";
    return EXIT_FAILURE;
  }
  return 0;
}

} // namespace commands

} // namespace bs
