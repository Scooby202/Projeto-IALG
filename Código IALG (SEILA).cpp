#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct atletas // estrutura que guarda todas as informações de registro dos atletas
{
	int identificador, idade, passaporte;
	char nome[20], pais[15], idioma[10], modalidade[15], preferenciaComida[15]; 
	char sexo, lixo;
	
	void escrita(ifstream &entrada)
	{
		entrada >> identificador;
		entrada >> lixo;
		entrada.getline(nome, 20, ',');
		entrada >> sexo;
		entrada >> lixo;
		entrada >> idade;
		entrada >> lixo;
		entrada.getline(pais, 15, ',');
		entrada >> passaporte;
		entrada >> lixo;
		entrada.getline(idioma, 10, ',');
		entrada.getline(modalidade, 15, ',');
		entrada.getline(preferenciaComida, 15);
	}
};

void redimensionamento (atletas* &pessoas, int &tamanhoVet) // faz o processo de redimensionamento do vetor quando é necessário
{	
	tamanhoVet += 5;
	atletas *vetAux = new atletas [tamanhoVet]; // criação do vetor auxiliar necessário para o redimensionamento
	copy(pessoas, pessoas+(tamanhoVet-5), vetAux);
	delete [] pessoas;
	pessoas = vetAux;
}

int leituraCSV(atletas* &pessoas, int &tamanhoVet, int &quantidadeDeRegistros) // função para a leitura dos dados vindos do arquivo csv
{
	string linha; // string auxiliar para guardar os o índice do csv
	ifstream entrada("entrada.csv"); // abertura do arquivo
	
	if (entrada) // verificação se o arquivo foi encontrado
	{
		getline(entrada, linha);
		entrada >> quantidadeDeRegistros; 
	}
	else // mensagem de erro e retorno para o menu inicial
	{
		cout << "Arquivo não encontrado" << endl;
		return 1;
	}

	int i = 0;
	while (i < quantidadeDeRegistros)
	{
		if (i < tamanhoVet)
		{
			pessoas[i].escrita(entrada); // chamada da função de escrita
			i++;
		}
		else
		{
			redimensionamento(pessoas, tamanhoVet); // chamada para a função de redimensionamento quando a quantidade de dados excede o tamanho do vetor
		}
	}
}

void escritaTela(int quantidadeDeRegistros, atletas* pessoas) // responsável pela escrita de todo os registos feitos em tela
{
	cout << "======================================================================================================================" << endl << endl;

	for(int i = 0; i < quantidadeDeRegistros; i++)
	{
		cout << pessoas[i].identificador << ' ' << pessoas[i].nome << ' ' << pessoas[i].sexo << ' ' << pessoas[i].idade << ' ' << pessoas[i].pais << ' ' << pessoas[i].passaporte << ' ' << pessoas[i].idioma << ' ' << pessoas[i].modalidade << ' ' << pessoas[i].preferenciaComida << endl;
	}

	cout << endl;
}

void gravarDados(int quantidadeDeRegistros, atletas* pessoas)
{
	int opcao;
	string nome;

	cout << "======================================================================================================================" << endl << endl;
	cout << "Em que tipo de arquivo gostaria de armazenar os dados ?" << endl << endl;
	cout << "1. Arquivo Tipado" << endl << "2. Arquivo CSV" << "0. Voltar para o menu" << endl << endl;
	cout << "Selecione uma opção: ";

	cin >> opcao; 

	cout << endl;

	do
	{
		if (opcao == 1)
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Qual o nome do arquivo? (adicione .txt ao final do nome)";

			cin >> nome;

			cout << endl;

			ofstream saida(nome);
			saida.write((const char *) (pessoas), sizeof(atletas) * quantidadeDeRegistros);
			saida.close();

			cout << "Arquivo escrito com sucesso!!" << endl << endl;
			opcao = 0;
		}
		
		else if (opcao == 2)
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Qual o nome do arquivo? (adicione .csv ao final do nome)";

			cin >> nome;

			cout << endl;

			ofstream saida(nome);
			
			saida << "#identificador(int),nome(string com espaço),sexo(char),idade(int),pais(string com espaço),numero passaporte(int),primeiro idioma(string),modalidade(string com espaço),preferencia de comida(string com espaço)" << endl << quantidadeDeRegistros << endl;

			for (int i = 0; i < quantidadeDeRegistros; i++)
			{
				saida << pessoas[i].identificador << ',' << pessoas[i].nome << ',' << pessoas[i].sexo << ',' << pessoas[i].idade << ',' << pessoas[i].pais << ',' << pessoas[i].passaporte << ',' << pessoas[i].idioma << ',' << pessoas[i].modalidade << ',' << pessoas[i].preferenciaComida << endl;
			}
			
			saida.close();

			cout << "Arquivo escrito com sucesso!!" << endl << endl;
			opcao = 0;
		}
		else if (opcao != 0)
		{
			cout << "Opção inválida!!" << endl << endl;
		}
	} while (opcao != 0);
}

void menuPrincipal(int &quantidadeDeRegistros, int &tamanhoVet, atletas* &pessoas) // menu com as principais funções do programa
{
	int opcao;

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "O que deseja fazer?" << endl << endl;
		cout << "1. Fazer mais um registro" << endl << "2. Remover um registro" << endl << "3. Buscar por um registro" << endl << "4. Escrever todos os registro na tela" << endl << "5. Gravar registros em um arquivo" << endl << "0. Encerrar o programa" << endl << endl;
		cout << "Selecione uma opção: ";

		cin >> opcao;

		cout << endl;

		switch (opcao)
		{
		case 1:
			
			break;
		
		case 2:
			
			break;

		case 3:
			
			break;

		case 4:
			escritaTela(quantidadeDeRegistros, pessoas);
			break;

		case 5:
			gravarDados(quantidadeDeRegistros, pessoas);
			break;
		
		default:
			break;
		}
	} while (opcao != 0);
}

int main()
{
	int tamanhoVet = 40; // controlador do tamnho do vetor
	int quantidadeDeRegistros = 0; // controlador da quantidade de registros
	atletas *pessoas = new atletas[tamanhoVet]; // vetor que armazena os dados de registro

	leituraCSV(pessoas, tamanhoVet, quantidadeDeRegistros);
	
	menuPrincipal(quantidadeDeRegistros, tamanhoVet, pessoas);
	
	delete[] pessoas;
	return 0;
}