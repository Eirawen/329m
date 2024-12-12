#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

void processVector() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

void processMap() {
    std::map<std::string, int> myMap = {{"Alice", 25}, {"Bob", 30}};
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << std::endl;
    }
}

void processSet() {
    std::set<int> mySet = {1, 2, 3, 4, 5};
    for (int s : mySet) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string message = "Hello, World!";
    std::cout << message << std::endl;

    processVector();
    processMap();
    processSet();

    return 0;
}
