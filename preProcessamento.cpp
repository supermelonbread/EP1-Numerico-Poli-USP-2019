#include "preProcessamento.h"
#include "fatoracaoNaoNeg.h"
#include "fatoracaoQR.h"
#include "MatrixOperations.h"
#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <iostream>
#include <math.h>

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
	int numLinA = numLinhas * numColunas;
	vector<vector<double>> A (numLinA, vector<double>(numImagens));
	//A.resize(numLinA);
	/*for (int i = 0; i < A.size(); i++){
		A[i].resize(numImagens);
	}
*/
	// ler do arquivo e armazenar na matriz A diretamente do arquivo e divide o valor por 255
	// repare que essa funcao serve para o caso generico de organizar a matriz em linha
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



	int numLinA = numLinhas * numColunas;
	vector<vector<double>> A(numLinA, vector<double>(numImagens));
	//A.resize(numLinA);
	//for (int i = 0; i < A.size(); i++) {
	//	A[i].resize(numImagens);
	//}

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
	int tamLinW = W.size();
	int tamColW = W[0].size();
	for (int i = 0; i < tamLinW; i++) {
		for (int j = 0; j < tamColW; j++) {
			output << W[i][j] << " ";
		}
		output << "\n";
	}

	output.close();

	return W;
}

void Aprende(string nomeDoArquivo, vector<vector<double>> A, int p, int numLinhas, int numColunas, int numImagens) {
	vector<vector<double>> W;
	fstream output(nomeDoArquivo, ios::out);

	if (!output.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo" << endl;
		return;
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
	int tamLinW = W.size();
	int tamColW = W[0].size();
	for (int i = 0; i < tamLinW; i++) {
		for (int j = 0; j < tamColW; j++) {
			output << W[i][j] << " ";
		}
		output << "\n";
	}

	output.close();
}
/*
Apos a fase de treinamento com ndig treino deve-se usar o conjunto de testes para se aferir o porcentual de acerto dos classificadores.
As imagens que serao usadas para os testes devem ser lidas do arquivo test images.txt e armazenadas em uma matriz A com 784 linhas e n test colunas,
sendo 10000 o numero de imagens neste arquivo, e portanto o maximo valor possıvel para o numero de imagens n test que se deseja testar.

Para cada dıgito devemos resolver o sistema WdH = A, no sentido de m´ınimos quadrados, onde H e uma matriz p × n test
(atraves do metodo de fatoracao QR da matriz Wd correspondente - veja a secao sobre sistemas simultaneos).

Calculamos entao, para cada coluna cj de A−WdH sua norma euclidiana (||cj || = SQRT(Soma de 1 a 784 de c(i,j)^2)
Este valor
nos permitir´a avaliar se a j-´esima imagem da matriz de testes deve ou n˜ao ser um d´ıgito d. Classificaremos
a j-´esima imagem como um d´ıgito d se o valor de erro correspondente ej = ||cj || for menor que o valor de
erro obtido para os outros d´ıgitos.
Para tanto defina dois vetores de tamanho n test. Em um deles vocˆe armazenar´a qual o d´ıgito mais
prov´avel correspondente `a imagem j (dentre os d´ıgitos j´a testados) e no outro o valor do erro ej correspondente. A cada novo d´ıgito testado, obtemos os erros correspondentes a cada imagem. Se o novo valor
de ej for menor que o anterior, armazenamos este novo valor de erro - m´ınimo at´e ent˜ao - e o novo d´ıgito
como o mais prov´avel. Se o erro novo for maior que o erro armazenado, conclu´ımos que a imagem j n˜ao
corresponde a este novo d´ıgito.
Ap´os percorrermos o procedimento para todos os d´ıgitos de 0 a 9, teremos armazenada uma classifica¸c˜ao
para cada uma das n test imagens teste.

*/

// funcao para realizar os testes e verificar a taxa de acertos
void acerto(string arquivoDigito, vector<vector<double>> A, vector<double> erro, vector<double> indice,int p, int numLinhas, int numColunas, int n_teste) {

	if (n_teste > 10000) {
		cout << endl << "Numero de teste invalido" << endl;
		return;
	}

	
	vector<vector<double>> salvaA; // matriz para deixar sempre salvo os valores a serem testados
	salvaA = A;

	vector<vector<double>> W(numLinA, vector<double>(p)); // declaracao da matriz onde serao armazenados os dados aprendidos
	//W.resize(numLinA);
	//for (int i = 0; i < numLinA; i++)
	//	W[i].resize(p);
	vector<vector<double>> H;
	vector<vector<double>> erro(n_teste, vector<double>(2, 0)); // matriz onde sera salvo qual provavelmente e aquele digito, inicialmente recebera 0 em todas suas casas

	// resolvendo o sistema para o digito 0
	fstream input0(arquivoDigito, ios::in);
	if (!input0.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D0" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input0.eof()); j++) {
			input0 >> W[i][j];
		}
		input0.ignore(99999999, '\n');
	}

	input0.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema

	A = salvaA;

	vector<vector<double>> produto;
	produto = MMultiplication(W, H); // produto de W e H

	vector<vector<double>> subtracao(produto.size(), vector<double>(produto[0].size())); // Matriz para salvar A - WH

	int tamColProd = produto[0].size();
	int tamLinProd = produto.size();
	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		// como se trata do primeiro caso, vai ser o erro inicial
		erro[j][0] = s;
		// nao preciso atribuir o erro[1][j] = 0 pois ja foi feito na declaracao
	}

}

