#include <iostream>
#include <string>
#include <cstdlib> // for system()
#include <unistd.h> // for sleep()
#include <map>     // for string to enum mapping
#include <algorithm> // for transform

// Color codes
const std::string COLOR_CYAN = "\033[36m";
const std::string COLOR_ORANGE = "\033[33m";
const std::string COLOR_WHITE = "\033[37m";
const std::string COLOR_YELLOW = "\033[33m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_RED = "\033[31m";
const std::string RESET = "\033[0m";

// Forward declarations
void screensr_menu();
void droid_adb_command_menu();
void kv_scrcpy();

// Enum for menu options
enum MenuOption {
    OPTION_KV_SCRCPY,
    OPTION_BACK,
    OPTION_CLEAR,
    OPTION_INVALID
};

// Map strings to enum values
MenuOption getMenuOption(const std::string& input) {
    static const std::map<std::string, MenuOption> optionMap = {
        {"kv_scrcpy", OPTION_KV_SCRCPY},
        {"0", OPTION_BACK},
        {"back", OPTION_BACK},
        {"cd ..", OPTION_BACK},
        {"99", OPTION_CLEAR},
        {"clear", OPTION_CLEAR}
    };

    auto it = optionMap.find(input);
    return (it != optionMap.end()) ? it->second : OPTION_INVALID;
}

void screensr_menu() {
    system("clear"); // Clear screen
    
    while (true) {
        // Print menu
        std::cout << "\n    [" << COLOR_CYAN << "99" << COLOR_ORANGE << ". Clear screen                 " 
                  << COLOR_CYAN << "0" << COLOR_ORANGE << ". Back" << COLOR_WHITE << "]\n"
                  << "    " << COLOR_WHITE << "[screenshot | recordscreen | clear | back] \n\n"
                  << "    " << COLOR_YELLOW << "[Screensr]" << COLOR_WHITE << " Enter selection " 
                  << COLOR_GREEN << ">>>" << COLOR_WHITE << " ";
        
        // Get user input
        std::string input;
        std::getline(std::cin, input);
        
        // Convert to lowercase
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        // Process input using switch-case
        switch (getMenuOption(input)) {
            case OPTION_KV_SCRCPY:
                kv_scrcpy();
                screensr_menu();
                break;
                
            case OPTION_BACK:
                droid_adb_command_menu();
                return; // Exit the loop and function
                
            case OPTION_CLEAR:
                screensr_menu();
                break;
                
            case OPTION_INVALID:
            default:
                std::cout << "\n" << COLOR_RED << "       [X] Invalid selection\n" 
                          << COLOR_YELLOW << "       Please enter a valid option on menu above\n" << RESET;
                sleep(3);
                screensr_menu();
                break;
        }
    }
}

// Placeholder implementations
void droid_adb_command_menu() {
    system("clear");
    std::cout << "Returning to ADB command menu...\n";
}

void kv_scrcpy() {
    system("clear");
    std::cout << "Running kv_scrcpy...\n";
    // Actual implementation would go here
}

int main() {
    screensr_menu();
    return 0;
}
