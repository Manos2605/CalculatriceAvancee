#include "../header/fonctions.h"

// Vérifie si un caractère est un chiffre (de '0' à '9')
bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

// Calcule et retourne la longueur d'une chaîne
int Longueur(const std::string& str) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

// Fonction pour extraire une sous-chaine
std::string extraireChaine(const std::string& str, int& position, int longueur) {
    std::string result = "";
    for (int i = 0; i < longueur && position < Longueur(str); ++i) {
        result += str[position++];
    }
    return result;
}

// Analyse les opérations de base addition, soustraction et les parenthèses
double completeOperation(const std::string& operation, int& posistion) {
    if (posistion < Longueur(operation) && operation[posistion] == '(') {
        ++posistion;
        double result = AnalyseOperation(operation, posistion);
        if (posistion < Longueur(operation) && operation[posistion] == ')') {
            ++posistion;
        }
        return result;
    } else {
        return AnalyseNumber(operation, posistion);
    }
}

// Analyse les termes d'une opération multiplication, division
double AnalyseTerme(const std::string& operation, int& posistion) {
    double result = completeOperation(operation, posistion);
    while (posistion < Longueur(operation)) {
        if (operation[posistion] == '*') {
            ++posistion;
            result *= completeOperation(operation, posistion);
        } else if (operation[posistion] == '/') {
            ++posistion;
            result /= completeOperation(operation, posistion);
        } else {
            break;
        }
    }
    return result;
}

// Analyse une expression complète
double AnalyseOperation(const std::string& operation, int& posistion) {
    double result = AnalyseTerme(operation, posistion);
    while (posistion < Longueur(operation)) {
        if (operation[posistion] == '+') {
            ++posistion;
            result += AnalyseTerme(operation, posistion);
        } else if (operation[posistion] == '-') {
            ++posistion;
            result -= AnalyseTerme(operation, posistion);
        } else {
            break;
        }
    }
    return result;
}

// Analyse les nombres à virgule flottante
double AnalyseNumber(const std::string& operation, int& posistion) {
    double result = 0.0;
    bool decimalPoint = false;
    double decimalPlace = 0.1;

    while (posistion < Longueur(operation) && (isDigit(operation[posistion]) || operation[posistion] == '.')) {
        if (operation[posistion] == '.') {
            decimalPoint = true;
        } else if (!decimalPoint) {
            result = result * 10 + (operation[posistion] - '0');
        } else {
            result += (operation[posistion] - '0') * decimalPlace;
            decimalPlace /= 10;
        }
        ++posistion;
    }
    return result;
}

// trigonométriques
double AnalyseFonction(const std::string& operation, int& position) {
    if (position + 3 <= Longueur(operation) && extraireChaine(operation, position, 3) == "cos") {
        position += 3;
        if (position < Longueur(operation) && operation[position] == '(') {
            ++position;
            double result = completeOperation(operation, position);
            if (position < Longueur(operation) && operation[position] == ')') {
                ++position;
                return cos(result * (M_PI / 180.0));
            }
        }
    } else if (position + 3 <= Longueur(operation) && extraireChaine(operation, position, 3) == "sin") {
        position += 3;
        if (position < Longueur(operation) && operation[position] == '(') {
            ++position;
            double result = completeOperation(operation, position);
            if (position < Longueur(operation) && operation[position] == ')') {
                ++position;
                return sin(result * (M_PI / 180.0));
            }
        }
    }
    return AnalyseNumber(operation, position);
}