#include "fatoracaoNaoNeg.h"
#include "fatoracaoQR.h"
#include <vector>
#include <stdio.h>      
#include <stdlib.h>    
#include <ctime>
#include <math.h>

#define EPS 0.00001

using namespace std;

/* Fatora a matriz A (n x m) nao negativa em duas matrizes
	W (n x p) e H (p x m) tambem nao negativas
	
	Com a matriz A e o valor de p:

	Inicialize randomicamente a matriz W com valores positivos
	
	Armazene uma copia da matriz A

	Repita os seguintes passos ate que a norma do erro se estabilize (diferenca entre as normas do erro em
	dois passos consecutivos < EPS (use EPS = 10−5 no seu programa) ou que um numero maximo de iteracoes
	(itmax, escolha itmax = 100) seja atingido

		Normalize W tal que a norma de cada uma de suas colunas seja 1 (w(i,j) = w(i,j)/s(j) , 
		com s(j) = raiz (somatorio de i=1 ate n de w(i,j)*w(i,j))

		Resolva o problema de minimos quadrados W H = A, determinando a matriz H (sao m sistemas
		simultaneos! Cuidado, pois A e modificada no processo de solucao. Na iteracao seguinte deve-se usar
		a matriz A original novamente. Por isso armazena-se uma copia de A!)

		Redefina H, com h(i,j) = max{0, h(i,j)}

		Compute a matriz At (transposta da matriz A original)

		Resolva o problema de minimos quadrados Ht*Wt = At, determinando a nova matriz Wt
		(sao n sistemas simultaneos!)

		Compute a matriz W (transposta de Wt)

		Redefina W, com w(i,j) = max{0, w(i,j)}
	Fim do Repita
	*/

vector<vector<double>> NMF(vector<vector<double>>& matriz, int p)
{
	vector<vector<double>> W;
	vector<vector<double>> A = matriz;

	W.resize(A.size());
	for (int i = 0; i < p; i++)
	{
		W[i].resize(p);
	}

	srand(time(NULL));

	// Posso inicializar com 0 ou apenas valores maiores do que zero??
	for (int i = 0; i < W.size(); i++)
	{
		for (int j = 0; j < W[0].size(); j++)
		{
			W[i][j] = rand() % 20; // Inicializa W com um inteiro aleatorio de 0 a 20
		}
	}

	// VERIFICAR COMO CALCULAR O ERRO
	double erro = 1;
	for (int itmax = 0; erro > EPS && itmax < 100; itmax++)
	{
		double s = 0; // norma da linha
		for (int j = 0; j < W[0].size(); j++)
		{
			double soma = 0;
			for (int i = 0; i < W.size(); i++)
			{
				soma += W[i][j]*W[i][j];
			}

			s = sqrt(soma);

			for (int i = 0; i < W.size(); i++)
			{
				W[i][j] = W[i][j] / s;
			}
		}

		// VERIFICAR SE PODE ALTERAR O VALOR DE W
		solucaoSimultaneos(W, A);
	}


	return W;
}

