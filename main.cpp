#include <iostream>
#include "header/fonctions.h"
#include "header/formes.h"

double analyser(const std::string& operation) {
    std::string cleanedOperation = nettoyerEntree(operation);
    int position = 0;
    return AnalyseOperation(cleanedOperation, position);
}

int main() {
    while (true){
        drawBox("Bienvenue Calculatrice Avancee (exit pour quitter)");
        std::cout << "\nEntrer une operation: ";
        std::string operation;
        std::cin >> operation;
        if (operation == "exit"){
            break;
        }
        int posistion = 0;
        try {
            double resultat = analyser(operation);
            std::cout << "Result: " << resultat << std::endl;
            std::cout << "Voulez-vous effectuer une autre operation? (o/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'n') {
                break;
            }
            else{
                clear();
            }
        } catch (...) {
            std::cout << "Error: Operation invalide" << std::endl;
        }
    }

    return 0;
}
