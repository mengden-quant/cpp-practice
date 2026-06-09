template <typename Container>
void run_demo(const char* title) {
    std::cout << title << ":\n";
    Container container;
    for (int i = 0; i < 10; ++i) {
        container.push_back(i);
    }
    std::cout << container << std::endl;
    std::cout << container.size() << std::endl;
    container.erase(2);
    container.erase(3);
    container.erase(4);
    std::cout << container << std::endl;
    container.insert(0, 10);
    std::cout << container << std::endl;
    container.insert(container.size() / 2, 20);
    std::cout << container << std::endl;
    container.insert(container.size(), 30);
    std::cout << container << std::endl;
}