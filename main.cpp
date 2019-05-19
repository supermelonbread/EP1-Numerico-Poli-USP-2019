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


	int m = 700;
	int n = 100;
	vector<vector<double>> W(m, vector<double>(n));
	vector<double> b(n);
	vector<double> x(n);
	int k = 0;
	double a;


    for (int i = 0; i < W.size(); i++) {
		for (int j = 0; j < W[0].size(); j++) {
            a = rand() %50;
            W[i][j]  = a/50;
		}
	}


	printf("Matriz Inicial: \n");
//	W = preProcessaImagem("teste.txt", 3, 1, 3);

	vector<vector<double>> A;
	vector<vector<double>> B;

//	for (int i = 0; i < W.size(); i++) {
//		cout << "|";
//		for (int j = 0; j < W[0].size(); j++) {
//			cout << " " << W[i][j] << " ";
//		}
//		cout << "|" << endl;
//	}
/*
	printf("Vetor B: \n");

	for (int k = 0; k < b.size(); k++) {
		cout << b[k] << " ";
	}

	cout << endl;
	*/
    //A = aprendizagem("saida.txt", W, 2, 3, 3, 1);
    A = NMF(W, 5, B);
    printf("Matriz 1: \n");

//	for (int i = 0; i < A.size(); i++) {
//		cout << "|";
//		for (int j = 0; j < A[0].size(); j++) {
//			cout << " " << A[i][j] << " ";
//		}
//		cout << "|" << endl;
//	}
//
//	printf("Matriz 2: \n");
//
//	for (int i = 0; i < B.size(); i++) {
//		cout << "|";
//		for (int j = 0; j < B[0].size(); j++) {
//			cout << " " << B[i][j] << " ";
//		}
//		cout << "|" << endl;
//	}
//
//	vector<vector<double>> M;
//	M = MMultiplication(A, B);
//
//	printf("\n Matriz Multiplicada: \n");
//
//	for (int i = 0; i < M.size(); i++) {
//		cout << "|";
//		for (int j = 0; j < M[0].size(); j++) {
//			cout << " " << M[i][j] << " ";
//		}
//		cout << "|" << endl;
//	}
/*
	printf("Vetor B modificado: \n");

	for (int k = 0; k < b.size(); k++) {
		cout << b[k] << " ";

	}
	cout << endl;

	printf("Vetor X: \n");

	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}

	cout << endl;
*/


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
