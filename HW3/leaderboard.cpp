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
    std::vector<std::string> names;
    std::vector<int> best_scores;
    while(true) {
        std::string username;
        int score = 0;
        in_file >> username;
        in_file >> score;
        in_file.ignore();
        if (in_file.fail()) {
            break;
        }
        bool user_found = false;
        for (int i = 0; i < names.size(); ++i) {
            if (names[i] == username) {
                user_found = true;
                if (score < best_scores[i]) {
                    best_scores[i] = score;
                }
                break;
            }
        }
        if (!user_found) {
            names.push_back(username);
            best_scores.push_back(score);
        }
    }
    in_file.close();
    std::ofstream out_file(high_scores_filename);
    if (!out_file.is_open()) {
        std::cout << "Failed to open file for write: "
                  << high_scores_filename
                  << "!"
                  << std::endl;
        return -1;
    }
    for (int i = 0; i < names.size(); ++i) {
        out_file << names[i] << " " << best_scores[i] << std::endl;
    }
    out_file.close();
    std::cout << "High scores table:" << std::endl;
    for (int i = 0; i < names.size(); ++i) {
        std::cout << names[i] << "\t" << best_scores[i] << std::endl;
    }
    return 0;
}
