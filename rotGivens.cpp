#include "rotGivens.h"
#include <math.h>
#include <vector>

using namespace std;
/* 
	rotação de givens
	dada a matriz w e as linhas i e j, tal que i<j
	os valores que não estão na linha i e j ficaram o mesmo
	b(i,k) = cos(teta)*w(i,k) − sen(teta)*w(j,k)
	b(j,k) = sin(teta)*w(i,k) + cos(teta)*w(j,k)
	k = 1, ..., m
	saída é a matriz b
*/

// OBS: teta deve ser em radianos
void Givens(vector< vector<double> >& matriz, int i, int j, double teta)
{
	vector<vector<double>> temp = matriz;
	for (int k = 0; k < matriz[i].size(); k++) { matriz[i][k] = cos(teta) * temp[i][k] - sin(teta) * temp[j][k]; }
	for (int k = 0; k < matriz[i].size(); k++) { matriz[j][k] = cos(teta) * temp[j][k] + sin(teta) * temp[i][k]; }
}

void Givens(vector<vector<double> >& matriz, int i, int j, double seno, double cosseno)
{
	vector<vector<double>> temp = matriz;
	for (int k = 0; k < matriz[i].size(); k++) { matriz[i][k] = cosseno * temp[i][k] - seno * temp[j][k]; }
	for (int k = 0; k < matriz[i].size(); k++) { matriz[j][k] = cosseno * temp[j][k] + seno * temp[i][k]; }
}

void Givens(vector<vector<double> >& matriz, vector<double>& vetor, int i, int j, double seno, double cosseno) 
{
	vector<vector<double>> temp = matriz;
	vector<double> tempvec = vetor;
	for (int k = 0; k < matriz[i].size(); k++) { matriz[i][k] = cosseno * temp[i][k] - seno * temp[j][k]; }
	vetor[i] = cosseno * tempvec[i] - seno * tempvec[j];
	for (int k = 0; k < matriz[i].size(); k++) { matriz[j][k] = cosseno * temp[j][k] + seno * temp[i][k]; }
	vetor[j] = cosseno * tempvec[j] + seno * tempvec[i];
}