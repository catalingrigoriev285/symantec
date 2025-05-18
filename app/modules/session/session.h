#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <cstring>
#include <memory>
#include <map>
#include <functional>
#include <utility>

namespace app::modules::session
{
    class Session
    {
    private:
        std::map<std::shared_ptr<char>, std::shared_ptr<char>, std::function<bool(const std::shared_ptr<char> &, const std::shared_ptr<char> &)>> variables{
            [](const std::shared_ptr<char> &a, const std::shared_ptr<char> &b)
            { return std::strcmp(a.get(), b.get()) < 0; }};

        std::vector<std::pair<std::string, std::string>> variables_vector;

    public:
        Session() = default;
        ~Session() = default;

        void setVariable(const std::string &key, const std::string &value);
        void setVariable(const std::string &key, const std::string &value, bool is_vector);
        std::string getVariable(const std::string &key) const;
        std::vector<std::pair<std::string, std::string>> getVariableVector(const std::string &key) const;
        std::vector<std::string> getAllVariables() const;
        bool hasVariable(const std::string &key) const;
        void removeVariable(const std::string &key);
    };
}

#endif