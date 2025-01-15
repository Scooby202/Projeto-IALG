#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct atletas
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

void redimensionamento (atletas* &pessoas, int &tamanhoVet)
{	
	tamanhoVet += 5;
	atletas *novoVetor = new atletas [tamanhoVet];
	copy(pessoas, pessoas+(tamanhoVet-5), novoVetor);
	delete [] pessoas;
	pessoas = novoVetor;
}

void tela(atletas* pessoas, int quantidadeDeRegistros)
{
	for(int i = 0; i < quantidadeDeRegistros; i++)
	{
		cout << pessoas[i].identificador << ' ' << pessoas[i].nome << ' ' << pessoas[i].sexo << ' ' << pessoas[i].idade << ' ' << pessoas[i].pais << ' ' << pessoas[i].passaporte << ' ' << pessoas[i].idioma << ' ' << pessoas[i].modalidade << ' ' << pessoas[i].preferenciaComida << endl;
	}
}

void arquivo(atletas* pessoas, int quantidadeDeRegistros)
{
	int opcao;
	string nome;

	cout << "===============================================================================" << endl << endl << "Qual tipo de arquivo:" << endl << endl << "1. Tipado" << endl << "2. CSV" << endl << "0. Fechar o programa" << endl << endl << "Digite um valor: ";

	cin >> opcao;

	cout << endl << endl;	

	cout << "===============================================================================" << endl << endl << "Digite o nome do arquivo: ";

	cin >> nome;

	ofstream saida(nome);

	switch (opcao)
	{
	case 1:
		saida.write((const char *) (pessoas), sizeof(atletas) * quantidadeDeRegistros);
		break;

	case 2:
		for (int i = 0; i < quantidadeDeRegistros; i++)
		{
			saida << pessoas[i].identificador << ',' << pessoas[i].nome << ',' << pessoas[i].sexo << ',' << pessoas[i].idade << ',' << pessoas[i].pais << ',' << pessoas[i].passaporte << ',' << pessoas[i].idioma << ',' << pessoas[i].modalidade << ',' << pessoas[i].preferenciaComida << endl;
		}
		break;
	
	default:
		break;
	}
}

void leitura()
{
	string nome;

	cout << "===============================================================================" << endl << endl << "Digite o nome no arquivo: ";

	cin >> nome;

	cout << endl << endl;

	int tamanhoVet = 40;
	int quantidadeDeRegistros = 0;
	string linha;
	
	ifstream entrada(nome);
	
	if (entrada)
	{
		getline(entrada, linha);
		entrada >> quantidadeDeRegistros; 
	}
	else
	{
		cout << "Arquvo não encontrado" << endl;
		leitura();
	}
	
	atletas *pessoas = new atletas[tamanhoVet];

	int i = 0;
	while (i < quantidadeDeRegistros)
	{
		if (i < tamanhoVet)
		{
			pessoas[i].escrita(entrada);
			i++;
		}
		else
		{
			redimensionamento(pessoas, tamanhoVet);
		}
	}

	// Menu de escolhas

	int opcao;

	cout << "===============================================================================" << endl << endl << "Selecione uma opção:" << endl << endl << "1. Escrever os dados na tela" <<  endl  << "2. Criar um arquivo com os dados" << endl << "0. Fechar o programa" << endl << endl << "Digite um valor:";

	cin >> opcao;

	cout << endl << endl;

	switch (opcao)
	{
	case 1:
		tela(pessoas, quantidadeDeRegistros);
		break;

	case 2:
		arquivo(pessoas, quantidadeDeRegistros);
		break;
		
	default:
		break;
	}
}

void menus(int chamada )
{
	int opcao;

	cout << "===============================================================================" << endl << endl << "Selecione uma opção:" << endl << endl << "1. Ler um arquivo" <<  endl << "0. Fechar o programa" << endl << endl << "Digite um valor:";

	cin >> opcao;

	cout << endl << endl;

	switch (opcao)
	{
	case 1:
		leitura();
		break;
	
	default:
		break;
	}


}

int main()
{
	menus(1);

	return 0;
}