#include "bs.pb.h"
#include "commands/init.h"
#include "commands/status.h"

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

}  // namespace

int main(int argc, char* argv[]) {
  ReadOptions(argc, argv);
  if (argc < 2) {
    std::cerr << kUsage;
    return EXIT_FAILURE;
  }
  const std::string_view command = argv[1];
  if (command == "init") {
    return bs::commands::Init();
  } else if (command == "status") {
    return bs::commands::Status();
  } else {
    std::cerr << "Unrecognised command " << std::quoted(command) << ".\n";
    return EXIT_FAILURE;
  }
}
