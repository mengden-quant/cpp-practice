#include <iostream>
#include <string>

#include "demo.hpp"
#include "list_type_container.hpp"
#include "sequential_container.hpp"
#include "sequential_container_with_capacity.hpp"
#include "singly_list_container.hpp"

int main(int argc, char** argv) {
    //  === Sequential Container ===
    run_demo<SequentialContainer<int>>("Sequential Container");
    run_move_demo<SequentialContainer<int>>("Sequential Container");
    run_r_value_demo<SequentialContainer<std::string>>("Sequential Container");

    //  === List Type Container ===
    run_demo<ListTypeContainer<int>>("List Type Container");
    run_move_demo<ListTypeContainer<int>>("List Type Container");
    run_r_value_demo<ListTypeContainer<std::string>>("List Type Container");

    //  === Sequential Container with capacity ===
    run_demo<SequentialContainerCap<int>>("Sequential Container with capacity");
    run_move_demo<SequentialContainerCap<int>>("Sequential Container with capacity");
    run_r_value_demo<SequentialContainerCap<std::string>>("Sequential Container with capacity");

    //  === Singly List Container ===
    run_demo<SinglyListTypeContainer<int>>("Singly List Container");
    run_move_demo<SinglyListTypeContainer<int>>("Singly List Container");
    run_r_value_demo<SinglyListTypeContainer<std::string>>("Singly List Container");
    return 0;
}