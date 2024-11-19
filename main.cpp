#include <iostream>
#include "header/fonctions.h"
#include "header/formes.h"


int main() {
    std::cout << "Entrer une opération: ";
    std::string operation;
    std::getline(std::cin, operation);
    int posistion = 0;
    try {
        double result = AnalyseOperation(operation, posistion);
        std::cout << "Result: " << result << std::endl;
    } catch (...) {
        std::cout << "Error: Invalid operationession" << std::endl;
    }
    return 0;
}