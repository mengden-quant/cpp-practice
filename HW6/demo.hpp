
#include <string>
#include <utility>

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

template <typename Container>
void run_move_demo(const char* title) {
    std::cout << title << " move constructor:" << std::endl;
    Container source;
    source.push_back(1);
    source.push_back(2);
    Container destination = std::move(source);
    std::cout << destination << std::endl;
    std::cout << destination.size() << std::endl;
    std::cout << source.size() << std::endl;
    std::cout << title << " move assignment:" << std::endl;
    Container first;
    first.push_back(1);
    first.push_back(2);
    Container second;
    second.push_back(99);
    second = std::move(first);
    std::cout << second << std::endl;
    std::cout << second.size() << std::endl;
    std::cout << first.size() << std::endl;
    second = std::move(second);
    std::cout << second.size() << std::endl;
}

template <typename Container>
void run_r_value_demo(const char* title) {
    std::cout << title << " r-value demo:" << std::endl;
    Container c;
    std::string s = "hello";
    c.push_back(s);
    c.insert(1, std::string{"world"});
    c.push_back(std::move(s));
    std::cout << c << std::endl;
}
