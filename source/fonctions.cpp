#include "../header/fonctions.h"

// Vérifie si un caractère est un chiffre (de '0' à '9')
bool isNumerique(char c) {
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
double AnalyseOperation(const std::string& operation, int& position) {
    if (position < Longueur(operation) && operation[position] == '(') {
        ++position;
        double result = completeOperation(operation, position);
        if (position < Longueur(operation) && operation[position] == ')') {
            ++position;
        }
        return result;
    } else {
        return AnalyseNumber(operation, position);
    }
}

// Analyse les termes d'une opération multiplication, division
double AnalyseTerme(const std::string& operation, int& position) {
    double result = AnalyseOperation(operation, position);
    while (position < Longueur(operation)) {
        if (operation[position] == '*') {
            ++position;
            result *= AnalyseOperation(operation, position);
        } else if (operation[position] == '/') {
            ++position;
            result /= AnalyseOperation(operation, position);
        } else if (operation[position] == '+' || operation[position] == '-') {
            break;
        } else {
            result = AnalyseFonction(operation, position);
        }
    }
    return result;
}

// Analyse une expression complète
double completeOperation(const std::string& operation, int& position) {
    double result = AnalyseTerme(operation, position);
    while (position < Longueur(operation)) {
        if (operation[position] == '+') {
            ++position;
            result += AnalyseTerme(operation, position);
        } else if (operation[position] == '-') {
            ++position;
            result -= AnalyseTerme(operation, position);
        } else {
            break;
        }
    }
    return result;
}

// Analyse les nombres à virgule flottante
double AnalyseNumber(const std::string& operation, int& position) {
    double result = 0.0;
    bool decimalPoint = false;
    double decimalPlace = 0.1;

    while (position < Longueur(operation) && (isNumerique(operation[position]) || operation[position] == '.')) {
        if (operation[position] == '.') {
            decimalPoint = true;
        } else if (!decimalPoint) {
            result = result * 10 + (operation[position] - '0');
        } else {
            result += (operation[position] - '0') * decimalPlace;
            decimalPlace /= 10;
        }
        ++position;
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