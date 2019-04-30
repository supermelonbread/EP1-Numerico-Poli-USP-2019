#include "fatoracaoQR.h"
#include <math.h>
#include <vector>
#include <stdlib.h>
#include "rotGivens.h"


#define	ZERO 0.0001
#define NULL 0

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

	//	TESTAR EM OUTRO PC PARA VER SE DETECTA O ERRO TAMBÉM


	for (int i = 0; i < matriz[0].size(); i++) {
		for (int j = 0; j < matriz.size(); j++) {
			if (abs(matriz[j][i]) < ZERO) {
				matriz[j][i] = 0;
			}
				
		}
	}
}

