#include "guess.hpp"
#include <iostream>

int guess(int target_value) {
    int current_value = 0;
    int counter = 0;
    std::cout << "Enter your guess:" << std::endl;
    while(true) {
         if (!std::cin) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        ++counter;
        std::cin >> current_value;
        if (current_value < target_value) {
            std::cout << "The value is greater than " << current_value << std::endl;
        }
        else if (current_value > target_value) {
            std::cout << "The value is less than " << current_value << std::endl;
        }
        else {
            std::cout << "You win!" << std::endl;
            std::cout << "attempts: " << counter << std::endl;
            break;
        }
    }
    return counter;
}
