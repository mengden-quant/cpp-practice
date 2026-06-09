#include <iostream>

#include "list_type_container.hpp"
#include "sequential_container.hpp"

int main(int argc, char** argv) {
    //  === Sequential Container ===
    std::cout << "Sequential Container:" << std::endl;
    SequentialContainer<int> seqcontainer;
    seqcontainer.push_back(0);
    seqcontainer.push_back(1);
    seqcontainer.push_back(2);
    seqcontainer.push_back(3);
    seqcontainer.push_back(4);
    seqcontainer.push_back(5);
    seqcontainer.push_back(6);
    seqcontainer.push_back(7);
    seqcontainer.push_back(8);
    seqcontainer.push_back(9);
    std::cout << seqcontainer.size() << std::endl;
    seqcontainer.erase(2);
    seqcontainer.erase(3);
    seqcontainer.erase(4);
    std::cout << seqcontainer << std::endl;
    seqcontainer.insert(0, 10);
    std::cout << seqcontainer << std::endl;
    seqcontainer.insert(static_cast<std::size_t>(seqcontainer.size() / 2), 20);
    std::cout << seqcontainer << std::endl;
    seqcontainer.insert(seqcontainer.size(), 30);
    std::cout << seqcontainer << std::endl;

    //  === List Type Container ===
    std::cout << "List Type Container:" << std::endl;
    ListTypeContainer<int> listtypecontaiener;
    listtypecontaiener.push_back(0);
    listtypecontaiener.push_back(1);
    listtypecontaiener.push_back(2);
    listtypecontaiener.push_back(3);
    listtypecontaiener.push_back(4);
    listtypecontaiener.push_back(5);
    listtypecontaiener.push_back(6);
    listtypecontaiener.push_back(7);
    listtypecontaiener.push_back(8);
    listtypecontaiener.push_back(9);
    std::cout << listtypecontaiener.size() << std::endl;
    listtypecontaiener.erase(2);
    listtypecontaiener.erase(3);
    listtypecontaiener.erase(4);
    std::cout << listtypecontaiener << std::endl;
    listtypecontaiener.insert(0, 10);
    std::cout << listtypecontaiener << std::endl;
    listtypecontaiener.insert(static_cast<std::size_t>(listtypecontaiener.size() / 2), 20);
    std::cout << listtypecontaiener << std::endl;
    listtypecontaiener.insert(listtypecontaiener.size(), 30);
    std::cout << listtypecontaiener << std::endl;
    return 0;
}