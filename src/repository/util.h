#ifndef BULLSHIT_SRC_REPOSITORY_UTIL_H
#define BULLSHIT_SRC_REPOSITORY_UTIL_H

#include <filesystem>

namespace repository {

namespace fs = std::filesystem;

fs::path RepositoryRoot();

} // namespace repository

#endif // ifndef BULLSHIT_SRC_REPOSITORY_UTIL_H
