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

void escritaFuncao(atletas* &pessoas, int &tamanhoVet, ifstream &entrada, int quantidadeDeRegistros)
{
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
}

int main()
{
	int tamanhoVet = 40;
	int quantidadeDeRegistros = 0;
	string linha;
	
	ifstream entrada("entrada.csv");
	
	if (entrada)
	{
		getline(entrada, linha);
		entrada >> quantidadeDeRegistros; 
	}
	else
	{
		cout << "ERRO" << endl;
		return 0;
	}
	
	atletas *pessoas = new atletas[tamanhoVet];

	escritaFuncao(pessoas, tamanhoVet, entrada, quantidadeDeRegistros);

	cout << tamanhoVet << endl;

	for(int i = 0; i < tamanhoVet; i++)
	{
		cout << pessoas[i].identificador << ' ' << pessoas[i].nome << ' ' << pessoas[i].sexo << ' ' << pessoas[i].idade << ' ' << pessoas[i].pais << ' ' << pessoas[i].passaporte << ' ' << pessoas[i].idioma << ' ' << pessoas[i].modalidade << ' ' << pessoas[i].preferenciaComida << endl;
	}
		
	delete[] pessoas;
	return 0;
}
