#include "fatoracaoQR.h"
#include <math.h>
#include <vector>
#include <stdlib.h>
#include "rotGivens.h"
#include <iostream>


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

// a funcao segue o algoritmo apresentado acima
// realiza a fatoracao QR da matriz de entrada
void QR(vector<vector<double> >& matriz) {
	int tamColMatriz = matriz[0].size();
	int tamLinMatriz = matriz.size();
    vector<vector<double>> temporario;
    double cosseno, seno, temp;

	for (int k = 0; k < tamColMatriz; k++) {
		for (int j = tamLinMatriz - 1; j > k; j--)  {
			int i = j - 1;
			if (fabs(matriz[j][k]) > ZERO) {

				if (fabs(matriz[i][k]) > fabs(matriz[j][k])) {
					temp = -matriz[j][k] / matriz[i][k];
					cosseno = 1 / sqrt(1 + temp * temp);
					seno = cosseno * temp;
					//Givens(matriz, i, j, seno, cosseno);

					temporario = matriz;
					for (int k = 0; k < tamColMatriz; k++) {
						matriz[i][k] = cosseno * temporario[i][k] - seno * temporario[j][k];
					}
					for (int k = 0; k < tamColMatriz; k++) {
						matriz[j][k] = cosseno * temporario[j][k] + seno * temporario[i][k];
					}

				}
				else {
					temp = -matriz[i][k] / matriz[j][k];
					seno = 1 / sqrt(1 + temp * temp);
					cosseno = seno * temp;
					//Givens(matriz, i, j, seno, cosseno);

					temporario = matriz;
					for (int k = 0; k < tamColMatriz; k++) {
						matriz[i][k] = cosseno * temporario[i][k] - seno * temporario[j][k];
					}
					for (int k = 0; k < tamColMatriz; k++) {
						matriz[j][k] = cosseno * temporario[j][k] + seno * temporario[i][k];
					}
				}
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

// utiliza a decomposicao QR para resolver um sistema determinado ou sobredeterminado
// utiliza o algoritmo apresentado acima
vector<double> solucaoSistemas(vector<vector<double> >& matriz, vector<double>& vetor)
{
	// parte 1: realiza a decomposicao QR na matriz e no vetor
	int tamColMatriz = matriz[0].size();
	int tamLinMatriz = matriz.size();
	double cosseno, seno, temp;
	vector<vector<double>> temporario;
	vector<double> tempvec;

	for (int k = 0; k < tamColMatriz; k++) {
		for (int j = tamLinMatriz - 1; j > k; j--) {
			int i = j - 1;
			if (fabs(matriz[j][k]) > ZERO) {

				if (fabs(matriz[i][k]) > fabs(matriz[j][k])) {
					temp = -matriz[j][k] / matriz[i][k];
					cosseno = 1 / sqrt(1 + temp * temp);
					seno = cosseno * temp;
					//Givens(matriz, vetor, i, j, seno, cosseno);

					temporario = matriz;
					tempvec = vetor;
					for (int k = 0; k < tamColMatriz; k++) {
						matriz[i][k] = cosseno * temporario[i][k] - seno * temporario[j][k];
					}

					// realizo no vetor B a mesma alteracao feita na matriz A
					vetor[i] = cosseno * tempvec[i] - seno * tempvec[j];

					for (int k = 0; k < tamColMatriz; k++) {
						matriz[j][k] = cosseno * temporario[j][k] + seno * temporario[i][k];
					}

					// realizo no vetor B a mesma alteracao feita na matriz A
					vetor[j] = cosseno * tempvec[j] + seno * tempvec[i];
				}
				else {
					temp = -matriz[i][k] / matriz[j][k];
					seno = 1 / sqrt(1 + temp * temp);
					cosseno = seno * temp;
					//Givens(matriz, vetor, i, j, seno, cosseno);

					temporario = matriz;
					tempvec = vetor;
					for (int k = 0; k < tamColMatriz; k++) {
						matriz[i][k] = cosseno * temporario[i][k] - seno * temporario[j][k];
					}

					// realizo no vetor B a mesma alteracao feita na matriz A
					vetor[i] = cosseno * tempvec[i] - seno * tempvec[j];

					for (int k = 0; k < tamColMatriz; k++) {
						matriz[j][k] = cosseno * temporario[j][k] + seno * temporario[i][k];
					}

					// realizo no vetor B a mesma alteracao feita na matriz A
					vetor[j] = cosseno * tempvec[j] + seno * tempvec[i];
				}
			}
		}
	}
	// parte 2: resolve o sistema
	vector<double> x;
	x.resize(tamColMatriz);

	for (int k = matriz[0].size() - 1; k >= 0; k--) {
		if (k == matriz[0].size() - 1) { x[k] = vetor[k] / matriz[k][k]; }
		else {
			double soma = 0;
			for (int j = k + 1; j <= matriz[0].size() - 1; j++) {
				soma += matriz[k][j] * x[j] / matriz[k][k];
			}
			x[k] = vetor[k] / matriz[k][k] - soma;
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
// resolve multiplos sistemas (determinados ou sobredeterminados)
// utiliza o algoritmo apresentado acima
// caso similar com o anterior, mas agora temos uma matriz de valores para as equacoes, nao apenas um vetor
vector<vector<double>> solucaoSimultaneos(vector<vector<double>>& W, vector<vector<double>>& A) {
	// Realiza a decomposicao QR
	int tamColW = W[0].size();
	int tamLinW = W.size();
	int tamCol2 = A[0].size();
    double cosseno, seno, temp;
    double temporario;
    double tempmat;

    // Realiza a rotacao de givens
    // Coloquei toda a funcao aqui dentro ao inves de chamar a funcao
    // Por uma razao: ao chamar ela o programa ficava muito mais lento
    // Realizando assim o programa roda mais rapido

	for (int k = 0; k < tamColW; k++){
		for (int j = tamLinW - 1; j > k; j--){
			int i = j - 1;
			if (fabs(W[j][k]) > ZERO){

				if (fabs(W[i][k]) > fabs(W[j][k])){
					temp = -W[j][k] / W[i][k];
					cosseno = 1 / sqrt(1 + temp * temp);
					seno = cosseno * temp;
					//Givens(W, A, i, j, seno, cosseno);

					// alteracoes feitas na matriz A e B sao as mesmas, em loops diferente pois podem possuir tamanhos diferentes
					for (int k = 0; k < tamColW; k++){
                        temporario = cosseno * W[i][k] - seno * W[j][k];
                        W[j][k] = cosseno * W[j][k] + seno * W[i][k];
						W[i][k] = temporario;
					}

					for (int k = 0; k < tamCol2; k++){
                        tempmat = cosseno * A[i][k] - seno * A[j][k];
                        A[j][k] = cosseno * A[j][k] + seno * A[i][k];
						A[i][k] = tempmat;
					}
				}
				else {
					temp = -W[i][k] / W[j][k];
					seno = 1 / sqrt(1 + temp * temp);
					cosseno = seno * temp;
					//Givens(W, A, i, j, seno, cosseno);

					// alteracoes feitas na matriz A e B sao as mesmas, em loops diferente pois podem possuir tamanhos diferentes
					for (int k = 0; k < tamColW; k++){
                        temporario = cosseno * W[i][k] - seno * W[j][k];
                        W[j][k] = cosseno * W[j][k] + seno * W[i][k];
						W[i][k] = temporario;
					}

					for (int k = 0; k < tamCol2; k++){
                        tempmat = cosseno * A[i][k] - seno * A[j][k];
                        A[j][k] = cosseno * A[j][k] + seno * A[i][k];
						A[i][k] = tempmat;
                    }
				}
			}
		}
	}

	// Resolve o sistema
	int tamLinA = A.size();
	int tamColA = A[0].size();

	vector<vector<double>> H(tamColW, vector<double>(tamColA));

	int k = tamColW - 1;

	for (int j = 0; j < tamColA; j++) 	// loop proprio para o caso em que k = W[0].size() - 1
		H[k][j] = A[k][j] / W[k][k];

	for (int k = tamColW - 2; k >= 0; k--){ // loop para os demais casos
		for (int j = 0; j < tamColA; j++){
				double soma = 0;
				for (int i = k + 1; i < tamColW; i++){
					soma += W[k][i] * H[i][j] / W[k][k];
				}
				H[k][j] = A[k][j] / W[k][k] - soma;
		}
	}
	return H;
}
