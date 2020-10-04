#include "repository/util.h"

#include <filesystem>
#include <iostream>

namespace bs {

namespace repository {

namespace fs = std::filesystem;

fs::path RepositoryRoot() {
  fs::path path = fs::current_path();
  while (true) {
    if (fs::exists(path / ".bs")) return path;
    if (path == path.parent_path()) {
      std::cerr << "Not inside a repository.\n";
      std::exit(1);
    }
    path = path.parent_path();
  }
}

} // namespace repository

} // namespace bs
