#include "Controller.h"
#include <iostream>

int main() {
    Controller controller;

    std::cout << "Presentation CLI\n";
    std::cout << "Commands: add slide, remove slide, list, exit\n\n";

    std::string line;
    while (!controller.shouldExitProgram()) {
        std::cout << "(ppt) > ";
        std::getline(std::cin, line);

        if (line.empty()) {
            continue;
        }
        
        if (!controller.processCommand(line)) {
            std::cerr << "Error: " << controller.getLastError() << "\n";
        }
    }

    return 0;
}