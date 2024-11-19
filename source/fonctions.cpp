#include "../header/fonctions.h"

// Supprime les espaces
std::string nettoyerEntree(const std::string& operation) {
    std::string resultat = "";
    for (char c : operation) {
        if (!isspace(c)) {
            resultat += c;
        }
    }
    return resultat;
}

// Vérifie si est un chiffre
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Calcule la longueur d'une chaîne
int Longueur(const std::string& str) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

// Extrait une sous-chaîne
std::string extraireChaine(const std::string& str, int& position, int longueur) {
    std::string result = "";
    for (int i = 0; i < longueur && position < Longueur(str); ++i) {
        result += str[position++];
    }
    return result;
}

// Analyse les nombres (flotants)
double AnalyseNombre(const std::string& operation, int& position) {
    double result = 0.0;
    bool decimal = false;
    double factor = 0.1;

    while (position < Longueur(operation) && (isDigit(operation[position]) || operation[position] == '.')) {
        if (operation[position] == '.') {
            decimal = true;
        } else if (decimal) {
            result += (operation[position] - '0') * factor;
            factor *= 0.1;
        } else {
            result = result * 10 + (operation[position] - '0');
        }
        ++position;
    }
    return result;
}

// Fonctions trigonométriques, logarithmiques, exponentielles
double AnalyseFonction(const std::string& operation, int& position) {
    std::string fonction = extraireChaine(operation, position, 3);

    if (fonction == "cos" || fonction == "sin" || fonction == "log" || fonction == "exp") {
        if (position < Longueur(operation) && operation[position] == '(') {
            ++position;
            double result = completeOperation(operation, position);
            if (position < Longueur(operation) && operation[position] == ')') {
                if (fonction == "cos") return cos(result * (M_PI / 180.0));
                if (fonction == "sin") return sin(result * (M_PI / 180.0));
                if (fonction == "log") {
                    if (result <= 0) throw std::domain_error("Logarithme négatif ou nul.");
                    return log(result);
                }
                if (fonction == "exp") return exp(result);
            } else {
                throw std::invalid_argument("Parenthèse fermante manquante pour " + fonction);
            }
        } else {
            throw std::invalid_argument("Parenthèse ouvrante manquante pour " + fonction);
        }
    }
    return AnalyseNombre(operation, position);
}

// les parenthèses ou les fonctions
double completeOperation(const std::string& operation, int& position) {
    if (position < Longueur(operation) && operation[position] == '(') {
        ++position;
        double result = AnalyseOperation(operation, position);
        if (position < Longueur(operation) && operation[position] == ')') {
            ++position;
        } else {
            throw std::invalid_argument("Parenthèse fermante manquante.");
        }
        return result;
    } else if (isalpha(operation[position])) {
        return AnalyseFonction(operation, position);
    } else {
        return AnalyseNombre(operation, position);
    }
}

// multiplication/division
double AnalyseTerme(const std::string& operation, int& position) {
    double result = completeOperation(operation, position);
    while (position < Longueur(operation)) {
        if (operation[position] == '*') {
            ++position;
            result *= completeOperation(operation, position);
        } else if (operation[position] == '/') {
            ++position;
            double divisor = completeOperation(operation, position);
            if (divisor == 0) throw std::domain_error("Division par zéro.");
            result /= divisor;
        } else {
            break;
        }
    }
    return result;
}

// addition/soustraction
double AnalyseOperation(const std::string& operation, int& position) {
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

