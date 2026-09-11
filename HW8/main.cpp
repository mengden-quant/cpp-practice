#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char>& data, uint32_t value) {
    std::copy_n(reinterpret_cast<const char*>(&value), 4, data.end() - 4);
}

/**
 * @brief Ищет комбинацию последних 4 байт, при которой CRC32 изменённого
 * вектора совпадает с CRC32 оригинального вектора
 * @details CRC32 неизменяемого префикса original + injection вычисляется
 * один раз. При переборе кандидатов CRC32 продолжается из сохраненного
 * состояния только для последних 4 байт.
 * @param original оригинальный вектор
 * @param injection строка, добавляемая после данных оригинального вектора
 * @param begin начало диапазона поиска, включительно
 * @param end конец диапазона поиска, не включительно
 * @return готовый изменённый вектор с совпадающим CRC32 или std::nullopt,
 * если в заданном диапазоне подходящее значение не найдено
 */
std::optional<std::vector<char>> hack(const std::vector<char>& original,
                                      const std::string& injection, std::uint64_t begin,
                                      std::uint64_t end) {
    const uint32_t originalCrc32 = crc32(original.data(), original.size());

    std::vector<char> result(original.size() + injection.size() + 4);
    auto it = std::copy(original.begin(), original.end(), result.begin());
    std::copy(injection.begin(), injection.end(), it);

    constexpr std::uint64_t rangeEnd = std::uint64_t{std::numeric_limits<std::uint32_t>::max()} + 1;
    if (end > rangeEnd) {
        end = rangeEnd;
    }
    const auto prefixSize = result.size() - 4;
    const uint32_t prefixCrc = crc32(result.data(), prefixSize);
    const uint32_t prefixState = ~prefixCrc;

    for (std::uint64_t i = begin; i < end; ++i) {
        const uint32_t candidate = static_cast<uint32_t>(i);
        replaceLastFourBytes(result, candidate);
        auto currentCrc32 = crc32(result.data() + result.size() - 4, 4, prefixState);

        if (currentCrc32 == originalCrc32) {
            return result;
        }
    }
    return std::nullopt;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Call with two args: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    unsigned int threadCount = std::thread::hardware_concurrency();

    if (threadCount == 0) {
        threadCount = 2;
    }
    std::vector<std::optional<std::vector<char>>> results(threadCount);
    std::vector<std::thread> threads;

    constexpr std::uint64_t totalValues =
        std::uint64_t{std::numeric_limits<std::uint32_t>::max()} + 1;
    try {
        const std::vector<char> data = readFromFile(argv[1]);
        const std::string injection = "He-he-he";
        for (std::uint64_t i = 0; i < threadCount; ++i) {
            std::uint64_t begin = i * totalValues / threadCount;
            std::uint64_t end = (i + 1) * totalValues / threadCount;
            std::thread thread(
                [&, i, begin, end]() { results[i] = hack(data, injection, begin, end); });

            threads.push_back(std::move(thread));
        }
        for (auto& thread : threads) {
            thread.join();
        }
        bool found = false;
        for (const auto& result : results) {
            if (result.has_value()) {
                writeToFile(argv[2], result.value());
                std::cout << "Success\n";
                found = true;
                break;
            }
        }

        if (!found) {
            throw std::logic_error("Can't hack");
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return 2;
    }
    return 0;
}
