#pragma once

#include <array>
#include <iosfwd>
#include <stdexcept>
#include <string_view>

namespace bs {

struct hash_error : std::runtime_error {
  using runtime_error::runtime_error;
};

struct hash {
  constexpr hash() noexcept = default;
  // Hash a string.
  hash(std::string_view input);
  std::array<std::byte, 32> bytes = {};
};

std::ostream& operator<<(std::ostream& output, const hash& h);

}  // namespace bs
