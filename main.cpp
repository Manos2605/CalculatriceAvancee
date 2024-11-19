#include <iostream>
#include "header/fonctions.h"
#include "header/formes.h"


int main() {
    while (true){
        drawBox("Bienvenue Calculatrice Avancee (exit pour quitter)");
        std::cout << "\nEntrer une operation: ";
        std::string operation;
        std::cin >> operation;
        int posistion = 0;
        try {
            double result = AnalyseOperation(operation, posistion);
            std::cout << "Result: " << result << std::endl;
            std::cout << "Voulez-vous effectuer une autre operation? (o/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'n') {
                break;
            }
        } catch (...) {
            std::cout << "Error: Operation invalide" << std::endl;
        }
    }

    return 0;
}