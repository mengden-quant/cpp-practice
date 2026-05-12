#include "leaderboard.hpp"
#include <iostream>
#include <fstream>
#include <string>

int save_results(const std::string& user_name, int attempts_count) {
    const std::string high_scores_filename = "high_scores.txt";
    std::ofstream out_file(high_scores_filename, std::ios_base::app);
    if (!out_file.is_open()) {
        std::cout << "Failed to open file for write: "
                  << high_scores_filename
                  << "!"
                  << std::endl;
        return -1;
    }
    out_file << user_name << " " << attempts_count << std::endl;
    return 0;
}

int show_results() {
    const std::string high_scores_filename = "high_scores.txt";
    std::ifstream in_file{high_scores_filename};
    if (!in_file.is_open()) {
        std::cout << "Failed to open file for read: "
                  << high_scores_filename
                  << "!"
                  << std::endl;
        return -1;
    }
    std::cout << "High scores table:" << std::endl;
    std::string username;
    int high_score = 0;
    while(true) {
        in_file >> username;
        in_file >> high_score;
        in_file.ignore();
        if (in_file.fail()) {
            break;
        }
        std::cout << username << "\t" << high_score << std::endl;
    }
return 0;
}
