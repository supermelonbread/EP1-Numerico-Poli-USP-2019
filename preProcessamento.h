#include <string>
#include <vector>
using namespace std;

#ifndef preProcessamento
#define preProcessamento

vector<vector<double>> preProcessaImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens);
vector<vector<double>> adquireImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens);
vector<vector<double>> aprendizagem(string nomeDoArquivo, vector<vector<double>> A, int p, int numLinhas, int numColunas, int numImagens);


#endif #pragma once

