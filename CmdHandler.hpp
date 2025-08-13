#ifndef CMDHANDLER_HPP
#define CMDHANDLER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <functional>
#include <unordered_map>
#include <regex>
class CommandHandler final {
    static unsigned int _lastReturnCode;
    static std::unordered_map<std::string, std::function<unsigned int(std::vector<std::string> &params)>> _commandMap;

    static void _addSingle(const std::string& keyw, const std::function<unsigned int(std::vector<std::string> &params)>& func) {
        _commandMap[keyw] = func;
    }


    static std::vector<std::string> splitCommand(const std::string &input, std::string &cmd) {
        std::vector<std::string> tokens;
        const std::regex re("\"([^\"]*)\"|(\\S+)");

        const auto begin = std::sregex_iterator(input.begin(), input.end(), re);
        const auto end   = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            if ((*it)[1].matched)
                tokens.push_back((*it)[1].str());
            else
                tokens.push_back((*it)[2].str());
        }

        if (!tokens.empty()) {
            cmd = tokens.front();
            tokens.erase(tokens.begin());
        } else {
            cmd.clear();
        }

        return tokens;
    }

public:
    CommandHandler() = delete;

    static bool Init(std::unordered_map<std::string, std::function<unsigned int(std::vector<std::string> &params)>>&& cmdMap) {
        try {
            _commandMap = std::move(cmdMap);
        } catch (const std::exception &ex) {
            std::cerr << "Init failed: " << ex.what()
                      << "\nFunction: " << __PRETTY_FUNCTION__ << std::endl;
            return false;
        }
        return true;
    }

    static void addFunction(const std::string& keyword, const std::function<unsigned int(std::vector<std::string> &params)>& func) {
        _addSingle(keyword, func);
    }

    template<typename... Args>
    static void addFunction(const std::string& keyword, const std::function<unsigned int(std::vector<std::string> &params)>& func, Args... rest) {
        _addSingle(keyword, func);
        addFunction(rest...);
    }

    static unsigned int Execute(const std::string& command) {
        std::string cmd{};
        std::vector<std::string> params = CommandHandler::splitCommand(command, cmd);
        if (_commandMap.contains(cmd)) {
            _lastReturnCode = _commandMap[cmd](params);
            return _lastReturnCode;
        }
        _lastReturnCode = 99;
        return 99;
    }


    static std::unordered_map<std::string, std::function<unsigned int(std::vector<std::string> &params)>>& getCommandMap() {
        return _commandMap;
    }

    static unsigned int getLastReturnCode() {
        return _lastReturnCode;
    }


};

std::unordered_map<std::string, std::function<unsigned int(std::vector<std::string> &params)>> CommandHandler::_commandMap;
unsigned int CommandHandler::_lastReturnCode{};
#endif // CMDHANDLER_HPP
