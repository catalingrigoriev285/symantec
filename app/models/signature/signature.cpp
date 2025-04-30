#include "signature.h"

namespace app::models::signature {
    Signature::Signature(const std::string &name, const std::string &description, const std::vector<unsigned char> &hash, HashAlgorithm algorithm)
        : Model("signatures"), name(name), description(description), algorithm(algorithm), hash(hash), created_at(std::time(nullptr)), updated_at(std::time(nullptr)) {}

}