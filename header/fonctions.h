#include <iostream>
#include<cmath>

#ifndef FONCTIONS_H
#define FONCTIONS_H

bool isDigit(char c);   
int Longueur(const std::string& str);
std::string extraireChaine(const std::string& str, int& position, int longueur);
double AnalyseOperation(const std::string& operation, int& posistion);
double AnalyseTerme(const std::string& operation, int& posistion);
double completeOperation(const std::string& operation, int& posistion);
double AnalyseNumber(const std::string& operation, int& posistion);
double AnalyseFonction(const std::string& operation, int& position);

#endif