#include "commands/status.h"
#include "repository/util.h"

#include <filesystem>
#include <iostream>

namespace bs {

namespace commands {

namespace fs = std::filesystem;

int Status() {
  fs::path root = repository::RepositoryRoot();
  std::cout << "Inside repository rooted at " << root << ".\n";
  return 0;
}

} // namespace commands

} // namespace bs
