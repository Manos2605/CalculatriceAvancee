#include "../header/formes.h"

void drawBox(const std::string& message) {
    std::string border(message.size() + 4, '*');
    std::cout << border << std::endl;
    std::cout << "* " << message << " *" << std::endl;
    std::cout << border << std::endl;
}