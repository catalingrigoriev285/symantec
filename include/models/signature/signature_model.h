#pragma once

#include "../model.h"

namespace Models
{
    class SignatureModel : public Model
    {
        public:
            SignatureModel() : Model("signatures") {}

            void setName(const std::string &name)
            {
                set("name", name);
            }

            void setDescription(const std::string &description)
            {
                set("description", description);
            }

            void setHash(const std::string &hash)
            {
                set("hash", hash);
            }

            void setAlgorithm(const std::string &algorithm)
            {
                set("algorithm", algorithm);
            }

            void setCreatedAt(const std::string &createdAt)
            {
                set("created_at", createdAt);
            }

            void setUpdatedAt(const std::string &updatedAt)
            {
                set("updated_at", updatedAt);
            }
    };
}