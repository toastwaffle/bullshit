#include "crypto.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <openssl/evp.h>

namespace bs {

hash::hash(std::string_view input) {
  assert(EVP_MD_size(EVP_sha256()) == (int)bytes.size());
  if (!EVP_Digest(input.data(), input.size(), (unsigned char*)bytes.data(),
                  nullptr, EVP_sha256(), nullptr)) {
    throw hash_error("Failed to hash message.");
  }
}

std::ostream& operator<<(std::ostream& output, const hash& h) {
  constexpr char kHex[] = "0123456789abcdef";
  for (std::byte b : h.bytes) {
    auto c = (unsigned char)b;
    output << kHex[c >> 4] << kHex[c & 0xf];
  }
  return output;
}

}  // namespace bs
