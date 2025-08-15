//
// Created by Lars on 13.08.2025.
//

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "CmdHandler.hpp"
#include <filesystem>
#include "Patcher.hpp"
#include <unordered_map>
namespace fs = std::filesystem;
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

    static unsigned int listFiles(const std::vector<std::string>& params) {
        if (params.empty()) {
            std::cout << "Please provide a path to list." << std::endl;
            return 1;
        }
        const fs::path unsafe_path(params[0]);
        const fs::path path = fs::weakly_canonical(unsafe_path);
        if (!fs::is_directory(path)) {
            throw std::runtime_error(std::string("The Path: " + path.string() + " is not a directory.\n") + __PRETTY_FUNCTION__);
        }
        std::vector<std::string> listing;
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".iso") {
                listing.push_back(entry.path().string());
            }
        }
        std::vector<bool> isPatched(listing.size());

        for (size_t i = 0; i < listing.size(); ++i) {
            std::vector<std::string> singleParam = { listing[i] };
            try {
                Patcher::isPatched(singleParam);
                isPatched[i] = false;
            } catch (const std::exception& ex) {
                if (std::string_view(ex.what()).contains("Already patched")) {
                    isPatched[i] = true;
                } else {
                    throw;
                }
            }
        }
        for (int i = 0; i < listing.size(); i++) {
            std::cout << listing[i] << " :" << (isPatched[i] ? " Patched" : " Unpatched") << std::endl;
        }


        return 0;
    }

}


#endif //FUNCTIONS_HPP
