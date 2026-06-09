#include <iostream>

#include "list_type_container.hpp"
#include "sequential_container.hpp"
#include "sequential_container_with_capacity.hpp"
#include "singly_list_container.hpp"
#include "demo.hpp"

int main(int argc, char** argv) {
    //  === Sequential Container ===
    run_demo<SequentialContainer<int>>("Sequential Container");

    //  === List Type Container ===
    run_demo<ListTypeContainer<int>>("List Type Container");

    //  === Sequential Container with capacity ===
    run_demo<SequentialContainerCap<int>>("Sequential Container with capacity");

    //  === Singly List Container ===
    run_demo<SinglyListTypeContainer<int>>("Singly List Container");
    return 0;
}