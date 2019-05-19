
#include <vector>

using namespace std;

#ifndef fatoracaoQR
#define fatoracaoQR

void QR(vector<vector<double> >& matriz);
vector<double> solucaoSistemas(vector<vector<double> >& matriz, vector<double>& vetor);
vector<vector<double>> solucaoSimultaneos(vector<vector<double>>& W, vector<vector<double>>& A);

#endif 

