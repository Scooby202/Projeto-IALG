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

	void red ( atletas pessoas[], int qReg, ifstream &entrada ){
		
			
		atletas *novoVetor = new atletas [qReg+5];
		memcpy ( novoVetor, pessoas, sizeof(atletas)* qReg);
		delete [] pessoas;
		pessoas = novoVetor;
		
		for (int i = qReg; i < qReg+5 ; i++)
	{
		pessoas[i].escrita(entrada);
	}
		
		
		for(int i = 0; i < qReg+5; i++)
	{
		cout << pessoas[i].identificador << ' ' << pessoas[i].nome << ' '<< pessoas[i].sexo <<' '<<  pessoas[i].idade <<' '<<  pessoas[i].pais << ' '<<  pessoas[i].passaporte 
		<<' '<<  pessoas[i].idioma <<' '<<  pessoas[i].modalidade <<' '<<  pessoas[i].preferenciaComida << endl;
	}
		
		
	}





int main()
{
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
	
	atletas *pessoas = new atletas[qReg];
	
	for (int i = 0; i < qReg; i++)
	{
		pessoas[i].escrita(entrada);
	}
	
	for(int i = 0; i < qReg; i++)
	{
		cout << pessoas[i].identificador << ' ' << pessoas[i].nome << ' '<< pessoas[i].sexo <<' '<<  pessoas[i].idade <<' '<<  pessoas[i].pais << ' '<<  pessoas[i].passaporte 
		<<' '<<  pessoas[i].idioma <<' '<<  pessoas[i].modalidade <<' '<<  pessoas[i].preferenciaComida << endl;
	}
	int i = 0;
	int identificador = 0;
	while ( pessoas[i].identificador < qReg+5) {
	    for (int i = 0; i < qReg+5; i++){
	 
		pessoas[i].identificador;
	    }
		if ( pessoas[i].identificador >= qReg ){
			red ( pessoas, qReg, entrada);
			
		}
      i++;
	}
	
	
	
	
	delete[] pessoas;
	return 0;
}
