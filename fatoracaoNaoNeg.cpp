#include "fatoracaoNaoNeg.h"
#include "fatoracaoQR.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include "MatrixOperations.h"

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
// realiza a fatoracao nao negativa da matriz de entrada
// utiliza o algoritmo apresentado acima
// a saida da funcao e a matriz Q
// como entrada temos a matriz a ser fatorada, qual deve ser o valor de p
// e a matriz saidaH se trata de um ponteiro que por deferenca ira fornecer o valor de H calculado
vector<vector<double>> NMF(vector<vector<double> >& matriz,  int p, vector<vector<double>>& saidaH) {
	vector<vector<double>> A;
	vector<vector<double>> W(matriz.size(), vector<double>(p));
	vector<vector<double>> H;
	vector<vector<double>> At; // transposta de A
	vector<vector<double>> Ht; // transposta de H
    vector<vector<double>> Wt;

	//srand(time(NULL)); // caso queira utilizar uma seed aleatoria
	int tamLinW = W.size();
	int tamColW = W[0].size();
	// inicializacao de W
	for (int i = 0; i < tamLinW; i++) {
		for (int j = 0; j < tamColW; j++) {
			W[i][j] = rand()%100; // Inicializa W com um inteiro aleatorio
			W[i][j]++; // para impedir valores nulos
		}
	}

	double erro = 1;

	for (int itmax = 0; erro > EPS && itmax < 100; itmax++) {

		A = matriz; // devo pegar esse valor em toda iteracao

		// normaliza W
		double s = 0; // norma da linha
		for (int j = 0; j < tamColW; j++) {
			double soma = 0;
			for (int i = 0; i < tamLinW; i++) {
				soma += W[i][j] * W[i][j];
			}
			s = sqrt(soma);
			for (int i = 0; i < tamLinW; i++) {
				W[i][j] = W[i][j] / s;
			}
		}

		// resolucao do mmq
		H = solucaoSimultaneos(W, A);

		int tamLinH = H.size();
		int tamColH = H[0].size();
		// Redefina H, com h(i,j) = max{0, h(i,j)}
		for (int i = 0; i < tamLinH; i++) {
			for (int j = 0; j < tamColH; j++) {
				if (H[i][j] < EPS)
					H[i][j] = 0;
			}
		}

		// calcula as transpostas
		At = MTranspose(matriz);
		Ht = MTranspose(H);

		// resolucao do mmq
		Wt = solucaoSimultaneos(Ht, At);

		int tamLinWt = Wt.size();
		int tamColWt = Wt[0].size();
		// Redefina W, com w(i,j) = max{0, w(i,j)}
		for (int i = 0; i < tamLinWt; i++) {
			for (int j = 0; j < tamColWt; j++) {
				if (Wt[i][j] < EPS)
					Wt[i][j] = 0;
			}
		}
		W = MTranspose(Wt);


		// calculo do erro quadratico
		erro = 0;
		vector<vector<double>> Aerro; // Aerro sera a matris WH
		Aerro = MMultiplication(W, H);
		int tamLinAerro = Aerro.size();
		int tamColAerro = Aerro[0].size();

		for (int i = 0; i < tamLinAerro; i++) {
			for (int j = 0; j < tamColAerro; j++) {
				double provisorio;
				provisorio = matriz[i][j] - Aerro[i][j];
				erro += provisorio * provisorio;
            }
        }
    }

    saidaH = H;
	return W;
}

// Caso nao precise do H
// O codigo e basicamente o mesmo
// A unica diferenca e que nao retorna uma matriz H por referencia
vector<vector<double>> NMF(vector<vector<double> >& matriz, int p) {
	vector<vector<double>> A;
	vector<vector<double>> W(matriz.size(), vector<double>(p));
	vector<vector<double>> H;
	vector<vector<double>> At; // transposta de A
	vector<vector<double>> Ht; // transposta de H
    vector<vector<double>> Wt;

	//srand(time(NULL));
	int tamLinW = W.size();
	int tamColW = W[0].size();
	// inicializacao de W
	for (int i = 0; i < tamLinW; i++) {
		for (int j = 0; j < tamColW; j++) {
			W[i][j] = rand()%100; // Inicializa W com um inteiro aleatorio
			W[i][j]++; // para impedir valores nulos
		}
	}

	double erro = 1;

	for (int itmax = 0; erro > EPS && itmax < 100; itmax++) {

		A = matriz; // devo pegar esse valor em toda iteracao

		// normaliza W
		double s = 0; // norma da linha
		for (int j = 0; j < tamColW; j++) {
			double soma = 0;
			for (int i = 0; i < tamLinW; i++) {
				soma += W[i][j] * W[i][j];
			}
			s = sqrt(soma);
			for (int i = 0; i < tamLinW; i++) {
				W[i][j] = W[i][j] / s;
			}
		}

		// resolucao do mmq
		H = solucaoSimultaneos(W, A);

		int tamLinH = H.size();
		int tamColH = H[0].size();
		// Redefina H, com h(i,j) = max{0, h(i,j)}
		for (int i = 0; i < tamLinH; i++) {
			for (int j = 0; j < tamColH; j++) {
				if (H[i][j] < EPS)
					H[i][j] = 0;
			}
		}

		// parte das transpostas
		At = MTranspose(matriz);
		Ht = MTranspose(H);

		// resolucao do mmq
		Wt = solucaoSimultaneos(Ht, At);

		int tamLinWt = Wt.size();
		int tamColWt = Wt[0].size();
		// Redefina W, com w(i,j) = max{0, w(i,j)}
		for (int i = 0; i < tamLinWt; i++) {
			for (int j = 0; j < tamColWt; j++) {
				if (Wt[i][j] < EPS)
					Wt[i][j] = 0;
			}
		}
		W = MTranspose(Wt);


		// calculo do erro quadratico
		erro = 0;
		vector<vector<double>> Aerro; // Aerro sera a matris WH
		Aerro = MMultiplication(W, H);
		int tamLinAerro = Aerro.size();
		int tamColAerro = Aerro[0].size();

		for (int i = 0; i < tamLinAerro; i++) {
			for (int j = 0; j < tamColAerro; j++) {
				double provisorio;
				provisorio = matriz[i][j] - Aerro[i][j];
				erro += provisorio * provisorio;
            }
        }
    }


	return W;
}
