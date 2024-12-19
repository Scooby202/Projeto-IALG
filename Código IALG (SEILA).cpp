#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


struct atletas
{
	int identificador, idade, passaporte, qReg;
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

void redimensionamento (atletas pessoas[], int &tamanhoVet, ifstream &entrada)
{	
	tamanhoVet += 5;		
	atletas *novoVetor = new atletas [tamanhoVet];
	memcpy(novoVetor, pessoas, sizeof(atletas)* tamanhoVet-5);
	delete [] pessoas;
	pessoas = novoVetor;
}

void escritaFuncao(atletas pessoas[], int &tamanhoVet, ifstream &entrada)
{
	int i = 0;
	while (entrada)
	{
		if (i > tamanhoVet)
		{
			pessoas[i].escrita(entrada);
			i++;
		}
		else
		{
			redimensionamento(pessoas, tamanhoVet, entrada);
		}
	}
}

int main()
{
	int tamanhoVet = 40;
	int qReg = 0;
	string linha;
	
	ifstream entrada("entrada.csv");
	
	if (entrada)
	{
		getline(entrada, linha);
		entrada >> qReg; 
	}
	else
	{
		cout << "ERRO" << endl;
		return 0;
	}
	
	atletas *pessoas = new atletas[tamanhoVet];

	escritaFuncao(pessoas, tamanhoVet, entrada);
		
	delete[] pessoas;
	return 0;
}
