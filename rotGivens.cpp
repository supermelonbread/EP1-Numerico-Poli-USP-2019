#include "rotGivens.h"
#include <math.h>
#include <vector>

using namespace std;
/*
	rotacao de givens
	dada a matriz w e as linhas i e j, tal que i<j
	os valores que não estão na linha i e j ficaram o mesmo
	b(i,k) = cos(teta)*w(i,k) − sen(teta)*w(j,k)
	b(j,k) = sin(teta)*w(i,k) + cos(teta)*w(j,k)
	k = 1, ..., m
	saída é a matriz b
*/

// OBS: teta deve ser em radianos
// realiza a rotacao de givens em uma matriz para um dado teta
void Givens(vector< vector<double> >& matriz, int i, int j, double teta)
{
	vector<vector<double>> temp = matriz;
	for (int k = 0; k < matriz[i].size(); k++) {
		matriz[i][k] = cos(teta) * temp[i][k] - sin(teta) * temp[j][k];
	}
	for (int k = 0; k < matriz[i].size(); k++) {
		matriz[j][k] = cos(teta) * temp[j][k] + sin(teta) * temp[i][k];
	}
}

// realiza a rotacao de givens dado um valor para seno e cosseno
void Givens(vector<vector<double> >& matriz, int i, int j, double seno, double cosseno)
{
	vector<vector<double>> temp = matriz;
	for (int k = 0; k < matriz[i].size(); k++) {
		matriz[i][k] = cosseno * temp[i][k] - seno * temp[j][k];
	}
	for (int k = 0; k < matriz[i].size(); k++) {
		matriz[j][k] = cosseno * temp[j][k] + seno * temp[i][k];
	}
}

// como o sistema e um sistema linear pode ser escrito da forma Ax=B
// em que A é a matriz de entrada, x é um vetor com as solucoes e B é um vetor com o valor do resultado de cada equacao
// devo realizar em B todas as alteracoes feitas na matriz A, para que o sistema continue com a mesma solucao
void Givens(vector<vector<double> >& matriz, vector<double>& vetor, int i, int j, double seno, double cosseno)
{
	vector<vector<double>> temp = matriz;
	vector<double> tempvec = vetor;
	for (int k = 0; k < matriz[i].size(); k++) {
		matriz[i][k] = cosseno * temp[i][k] - seno * temp[j][k];
	}

	// realizo no vetor B a mesma alteracao feita na matriz A
	vetor[i] = cosseno * tempvec[i] - seno * tempvec[j];

	for (int k = 0; k < matriz[i].size(); k++) {
		matriz[j][k] = cosseno * temp[j][k] + seno * temp[i][k];
	}

	// realizo no vetor B a mesma alteracao feita na matriz A
	vetor[j] = cosseno * tempvec[j] + seno * tempvec[i];
}

// sistema parecido com o do caso anterior, mas agora ao inves de existir apenas um valor para cada equacao
// sao varios sistemas lineares (B agora e uma matriz, nao um vetor)
// o sistema continua a forma Ax=B
// mas agora x e B sao matrizes
void Givens(vector<vector<double>>& matriz, vector<vector<double>>& matriz2, int i, int j, double seno, double cosseno)
{
	vector<vector<double>> temp = matriz;
	vector<vector<double>> tempmat = matriz2;

	// alteracoes feitas na matriz A e B sao as mesmas, em loops diferente pois podem possuir tamanhos diferentes
	for (int k = 0; k < matriz[i].size(); k++)
		matriz[i][k] = cosseno * temp[i][k] - seno * temp[j][k];
	for (int k = 0; k < matriz2[i].size(); k++)
		matriz2[i][k] = cosseno * tempmat[i][k] - seno * tempmat[j][k];

	for (int k = 0; k < matriz[i].size(); k++)
		matriz[j][k] = cosseno * temp[j][k] + seno * temp[i][k];
	for (int k = 0; k < matriz2[i].size(); k++)
		matriz2[j][k] = cosseno * tempmat[j][k] + seno * tempmat[i][k];
}
