#include "bs.pb.h"
#include "crypto.h"

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string_view>

namespace {

namespace fs = std::filesystem;

constexpr const char kUsage[] = R"(Usage: bs <command> [<args>]

  bs init - Initialize a new repository.
)";

struct {
  bool help = false;
} options;

void ReadOptions(int& argc, char**& argv) {
  int j = 0;
  bool parse_options = true;
  for (int i = 0; i < argc; i++) {
    const std::string_view option = argv[i];
    if (option == "--") {
      parse_options = false;
      continue;
    }
    if (parse_options && option.substr(0, 2) == "--") {
      // Parse command-line options.
      if (option == "--help") {
        options.help = true;
      } else {
        std::cerr << "Unrecognised option " << std::quoted(option) << ".\n";
        std::exit(1);
      }
    } else {
      argv[j++] = argv[i];
    }
  }
  if (options.help) {
    std::cerr << kUsage;
    std::exit(0);
  }
  argc = j;
  argv[argc] = nullptr;
}

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

}  // namespace

int main(int argc, char* argv[]) {
  ReadOptions(argc, argv);
  if (argc < 2) {
    std::cerr << kUsage;
    return EXIT_FAILURE;
  }
  const std::string_view command = argv[1];
  if (command == "init") {
    if (fs::exists(".bs")) {
      std::cerr << "Cannot initialise new repository: .bs already exists.\n";
      return EXIT_FAILURE;
    }
    if (!fs::create_directory(".bs")) {
      std::cerr << "Failed to create .bs directory.\n";
      return EXIT_FAILURE;
    }
  } else if (command == "status") {
    fs::path root = RepositoryRoot();
    std::cout << "Inside repository rooted at " << root << ".\n";
  } else if (command == "demo_hash") {
    if (argc != 3) std::exit(1);
    std::cout << "sha256(" << std::quoted(argv[2]) << "): " << bs::hash(argv[2])
              << '\n';
  } else {
    std::cerr << "Unrecognised command " << std::quoted(command) << ".\n";
    return EXIT_FAILURE;
  }
}
