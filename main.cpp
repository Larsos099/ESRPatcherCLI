#include <iostream>
#include <functional>
#include <vector>
#include <sstream>
#include <string>
#include <ranges>
#include "functions.hpp"
#include "CmdHandler.hpp"
#include "Patcher.hpp"

int main() {
    bool isRunning = true;
    CommandHandler::addFunction("exit", [&isRunning](std::vector<std::string> &) {
        return functions::exitCLI(&isRunning);
    }, "quit", [&isRunning](std::vector<std::string> &) {
        return functions::exitCLI(&isRunning);
    });
    CommandHandler::addFunction("patch", [](const std::vector<std::string> &params) {return Patcher::patch(params);});
    CommandHandler::addFunction("unpatch", [](const std::vector<std::string> &params) {return Patcher::unpatch(params);});
    CommandHandler::addFunction("help", functions::helpCmd);
    CommandHandler::addFunction("list", functions::listFiles);
    while (isRunning) {
        std::string command{};
        std::cout << "esr> " << std::flush;
        std::getline(std::cin, command);
        try {
        CommandHandler::Execute(command);
        } catch (std::exception &ex) {
            std::cout << "Error thrown by command:\n" << ex.what() << std::endl;
            continue;
        }

    }
    return 0;
}
