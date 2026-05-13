#include <iostream>
#include <string>
#include "rnd.hpp"
#include "guess.hpp"
#include "leaderboard.hpp"

int main(int argc, char** argv) {
    int max_value = 100;
    bool max_was_set = false;
    bool level_was_set = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg{argv[i]};
        if (arg == "-table") {
            if (argc != 2) {
                std::cout << "Wrong usage! The argument '-table' does not accept values!"
                          << std::endl;
                return -1;
            }
            show_results();
            return 0;
        }
        else if (arg == "-max") {
            if (max_was_set) {
                std::cout << "Wrong usage! The argument '-max' was provided more than once!"
                          << std::endl;
                return -1;
            }
            if (level_was_set) {
                std::cout << "Wrong_usage! Arguments '-max' and '-level' cannot be used together!"
                          << std::endl;
                return -1;
            }
            if (i + 1 >= argc) {
                std::cout << "Wrong usage! The argument '-max' requires exactly one value!"
                          << std::endl;
                return -1;
            }
            max_value = std::stoi(argv[i+1]);
            if (max_value <= 0) {
                std::cout << "Wrong usage! The argument '-max' must be positive!"
                          << std::endl;
                return -1;
            }
            max_was_set = true;
            ++i;
        }
        else if (arg == "-level") {
            if (level_was_set) {
                std::cout << "Wrong usage! The argument '-level' was provided more than once!"
                          << std::endl;
                return -1;
            }
            if (max_was_set) {
                std::cout << "Wrong usage! Arguments '-max' and '-level' cannot be used together!"
                          << std::endl;
                return -1;
            }
            int level = std::stoi(argv[i+1]);
            if (level == 1) {
                max_value = 10;
            }
            else if (level == 2) {
                max_value = 50;
            }
            else if (level == 3) {
                max_value = 100;
            }
            else {
                std::cout << "Wrong usage! The argument '-level' must be 1, 2, or 3!"
                          << std::endl;
                return -1;
            }
            level_was_set = true;
            ++i;
        }
        else {
            std::cout << "Unknown argument: " << arg << std::endl;
            return -1;
        }
    }
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::string user_name;
    std::cin >> user_name;
    const int target_value = get_rnd_int(max_value);
    const int attempts_count = guess(target_value);
    save_results(user_name, attempts_count);
    show_results();
    return 0;
}
