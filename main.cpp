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

	int m = 4, n = 4;
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
	a[0] = { 1, 2.38629, 3.19722, 3.77258 };
	a[1] = { 4.21887, 4.58351, 4.89182, 5.15888 };
	a[2] = { 5.39445, 5.60517, 5.79579, 5.96981 };
	a[3] = { 6.12989, 6.27811, 6.41610, 6.54517 };

	vector<double> b;
	b.resize(4);
	b = { 1, 2, 3, 4 };


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

	x = QR(a, b);

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
	cout << "Soluçao: " << endl;
	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;

	return 0;
}