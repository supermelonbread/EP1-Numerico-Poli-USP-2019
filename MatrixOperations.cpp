#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

#include "MatrixOperations.h"

using namespace std;

vector<vector<double> > MMultiplication(vector<vector<double> > a, vector<vector<double> > b) {

	/*
	a_columns = a[0].size();
	a_rows = a.size();
	b_columns = b[0].size();
	b_rows = b.size();
	*/

	vector<vector<double>> result(a.size(), vector<double>(b[0].size()));

	if (a[0].size() != b.size()) {
		cout << "Erro: O numero de colunas da primeira matriz nao eh igual ao numero de linhas da segunda coluna!" << endl;
		return result;
	}

	for (int i = 0; i < a.size(); i++) { //i iterate a rows
		for (int j = 0; j < b[0].size(); j++) //j iterates b columns
		{
			for (int k = 0; k < a[0].size(); k++) { //k goes back to a and iterates its columns
				cout << i << "x" << j << endl;

				result[i][j] += a[i][k] * b[k][j]; //sums all multiplications into result[i][j]

			}
		}
	}

	return result;
}

vector<vector<double> > MTranspose(vector<vector<double> > a) {

	vector<vector <double> > result(a[0].size(), vector<double>(a.size())); //result constructor passing lines 

	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[0].size(); j++) {
			result[j][i] = a[i][j];
		}
	}

	return result;
}