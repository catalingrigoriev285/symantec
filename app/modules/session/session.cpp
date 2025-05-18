#include "session.h"

namespace app::modules::session
{
    void Session::setVariable(const std::string &key, const std::string &value)
    {
        char *k = new char[key.size() + 1];
        std::strcpy(k, key.c_str());
        char *v = new char[value.size() + 1];
        std::strcpy(v, value.c_str());
        variables[std::shared_ptr<char>(k, [](char *p) { delete[] p; })] = std::shared_ptr<char>(v, [](char *p) { delete[] p; });
    }

    std::string Session::getVariable(const std::string &key) const
    {
        for (const auto &pair : variables)
        {
            if (std::strcmp(pair.first.get(), key.c_str()) == 0)
            {
                return std::string(pair.second.get());
            }
        }
        return "";
    }

    bool Session::hasVariable(const std::string &key) const
    {
        for (const auto &pair : variables)
        {
            if (std::strcmp(pair.first.get(), key.c_str()) == 0)
            {
                return true;
            }
        }
        return false;
    }

    void Session::removeVariable(const std::string &key)
    {
        for (auto it = variables.begin(); it != variables.end(); ++it)
        {
            if (std::strcmp(it->first.get(), key.c_str()) == 0)
            {
                variables.erase(it);
                break;
            }
        }
    }
}