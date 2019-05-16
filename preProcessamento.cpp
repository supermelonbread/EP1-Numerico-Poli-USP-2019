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
void acerto(string arquivoD0, string arquivoD1, string arquivoD2, string arquivoD3, string arquivoD4,
	string arquivoD5, string arquivoD6, string arquivoD7, string arquivoD8, string arquivoD9,
	string arquivoTestes, string arquivoIndices, int p, int numLinhas, int numColunas, int n_teste) {

	if (n_teste > 10000) {
		cout << endl << "Numero de teste invalido" << endl;
		return;
	}

	// adquire a matriz com os valores a serem classificados
	int numLinA = numColunas * numLinhas;
	vector<vector<double>> A(numLinA, vector<double>(n_teste)); // declaracao da matriz A
	/*A.resize(numLinA);
	for (int i = 0; i < numLinA; i++)
		A[i].resize(n_teste);*/

	fstream inputA(arquivoTestes, ios::in); // Abertura do arquivo
	if (!inputA.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo de Testes" << endl;
		return;
	}

	double temp;
	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz A
		for (int j = 0; j < n_teste && !(inputA.eof()); j++) {
			inputA >> temp;
			A[i][j] = temp / 255;
		}
		inputA.ignore(99999999, '\n');
	}

	inputA.close();
	vector<vector<double>> salvaA; // matriz para deixar sempre salvo os valores a serem testados
	salvaA = A;

	vector<vector<double>> W(numLinA, vector<double>(p)); // declaracao da matriz onde serao armazenados os dados aprendidos
	//W.resize(numLinA);
	//for (int i = 0; i < numLinA; i++)
	//	W[i].resize(p);
	vector<vector<double>> H;
	vector<vector<double>> erro(n_teste, vector<double>(2, 0)); // matriz onde sera salvo qual provavelmente e aquele digito, inicialmente recebera 0 em todas suas casas

	// resolvendo o sistema para o digito 0
	fstream input0(arquivoD0, ios::in);
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

	// resolvendo o sistema para o digito 1
	fstream input1(arquivoD1, ios::in);
	if (!input1.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D1" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input1.eof()); j++) {
			input1 >> W[i][j];
		}
		input1.ignore(99999999, '\n');
	}
	input1.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) { // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 1;
		}
	}

	// resolvendo o sistema para o digito 2
	fstream input2(arquivoD2, ios::in);
	if (!input2.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D2" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input2.eof()); j++) {
			input2 >> W[i][j];
		}
		input2.ignore(99999999, '\n');
	}
	input2.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 2;
		}
	}

	// resolvendo o sistema para o digito 3
	fstream input3(arquivoD3, ios::in);
	if (!input3.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D3" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input3.eof()); j++) {
			input3 >> W[i][j];
		}
		input3.ignore(99999999, '\n');
	}
	input3.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 3;
		}
	}

	// resolvendo o sistema para o digito 4
	fstream input4(arquivoD4, ios::in);
	if (!input4.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D4" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input4.eof()); j++) {
			input4 >> W[i][j];
		}
		input4.ignore(99999999, '\n');
	}
	input4.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 4;
		}
	}

	// resolvendo o sistema para o digito 5
	fstream input5(arquivoD5, ios::in);
	if (!input5.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D5" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input5.eof()); j++) {
			input5 >> W[i][j];
		}
		input5.ignore(99999999, '\n');
	}
	input5.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 5;
		}
	}

	// resolvendo o sistema para o digito 6
	fstream input6(arquivoD6, ios::in);
	if (!input6.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D6" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input6.eof()); j++) {
			input6 >> W[i][j];
		}
		input6.ignore(99999999, '\n');
	}
	input6.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 6;
		}
	}

	// resolvendo o sistema para o digito 7
	fstream input7(arquivoD7, ios::in);
	if (!input7.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D7" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input7.eof()); j++) {
			input7 >> W[i][j];
		}
		input7.ignore(99999999, '\n');
	}
	input7.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 7;
		}
	}

	// resolvendo o sistema para o digito 8
	fstream input8(arquivoD8, ios::in);
	if (!input8.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D8" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input8.eof()); j++) {
			input8 >> W[i][j];
		}
		input8.ignore(99999999, '\n');
	}
	input8.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 8;
		}
	}

	// resolvendo o sistema para o digito 9
	fstream input9(arquivoD9, ios::in);
	if (!input9.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo do D9" << endl;
		return;
	}

	for (int i = 0; i < numLinA; i++) { // Atribuicao da matriz W
		for (int j = 0; j < p && !(input9.eof()); j++) {
			input9 >> W[i][j];
		}
		input9.ignore(99999999, '\n');
	}
	input9.close();

	H = solucaoSimultaneos(W, A); // solucao do sistema
	A = salvaA;
	produto = MMultiplication(W, H); // produto de W e H

	for (int j = 0; j < tamColProd; j++) {
		double soma = 0;
		double s = 0;// norma da linha
		for (int i = 0; i < tamLinProd; i++) {
			subtracao[i][j] = A[i][j] - produto[i][j];
			soma += subtracao[i][j] * subtracao[i][j];
		}
		s = sqrt(soma);
		if (s < erro[j][0]) {  // caso o erro seja menor, atualiza o erro
			erro[j][0] = s;
			erro[j][1] = 9;
		}
	}

	// agora como ja sabemos como foi identificado cada digito
	// podemos verificar com o gabarito

	vector<double> gabarito(n_teste);
	fstream inputGabarito(arquivoD9, ios::in);
	if (!inputGabarito.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo dos Indices" << endl;
		return;
	}

	for (int j = 0; j < n_teste && !(inputGabarito.eof()); j++) {
		inputGabarito >> gabarito[j];
	}
	inputGabarito.close();

	double acertos0 = 0;
	double acertos1 = 0;
	double acertos2 = 0;
	double acertos3 = 0;
	double acertos4 = 0;
	double acertos5 = 0;
	double acertos6 = 0;
	double acertos7 = 0;
	double acertos8 = 0;
	double acertos9 = 0;
	for (int i = 0; i < n_teste; i++) {
		if (gabarito[i] == erro[i][1]) {
			if (gabarito[i] == 0) {
				acertos0++;
			}
			else if (gabarito[i] == 1) {
				acertos1++;
			}
			else if (gabarito[i] == 2) {
				acertos2++;
			}
			else if (gabarito[i] == 3) {
				acertos3++;
			}
			else if (gabarito[i] == 4) {
				acertos4++;
			}
			else if (gabarito[i] == 5) {
				acertos5++;
			}
			else if (gabarito[i] == 6) {
				acertos6++;
			}
			else if (gabarito[i] == 7) {
				acertos7++;
			}
			else if (gabarito[i] == 8) {
				acertos8++;
			}
			else if (gabarito[i] == 9) {
				acertos9++;
			}
		}
	}

	double acertosTotal = acertos0 + acertos1 + acertos2 + acertos3 + acertos4 + acertos5 + acertos6 + acertos7 + acertos8 + acertos9;
	cout << endl << "Acertos dig0: " << acertos0 << endl;
	cout << "Acertos dig1: " << acertos1 << endl;
	cout << "Acertos dig2: " << acertos2 << endl;
	cout << "Acertos dig3: " << acertos3 << endl;
	cout << "Acertos dig4: " << acertos4 << endl;
	cout << "Acertos dig5: " << acertos5 << endl;
	cout << "Acertos dig6: " << acertos6 << endl;
	cout << "Acertos dig7: " << acertos7 << endl;
	cout << "Acertos dig8: " << acertos8 << endl;
	cout << "Acertos dig9: " << acertos9 << endl;
	cout << "Acertos Total: " << acertosTotal << endl;
	cout << "Total de Testes: " << n_teste << endl;

}