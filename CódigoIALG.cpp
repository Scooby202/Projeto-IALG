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

void redimensionamento (atletas* &registros, int &tamanhoVet) // faz o processo de redimensionamento do vetor quando é necessário
{	
	tamanhoVet += 5;
	atletas *vetAux = new atletas [tamanhoVet]; // criação do vetor auxiliar necessário para o redimensionamento
	copy(registros, registros+(tamanhoVet-5), vetAux);
	delete [] registros;
	registros = vetAux;
}

int leituraTipado(atletas* &registros, int &tamanhoVet, int &quantidadeDeRegistros) // função para a leitura dos dados vindos do arquivo tipado
{
	string nome;

	cout << "======================================================================================================================" << endl << endl;
	cout << "Digite o nome do arquivo: ";

	cin >> nome;

	cout << endl;

	ifstream entrada(nome); // abertura do arquivo
	
	if (entrada) // verificação se o arquivo foi encontrado
	{
		entrada.seekg (0, entrada.end);
    	quantidadeDeRegistros = entrada.tellg();
		quantidadeDeRegistros /= 92;
		entrada.seekg (0, entrada.beg);
	}
	else // mensagem de erro e retorno para o menu inicial
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo não encontrado! Voltando para o menu incial..." << endl << endl;
		return 1;
	}

	while (tamanhoVet < quantidadeDeRegistros)
	{
		redimensionamento(registros, tamanhoVet);
	}
	
	entrada.read((char *) (registros), sizeof(atletas) * quantidadeDeRegistros);

	entrada.close();

	return 0;
}

int leituraCSV(atletas* &registros, int &tamanhoVet, int &quantidadeDeRegistros) // função para a leitura dos dados vindos do arquivo csv
{
	string nome;

	cout << "======================================================================================================================" << endl << endl;
	cout << "Digite o nome do arquivo: ";

	cin >> nome;

	cout << endl;

	string linha; // string auxiliar para guardar os o índice do csv
	ifstream entrada(nome); // abertura do arquivo
	
	if (entrada) // verificação se o arquivo foi encontrado
	{
		getline(entrada, linha);
		entrada >> quantidadeDeRegistros; 
	}
	else // mensagem de erro e retorno para o menu inicial
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo não encontrado! Voltando para o menu incial..." << endl << endl;
		return 1;
	}

	int i = 0;
	while (i < quantidadeDeRegistros)
	{
		if (i < tamanhoVet)
		{
			registros[i].escrita(entrada); // chamada da função de escrita
			i++;
		}
		else
		{
			redimensionamento(registros, tamanhoVet); // chamada para a função de redimensionamento quando a quantidade de dados excede o tamanho do vetor
		}
	}

	entrada.close();

	return 0;
}

void ordenacaoID(int quantidadeDeRegistros, atletas* registros) // faz a ordenação baseando-se no identificador
{
	atletas pivo;
	int j;

	int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int posicaoGap = 8;

    while (gaps[posicaoGap] > quantidadeDeRegistros)
    {
        posicaoGap--;
    }
	
	while (posicaoGap >= 0)
	{
		int gap = gaps[posicaoGap];
		for (int i = gap; i < quantidadeDeRegistros; i++)
		{
			pivo = registros[i];
			j = i;

			while (j >= gap and pivo.identificador < registros[j - gap].identificador)
			{
				registros[j] = registros[j - gap];
				j -= gap;
			}
			registros[j] = pivo;
		}
		posicaoGap--;
	}
}

void ordenacaoPassaporte(int quantidadeDeRegistros, atletas* registros) // faz a ordenação baseando-se no número do passaporte
{
	atletas pivo;
	int j;

	int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int posicaoGap = 8;

    while (gaps[posicaoGap] > quantidadeDeRegistros)
    {
        posicaoGap--;
    }
	
	while (posicaoGap >= 0)
	{
		int gap = gaps[posicaoGap];
		for (int i = gap; i < quantidadeDeRegistros; i++)
		{
			pivo = registros[i];
			j = i;

			while (j >= gap and pivo.passaporte < registros[j - gap].passaporte)
			{
				registros[j] = registros[j - gap];
				j -= gap;
			}
			registros[j] = pivo;
		}
		posicaoGap--;
	}
}

int buscaBinariaID(int quantidadeDeRegistros, int procurado, atletas* registros)
{
    ordenacaoID(quantidadeDeRegistros, registros);
    
    int inicio = 0;
    int fim = quantidadeDeRegistros - 1;
    int meio;
    int posicao = -1;
    while (inicio <= fim)
    {
        meio = (inicio + fim)/2;
        if (registros[meio].identificador == procurado)
        {
            posicao = meio;
            inicio = fim + 1;
        }

        else
        {
            if (registros[meio].identificador < procurado)
            {
                inicio = meio + 1;
            }
            else
            {
                fim = meio - 1;
            }
            
        }
    }

    return posicao;
}

int buscaBinariaPassaporte(int quantidadeDeRegistros, int procurado, atletas* registros)
{
    ordenacaoPassaporte(quantidadeDeRegistros, registros);
    
    int inicio = 0;
    int fim = quantidadeDeRegistros - 1;
    int meio;
    int posicao = -1;
    while (inicio <= fim)
    {
        meio = (inicio + fim)/2;
        if (registros[meio].passaporte == procurado)
        {
            posicao = meio;
            inicio = fim + 1;
        }

        else
        {
            if (registros[meio].passaporte < procurado)
            {
                inicio = meio + 1;
            }
            else
            {
                fim = meio - 1;
            }
            
        }
    }

    return posicao;
}

void buscaDeRegistro(int quantidadeDeRegistros, atletas* registros) // possibilita a busca de um determinado registro pelo usuário e permite sua modificação
{
	int opcao;
	int posicao = -1;
	int procurado;
	bool proximoMenu = false;

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Gostaria de fazer a busca pelo identificador ou pelo passaporte ?" << endl << endl;
		cout << "1. Identificador" << endl << "2. Passaporte" << endl << "0. Voltar para o menu principal" << endl << endl;
		cout << "Selecione uma opção: ";
		
		cin >> opcao;

		cout << endl;

		switch (opcao)
		{
		case 1:
			cout << "======================================================================================================================" << endl << endl;
			cout << "Digite o identificador que gostaria de procurar: ";
			cin >> procurado;
			cout << endl;
			posicao = buscaBinariaID(quantidadeDeRegistros, procurado, registros);
			break;
		
		case 2:
			cout << "======================================================================================================================" << endl << endl;
			cout << "Digite o passaporte que gostaria de procurar: ";
			cin >> procurado;
			cout << endl;
			posicao = buscaBinariaPassaporte(quantidadeDeRegistros, procurado, registros);
			break;

		case 0:
			break;

		default:
			cout << "======================================================================================================================" << endl << endl;
			cout << "Opção inválida!!" << endl << endl;
			break;
		}

		if (posicao != -1)
		{
			proximoMenu = true;
		}
		

	} while (opcao != 0 and not proximoMenu);
	
	if (posicao != -1)
	{
		int numeroAux;

		cout << "======================================================================================================================" << endl << endl;
		cout << registros[posicao].identificador << ' ' << registros[posicao].nome << ' ' << registros[posicao].sexo << ' ' << registros[posicao].idade << ' ' << registros[posicao].pais << ' ' << registros[posicao].passaporte << ' ' << registros[posicao].idioma << ' ' << registros[posicao].modalidade << ' ' << registros[posicao].preferenciaComida << endl << endl;

		do
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Deseja modificar algum dado do registro ?" << endl << endl << "1. Identificador" << endl << "2. Nome" << endl << "3. Sexo" << endl << "4. Idade" << endl << "5. Passaporte" << endl << "6. Idioma" << endl << "7. Modalidade" << endl << "8. Preferencia de comida" << endl << "0. Não" << endl << endl;
			cout << "Selecione uma opção: ";

			cin >> opcao;

			cout << endl;

			switch (opcao)
			{
			case 1:
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o novo identificador: ";
				
				cin >> numeroAux;
				
				cout << endl;

				if (buscaBinariaID(quantidadeDeRegistros, numeroAux, registros) == -1)
				{
					registros[posicao].identificador = numeroAux;
					cout << "Identificador modificado!!" << endl << endl;
				}
				else
				{
					cout << "ERRO. O identificador já for registrado" << endl << endl;
				}
				break;
			
			case 2:
				break;

			case 3:
				break;

			case 4:
				break;

			case 5:
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o novo passaporte: ";
				
				cin >> numeroAux;
				
				cout << endl;

				if (buscaBinariaPassaporte(quantidadeDeRegistros, numeroAux, registros) == -1)
				{
					registros[posicao].passaporte = numeroAux;
					cout << "Passaporte modificado!!" << endl << endl;
				}
				else
				{
					cout << "ERRO. O passaporte já foi registrado" << endl << endl;
				}
				break;

			case 6:
				break;

			case 7:
				break;

			case 8:
				break;

			case 0:
				break;
			
			default:
				break;
			}
		} while (opcao != 0);
	}
}

void escritaTela(int quantidadeDeRegistros, atletas* registros) // responsável pela escrita de todo os registos feitos em tela
{
	cout << "======================================================================================================================" << endl << endl;

	for(int i = 0; i < quantidadeDeRegistros; i++)
	{
		cout << registros[i].identificador << ' ' << registros[i].nome << ' ' << registros[i].sexo << ' ' << registros[i].idade << ' ' << registros[i].pais << ' ' << registros[i].passaporte << ' ' << registros[i].idioma << ' ' << registros[i].modalidade << ' ' << registros[i].preferenciaComida << endl;
	}

	cout << endl;
}

void gravarDados(int quantidadeDeRegistros, atletas* registros) // responsável pela gravação dos registros num arquivo csv ou tipado
{
	int opcao;
	string nome;

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Em que tipo de arquivo gostaria de armazenar os dados ?" << endl << endl;
		cout << "1. Arquivo Tipado" << endl << "2. Arquivo CSV" << endl << "0. Voltar para o menu" << endl << endl;
		cout << "Selecione uma opção: ";

		cin >> opcao; // seleção da opção

		cout << endl;
		
		if (opcao == 1) // execução da gravação em um arquivo tipado
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Qual o nome do arquivo? (adicione .txt ao final do nome) ";

			cin >> nome;

			cout << endl;

			ofstream saida(nome);
			saida.write((const char *) (registros), sizeof(atletas) * quantidadeDeRegistros);
			saida.close();

			cout << "Arquivo escrito com sucesso!!" << endl << endl;
			opcao = 0; // troca do valor da função para que ela seja encerrada
		}
		
		else if (opcao == 2) // gravação em um arquivo csv
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Qual o nome do arquivo? (adicione .csv ao final do nome) ";

			cin >> nome;

			cout << endl;

			ofstream saida(nome);
			
			saida << "#identificador(int),nome(string com espaço),sexo(char),idade(int),pais(string com espaço),numero passaporte(int),primeiro idioma(string),modalidade(string com espaço),preferencia de comida(string com espaço)" << endl << quantidadeDeRegistros << endl; // escrita do índice

			for (int i = 0; i < quantidadeDeRegistros; i++)
			{
				saida << registros[i].identificador << ',' << registros[i].nome << ',' << registros[i].sexo << ',' << registros[i].idade << ',' << registros[i].pais << ',' << registros[i].passaporte << ',' << registros[i].idioma << ',' << registros[i].modalidade << ',' << registros[i].preferenciaComida << endl;
			}
			
			saida.close();

			cout << "Arquivo escrito com sucesso!!" << endl << endl;
			opcao = 0; // troca do valor da função para que ela seja encerrada
		}
		else if (opcao != 0) // caso em que o usuário escolhe uma opção inválida
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Opção inválida!!" << endl << endl;
		}
	} while (opcao != 0);
}

void menuPrincipal(int &quantidadeDeRegistros, int &tamanhoVet, atletas* &registros) // menu com as principais funções do programa
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
		case 1: // adicionar registro
			cout << "======================================================================================================================" << endl << endl;
			cout << "Em desenvolvimento..." << endl << endl;
			ordenacaoPassaporte(quantidadeDeRegistros, registros);
			break;
		
		case 2: // remover registro
			cout << "======================================================================================================================" << endl << endl;
			cout << "Em desenvolvimento..." << endl << endl;
			ordenacaoID(quantidadeDeRegistros, registros);
			break;

		case 3: // buscar um registro
			buscaDeRegistro(quantidadeDeRegistros, registros);
			break;

		case 4: // escrever registros na tela
			escritaTela(quantidadeDeRegistros, registros);
			break;

		case 5: // registos em um arquivo
			gravarDados(quantidadeDeRegistros, registros);
			break;

		case 0: // fechar o programa
			// o 0 não cai no default
			break;

		default: // caso usuário escolha uma opção inválida
			cout << "======================================================================================================================" << endl << endl;
			cout << "Opção inválida!!" << endl << endl;
			break;
		}
	} while (opcao != 0);
}

int main()
{
	int tamanhoVet = 40; // controlador do tamnho do vetor
	int quantidadeDeRegistros = 0; // controlador da quantidade de registros
	int opcao;
	atletas *registros = new atletas[tamanhoVet]; // vetor que armazena os dados de registro

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "O que deseja fazer?" << endl << endl;
		cout << "1. Ler uma arquivo CSV" << endl << "2. Ler um arquivo tipado" << endl << "0. Fechar programa" << endl << endl;
		cout << "Selecione uma opção: ";

		cin >> opcao;

		cout << endl;

		switch (opcao)
		{
		case 1: // faz a leitura de um arquivo CSV
			if (leituraCSV(registros, tamanhoVet, quantidadeDeRegistros) == 0) // condicicional q vai chamar a função e executar as outras partes do programa caso o arquivo tenha sido lido
			{
				menuPrincipal(quantidadeDeRegistros, tamanhoVet, registros);
				opcao = 0;
			}
			break;
		
		case 2: // faz a leitura de um arquivo Tipado
			if (leituraTipado(registros, tamanhoVet, quantidadeDeRegistros) == 0) // condicicional q vai chamar a função e executar as outras partes do programa caso o arquivo tenha sido lido
			{
				menuPrincipal(quantidadeDeRegistros, tamanhoVet, registros);
				opcao = 0;
			}
			break;

		case 0: // opção para fechar o programa 
			// o 0 não pode cair no default
			break;

		default:
			cout << "======================================================================================================================" << endl << endl;
			cout << "Opção inválida!!" << endl << endl;
			break;
		}

	} while (opcao !=0);

	delete[] registros;
	cout << "Fechando programa...";
	return 0;
}
