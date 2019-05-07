#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include "fatoracaoQR.h"
#include "MatrixOperations.h"
#include "rotGivens.h"
#include "fatoracaoNaoNeg.h"

using namespace std;

int main() {

	vector<vector<double> > a;

	//m * n is the size of the matrix

	int m = 3, n = 3;
	//Grow rows by m
	a.resize(m);
	for (int i = 0; i < m; i++)
	{
		//Grow Columns by n
		a[i].resize(n);
	}
	//Now you have matrix m*n with default values

	//you can use the Matrix, now
	//a[0] = { 2, 1, 1, -1, 1 };
	//a[1] = { 0, 3, 0, 1, 2 };
	//a[2] = { 0, 0, 2, 2, -1 };
	//a[3] = { 0, 0, -1, 1, 2 };
	//a[4] = { 0, 0, 0, 3, 1 };
	a[0] = { 0.3, 0.6, 0 };
	a[1] = { 0.5, 0, 1 };
	a[2] = { 0.4, 0.8, 0 };


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
	//int p = 2;
	//b.resize(m);
	//for (int i = 0; i < m; i++)
	//	b[i].resize(p);
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

	cout << "Matriz inicial: " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	
	//cout << "B inicial: " << endl;
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < p; j++) {
	//		cout << b[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	
	vector<vector<double>> x;

	// IMPORTANTE LEMBRAR DISSO
	cout << endl << "Numero de colunas: " << a[0].size() << endl;
	cout << "Numero de linhas: " << a.size() << endl;

	x = NMF(a, 2);

	cout << endl << "Matriz final: " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//cout << "B final: " << endl;
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < p; j++) {
	//		cout << b[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	cout << endl << endl;
	cout << "Solucao: " << endl;
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x[0].size(); j++) {
			cout << x[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}