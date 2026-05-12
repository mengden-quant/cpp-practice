#include "rnd.hpp"
#include <cstdlib>
#include <ctime>

int get_rnd_int(int max_value) {
    std::srand(std::time(nullptr));
    const int rnd_value = std::rand() % max_value;
    return rnd_value;
}
