#include <string>
#include <vector>
using namespace std;

#ifndef preProcessamento
#define preProcessamento

vector<vector<double>> preProcessaImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens);
vector<vector<double>> adquireImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens);
vector<vector<double>> aprendizagem(string nomeDoArquivo, vector<vector<double>> A, int p, int numLinhas, int numColunas, int numImagens);
void Aprende(string nomeDoArquivo, vector<vector<double>> A, int p, int numLinhas, int numColunas, int numImagens);
void acerto(string arquivoD0, string arquivoD1, string arquivoD2, string arquivoD3, string arquivoD4,
	string arquivoD5, string arquivoD6, string arquivoD7, string arquivoD8, string arquivoD9,
	string arquivoTestes, string arquivoIndices, int p, int numLinhas, int numColunas, int n_teste);

#endif 

