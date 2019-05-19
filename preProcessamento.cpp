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

	/*
	// caso tenha que salvar W no formato original
	int contador = 0;
	for (int z = 0; z < numImagens; z++) {
		for (int i = 0; i < numLinhas; i++) {
			for (int j = 0; j < numColunas; j++) {
				output << W[contador][z] << " ";  // coloca os valores separador por espaco
				contador++;
			}
			output << "\n"; // pula a linha
		}
		output << "\n";
		contador = 0;
	} */

	// salvando W no arquivo:
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

	/*
	// caso tenha que salvar W no formato original
	int contador = 0;
	for (int z = 0; z < numImagens; z++) {
		for (int i = 0; i < numLinhas; i++) {
			for (int j = 0; j < numColunas; j++) {
				output << W[contador][z] << " ";  // coloca os valores separador por espaco
				contador++;
			}
			output << "\n"; // pula a linha
		}
		output << "\n";
		contador = 0;
	} */

	// salvando W no arquivo:
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
// 
void classificaDigito(string arquivoDigito, vector<vector<double>> A, vector<double>& erro, vector<double>& indice,int digito, 
	int p, int numLinhas, int numColunas, int n_teste) {

	if (n_teste > 10000) {
		cout << endl << "Numero de teste invalido" << endl;
		return;
	}

	int numLinA = numColunas * numLinhas;
	
	vector<vector<double>> salvaA; // matriz para deixar sempre salvo os valores a serem testados
	salvaA = A;

	vector<vector<double>> W(numLinA, vector<double>(p)); // matriz com os valores já treinados
	vector<vector<double>> H;
	

	// resolvendo o sistema para o digito 0
	fstream input0(arquivoDigito, ios::in);
	if (!input0.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo: "<< arquivoDigito << endl;
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
	int tamColProd = produto[0].size();
	int tamLinProd = produto.size();

	double provisorio; // para salvar A - WH

	// calculo do erro
	double soma;
	double erro_atual;
	for (int j = 0; j < tamColProd; j++) {
		soma = 0;
		for (int i = 0; i < tamLinProd; i++) {
			provisorio = A[i][j] - produto[i][j];
			soma += provisorio * provisorio; // calcula o quadrado de cada elemento da coluna e soma todos eles
		}
		erro_atual = sqrt(soma); // raiz do somatorio, esse e o erro
		if (digito != 0) { // atualiza o erro para os digitos subsequentes
			if (erro_atual > erro[j]) {
				erro[j] = erro_atual;
				indice[j] = digito;

			}

		}
		else { // erro inicial corresponde ao erro do digito 0
			erro[j] = erro_atual;
			indice[j] = 0;
		}
	}
}

// Mesma funcao que a anterior, mas quando ja sei o W do digito, para nao ter que abrir o arquivo e ler

void classificaDigito(vector<vector<double>> Wdigito, vector<vector<double>> A, vector<double>& erro, vector<double>& indice, int digito,
	int p, int numLinhas, int numColunas, int n_teste) {
	if (n_teste > 10000) {
		cout << endl << "Numero de teste invalido" << endl;
		return;
	}

	int numLinA = numColunas * numLinhas;

	vector<vector<double>> salvaA; // matriz para deixar sempre salvo os valores a serem testados
	salvaA = A;
	vector<vector<double>> H;


	H = solucaoSimultaneos(Wdigito, A); // solucao do sistema

	A = salvaA;

	vector<vector<double>> produto;
	produto = MMultiplication(Wdigito, H); // produto de W e H
	int tamColProd = produto[0].size();
	int tamLinProd = produto.size();

	double provisorio; // para salvar A - WH
	int contagem = 0;
	// calculo do erro
	double soma;
	double erro_atual;
	for (int j = 0; j < tamColProd; j++) {
		soma = 0;
		for (int i = 0; i < tamLinProd; i++) {
			provisorio = A[i][j] - produto[i][j];
			soma += provisorio * provisorio; // calcula o quadrado de cada elemento da coluna e soma todos eles
		}
		erro_atual = sqrt(soma); // raiz do somatorio, esse e o erro
		if (digito != 0) { // atualiza o erro para os digitos subsequentes
			if (erro_atual > erro[j]) {
				erro[j] = erro_atual;
				indice[j] = digito;
			}

		}
		else { // erro inicial corresponde ao erro do digito 0
			erro[j] = erro_atual;
			indice[j] = 0;
		}
	}
}

/*
	Essa funcao ira calcula a taxa de acerto total e a taxa de acerto por digito
*/

double taxaDeAcerto(string arquivoIndices, vector<double> indice, int n_teste,
	double& acerto0, double& acerto1, double& acerto2, double& acerto3, double& acerto4, double& acerto5, 
	double& acerto6, double& acerto7, double& acerto8, double& acerto9) {
	// pegando os dados do gabarito
	fstream input(arquivoIndices, ios::in);
	if (!input.is_open()) {
		cout << endl << "Nao foi possivel abrir o arquivo: " << arquivoIndices << endl;
		return 0;
	}
	vector<double> gabarito(n_teste);
	for (int i = 0; i < n_teste && !(input.eof()); i++) { // Pegando os dados do gabarito
		input >> gabarito[i];		
	}

	input.close();
	
	
	double acertos = 0;
	acerto0 = 0;
	acerto1 = 0;
	acerto2 = 0;
	acerto3 = 0;
	acerto4 = 0;
	acerto5 = 0;
	acerto6 = 0;
	acerto7 = 0;
	acerto8 = 0;
	acerto9 = 0;

	double quantidade0 = 0;
	double quantidade1 = 0;
	double quantidade2 = 0;
	double quantidade3 = 0;
	double quantidade4 = 0;
	double quantidade5 = 0;
	double quantidade6 = 0;
	double quantidade7 = 0;
	double quantidade8 = 0;
	double quantidade9 = 0;

	for (int i = 0; i < n_teste; i++) {
		// verificar o numero total de cada digito no arquivo
		// utilizando uma busca binaria por ser mais rapida
		if (gabarito[i] < 4.5) { // pode ser 0,1,2,3,4

			if (gabarito[i] < 2.5) { // pode ser 0,1,2

				if (gabarito[i] < 1.5) { // pode ser 0,1

					if (gabarito[i] == 0) { // apenas 0
						quantidade0++;
					}
					else { // apenas 1
						quantidade1++;
					}
				}
				else { // apenas 2
					quantidade2++;
				}
			}
			else { // pode ser 3,4
				if (gabarito[i] == 3) { // apenas 3
					quantidade3++;
				}
				else { // apenas 4
					quantidade4++;
				}

			}

		}
		else { // pode ser 5,6,7,8,9

			if (gabarito[i] < 7.5) { // pode ser 5,6,7

				if (gabarito[i] < 6.5) { // pode ser 5 ou 6

					if (gabarito[i] == 5) { // apenas 5
						quantidade5++;
					}
					else { // apenas 6
						quantidade6++;
					}
				}
				else { // apenas 7
					quantidade7++;
				}
			}
			else { // pode ser 8 ou 9

				if (indice[i] == 8) { // apenas 8
					quantidade8++;
				}
				else { // apenas 9
					quantidade9++;
				}
			}
		}

		if (gabarito[i] == indice[i]) {
			acertos++;
			// vamos categorizar utilizando uma arvore de busca, de modo a reduzir o tempo medio de execucao
			if (indice[i] < 4.5) { // pode ser 0,1,2,3,4

				if (indice[i] < 2.5) { // pode ser 0,1,2

					if (indice[i] < 1.5) { // pode ser 0,1

						if (indice[i] == 0) { // apenas 0
							acerto0++;
						}
						else { // apenas 1
							acerto1++;
						}
					}
					else { // apenas 2
						acerto2++;
					}
				}
				else { // pode ser 3,4
					if (indice[i] == 3) { // apenas 3
						acerto3++;
					}
					else { // apenas 4
						acerto4++;
					}

				}

			}
			else { // pode ser 5,6,7,8,9

				if (indice[i] < 7.5) { // pode ser 5,6,7

					if (indice[i] < 6.5){ // pode ser 5 ou 6
						
						if (indice[i] == 5) { // apenas 5
							acerto5++;
						}
						else { // apenas 6
							acerto6++;
						}
					}
					else { // apenas 7
						acerto7++;
					}
				}
				else { // pode ser 8 ou 9

					if (indice[i] == 8) { // apenas 8
						acerto8++;
					}
					else { // apenas 9
						acerto9++;
					}
				}
			}

		}
	}

	acertos = acertos / n_teste;
	acerto0 = acerto0 / quantidade0;
	acerto1 = acerto1 / quantidade1;
	acerto2 = acerto2 / quantidade2;
	acerto3 = acerto3 / quantidade3;
	acerto4 = acerto4 / quantidade4;
	acerto5 = acerto5 / quantidade5;
	acerto6 = acerto6 / quantidade6;
	acerto7 = acerto7 / quantidade7;
	acerto8 = acerto8 / quantidade8;
	acerto9 = acerto9 / quantidade9;

	return acertos;
}
