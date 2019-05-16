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
#include <thread> // biblioteca para trabalhar em paralelo
//#include <amp.h> // biblioteca para trabalhar em paralelo

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

	vector<vector<double> > a;

	//m * n is the size of the matrix

	//int m = 3, n = 3;
	////Grow rows by m
	//a.resize(m);
	//for (int i = 0; i < m; i++)
	//{
	//	//Grow Columns by n
	//	a[i].resize(n);
	//}
	//Now you have matrix m*n with default values

	//a[0] = { 0.3, 0.6, 0 };
	//a[1] = { 0.5, 0, 1 };
	//a[2] = { 0.4, 0.8, 0 };


	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		if (abs(i - j) < 5) {
	//			double soma = i + j + 1;
	//			a[i][j] = 1 / soma;
	//		}
	//		else if (abs(i - j) > 4)
	//			a[i][j] = 0;
	//		else
	//			a[i][j] = 0;
	//	}
	//}

	// b é m * p
	vector<vector<double>> b;
	/*int p = 2;
	b.resize(m);
	for (int i = 0; i < m; i++)
		b[i].resize(p);*/
	//b = { 1, 2, 4, 8 };
	//b = { 1,2 };
	/*for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			if (j == 0)
				b[i][j] = 1;
			else if (j == 1) 
				b[i][j] = (i + 1);
			else if (j == 2)
				b[i][j] = 2 * (i + 1) - 1;
		}
	}*/

	//cout << "Matriz inicial: " << endl;
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		cout << a[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	
	//cout << "B inicial: " << endl;
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < p; j++) {
	//		cout << b[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	
	vector<vector<double>> x;

	// IMPORTANTE LEMBRAR DISSO
	//cout << endl << "Numero de colunas: " << a[0].size() << endl;
	//cout << "Numero de linhas: " << a.size() << endl;

	
	// treinamento
	b = adquireImagem("train_dig0.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig0 \n");
	Aprende("treino_d0_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 0 feito \n");

	b = adquireImagem("train_dig1.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig1 \n");
	Aprende("treino_d1_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 1 feito \n");

	b = adquireImagem("train_dig2.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig2 \n");
	Aprende("treino_d2_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 2 feito \n");

	b = adquireImagem("train_dig3.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig3 \n");
	Aprende("treino_d3_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 3 feito \n");

	b = adquireImagem("train_dig4.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig4 \n");
	Aprende("treino_d4_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 4 feito \n");

	b = adquireImagem("train_dig5.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig5 \n");
	Aprende("treino_d5_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 5 feito \n");

	b = adquireImagem("train_dig6.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig6 \n");
	Aprende("treino_d6_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 6 feito \n");

	b = adquireImagem("train_dig7.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig7 \n");
	Aprende("treino_d7_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 7 feito \n");

	b = adquireImagem("train_dig8.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig8 \n");
	Aprende("treino_d8_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 8 feito \n");

	b = adquireImagem("train_dig9.txt", numeroLinhas, numeroColunas, numeroImagens);
	printf("Realizando dig9 \n");
	Aprende("treino_d9_p5_treino100.txt", b, tamanhoP, numeroLinhas, numeroColunas, numeroImagens);
	printf("Digito 9 feito \n");
	
	//acerto("treino_d0_p5_treino100.txt", "treino_d1_p5_treino100.txt", "treino_d2_p5_treino100.txt", "treino_d3_p5_treino100.txt",
	//	"treino_d4_p5_treino100.txt", "treino_d5_p5_treino100.txt", "treino_d6_p5_treino100.txt", "treino_d7_p5_treino100.txt", "treino_d8_p5_treino100.txt",
	//	"treino_d9_p5_treino100.txt", "test_images.txt", "test_index.txt", tamanhoP, numeroLinhas, numeroColunas, numeroTestes);

	//cout << endl << "Matriz final: " << endl;
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		cout << a[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	/*cout << "B final: " << endl;*/
	//for (int i = 0; i < b.size(); i++) {
	//	for (int j = 0; j < b[0].size(); j++) {
	//		cout << b[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	/*cout << "Solucao: " << endl;*/
	//for (int i = 0; i < x.size(); i++) {
	//	for (int j = 0; j < x[0].size(); j++) {
	//		cout << x[i][j] << " ";
	//	}
	//	cout << endl;
	//}


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