//
// Created by Lars on 13.08.2025.
//

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "CmdHandler.hpp"

namespace functions {
    static unsigned int exitCLI(bool *isRunning) {
        *isRunning = false;
        return 0;
    }
    static unsigned int helpCmd(std::vector<std::string>& params) {
        std::cout << "ESRPatcherCLI\nAvailable Commands: " << std::endl;
        for (const auto &key: CommandHandler::getCommandMap() | std::views::keys) {
            std::cout << key << std::endl;
        }
        return 0;
    }
    static unsigned int getLastReturnCode(std::vector<std::string>& params) {
        std::cout << CommandHandler::getLastReturnCode() << std::endl;
        return 0;
    }
}


#endif //FUNCTIONS_HPP
