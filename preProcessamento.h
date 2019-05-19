#include <string>
#include <vector>
using namespace std;

#ifndef preProcessamento
#define preProcessamento

vector<vector<double>> preProcessaImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens);
vector<vector<double>> adquireImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens);
vector<vector<double>> aprendizagem(string nomeDoArquivo, vector<vector<double>> A, int p, int numLinhas, int numColunas, int numImagens);
void Aprende(string nomeDoArquivo, vector<vector<double>> A, int p, int numLinhas, int numColunas, int numImagens);
void classificaDigito(string arquivoDigito, vector<vector<double>> A, vector<double>& erro, vector<double>& indice, int digito, 
	int p, int numLinhas, int numColunas, int n_teste);
void classificaDigito(vector<vector<double>> Wdigito, vector<vector<double>> A, vector<double>& erro, vector<double>& indice, int digito,
	int p, int numLinhas, int numColunas, int n_teste);
double taxaDeAcerto(string arquivoIndices, vector<double> indice, int n_teste,
	double& acerto0, double& acerto1, double& acerto2, double& acerto3, double& acerto4, double& acerto5,
	double& acerto6, double& acerto7, double& acerto8, double& acerto9);
#endif 

