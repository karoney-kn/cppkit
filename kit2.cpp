#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <unordered_map>

using namespace std;

// Color definitions for terminal output (basic simulation)
namespace color {
    const string CYAN = "\033[36m";
    const string ORANGE = "\033[33m";
    const string WHITE = "\033[37m";
    const string YELLOW = "\033[93m";
    const string GREEN = "\033[32m";
    const string RED = "\033[31m";
    const string RESET = "\033[0m";
}

// Simulated functions
void kv_scrcpy()        { cout << "Launching kv_scrcpy...\n"; }
void droid_adb_command_menu() { cout << "Returning to ADB command menu...\n"; }
void screensr_menu()    {
    system("clear"); // Clear terminal
    cout << color::CYAN << "99." << color::ORANGE << " Clear screen                 "
         << color::CYAN << "0." << color::ORANGE << " Back" << color::WHITE << "\n"
         << "[screenshot | recordscreen | clear | back] \n"
         << color::YELLOW << "[Screensr]" << color::WHITE << " Enter selection "
         << color::GREEN << ">>> " << color::WHITE;
}

int main() {
    string input;
    int option;

    // Map string inputs to integer codes
    unordered_map<string, int> inputMap = {
        {"kv_scrcpy", 1},
        {"0", 2}, {"back", 2}, {"cd ..", 2},
        {"99", 3}, {"clear", 3}
    };

    while (true) {
        screensr_menu();
        getline(cin, input);

        // Convert input to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        // Map input string to integer
        option = inputMap.count(input) ? inputMap[input] : -1;

        switch (option) {
            case 1:
                kv_scrcpy();
                break;
            case 2:
                droid_adb_command_menu();
                return 0; // Exit loop
            case 3:
                continue; // Clear screen & show menu again
            default:
                cout << "\n" << color::RED << "       [X] Invalid selection\n"
                     << color::YELLOW << "       Please enter a valid option on menu above\n"
                     << color::RESET;
                this_thread::sleep_for(chrono::seconds(3));
                break;
        }
    }

    return 0;
}
