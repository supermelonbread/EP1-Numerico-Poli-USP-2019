#include "fatoracaoQR.h"
#include <math.h>
#include <vector>
#include <stdlib.h>
#include "rotGivens.h"


#define	ZERO 0.0001

using namespace std;

/*	Fatoração QR:
	dado n o número de linhas e m o número de colunas

	Para k = 1 até m faça
		Para j = n até k + 1 com passo −1 faça
			i = j − 1
			Se w(j,k) != 0 aplique Q(i, j, θ) a matriz W (com cos e sin definidos por w(i,k) e w(j,k))
		Fim do para
	Fim do para

	caso |w(i,k)| > |w(j,k)|
	τ = −w(j,k)/w(i,k)
	cosseno = 1/raiz(1 + τ)
	seno = seno*τ

	caso contrário
	τ = −w(i,k)/w(j,k)
	seno = 1/raiz(1 + τ)
	cosseno = seno*τ

*/

void QR(vector<vector<double> >& matriz)
{
	for (int k = 0; k < matriz[0].size(); k++)
	{
		for (int j = matriz.size() - 1; j > k; j--) 
		{
			int i = j - 1;
			if (abs(matriz[j][k]) > ZERO)
			{
				double cosseno, seno, temp;
				if (abs(matriz[i][k]) > abs(matriz[j][k]))
				{
					temp = -matriz[j][k] / matriz[i][k];
					cosseno = 1 / sqrt(1 + temp * temp);
					seno = cosseno * temp;
					Givens(matriz, i, j, seno, cosseno);
				}
				else {
					temp = -matriz[i][k] / matriz[j][k];
					seno = 1 / sqrt(1 + temp * temp);
					cosseno = seno * temp;
					Givens(matriz, i, j, seno, cosseno);
				}
			}
		}
	}
	// Zera os valores praticamente nulos
	for (int i = 0; i < matriz[0].size(); i++) {
		for (int j = 0; j < matriz.size(); j++) {
			if (abs(matriz[j][i]) < ZERO) {
				matriz[j][i] = 0;
			}	
		}
	}
}

/*	Fatoração QR:
	dado n o número de linhas e m o número de colunas

	Para k = 1 até m faça
		Para j = n até k + 1 com passo −1 faça
			i = j − 1
			Se w(j,k) != 0 aplique Q(i, j, θ) a matriz W e ao vetor b(com cos e sin definidos por w(i,k) e w(j,k))
		Fim do para
	Fim do para
	Para k = m a 1 com passo -1
		x(k) = (b(k) - Somatório de j = k+1 a m de w(k,j)*x(j))/w(k,k)
	Fim do para

	caso |w(i,k)| > |w(j,k)|
	τ = −w(j,k)/w(i,k)
	cosseno = 1/raiz(1 + τ)
	seno = seno*τ

	caso contrário
	τ = −w(i,k)/w(j,k)
	seno = 1/raiz(1 + τ)
	cosseno = seno*τ

*/
vector<double> solucaoSistemas(vector<vector<double> >& matriz, vector<double>& vetor)
{
	for (int k = 0; k < matriz[0].size(); k++)
	{
		for (int j = matriz.size() - 1; j > k; j--)
		{
			int i = j - 1;
			if (abs(matriz[j][k]) > ZERO)
			{
				double cosseno, seno, temp;
				if (abs(matriz[i][k]) > abs(matriz[j][k]))
				{
					temp = -matriz[j][k] / matriz[i][k];
					cosseno = 1 / sqrt(1 + temp * temp);
					seno = cosseno * temp;
					Givens(matriz, vetor, i, j, seno, cosseno);
				}
				else {
					temp = -matriz[i][k] / matriz[j][k];
					seno = 1 / sqrt(1 + temp * temp);
					cosseno = seno * temp;
					Givens(matriz, vetor, i, j, seno, cosseno);
				}
			}
		}
	}
	vector<double> x;
	x.resize(matriz[0].size());
	for (int k = matriz[0].size() - 1; k >= 0; k--)
	{
		if (k == matriz[0].size() - 1) { x[k] = vetor[k] / matriz[k][k]; }
		else
		{
			double soma = 0;
			for (int j = k + 1; j <= matriz[0].size() - 1; j++)
			{
				soma += matriz[k][j] * x[j] / matriz[k][k];
			}
			x[k] = vetor[k] / matriz[k][k] - soma;
		}
	}
	// Zera os valores praticamente nulos
	for (int i = 0; i < matriz[0].size(); i++) {
		for (int j = 0; j < matriz.size(); j++) {
			if (abs(matriz[j][i]) < ZERO) {
				matriz[j][i] = 0;
			}
		}
	}
	return x;
}

/* Dado sistema da forma |A - WH| 

Em que A é uma matriz n x m
W é n x p   e    H é p x m

Com entrada A e W a saída é a matriz H que resolve o sistema pelo MMQ

	Para k=1 a p faca  -> p = numero de colunas de W
		Para j=n a k+1 com passo -1 faca    -> n = numero de linhas de A e W
			i=j-1
			Se w(j,k) != 0 aplique Q(i, j, θ) a matriz W e a matriz A (com cosseno e seno definidos por w(i,k) e w(j,k))
		Fim do para
	Fim do para

	Para k=p a 1 com passo -1
		Para j=1 a m faca      -> m = numero de colunas de A 
			h(k,j) = (a(k,j) − somatorio de i = k + 1 a p de w(k,i) h(i,j) )/w(k,k)
		Fim do para
	Fim do para

	caso |w(i,k)| > |w(j,k)|
	τ = −w(j,k)/w(i,k)
	cosseno = 1/raiz(1 + τ)
	seno = seno*τ

	caso contrário
	τ = −w(i,k)/w(j,k)
	seno = 1/raiz(1 + τ)
	cosseno = seno*τ

*/

vector<vector<double>> solucaoSimultaneos(vector<vector<double>>& W, vector<vector<double>>& A) 
{
	for (int k = 0; k < W[0].size(); k++)
	{
		for (int j = W.size() - 1; j > k; j--)
		{
			int i = j - 1;
			if (abs(W[j][k]) > ZERO)
			{
				double cosseno, seno, temp;
				if (abs(W[i][k]) > abs(W[j][k]))
				{
					temp = -W[j][k] / W[i][k];
					cosseno = 1 / sqrt(1 + temp * temp);
					seno = cosseno * temp;
					Givens(W, A, i, j, seno, cosseno);
				}
				else {
					temp = -W[i][k] / W[j][k];
					seno = 1 / sqrt(1 + temp * temp);
					cosseno = seno * temp;
					Givens(W, A, i, j, seno, cosseno);
				}
			}
		}
	}
	vector<vector<double>> H;
	H.resize(W[0].size()); // numero de linhas
	for (int i = 0; i < H.size(); i++)
	{
		H[i].resize(A[0].size()); // numero de colunas
	}

	for (int k = W[0].size() - 1; k >= 0; k--)
	{
		for (int j = 0; j < A[0].size(); j++)
		{
			if (k == W[0].size() - 1) 
				H[k][j] = A[k][j] / W[k][k]; 
			else
			{
				double soma = 0;
				for (int i = k + 1; i < W[0].size(); i++)
				{
					soma += W[k][i] * H[i][j] / W[k][k];
				}
				H[k][j] = A[k][j] / W[k][k] - soma;
			}
		}
	}
	// Zera os valores praticamente nulos
	for (int i = 0; i < W[0].size(); i++) {
		for (int j = 0; j < W.size(); j++) {
			if (abs(W[j][i]) < ZERO) {
				W[j][i] = 0;
			}
		}
	}
	for (int i = 0; i < A[0].size(); i++) {
		for (int j = 0; j < A.size(); j++) {
			if (abs(A[j][i]) < ZERO) {
				A[j][i] = 0;
			}
		}
	}
	for (int i = 0; i < H[0].size(); i++) {
		for (int j = 0; j < H.size(); j++) {
			if (abs(H[j][i]) < ZERO) {
				H[j][i] = 0;
			}
		}
	}
	return H;
}
