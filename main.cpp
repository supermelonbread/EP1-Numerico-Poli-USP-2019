#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include "fatoracaoQR.h"

#include "rotGivens.h"

using namespace std;

int main() {
	
	vector<vector<double> > a;

	//m * n is the size of the matrix

	int m = 4, n = 3;
	//Grow rows by m
	a.resize(m);
	for (int i = 0; i < m; ++i)
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
	a[0] = { 1, -1, 4 };
	a[1] = { 1, 4, -2 };
	a[2] = { 1, 4, 2 };
	a[3] = { 1, -1, 0 };

	cout << "Matriz inicial: " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	
	QR(a);

	cout << endl << "Matriz final: " << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}