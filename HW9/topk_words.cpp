// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <thread>
#include <vector>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string& str);

void count_words(std::istream& stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;
    const auto file_count = static_cast<std::size_t>(argc - 1);
    std::vector<Counter> counters(file_count);
    std::vector<int> errors(file_count, 0);
    std::vector<std::thread> threads;

    for (int i = 1; i < argc; ++i) {
        const auto index = static_cast<std::size_t>(i - 1);
        threads.emplace_back([&, i, index]() {
            std::ifstream input{argv[i]};
            if (!input.is_open()) {
                errors[index] = 1;
                return;
            }
            count_words(input, counters[index]);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (int i = 1; i < argc; ++i) {
        const auto index = static_cast<std::size_t>(i - 1);
        if (errors[index] != 0) {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;
        }
    }

    for (const auto& counter : counters) {
        for (const auto& [word, count] : counter) {
            freq_dict[word] += count;
        }
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_us.count() << " us\n";
}

std::string tolower(const std::string& str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str), std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
}

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
                  [&counter](const std::string& s) { ++counter[tolower(s)]; });
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());

    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    const auto top_k = std::min(k, words.size());
    std::partial_sort(std::begin(words), std::begin(words) + top_k, std::end(words),
                      [](auto lhs, auto& rhs) { return lhs->second > rhs->second; });

    std::for_each(std::begin(words), std::begin(words) + top_k,
                  [&stream](const Counter::const_iterator& pair) {
                      stream << std::setw(4) << pair->second << " " << pair->first << '\n';
                  });
}
