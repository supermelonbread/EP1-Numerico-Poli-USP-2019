#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include "fatoracaoQR.h"
#include "MatrixOperations.h"
#include "rotGivens.h"

using namespace std;

int main() {

	vector<vector<double> > a;

	//m * n is the size of the matrix

	int m = 4, n = 2;
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
	a[0] = { 1, 0 };
	a[1] = { 1, 1 };
	a[2] = { 1, 2 };
	a[3] = { 1, 3 };

	vector<double> b;
	b.resize(m);
	b = { 1, 2, 4, 8 };
	//b = { 1,2 };

	cout << "Matriz inicial: " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	cout << "B inicial: " << endl;
	for (int i = 0; i < b.size(); i++) {
		cout << b[i] << " ";
	}
	cout << endl;

	vector<double> x;

	// IMPORTANTE LEMBRAR DISSO
	cout << endl << "Numero de colunas: " << a[0].size() << endl;
	cout << "Numero de linhas: " << a.size() << endl;

	x = solucaoSistemas(a, b);

	cout << endl << "Matriz final: " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "B final: " << endl;
	for (int i = 0; i < b.size(); i++) {
		cout << b[i] << " ";
	}
	cout << endl << endl;
	cout << "Solucao: " << endl;
	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;

	return 0;
}