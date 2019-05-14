#include "preProcessamento.h"
#include "fatoracaoNaoNeg.h"
#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
/*
	Cada imagem e uma matrix nx × ny(no caso acima, 28 × 28) com valores entre 0 e 255 (escala RGB), que
	representam escalas de cinza, sendo 0 o preto e o 255 o branco.

	Ha algumas etapas importantes de pre - processamento das imagens para que estas possam ser representadas
	por uma unica matriz A, que sera usada no metodo de aprendizagem :

		Leitura de m imagens originais, cada uma com tamanho nx × ny de uma base de dados fornecida.

			Cada imagem deve ser redimensionada para se tornar um vetor coluna com n = nx ny linhas.No exemplo
			dado, cada imagem e convertida em um vetor coluna de tamanho n = 282 = 784. Essa transformacao
			pode ser feita simplesmente “empilhando” as colunas da matrix que define a imagem.

			Juntam - se os m vetores colunas gerados para formar uma matrix A de tamanho n × m, onde cada coluna
			representa uma imagem.

			Por fim, e conveniente normalizarmos os valores da matriz for¸cando com que fiquem entre 0 e 1. O mais
			simples neste caso e simplesmente dividir cada elemento da matriz por 255, que e o maior valor da escala
			RGB.
*/

// IMPORTANTE VERIFICAR SE ESTA DIVIDINDO POR 255
vector<vector<double>> preProcessaImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens) {

	// abre o arquivo para leitura
	fstream input(nomeDoArquivo, ios::in);
	if (!input.is_open()) {
		cout << endl <<"Nao foi possivel abrir o arquivo" << endl;
		return vector<vector<double>> ();
	}
	
	// declaracao da matriz A
	vector<vector<double>> A;
	int numLinA = numLinhas * numColunas;
	A.resize(numLinA);
	for (int i = 0; i < A.size(); i++){
		A[i].resize(numImagens);
	}

	// ler do arquivo e armazenar na matriz A transformando cada imagem em uma coluna 
	double temp;
	for (int j = 0; j < numImagens ; j++){
		for (int i = 0; i < numLinA && !(input.eof()); i++) {
			input >> temp;
			A[i][j] = temp/255;
		}
	}
	input.close();

	return A;
}

// funcao a ser utilizada pois parte do pre processamento ja foi feito
// adquire a imagem da forma que esta, arrumando apenas o modulo

vector<vector<double>> adquireImagem(string nomeDoArquivo, int numLinhas, int numColunas, int numImagens) {
	fstream input(nomeDoArquivo, ios::in);
	if (!input.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo" << endl;
		return vector<vector<double>>();
	}


	vector<vector<double>> A;
	int numLinA = numLinhas * numColunas;
	A.resize(numLinA);
	for (int i = 0; i < A.size(); i++) {
		A[i].resize(numImagens);
	}

	// ler do texto
	double temp;
	for (int i = 0; i < numLinA; i++) {
		for (int j = 0; j < numImagens && !(input.eof()); j++) {
			input >> temp;
			A[i][j] = temp/255;
		}
		input.ignore(99999999, '\n');
	}

	input.close();

	return A;
}

/*
	A partir da matriz A, que contem informacoes referentes a um unico dıgito, podemos realizar a fatoracao nao
	negativa desta matriz em p componentes.

	Por exemplo, usando a base de imagens MNIST com 5958 imagens manuscritas do numero 2, encontramos
	p = 10 componentes W que estao representadas na figura abaixo.
	Cada imagem abaixo representa uma coluna da matriz W.
	Estas foram novamente escritas na forma 28 × 28 e reescaladas, multiplicando por 255, para a visualizacao
	sempre que voce quiser visualizar uma imagem sera necessario este procedimento.
	Cada uma representa um “perfil tıpico” de um 2.

	A matrix W representa o que foi aprendido sobre o dıgito manuscrito 2,
	a partir dos dados disponıveis de aprendizagem e sera usada na classificacao de dıgitos.
*/

vector<vector<double>> aprendizagem(string nomeDoArquivo, vector<vector<double>> A, int p, int numLinhas, int numColunas, int numImagens) {
	vector<vector<double>> W;
	fstream output(nomeDoArquivo, ios::out);

	if (!output.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo" << endl;
		return vector<vector<double>>();
	}

	

	// obter W

	W = NMF(A, p);
	//W = A;

	// caso tenha que salvar W no formato original

	 //int contador = 0;
	//for (int z = 0; z < numImagens; z++) {
	//	for (int i = 0; i < numLinhas; i++) {
	//		for (int j = 0; j < numColunas; j++) {
	//			output << W[contador][z] << " ";  // coloca os valores separador por espaco
	//			contador++;
	//		}
	//		output << "\n"; // pula a linha
	//	}
	//	output << "\n";
	//	contador = 0;
	//}

	// salvando W no arquivo:

	// analisar se vale a pena dividir por 255
	for (int i = 0; i < W.size(); i++) {
		for (int j = 0; j < W[0].size(); j++) {
			output << W[i][j] << " ";
		}
		output << "\n";
	}

	output.close();

	return W;
}