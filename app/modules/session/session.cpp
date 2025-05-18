#include "session.h"

namespace app::modules::session
{
    void Session::setVariable(const std::string &key, const std::string &value)
    {
        char *k = new char[key.size() + 1];
        std::strcpy(k, key.c_str());
        char *v = new char[value.size() + 1];
        std::strcpy(v, value.c_str());
        variables[std::shared_ptr<char>(k, [](char *p)
                                        { delete[] p; })] = std::shared_ptr<char>(v, [](char *p)
                                                                                  { delete[] p; });
    }

    void Session::setVariable(const std::string &key, const std::string &value, bool is_vector)
    {
        if (is_vector)
        {
            variables_vector.push_back(std::make_pair(key, value));
        }
        else
        {
            setVariable(key, value);
        }
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

    std::vector<std::pair<std::string, std::string>> Session::getVariableVector(const std::string &key) const
    {
        std::vector<std::pair<std::string, std::string>> result;
        for (const auto &pair : variables_vector)
        {
            if (pair.first == key)
            {
                result.push_back(pair);
            }
        }
        return result;
    }

    std::vector<std::string> Session::getAllVariables() const
    {
        std::vector<std::string> allVariables;
        for (const auto &pair : variables)
        {
            allVariables.push_back(std::string(pair.first.get()));
        }
        return allVariables;
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