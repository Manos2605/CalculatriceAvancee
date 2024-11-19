#include <iostream>
#include<cmath>

#ifndef FONCTIONS_H
#define FONCTIONS_H

bool isNumerique(char c);
int Longueur(const std::string& str);
std::string extraireChaine(const std::string& str, int& position, int longueur);
double completeOperation(const std::string& operation, int& position);
double AnalyseTerme(const std::string& operation, int& position);
double AnalyseOperation(const std::string& operation, int& position);
double AnalyseNumber(const std::string& operation, int& position);
double AnalyseFonction(const std::string& operation, int& position);

#endif