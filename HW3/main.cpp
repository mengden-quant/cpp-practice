#include <iostream>
#include <string>
#include "rnd.hpp"
#include "guess.hpp"
#include "leaderboard.hpp"

int main() {
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::string user_name;
    std::cin >> user_name;
    int max_value = 100;
    const int target_value = get_rnd_int(max_value);
    const int attempts_count = guess(target_value);
    save_results(user_name, attempts_count);
    show_results();
    return 0;
}