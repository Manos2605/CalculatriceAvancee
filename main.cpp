#include <iostream>
#include "header/fonctions.h"
#include "header/formes.h"


int main(int argc, char** argv){
    drawBox("Binvenue sur la Calculatrice Avancée (Exit pour quitter)");

    while ((true))
    {
       try {
        std::cout << "Entrer l'opération à exécuter: ";
        std::string operation;
        std::cin >> operation;
        if (operation == "exit"){
            break;
        }
        int position = 0;
        double result = completeOperation(operation, position);
        std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << std::endl;
        } 
    }
    return 0;
}