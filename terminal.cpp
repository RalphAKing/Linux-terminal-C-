#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <unistd.h> 
#include <sys/stat.h> 
#include <cstdio> 

namespace fs = std::filesystem;

const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[32m";
const std::string MAGENTA = "\033[35m";
const std::string RED = "\033[31m";
const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

std::vector<std::string> split(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream stream(input);
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


bool endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void showHelp() {
    std::cout << "Available commands:\n"
              << "  cd <path>       - Change directory\n"
              << "  pwd             - Print current directory\n"
              << "  ls              - List files in the current directory\n"
              << "  mkdir <name>    - Create a new directory\n"
              << "  rm <name>       - Remove a file\n"
              << "  clear           - Clear the terminal\n"
              << "  echo <text>     - Print text to the terminal\n"
              << "  help            - Show this help message\n"
              << "  exit            - Exit the terminal\n";
}

std::string getFileColor(const fs::directory_entry& entry) {
    if (entry.is_directory()) {
        return BLUE; 
    } else if (entry.is_symlink()) {
        return CYAN;
    } else if (entry.is_regular_file()) {
        auto path = entry.path().string();
        if (endsWith(path, ".png") || endsWith(path, ".jpg") || endsWith(path, ".jpeg") ||
            endsWith(path, ".gif") || endsWith(path, ".bmp") || endsWith(path, ".tiff")) {
            return MAGENTA; 
        } else if (endsWith(path, ".tar") || endsWith(path, ".gz") || endsWith(path, ".zip") ||
                   endsWith(path, ".rar") || endsWith(path, ".bz2") || endsWith(path, ".7z")) {
            return RED; 
        } else if ((fs::status(entry).permissions() & fs::perms::owner_exec) != fs::perms::none) {
            return GREEN; 
        }
    }
    return RESET;
}

void listDirectory() {
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        std::string color = getFileColor(entry);
        std::cout << color << entry.path().filename().string() << RESET << "  ";
    }
    std::cout << std::endl;
}

void executeCommand(const std::vector<std::string>& commandParts) {
    if (commandParts.empty()) {
        return;
    }

    const std::string& command = commandParts[0];

    if (command == "cd") {
        if (commandParts.size() < 2) {
            std::cerr << "Error: Missing path for cd\n";
        } else {
            if (chdir(commandParts[1].c_str()) != 0) {
                perror("cd");
            }
        }
    } else if (command == "pwd") {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::cout << cwd << std::endl;
        } else {
            perror("pwd");
        }
    } else if (command == "ls") {
        listDirectory();
    } else if (command == "mkdir") {
        if (commandParts.size() < 2) {
            std::cerr << "Error: Missing name for mkdir\n";
        } else {
#ifdef _WIN32
            if (mkdir(commandParts[1].c_str()) != 0) {
                perror("mkdir");
            }
#else
            if (mkdir(commandParts[1].c_str(), 0755) != 0) {
                perror("mkdir");
            }
#endif
        }
    } else if (command == "rm") {
        if (commandParts.size() < 2) {
            std::cerr << "Error: Missing name for rm\n";
        } else {
            if (remove(commandParts[1].c_str()) != 0) {
                perror("rm");
            }
        }
    } else if (command == "clear") {
#ifdef _WIN32
        std::system("cls"); 

#endif
    } else if (command == "echo") {
        for (size_t i = 1; i < commandParts.size(); ++i) {
            std::cout << commandParts[i] << " ";
        }
        std::cout << std::endl;
    } else if (command == "help") {
        showHelp();
    } else if (command == "exit") {
        std::cout << "Exiting terminal. Goodbye!" << std::endl;
        std::exit(0);
    } else {
    #ifdef _WIN32
            std::string powershellCmd = "powershell.exe -Command \"";
            for (const auto& part : commandParts) {
                powershellCmd += part + " ";
            }
            powershellCmd += "\"";
            
            int result = std::system(powershellCmd.c_str());
            if (result != 0) {
                std::cerr << "Error: Unknown command '" << command << "'\n";
            }
    #endif
        }

}


int main() {
    std::cout << "Welcome to the custom terminal emulator!\n";
    std::cout << "Type 'help' for a list of commands.\n";

    while (true) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::cout  << cwd << " $ ";
        } else {
            perror("getcwd");
        }

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> commandParts = split(input);

        executeCommand(commandParts);
    }

    return 0;
}
