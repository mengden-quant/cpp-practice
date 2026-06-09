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
    std::cout << seqcontainer << std::endl;
    std::cout << seqcontainer.size() << std::endl;
    seqcontainer.erase(2);
    seqcontainer.erase(3);
    seqcontainer.erase(4);
    std::cout << seqcontainer << std::endl;
    seqcontainer.insert(0, 10);
    std::cout << seqcontainer << std::endl;
    seqcontainer.insert(seqcontainer.size() / 2, 20);
    std::cout << seqcontainer << std::endl;
    seqcontainer.insert(seqcontainer.size(), 30);
    std::cout << seqcontainer << std::endl;

    //  === List Type Container ===
    std::cout << "List Type Container:" << std::endl;
    ListTypeContainer<int> listtypecontainer;
    listtypecontainer.push_back(0);
    listtypecontainer.push_back(1);
    listtypecontainer.push_back(2);
    listtypecontainer.push_back(3);
    listtypecontainer.push_back(4);
    listtypecontainer.push_back(5);
    listtypecontainer.push_back(6);
    listtypecontainer.push_back(7);
    listtypecontainer.push_back(8);
    listtypecontainer.push_back(9);
    std::cout << listtypecontainer << std::endl;
    std::cout << listtypecontainer.size() << std::endl;
    listtypecontainer.erase(2);
    listtypecontainer.erase(3);
    listtypecontainer.erase(4);
    std::cout << listtypecontainer << std::endl;
    listtypecontainer.insert(0, 10);
    std::cout << listtypecontainer << std::endl;
    listtypecontainer.insert(listtypecontainer.size() / 2, 20);
    std::cout << listtypecontainer << std::endl;
    listtypecontainer.insert(listtypecontainer.size(), 30);
    std::cout << listtypecontainer << std::endl;
    return 0;
}