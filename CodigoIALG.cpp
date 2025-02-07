//Tema do Projeto: Cadastro de atletas em um hotel.
//Nomes dos Membros do Grupo: Erick David Forzan Pereira, Lívia Maria Almeida Silva e Maurício Vicente Sandim.

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct atletas // estrutura que guarda todas as informações de registro dos atletas
{
	int identificador, idade;
	int passaporte;
	char nome[36], pais[26], idioma[21], modalidade[26], preferenciaComida[26]; // declaração do tamanho do vetor de char com uma posição mais para que o último caractere seja o '\0'
	char sexo;
};

bool validacaoInt(string aux) // verifica se o que foi digitado é um número inteiro
{
	for (long unsigned int i = 0; i < aux.size(); i++)
	{
		if (not isdigit(aux[i]) or aux.size() > 9) // verifica se o caractere é um dígito e se o número é menor que 10^9
		{
			return false;
		}
	}

	return true;
}

void ordenacaoID(int quantidadeDeRegistros, atletas* registros) // faz a ordenação baseando-se no identificador
{
	// shell sort
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
	// shell sort
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

int buscaBinariaID(int quantidadeDeRegistros, int procurado, atletas* registros) // busca binária para o identidicador
{
    ordenacaoID(quantidadeDeRegistros, registros);
    
    int inicio = 0;
    int fim = quantidadeDeRegistros - 1;
    int meio;
    while (inicio <= fim)
    {
        meio = (inicio + fim)/2;
        if (registros[meio].identificador == procurado)
        {
            return meio;
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

    return -1;
}

int buscaBinariaPassaporte(int quantidadeDeRegistros, int procurado, atletas* registros) // busca binária para o passaporte 
{
    ordenacaoPassaporte(quantidadeDeRegistros, registros);
    
    int inicio = 0;
    int fim = quantidadeDeRegistros - 1;
    int meio;
    while (inicio <= fim)
    {
        meio = (inicio + fim)/2;
        if (registros[meio].passaporte == procurado)
        {
            return meio;
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

    return -1;
}

int validacaoDoArquivo(int quantidadeDeRegistros, atletas* registros) // verifica no arquivo se há identificadores ou passaportes repetidos, comparando os adjascentes depois de ordenados
{
	ordenacaoPassaporte(quantidadeDeRegistros, registros);

	for (int i = 0; i < quantidadeDeRegistros - 1; i++)
	{
		if (registros[i].passaporte == registros[i + 1].passaporte)
		{
			return 1;
		}
	}

	ordenacaoID(quantidadeDeRegistros, registros);

	for (int i = 0; i < quantidadeDeRegistros - 1; i++)
	{
		if (registros[i].identificador == registros[i + 1].identificador)
		{
			return 1;
		}
	}

	return 0;	
}

void redimensionamento(atletas* &registros, int &tamanhoVet) // faz o processo de redimensionamento do vetor quando é necessário
{	
	tamanhoVet += 5;
	atletas *vetAux = new atletas [tamanhoVet]; // criação do vetor auxiliar necessário para o redimensionamento
	copy(registros, registros+(tamanhoVet-5), vetAux);
	delete [] registros;
	registros = vetAux;
}

int leituraCSV(atletas* &registros, int &tamanhoVet, int &quantidadeDeRegistros, string &nomeArqAberto) // função para a leitura dos dados vindos do arquivo csv
{
	cout << "======================================================================================================================" << endl << endl;
	cout << "Digite o nome do arquivo: ";

	getline(cin, nomeArqAberto);
	nomeArqAberto += ".csv"; // adição da extensão do arquivo

	cout << endl;

	string linha; // string auxiliar para guardar o índice do csv
	ifstream entrada(nomeArqAberto); // abertura do arquivo
	
	if (entrada) // verificação se o arquivo foi encontrado
	{
		getline(entrada, linha);
		entrada >> quantidadeDeRegistros; 
	}
	else // mensagem de erro e retorno para o menu inicial
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo não encontrado! Voltando para o menu incial..." << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}

	char lixo; // char auxliliar para remover as vírgulas do arquivo csv
	int i = 0; 
	while (i < quantidadeDeRegistros)
	{
		if (i < tamanhoVet)
		{
			entrada >> registros[i].identificador;
			entrada >> lixo;
			entrada.getline(registros[i].nome, 36, ',');
			entrada >> registros[i].sexo;
			entrada >> lixo;
			entrada >> registros[i].idade;
			entrada >> lixo;
			entrada.getline(registros[i].pais, 26, ',');
			entrada >> registros[i].passaporte;
			entrada >> lixo;
			entrada.getline(registros[i].idioma, 21, ',');
			entrada.getline(registros[i].modalidade, 26, ',');
			entrada.getline(registros[i].preferenciaComida, 26);
			i++;
		}
		else
		{
			redimensionamento(registros, tamanhoVet); // chamada para a função de redimensionamento quando a quantidade de dados excede o tamanho do vetor
		}
	}

	entrada.close();

	// sistema de validação de arquivo para passaporte e identificador
	if (validacaoDoArquivo(quantidadeDeRegistros, registros) == 1)
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo inválido! Voltando para o menu incial..." << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}
	
	cout << "======================================================================================================================" << endl << endl;
	cout << "Arquivo aberto com sucesso!!" << endl << endl;

	return 0; // return 0 para que o menu principal seja chamado
}

int leituraTipado(atletas* &registros, int &tamanhoVet, int &quantidadeDeRegistros, string &nomeArqAberto) // função para a leitura dos dados vindos do arquivo tipado
{
	cout << "======================================================================================================================" << endl << endl;
	cout << "Digite o nome do arquivo: ";

	getline(cin, nomeArqAberto);
	nomeArqAberto += ".bin"; // adição da extensão do arquivo

	cout << endl;

	ifstream entrada(nomeArqAberto); // abertura do arquivo
	
	if (entrada) // verificação se o arquivo foi encontrado
	{
		entrada.seekg (0, entrada.end);
    	quantidadeDeRegistros = entrada.tellg();
		quantidadeDeRegistros /= 148;
		entrada.seekg (0, entrada.beg);
	}
	else // mensagem de erro e retorno para o menu inicial
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo não encontrado! Voltando para o menu incial..." << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}

	while (tamanhoVet < quantidadeDeRegistros) // repetição para realizar o redimensionamento do vetor quando a quantidade de dados excede o tamanho do vetor
	{
		redimensionamento(registros, tamanhoVet);
	}
	
	entrada.read((char *) (registros), sizeof(atletas) * quantidadeDeRegistros); // cópia do arquivo tipado para o vetor de registros

	entrada.close();

	// sistema de validação de arquivo para passaporte e identificador
	if (validacaoDoArquivo(quantidadeDeRegistros, registros) == 1)
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo inválido! Voltando para o menu incial......" << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}

	cout << "======================================================================================================================" << endl << endl;
	cout << "Arquivo aberto com sucesso!!" << endl << endl;

	return 0; // return 0 para que o menu principal seja chamado
}

int adicionarRegistro(int &quantidadeDeRegistros, int &tamanhoVet, atletas* &registros) // responsável pela adição de um novo registro
{
	quantidadeDeRegistros++;
	int posicao = quantidadeDeRegistros - 1;
	string aux; // string auxiliar para verificar se o dado é válido

	if (tamanhoVet < quantidadeDeRegistros) // condicional para verificar se é necessário o redimensionamento do vetor
	{
		redimensionamento (registros, tamanhoVet);
	}
	
	// identificador
	do
	{
		cout << "Digite o identificador (número inteiro): ";
		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o identificador é válido
		{
			registros[posicao].identificador = stoi(aux);
		}
		else 
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Identificador inválido!!" << endl << endl;
		}
	} while (aux.empty() or not validacaoInt(aux)); // repetição para que o usuário digite um identificador válido
	
	if (buscaBinariaID(quantidadeDeRegistros - 1, registros[posicao].identificador, registros) != -1) // verifica se o identificador já foi registrado
	{
		quantidadeDeRegistros--; // apaga o registro que foi adicionado
		return 1; // return 1 para que o menu principal seja chamado e imprima a mensagem de erro
	}	

	// nome
	do
	{
		cout << "Digite o nome (até 35 caracteres): ";
		getline(cin, aux);
		cout << endl;

		if(aux.size() <= 35 and not aux.empty()) // verifica se o nome é válido
		{
			copy(&aux[0], &aux[aux.size()], registros[posicao].nome);
			registros[posicao].nome[aux.size()] = '\0';
		}
		else
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Nome inválido!!" << endl << endl;
		}
	} while (aux.size() > 35 or aux.empty()); // repetição para que o usuário digite um nome válido
	
	// sexo
	do
	{
		cout << "Digite o novo sexo (M para masculino e F para feminino): ";
		getline(cin, aux);
		cout << endl;

		if(aux == "M" or aux == "F") // verifica se o sexo é válido
		{
			registros[posicao].sexo = aux[0];
		}
		else
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Sexo inválido!!" << endl << endl;
		}
	} while (aux != "M" and aux != "F"); // repetição para que o usuário digite um sexo válido

	// idade
	do
	{	cout << "Digite a idade (número inteiro): ";
		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se a idade é válida
		{
			registros[posicao].idade = stoi(aux);
		}
		else
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Idade inválida!!" << endl << endl;
		}
	} while (aux.empty() or not validacaoInt(aux)); // repetição para que o usuário digite uma idade válida

	// país
	do
	{
		cout << "Digite o país (até 25 caracteres): ";
		getline(cin, aux);
		cout << endl;

		if(aux.size() <= 25 and not aux.empty()) // verifica se o país é válido
		{
			copy(&aux[0], &aux[aux.size()], registros[posicao].pais);
			registros[posicao].pais[aux.size()] = '\0';
		}	
		else
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "País inválido!!" << endl << endl;
		}
	} while (aux.size() > 25 or aux.empty()); // repetição para que o usuário digite um país válido

	// passaporte
	do
	{
		cout << "Digite o número de passaporte (sequência de dígitos): ";
		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o passaporte é válido
		{
			registros[posicao].passaporte = stoi(aux);
		}
		else 
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Número de passaporte inválido!!" << endl << endl;
		}
	} while (aux.empty() or not validacaoInt(aux)); // repetição para que o usuário digite um passaporte válido
	
	if (buscaBinariaPassaporte(quantidadeDeRegistros - 1, registros[posicao].passaporte, registros) != -1) // verifica se o passaporte já foi registrado
	{
		quantidadeDeRegistros--; // apaga o registro que foi adicionado
		return 2; // return 2 para que o menu principal seja chamado e imprima a mensagem de erro
	}

	// idioma
	do
	{
		cout << "Digite o idioma (até 20 caracteres): ";
		getline(cin, aux);
		cout << endl;

		if(aux.size() <= 20 and not aux.empty()) // verifica se o idioma é válido
		{
			copy(&aux[0], &aux[aux.size()], registros[posicao].idioma);
			registros[posicao].idioma[aux.size()] = '\0';
		}
		else
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Idioma inválido!!" << endl << endl;
		}
	} while (aux.size() > 20 or aux.empty()); // repetição para que o usuário digite um idioma válido
	
	// modalidade
	do
	{
		cout << "Digite a modalidade (até 25 caracteres): ";
		getline(cin, aux);
		cout << endl;

		if (aux.size() <= 25 and not aux.empty()) // verifica se a modalidade é válida
		{
			copy(&aux[0], &aux[aux.size()], registros[posicao].modalidade);
			registros[posicao].modalidade[aux.size()] = '\0';
		}
		else
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Modalidade inválida!!" << endl << endl;
		}
	} while (aux.size() > 25 or aux.empty()); // repetição para que o usuário digite uma modalidade válida
	
	// preferência de comida
	do
	{
		cout << "Digite a preferência de comida (até 25 caracteres): ";
		getline(cin, aux);
		cout << endl;

		if(aux.size() <= 25 and not aux.empty()) // verifica se a preferência de comida é válida
		{
			copy(&aux[0], &aux[aux.size()], registros[posicao].preferenciaComida);
			registros[posicao].preferenciaComida[aux.size()] = '\0';
		}
		else
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Preferência de comida inválida!!" << endl << endl;
		}
	} while (aux.size() > 25 or aux.empty()); // repetição para que o usuário digite uma preferência de comida válida

	cout << "Novo registro cadastrado!!" << endl << endl;

	return 0;
}

void removerRegistro(int &quantidadeDeRegistros, atletas* registros) // realiza o processo de remoção de um arquivo
{
	int posicao;
	int opcao;
	int procurado;
	string aux; // string auxiliar para verificar se a opção é válida

	do
	{
		do
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Digite o identificador do registro que gostaria de remover: ";

			getline(cin, aux);
			cout << endl;

			if (not aux.empty() and validacaoInt(aux)) // verifica se o identificador é válido
			{
				procurado = stoi(aux);
			}
			
		} while (aux.empty() or not validacaoInt(aux)); // repetição para que o usuário digite um identificador válido
		

		posicao = buscaBinariaID(quantidadeDeRegistros, procurado, registros);

		if (posicao == -1) // verifica se o registro foi encontrado
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Registro inexistente!!" << endl << endl;
		}
		
	} while (posicao == -1); // repetição para que o usuário digite um identificador existente

	do
	{
		cout << "Tem certeza que deseja remover o resgistro: " << registros[posicao].identificador << " | " << registros[posicao].nome << " | " << registros[posicao].sexo << " | " << registros[posicao].idade << " | " << registros[posicao].pais << " | " << registros[posicao].passaporte << " | " << registros[posicao].idioma << " | " << registros[posicao].modalidade << " | " << registros[posicao].preferenciaComida << " ?" << endl << endl;
		cout << "1. Sim" << endl << "2. Não" << endl << endl;
		cout << "Selecione uma opção: ";

		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o input é um número inteiro
		{
			opcao = stoi(aux);
		}
		else
		{
			opcao = -1; // mudança no opcao para ele cair no default e repetir
		}

		switch (opcao)
		{
			case 1: // realiza a remoção do registro
				quantidadeDeRegistros--;
				for (int i = posicao; i < quantidadeDeRegistros; i++)
				{
					registros[i] = registros[i + 1];
				}

				cout << "Registro apagado com sucesso!!" << endl << endl;
				
				break;
			
			case 2: // cancela a remoção
				// caso 2 não pode cair do default
				break;
			
			default:
				cout << "======================================================================================================================" << endl << endl;
				cout << "Opção inválida!!" << endl << endl;
				break;
		}
	} while (opcao > 2 or opcao < 1); // repetição para que o usuário digite uma opção válida
	
}

void buscaDeRegistro(int quantidadeDeRegistros, atletas* registros) // possibilita a busca de um determinado registro pelo usuário e permite sua modificação
{
	int opcao;
	int selecionado; // variável auxiliar para armazenar qual deve ser o tipo de ordenação a ser usado durante toda a busca
	int posicao = -1; // variável para armazenar a posição do registro, iniciada com -1 pois ainda não houve a busca
	int procurado; // variável para armazenar o valor que o usuário deseja procurar
	bool procurou; // variavel auxiliar para verificar se o registro foi encontrado
	string aux; // string auxiliar para receber a opção do usuário

	do
	{	
		procurou = false;

		cout << "======================================================================================================================" << endl << endl;
		cout << "Gostaria de fazer a busca pelo identificador ou pelo passaporte ?" << endl << endl;
		cout << "1. Identificador" << endl << "2. Número de passaporte" << endl << "0. Voltar para o menu principal" << endl << endl;
		cout << "Selecione uma opção: ";
		
		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o input é um número inteiro
		{
			opcao = stoi(aux); // conversão da string para inteiro
		}
		else
		{
			opcao = -1; // mudança no opcao para ele cair no default e repetir  
		}

		switch (opcao)
		{
			case 1: // realiza a busca pelo identificador
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o identificador que gostaria de procurar: ";
				getline(cin, aux);
				cout << endl;

				if (not aux.empty() and validacaoInt(aux)) // verifica se o identificador é válido
				{
					procurado = stoi(aux);
					posicao = buscaBinariaID(quantidadeDeRegistros, procurado, registros);
					selecionado = opcao;
					procurou = true;
				}
				else
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "Identificador inválido!!" << endl << endl;
				}
				
				break;
			
			case 2: // realiza a busca pelo passaporte
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o número de passaporte que gostaria de procurar: ";
				getline(cin, aux);
				cout << endl;

				if (not aux.empty() and validacaoInt(aux)) // verifica se o passaporte é válido
				{
					procurado = stoi(aux);
					posicao = buscaBinariaPassaporte(quantidadeDeRegistros, procurado, registros);
					selecionado = opcao;
					procurou = true;
				}
				else
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "Número de passaporte inválido!!" << endl << endl;
				}
				break;

			case 0: // volta para o menu inicial
				// caso 0 não pode cair no default
				break;

			default:
				cout << "======================================================================================================================" << endl << endl;
				cout << "Opção inválida!!" << endl << endl;
				break;
		}

		if (posicao == -1 and procurou) // condicional para verificar se a busca foi realizada e se o registro foi encontrado
		{
			cout << "Registro não encontrado" << endl << endl;
		}
		else if (posicao >= 0 and procurou)// caso o registro tenha sido encontrado
		{
			opcao = 0; // mudança para encerrar a repetição
		}
	
	} while (opcao != 0); // repetição para que o usuário digite uma opção ou informação válida
	
	if (posicao != -1) // condicional para verificar se a busca foi concretizada e abrir o menu de modificação
	{
		int numeroAux; // variável auxiliar para armazenar os novos valores e verificar se são válidos
		atletas aModificar = registros[posicao]; // variável auxiliar em que serão feitas as mudanças para depois serem registradas no vetor de registros
		do
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Identificador" << " | " << "Nome" << " | " << "Sexo" << " | " << "Idade" << " | " << "País" << " | " << "Número do Passaporte" << " | " << "Primeiro Idioma Falado" << " | " << "Modalidade" << " | " << "Preferência de Comida" << endl << endl; // cabeçalho

			cout << aModificar.identificador << " | " << aModificar.nome << " | " << aModificar.sexo << " | " << aModificar.idade << " | " << aModificar.pais << " | " << aModificar.passaporte << " | " << aModificar.idioma << " | " << aModificar.modalidade << " | " << aModificar.preferenciaComida << endl << endl;

			cout << "======================================================================================================================" << endl << endl;
			cout << "Deseja modificar algum dado do registro ?" << endl << endl << "1. Identificador" << endl << "2. Nome" << endl << "3. Sexo" << endl << "4. Idade" << endl << "5. País" << endl << "6. Passaporte" << endl << "7. Idioma" << endl << "8. Modalidade" << endl << "9. Preferencia de comida" << endl << "0. Não" << endl << endl;
			cout << "Selecione uma opção: ";

			getline(cin, aux);
			cout << endl;

			if (not aux.empty() and validacaoInt(aux))
			{
				opcao = stoi(aux);
			}
			else
			{
				opcao = -1; // mudança no opcao para ele cair no default e repetir
			}


			switch (opcao)
			{
				case 1: // modificar o identificador
					do
					{
						cout << "======================================================================================================================" << endl << endl;
						cout << "Digite o novo identificador (número inteiro): ";
						
						getline(cin, aux);
						cout << endl;

						if (not aux.empty() and validacaoInt(aux)) // verifica se o identificador é válido
						{
							numeroAux = stoi(aux);
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Identificador inválido!!" << endl << endl;
						}
					} while (aux.empty() or not validacaoInt(aux)); // repetição para que o usuário digite um identificador válido

					if (buscaBinariaID(quantidadeDeRegistros, numeroAux, registros) == -1) // condicional para vericação da existencia não existencia do novo identificador
					{
						aModificar.identificador = numeroAux;
						cout << "Identificador modificado!!" << endl << endl;
					}
					else
					{
						cout << "ERRO. O identificador já for registrado" << endl << endl;
					}
					break;
				
				case 2: // modificar o nome
					do
					{
						cout << "Digite o novo nome (até 35 caracteres): ";
						getline(cin, aux);
						cout << endl;

						if (aux.size() <= 35 and not aux.empty()) // verifica se o nome é válido
						{
							copy(&aux[0], &aux[aux.size()], aModificar.nome);
							aModificar.nome[aux.size()] = '\0';
							cout << "Nome modificado!!" << endl << endl;
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Nome inválido!!" << endl << endl;
						}
					} while (aux.size() > 35 or aux.empty()); // repetição para que o usuário digite um nome válido				
					break;

				case 3: // modificar o sexo
					do
					{
						cout << "Digite o novo sexo (M para masculino e F para feminino): ";
						getline(cin, aux);
						cout << endl;

						if(aux == "M" or aux == "F") // verifica se o sexo é válido
						{
							aModificar.sexo = aux[0];
							cout << "Sexo modificado!!" << endl << endl;
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Sexo inválido!!" << endl << endl;
						}
					} while (aux != "M" and aux != "F"); // repetição para que o usuário digite um sexo válido					
					break;

				case 4: // modificar a idade
					do 
					{
						cout << "Digite a nova idade (número inteiro): ";
						getline(cin, aux);
						cout << endl;

						if (not aux.empty() and validacaoInt(aux)) // verifica se a idade é válida
						{
							aModificar.idade = stoi(aux);
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Idade inválida!!" << endl << endl;
						}
					} while (aux.empty() or not validacaoInt(aux)); // repetição para que o usuário digite uma idade válida
					break;

				case 5: // modificar o país
					do 
					{
						cout << "Digite o novo país (até 25 caracteres): ";
						getline(cin, aux);
						cout << endl;

						if ((aux.size() <= 25) and (not aux.empty())) // verifica se o país é válido
						{
							copy(&aux[0], &aux[aux.size()], aModificar.pais);
							aModificar.pais[aux.size()] = '\0';
							cout << "País modificado!!" << endl << endl;
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "País inválido!!" << endl << endl;
						}
					} while (aux.size() > 25 or aux.empty()); // repetição para que o usuário digite um país válido
					break;

				case 6: // modificar o passaporte
					do 
					{
						cout << "Digite o novo número de passaporte (sequência de dígitos): ";
						getline(cin, aux);
						cout << endl;

						if (not aux.empty() and validacaoInt(aux)) // verifica se o passaporte é válido
						{
							numeroAux = stoi(aux);
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Número de passaporte inválido!!" << endl << endl;
						}
					} while (aux.empty() or not validacaoInt(aux)); // repetição para que o usuário digite um passaporte válido

					if (buscaBinariaPassaporte(quantidadeDeRegistros, numeroAux, registros) == -1) // condicional para vericação da existencia não existencia do novo passaporte
					{	
						aModificar.passaporte = numeroAux;
						cout << "Número de passaporte modificado!!" << endl << endl;
					}
					else
					{
						cout << "ERRO. O número de passaporte já foi registrado" << endl << endl;
					}
					break;

				case 7: // modificar o idioma
					do 
					{
						cout << "Digite o novo idioma (até 20 caracteres): ";
						getline(cin, aux);
						cout << endl;

						if (aux.size() <= 20 and not aux.empty()) // verifica se o idioma é válido
						{
							copy(&aux[0], &aux[aux.size()], aModificar.idioma);
							aModificar.idioma[aux.size()] = '\0';
							cout << "Idioma modificado!!" << endl << endl;
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Idioma inválido!!" << endl << endl;
						}
					} while (aux.size() > 20 or aux.empty()); // repetição para que o usuário digite um idioma válido
					break;

				case 8: // modificar a modalidade
					do 
					{
						cout << "Digite a nova modalidade (até 25 caracteres): ";
						getline(cin, aux);
						cout << endl;

						if (aux.size() <= 25 and not aux.empty()) // verifica se a modalidade é válida
						{
							copy(&aux[0], &aux[aux.size()], aModificar.modalidade);
							aModificar.modalidade[aux.size()] = '\0';
							cout << "Modalidade modificada!!" << endl << endl;
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Modalidade inválida!!" << endl << endl;
						}
					} while (aux.size() > 25 or aux.empty()); // repetição para que o usuário digite uma modalidade válida
					break;

				case 9: // modificar a preferência de comida
					do 
					{
						cout << "Digite a nova preferência de comida (até 25 caracteres): ";
						getline(cin, aux);
						cout << endl;

						if (aux.size() <= 25 and not aux.empty()) // verifica se a preferência de comida é válida
						{
							copy(&aux[0], &aux[aux.size()], aModificar.preferenciaComida);
							aModificar.preferenciaComida[aux.size()] = '\0';
							cout << "Preferência de comida modificada!!" << endl << endl;
						}
						else
						{
							cout << "======================================================================================================================" << endl << endl;
							cout << "Preferência de comida inválida!!" << endl << endl;
						}
					} while (aux.size() > 25 or aux.empty());
					break;

				case 0: // volta para o menu principal
					// caso 0 não pode cair no default
					break;
				
				default: // caso usuário escolha uma opção inválida
					cout << "======================================================================================================================" << endl << endl;
					cout << "Opção inválida!!" << endl << endl;
					break;
			}
		} while (opcao != 0);
		
		if (selecionado == 1) // condicional para retornar a ordenação setada a partir do tipo de busca
		{
			ordenacaoID(quantidadeDeRegistros, registros);
		}
		else
		{
			ordenacaoPassaporte(quantidadeDeRegistros, registros);
		}
		
		registros[posicao] = aModificar; // registro modificado é registrado no vetor de registros
	}
}

void escritaTela(int quantidadeDeRegistros, atletas* registros) // responsável pela escrita de todos os registos na tela
{
	int opcao;
	string aux; // string auxiliar para verificar se a opção é válida

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "O que deseja fazer?" << endl << endl;
		cout << "1. Mostrar todo o resgistro" << endl << "2. Mostrar parte do registro" << endl << "0. Voltar para o menu" << endl << endl;
		cout << "Selecione uma opção: ";

		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o input não está vazio e se é um número
		{
			opcao = stoi(aux); 
		}
		else
		{
			opcao = -1; // mudança no opcao para ele cair no default e repetir  
		}

		switch (opcao)
		{
			case 1: // mostrar todo o registro
				cout << "Identificador" << " | " << "Nome" << " | " << "Sexo" << " | " << "Idade" << " | " << "País" << " | " << "Número do Passaporte" << " | " << "Primeiro Idioma Falado" << " | " << "Modalidade" << " | " << "Preferência de Comida" << endl << endl; // cabeçalho

				for(int i = 0; i < quantidadeDeRegistros; i++)
				{
					cout << registros[i].identificador << " | " << registros[i].nome << " | " << registros[i].sexo << " | " << registros[i].idade << " | " << registros[i].pais << " | " << registros[i].passaporte << " | " << registros[i].idioma << " | " << registros[i].modalidade << " | " << registros[i].preferenciaComida << endl << endl;
				}

				cout << endl;
				break;

			case 2: // mostrar parte do registro
				int inicio, fim;

				do
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "Posição inicial: ";
					getline(cin, aux);
					cout << endl;

					if (not aux.empty() and validacaoInt(aux)) // verifica se o input não está vazio e se é um número 
					{
						inicio = stoi(aux); 
					}
					else
					{
						inicio = -1; // caso o input seja inválido, repete
					}

					if (inicio < 1 or inicio > quantidadeDeRegistros) // verifica se a posição é válida
					{
						cout << "======================================================================================================================" << endl << endl;
						cout << "Posição inválida!!" << endl << endl;
					}
					
				} while (inicio < 1 or inicio > quantidadeDeRegistros); // repetição para que o usuário digite uma posição válida
				
				do
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "Posição final: ";
					getline(cin, aux);
					cout << endl;

					if (not aux.empty() and validacaoInt(aux)) // verifica se o input não está vazio e se é um número
					{
						fim = stoi(aux); 
					}
					else
					{
						fim = -1; // caso o input seja inválido, repete
					}

					if (inicio > fim or fim > quantidadeDeRegistros)
					{
						cout << "======================================================================================================================" << endl << endl;
						cout << "Posição inválida!!" << endl << endl;
					}
					
				} while (inicio > fim or fim > quantidadeDeRegistros); // repetição para que o usuário digite uma posição válida

				cout << "Identificador" << " | " << "Nome" << " | " << "Sexo" << " | " << "Idade" << " | " << "País" << " | " << "Número do Passaporte" << " | " << "Primeiro Idioma Falado" << " | " << "Modalidade" << " | " << "Preferência de Comida" << endl << endl; // cabeçalho

				for(int i = inicio - 1; i < fim; i++)
				{
					cout << registros[i].identificador << " | " << registros[i].nome << " | " << registros[i].sexo << " | " << registros[i].idade << " | " << registros[i].pais << " | " << registros[i].passaporte << " | " << registros[i].idioma << " | " << registros[i].modalidade << " | " << registros[i].preferenciaComida << endl << endl;
				}

				cout << endl;
				break;

			case 0: // volta para o menu principal
				// caso 0 não pode cair no default
				break;
			
			default: // caso usuário escolha uma opção inválida
				cout << "======================================================================================================================" << endl << endl;
				cout << "Opção inválida!!" << endl << endl;
				break;
		}
	} while (opcao != 0);
}

void gravarDados(int quantidadeDeRegistros, int tipoArqAberto, atletas* registros, string nomeArqAberto) // responsável pela gravação dos registros num arquivo csv ou tipado
{
	int opcao;
	string nome; // string para receber o nome do arquivo
	bool mesmoArq = false; // variável auxiliar para guardar se a gravação vai ser feita no mesmo arquivo que foi aberto
	string aux; // string auxiliar para verificar se a opção é válida

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Em que tipo de arquivo gostaria de armazenar os dados ?" << endl << endl;
		cout << "1. Gravar no mesmo arquivo" << endl << "2. Novo arquivo CSV" << endl << "3. Novo arquivo tipado" << endl << "0. Voltar para o menu" << endl << endl;
		cout << "Selecione uma opção: ";

		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o input não está vazio e se é um número
		{
			opcao = stoi(aux); // converte a string para um inteiro
		}
		else
		{
			opcao = -1; // mudança no opcao para ele cair no default e repetir
		}

		if (opcao == 1) // gravar no arquivo que havia sido aberto
		{
			mesmoArq = true;
			nome = nomeArqAberto;
			opcao = tipoArqAberto + 1; // executa a opção de referente ao tipo de arquivo que havia sido aberto
		}
		
		if (opcao == 2) // execução da gravação em um arquivo csv
		{
			if (not mesmoArq) // caso o arquivo não seja o mesmo que foi aberto
			{
				cout << "======================================================================================================================" << endl << endl;
				cout << "Qual o nome do arquivo? ";
				getline(cin, nome);
				nome += ".csv"; // adição da extensão do arquivo
				cout << endl;
			}
			
			ofstream saida(nome);
			
			saida << "#identificador(int),nome(string com espaço),sexo(char),idade(int),pais(string com espaço),numero passaporte(int),primeiro idioma(string),modalidade(string com espaço),preferencia de comida(string com espaço)" << endl << quantidadeDeRegistros << endl; // escrita do índice

			for (int i = 0; i < quantidadeDeRegistros; i++)
			{
				saida << registros[i].identificador << ',' << registros[i].nome << ',' << registros[i].sexo << ',' << registros[i].idade << ',' << registros[i].pais << ',' << registros[i].passaporte << ',' << registros[i].idioma << ',' << registros[i].modalidade << ',' << registros[i].preferenciaComida << endl;
			}
			
			saida.close();

			cout << "Arquivo escrito com sucesso!!" << endl << endl;
			opcao = 0; // troca do valor da opcao para que ela seja encerrada
		}
		
		else if (opcao == 3) // gravação em um arquivo tipado
		{
			
			if (not mesmoArq) // caso o arquivo não seja o mesmo que foi aberto
			{
				cout << "======================================================================================================================" << endl << endl;
				cout << "Qual o nome do arquivo? ";
				getline(cin, nome);
				nome += ".bin"; // adição da extensão do arquivo
				cout << endl;
			}

			ofstream saida(nome);
			saida.write((const char *) (registros), sizeof(atletas) * quantidadeDeRegistros);
			saida.close();

			cout << "Arquivo escrito com sucesso!!" << endl << endl;
			opcao = 0; // troca do valor da opcao para que ela seja encerrada
		}
		
		else if (opcao != 0) // caso usuário escolha uma opção inválida
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Opção inválida!!" << endl << endl;
		}
	} while (opcao != 0);
}

void menuPrincipal(int &quantidadeDeRegistros, int &tamanhoVet, int tipoDeArq, atletas* &registros, string nomeDoArqAberto) // menu com as principais funções do programar
{
	int opcao;
	int verifica;
	string aux; // string auxiliar para verificar se a opção é válida

	do
	{
		ordenacaoID(quantidadeDeRegistros, registros); // ordenação padrão do programa 

		cout << "======================================================================================================================" << endl << endl;
		cout << "O que deseja fazer?" << endl << endl;
		cout << "1. Fazer mais um registro" << endl << "2. Remover um registro" << endl << "3. Buscar por um registro" << endl << "4. Escrever registro na tela" << endl << "5. Gravar registros em um arquivo" << endl << "0. Encerrar o programa" << endl << endl;
		cout << "Selecione uma opção: ";

		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o input não está vazio e se é um número
		{
			opcao = stoi(aux); 
		}
		else
		{
			opcao = -1; // mudança no opcao para ele cair no default e repetir  
		}


		switch (opcao)
		{
			case 1: // adicionar registro
				verifica = adicionarRegistro(quantidadeDeRegistros, tamanhoVet, registros);
				// mensagens de retorno sobre a adição de registro
				if(verifica == 0)
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "Registro adicionado com sucesso!!" << endl << endl;
				}
				else if(verifica == 1)
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "ERRO. O identificador já foi registrado" << endl << endl;
				}
				else if(verifica == 2)
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "ERRO. O passaporte já foi registrado" << endl << endl;
				}
				break;
			
			case 2: // remover registro
				removerRegistro(quantidadeDeRegistros, registros);
				break;

			case 3: // buscar um registro
				buscaDeRegistro(quantidadeDeRegistros, registros);
				break;

			case 4: // escrever registros na tela
				escritaTela(quantidadeDeRegistros, registros);
				break;

			case 5: // registos em um arquivo
				gravarDados(quantidadeDeRegistros, tipoDeArq, registros, nomeDoArqAberto);
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

int main() // inicia as variáveis, chama a abertura do arquivo e do menu principal
{
	int tamanhoVet = 40; // controlador do tamnho do vetor
	int quantidadeDeRegistros = 0; // controlador da quantidade de registros
	int tipoDeArqAberto; // armazena o tipo do arquivo que foi aberto
	int opcao; // opção do menu
	atletas *registros = new atletas[tamanhoVet]; // vetor que armazena os dados de registro
	string nomeArqAberto; // armazena o nome do arquivo que foi aberto
	string aux; // string auxiliar para verificar se o dado é válido

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "O que deseja fazer?" << endl << endl;
		cout << "1. Ler uma arquivo CSV" << endl << "2. Ler um arquivo tipado" << endl << "0. Fechar programa" << endl << endl;
		cout << "Selecione uma opção: ";

		getline(cin, aux);
		cout << endl;

		if (not aux.empty() and validacaoInt(aux)) // verifica se o input não está vazio e se é um número
		{
			opcao = stoi(aux); 
		}
		else
		{
			opcao = -1; // mudança no opcao para ele cair no default e repetir  
		}

		switch (opcao)
		{
			case 1: // faz a leitura de um arquivo CSV
				if (leituraCSV(registros, tamanhoVet, quantidadeDeRegistros, nomeArqAberto) == 0) // condicicional q vai chamar a função e executar as outras partes do programa caso o arquivo tenha sido lido
				{
					tipoDeArqAberto = 1;
					menuPrincipal(quantidadeDeRegistros, tamanhoVet, tipoDeArqAberto, registros, nomeArqAberto);
					opcao = 0; // mudança no opcao para ele fechar o programa depois de que o menu principal acaba
				}
				break;
			
			case 2: // faz a leitura de um arquivo Tipado
				if (leituraTipado(registros, tamanhoVet, quantidadeDeRegistros, nomeArqAberto) == 0) // condicicional q vai chamar a função e executar as outras partes do programa caso o arquivo tenha sido lido
				{
					tipoDeArqAberto = 2;
					menuPrincipal(quantidadeDeRegistros, tamanhoVet, tipoDeArqAberto, registros, nomeArqAberto);
					opcao = 0; // mudança no opcao para ele fechar o programa depois de que o menu principal acaba
				}
				break;

			case 0: // opção para fechar o programa 
				// o 0 não pode cair no default
				break;

			default: // opção inválida
				cout << "======================================================================================================================" << endl << endl;
				cout << "Opção inválida!!" << endl << endl;
				break;
		}

	} while (opcao != 0);

	delete[] registros;
	cout << "Fechando programa...";
	return 0;
}
