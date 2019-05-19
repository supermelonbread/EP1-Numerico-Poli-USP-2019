#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <chrono> // verificar quanto tempo leva para rodar
#include <iomanip>// tirar essa biblioteca depois
#include "fatoracaoQR.h"
#include "MatrixOperations.h"
#include "rotGivens.h"
#include "fatoracaoNaoNeg.h"
#include "preProcessamento.h"


#define numeroLinhas 28
#define numeroColunas 28
#define tamanhoP 5
#define numeroImagens 100
#define numeroTestes 10000

using namespace std;
using namespace std::chrono;

int main() {

	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	vector<vector<double>> b, W0, W1, W2, W3, W4, W5, W6, W7, W8, W9;

	cout << "EP1 Calculo Numerico" << endl;
	cout << "Alunos: Lucas Werner e Pedro Rabelo" << endl;
	cout << endl;
	cout << "Parametros utilizados: " << endl;
	cout << "p = " << tamanhoP << endl;
	cout << "ndig_treino = " << numeroImagens << endl;
	cout << "n_test = " << numeroTestes << endl;

	b = adquireImagem("train_dig0.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig0 \n");
	W0 = aprendizagem("treino_d0_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 0 feito \n");

	b = adquireImagem("train_dig1.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig1 \n");
	W1 = aprendizagem("treino_d1_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 1 feito \n");

	b = adquireImagem("train_dig2.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig2 \n");
	W2 = aprendizagem("treino_d2_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 2 feito \n");

	b = adquireImagem("train_dig3.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig3 \n");
	W3 = aprendizagem("treino_d3_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 3 feito \n");

	b = adquireImagem("train_dig4.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig4 \n");
	W4 = aprendizagem("treino_d4_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 4 feito \n");

	b = adquireImagem("train_dig5.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig5 \n");
	W5 = aprendizagem("treino_d5_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 5 feito \n");

	b = adquireImagem("train_dig6.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig6 \n");
	W6 = aprendizagem("treino_d6_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 6 feito \n");

	b = adquireImagem("train_dig7.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig7 \n");
	W7 = aprendizagem("treino_d7_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 7 feito \n");

	b = adquireImagem("train_dig8.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig8 \n");
	W8 = aprendizagem("treino_d8_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 8 feito \n");

	b = adquireImagem("train_dig9.txt", numeroLinhas, numeroColunas, numeroImagens);
	//printf("Realizando dig9 \n");
	W9 = aprendizagem("treino_d9_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	//printf("Digito 9 feito \n");


	vector<double> erro(numeroTestes);
	vector<double> indice(numeroTestes, 0);

	// arquivo com as imagens para testar se acertou a classificacao
	fstream input("test_images.txt", ios::in);
	if (!input.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo de teste de imagens" << endl;
		return 0;
	}
	int numLinA = numeroLinhas * numeroColunas;
	vector<vector<double>> A(numLinA, vector<double>(numeroTestes));
	for (int i = 0; i < numLinA; i++) {
		for (int j = 0; j < numeroTestes && !(input.eof()); j++) {
			input >> A[i][j];
		}
		input.ignore(99999999, '\n');
	}
	input.close();
	
	//printf("Realizando classificacao: \n");
	classificaDigito(W0, A, erro, indice, 0, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W1, A, erro, indice, 1, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W2, A, erro, indice, 2, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W3, A, erro, indice, 3, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W4, A, erro, indice, 4, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W5, A, erro, indice, 5, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W6, A, erro, indice, 6, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W7, A, erro, indice, 7, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W8, A, erro, indice, 8, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	classificaDigito(W9, A, erro, indice, 9, tamanhoP, numeroLinhas, numeroColunas, numeroTestes);
	

	double acertos;
	double acerto0, acerto1, acerto2, acerto3, acerto4, acerto5, acerto6, acerto7, acerto8, acerto9;
	acertos = taxaDeAcerto("test_index.txt", indice, numeroImagens, acerto0, acerto1, acerto2, acerto3, acerto4, acerto5, acerto6, acerto7, acerto8, acerto9);
	cout <<"Taxa de acerto total: " << acertos*100 <<"%" << endl;
	cout << "Acertos do digito 0: " << acerto0 * 100 << "%" << endl;
	cout << "Acertos do digito 1: " << acerto1 * 100 << "%" << endl;
	cout << "Acertos do digito 2: " << acerto2 * 100 << "%" << endl;
	cout << "Acertos do digito 3: " << acerto3 * 100 << "%" << endl;
	cout << "Acertos do digito 4: " << acerto4 * 100 << "%" << endl;
	cout << "Acertos do digito 5: " << acerto5 * 100 << "%" << endl;
	cout << "Acertos do digito 6: " << acerto6 * 100 << "%" << endl;
	cout << "Acertos do digito 7: " << acerto7 * 100 << "%" << endl;
	cout << "Acertos do digito 8: " << acerto8 * 100 << "%" << endl;
	cout << "Acertos do digito 9: " << acerto9 * 100 << "%" << endl;

	auto end = chrono::high_resolution_clock::now();

	// Calculating total time taken by the program. 
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;

	cout << "Time taken by program is : " << fixed
		<< time_taken << setprecision(9);
	cout << " sec" << endl;

	return 0;
}
