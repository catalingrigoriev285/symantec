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
        std::unordered_map<std::string, std::string> variables;
        std::map<std::shared_ptr<char>, std::shared_ptr<char>, std::function<bool(const std::shared_ptr<char> &, const std::shared_ptr<char> &)>> variables{
            [](const std::shared_ptr<char> &a, const std::shared_ptr<char> &b)
            { return std::strcmp(a.get(), b.get()) < 0; }};

    public:
        void setVariable(const std::string &key, const std::string &value);
        std::string getVariable(const std::string &key) const;
        bool hasVariable(const std::string &key) const;
        void removeVariable(const std::string &key);
    };
}

#endif