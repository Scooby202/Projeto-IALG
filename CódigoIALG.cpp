#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct atletas // estrutura que guarda todas as informações de registro dos atletas
{
	int identificador, idade;
	int passaporte;
	char nome[35], pais[25], idioma[20], modalidade[25], preferenciaComida[25]; 
	char sexo;
};

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

int buscaBinariaPassaporte(int quantidadeDeRegistros, int procurado, atletas* registros) // busca binária para o passaporte 
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

int validacaoDoArquivo(int quantidadeDeRegistros, atletas* registros) // verifica no arquivo se há identificadores ou passaportes repetidos, comparando os adjascentes depois de ordenados
{
	ordenacaoPassaporte(quantidadeDeRegistros, registros);

	for (int i = 0; i < quantidadeDeRegistros - 1; i++)
	{
		if (registros[i].passaporte == registros[i + 1].passaporte)
		{
			cout << registros[i].identificador << ' ' << registros[i].nome << ' ' << registros[i].sexo << ' ' << registros[i].idade << ' ' << registros[i].pais << ' ' << registros[i].passaporte << ' ' << registros[i].idioma << ' ' << registros[i].modalidade << ' ' << registros[i].preferenciaComida << endl;

			return 1;
		}
	}

	ordenacaoID(quantidadeDeRegistros, registros);

	for (int i = 0; i < quantidadeDeRegistros - 1; i++)
	{
		if (registros[i].identificador == registros[i + 1].identificador)
		{
			return 2;
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

int leituraTipado(atletas* &registros, int &tamanhoVet, int &quantidadeDeRegistros, string &nomeArqAberto) // função para a leitura dos dados vindos do arquivo tipado
{
	cout << "======================================================================================================================" << endl << endl;
	cout << "Digite o nome do arquivo: ";

	cin >> nomeArqAberto;

	cout << endl;

	ifstream entrada(nomeArqAberto); // abertura do arquivo
	
	if (entrada) // verificação se o arquivo foi encontrado
	{
		entrada.seekg (0, entrada.end);
    	quantidadeDeRegistros = entrada.tellg();
		quantidadeDeRegistros /= 144;
		entrada.seekg (0, entrada.beg);
	}
	else // mensagem de erro e retorno para o menu inicial
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo não encontrado! Voltando para o menu incial..." << endl << endl;
		return 1;
	}

	while (tamanhoVet < quantidadeDeRegistros) // repetição para realizar o redimensionamento do vetor quando a quantidade de dados excede o tamanho do vetor
	{
		redimensionamento(registros, tamanhoVet);
	}
	
	entrada.read((char *) (registros), sizeof(atletas) * quantidadeDeRegistros);

	entrada.close();

	// sistema de validação de arquivo para passaporte e identificador
	if (validacaoDoArquivo(quantidadeDeRegistros, registros) == 1)
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo com passaportes repetidos! Voltando para o menu incial..." << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}

	else if (validacaoDoArquivo(quantidadeDeRegistros, registros) == 2)
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo com identificadores repetidos! Voltando para o menu incial..." << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}
	
	cout << "======================================================================================================================" << endl << endl;
	cout << "Arquivo aberto com sucesso!!" << endl << endl;

	return 0; // return 0 para que o menu principal seja chamado
}

int leituraCSV(atletas* &registros, int &tamanhoVet, int &quantidadeDeRegistros, string &nomeArqAberto) // função para a leitura dos dados vindos do arquivo csv
{
	cout << "======================================================================================================================" << endl << endl;
	cout << "Digite o nome do arquivo: ";

	cin >> nomeArqAberto;

	cout << endl;

	string linha; // string auxiliar para guardar os o índice do csv
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
		return 1;
	}

	char lixo; // char auxliliar para remover as vírgulas do arquivo csv
	int i = 0; 
	while (i < quantidadeDeRegistros)
	{
		if (i < tamanhoVet)
		{
			entrada >> registros[i].identificador;
			entrada >> lixo;
			entrada.getline(registros[i].nome, 35, ',');
			entrada >> registros[i].sexo;
			entrada >> lixo;
			entrada >> registros[i].idade;
			entrada >> lixo;
			entrada.getline(registros[i].pais, 25, ',');
			entrada >> registros[i].passaporte;
			entrada >> lixo;
			entrada.getline(registros[i].idioma, 20, ',');
			entrada.getline(registros[i].modalidade, 25, ',');
			entrada.getline(registros[i].preferenciaComida, 25);
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
		cout << "Arquivo com passaportes inválidos! Voltando para o menu incial..." << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}

	else if (validacaoDoArquivo(quantidadeDeRegistros, registros) == 2)
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Arquivo com identificadores inválidos! Voltando para o menu incial..." << endl << endl;
		return 1; // return 1 para que o menu inicial repita novamente
	}
	
	cout << "======================================================================================================================" << endl << endl;
	cout << "Arquivo aberto com sucesso!!" << endl << endl;

	return 0; // return 0 para que o menu principal seja chamado
}

void removerRegistro(int &quantidadeDeRegistros, atletas* registros) // realiza o processo de remoção de um arquivo
{
	int posicao;
	int opcao;
	int procurado;

	do
	{

		cout << "======================================================================================================================" << endl << endl;
		cout << "Digite o identificador do registro que gostaria de remover: ";
		
		cin >> procurado;
		
		cout << endl;

		posicao = buscaBinariaID(quantidadeDeRegistros, procurado, registros);

		if (posicao == -1)
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Registro inexistente!!" << endl << endl;
		}
		
	} while (posicao == -1);

	do
	{
		cout << "Tem certeza que deseja remover o resgistro: " << registros[posicao].identificador << " " << registros[posicao].nome << " " << registros[posicao].sexo << " " << registros[posicao].idade << " " << registros[posicao].pais << " " << registros[posicao].passaporte << " " << registros[posicao].idioma << " " << registros[posicao].modalidade << " " << registros[posicao].preferenciaComida << "?" << endl << endl;
		cout << "1. Sim" << endl << "2. Não" << endl << endl;
		cout << "Selecione uma opção: ";

		cin >> opcao;

		cout << endl;

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
	} while (opcao > 2 or opcao < 1);
	
}

void adicionarRegistro(int &quantidadeDeRegistros, int &tamanhoVet, atletas* &registros) // responsável pela adição de um novo registro
{
	quantidadeDeRegistros++;
	int posicao = quantidadeDeRegistros - 1;
	bool analise;

	if (tamanhoVet < quantidadeDeRegistros) // condicional para verificar se é necessário o redimensionamento do vetor
	{
		redimensionamento (registros, tamanhoVet);
	}

	cout << "Digite o identificador: ";
	cin >> registros[posicao].identificador;
	cout << endl;
		
	if (buscaBinariaID(quantidadeDeRegistros - 1, registros[posicao].identificador, registros) != -1) // verifica se o identificador já foi registrado
	{
		// encerra a função, exclui o resgistro e volta para o menu principal
		cout << "ERRO. O identificador já foi registrado. Voltando para o menu principal..." << endl << endl;
		quantidadeDeRegistros--;
		return; 
	}

	cin.ignore();

	cout << "Digite o nome: ";
	cin.getline(registros[posicao].nome, 35);
	cout << endl;

	do
	{
		cout << "Digite o sexo (M para masculino e F para feminino): ";
		cin >> registros[posicao].sexo;
		cout << endl;

		if (registros[posicao].sexo != 'M' and registros[posicao].sexo != 'F') // verifica se o sexo é válido
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << "Sexo inválido!!" << endl << endl;
		}
	} while (registros[posicao].sexo != 'M' and registros[posicao].sexo != 'F');
	
	
	cout << "Digite a idade: ";
	cin >> registros[posicao].idade;
	cout << endl;

	cin.ignore();

	cout << "Digite o país: ";
	cin.getline(registros[posicao].pais, 25);
	cout << endl;

	cout << "Digite o passaporte: ";
	cin >> registros[posicao].passaporte;
	cout << endl;
	
	if (buscaBinariaPassaporte(quantidadeDeRegistros - 1, registros[posicao].passaporte, registros) != -1) // verifica se o passaporte já foi registrado
	{
		// encerra a função, exclui o resgistro e volta para o menu principal
		cout << "ERRO. O passaporte já foi registrado. Voltando para o menu principal..." << endl << endl;
		quantidadeDeRegistros--;
		return;
	}

	cin.ignore();

	cout << "Digite o primeiro idioma: ";
	cin.getline(registros[posicao].idioma, 20);
	cout << endl;
	
	cout << "Digite a modalidade: ";
	cin.getline(registros[posicao].modalidade, 25);
	cout << endl;

	cout << "Digite a preferência de comida: ";
	cin.getline(registros[posicao].preferenciaComida, 25);
	cout << endl;

	cout << "Novo registro cadastrado!!" << endl << endl;

	return;
}

void buscaDeRegistro(int quantidadeDeRegistros, atletas* registros) // possibilita a busca de um determinado registro pelo usuário e permite sua modificação
{
	int selecionado; // variável auxiliar para armazenar qual deve ser o tipo de ordenação a ser usado durante toda a busca
	int opcao;
	int posicao = -1;
	int procurado;
	bool procurou; // variavel auxiliar para verificar se o registro foi encontrado
	do
	{	
		procurou = false;

		cout << "======================================================================================================================" << endl << endl;
		cout << "Gostaria de fazer a busca pelo identificador ou pelo passaporte ?" << endl << endl;
		cout << "1. Identificador" << endl << "2. Passaporte" << endl << "0. Voltar para o menu principal" << endl << endl;
		cout << "Selecione uma opção: ";
		
		cin >> opcao;

		cout << endl;

		switch (opcao)
		{
		case 1: // realiza a busca pelo identificador
			cout << "======================================================================================================================" << endl << endl;
			cout << "Digite o identificador que gostaria de procurar: ";
			cin >> procurado;
			cout << endl;
			posicao = buscaBinariaID(quantidadeDeRegistros, procurado, registros);
			selecionado = opcao;
			procurou = true;
			break;
		
		case 2: // realiza a busca pelo passaporte
			cout << "======================================================================================================================" << endl << endl;
			cout << "Digite o passaporte que gostaria de procurar: ";
			cin >> procurado;
			cout << endl;
			posicao = buscaBinariaPassaporte(quantidadeDeRegistros, procurado, registros);
			selecionado = opcao;
			procurou = true;
			break;

		case 0: // volta para o menu inicial
			
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
		else if (posicao >= 0 and procurou)// caso o registro seja encontrado
		{
			opcao = 0; // mudança para encerrar a repetição
		}
		

	} while (opcao != 0);
	
	if (posicao != -1) // condicional para verificar se a busca foi realizada e abrir o menu de modificação
	{
		int numeroAux; // variável auxiliar para armazenar os novos valores e verificar se são válidos


		do
		{
			cout << "======================================================================================================================" << endl << endl;
			cout << registros[posicao].identificador << ' ' << registros[posicao].nome << ' ' << registros[posicao].sexo << ' ' << registros[posicao].idade << ' ' << registros[posicao].pais << ' ' << registros[posicao].passaporte << ' ' << registros[posicao].idioma << ' ' << registros[posicao].modalidade << ' ' << registros[posicao].preferenciaComida << endl << endl;

			cout << "======================================================================================================================" << endl << endl;
			cout << "Deseja modificar algum dado do registro ?" << endl << endl << "1. Identificador" << endl << "2. Nome" << endl << "3. Sexo" << endl << "4. Idade" << endl << "5. País" << endl << "6. Passaporte" << endl << "7. Idioma" << endl << "8. Modalidade" << endl << "9. Preferencia de comida" << endl << "0. Não" << endl << endl;
			cout << "Selecione uma opção: ";

			cin >> opcao;

			cout << endl;

			switch (opcao)
			{
			case 1: // modificar o identificador
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o novo identificador: ";
				
				cin >> numeroAux;
				
				cout << endl;

				if (buscaBinariaID(quantidadeDeRegistros, numeroAux, registros) == -1) // condicional para vericação da existencia não existencia do novo identificador
				{
					if(selecionado == 2) // condicional para que a ordenação se mantenha correta depois da busca
					{
						ordenacaoPassaporte(quantidadeDeRegistros, registros);
					}
					registros[posicao].identificador = numeroAux;
					cout << "Identificador modificado!!" << endl << endl;
				}
				else
				{
					if(selecionado == 2)
					{
						ordenacaoPassaporte(quantidadeDeRegistros, registros);
					}
					cout << "ERRO. O identificador já for registrado" << endl << endl;
				}
				break;
			
			case 2: // modificar o nome
				cin.ignore();
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o novo nome: ";
				
				cin.getline(registros[posicao].nome, 35);
				
				cout << endl << "Nome modificado!!" << endl << endl;
				break;

			case 3: // modificar o sexo
				do
				{
					cout << "Digite o sexo (M para masculino e F para feminino): ";
					cin >> registros[posicao].sexo;
					cout << endl;

					if (registros[posicao].sexo != 'M' and registros[posicao].sexo != 'F') // verifica se o sexo é válido
					{
						cout << "======================================================================================================================" << endl << endl;
						cout << "Sexo inválido!!" << endl << endl;
					}
				} while (registros[posicao].sexo != 'M' and registros[posicao].sexo != 'F');

				cout << "Sexo modificado!!" << endl << endl;
				break;

			case 4: // modificar a idade
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite a nova idade: ";
				
				cin >> registros[posicao].idade;
				
				cout << endl << "Idade modificada!!" << endl << endl;
				break;

			case 5: // modificar o país
				cin.ignore();
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o novo país: ";
				
				cin.getline(registros[posicao].pais, 25);
				
				cout << endl << "País modificado!!" << endl << endl;
				break;

			case 6: // modificar o passaporte
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o novo passaporte: ";
				
				cin >> numeroAux;
				cout << numeroAux;
				
				cout << endl;

				if (buscaBinariaPassaporte(quantidadeDeRegistros, numeroAux, registros) == -1) // condicional para vericação da existencia não existencia do novo passaporte
				{	
					if(selecionado == 1) // condicional para que a ordenação se mantenha correta depois da busca
					{
						ordenacaoID(quantidadeDeRegistros, registros);
					}
					registros[posicao].passaporte = numeroAux;
					cout << "Passaporte modificado!!" << endl << endl;
					cout << posicao;
				}
				else
				{
					if(selecionado == 1)
					{
						ordenacaoID(quantidadeDeRegistros, registros);
					}
					cout << "ERRO. O passaporte já foi registrado" << endl << endl;
				}
				break;

			case 7: // modificar o idioma
				cin.ignore();
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite o novo idioma: ";
				
				cin.getline(registros[posicao].idioma, 20);
				
				cout << endl << "Idioma modificado!!" << endl << endl;
				break;

			case 8: // modificar a modalidade
				cin.ignore();
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite a nova modalidade: ";
				
				cin.getline(registros[posicao].modalidade, 25);
				
				cout << endl << "Modalidade modificada!!" << endl << endl;
				break;

			case 9: // modificar a preferência de comida
				cin.ignore();
				cout << "======================================================================================================================" << endl << endl;
				cout << "Digite a nova prefenrência de comida: ";
				
				cin.getline(registros[posicao].preferenciaComida, 25);
				
				cout << endl << "Preferência de comida modificada!!" << endl << endl;
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
}

void escritaTela(int quantidadeDeRegistros, atletas* registros) // responsável pela escrita de todos os registos feitos na tela
{
	int opcao;

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "O que deseja fazer?" << endl << endl;
		cout << "1. Mostrar todo o resgistro" << endl << "2. Mostrar parte do registro" << endl << "0. Voltar para o menu" << endl << endl;
		cout << "Selecione uma opção: ";

		cin >> opcao;

		cout << endl;

		switch (opcao)
		{
		case 1: // mostrar todo o registro
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
				cin >> inicio;
				cout << endl;

				if (inicio < 1 or inicio > quantidadeDeRegistros)
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "Posição inválida!!" << endl << endl;
				}
				
			} while (inicio < 1 or inicio > quantidadeDeRegistros); // verifica se a posição é válida
			
			do
			{
				cout << "======================================================================================================================" << endl << endl;
				cout << "Posição final: ";
				cin >> fim;
				cout << endl;

				if (inicio > fim or fim > quantidadeDeRegistros)
				{
					cout << "======================================================================================================================" << endl << endl;
					cout << "Posição inválida!!" << endl << endl;
				}
				
			} while (inicio > fim or fim > quantidadeDeRegistros); // verifica se a posição é válida

			for(int i = inicio - 1; i < fim; i++)
			{
				cout << registros[i].identificador << " | " << registros[i].nome << " | " << registros[i].sexo << " | " << registros[i].idade << " | " << registros[i].pais << " | " << registros[i].passaporte << " | " << registros[i].idioma << " | " << registros[i].modalidade << " | " << registros[i].preferenciaComida << endl << endl;
			}

			cout << endl;

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

	do
	{
		cout << "======================================================================================================================" << endl << endl;
		cout << "Em que tipo de arquivo gostaria de armazenar os dados ?" << endl << endl;
		cout << "1. Gravar no mesmo arquivo" << endl << "2. Novo arquivo CSV" << endl << "3. Novo arquivo tipado" << endl << "0. Voltar para o menu" << endl << endl;
		cout << "Selecione uma opção: ";

		cin >> opcao; 

		cout << endl;

		if (opcao == 1)
		{
			mesmoArq = true;
			nome = nomeArqAberto;
			opcao = tipoArqAberto + 1;
		}
		
		
		if (opcao == 2) // execução da gravação em um arquivo csv
		{
			if (not mesmoArq)
			{
				cout << "======================================================================================================================" << endl << endl;
				cout << "Qual o nome do arquivo? (adicione .csv ao final do nome) ";

				cin >> nome;

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
			
			if (not mesmoArq)
			{
				cout << "======================================================================================================================" << endl << endl;
				cout << "Qual o nome do arquivo? (adicione .txt ao final do nome) ";

				cin >> nome;

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

void menuPrincipal(int &quantidadeDeRegistros, int &tamanhoVet, int tipoDeArq, atletas* &registros, string nomeDoArqAberto) // menu com as principais funções do programa
{
	int opcao;

	do
	{
		ordenacaoID(quantidadeDeRegistros, registros); // ordenação padrão do programa 

		cout << "======================================================================================================================" << endl << endl;
		cout << "O que deseja fazer?" << endl << endl;
		cout << "1. Fazer mais um registro" << endl << "2. Remover um registro" << endl << "3. Buscar por um registro" << endl << "4. Escrever registro na tela" << endl << "5. Gravar registros em um arquivo" << endl << "0. Encerrar o programa" << endl << endl;
		cout << "Selecione uma opção: ";

		cin >> opcao;

		cout << endl;

		switch (opcao)
		{
		case 1: // adicionar registro
			adicionarRegistro(quantidadeDeRegistros, tamanhoVet, registros);
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
	int opcao;
	int tipoDeArqAberto; // armazena o tipo do arquivo que foi aberto
	atletas *registros = new atletas[tamanhoVet]; // vetor que armazena os dados de registro
	string nomeArqAberto; // armazena o nome do arquivo que foi aberto

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
			if (leituraCSV(registros, tamanhoVet, quantidadeDeRegistros, nomeArqAberto) == 0) // condicicional q vai chamar a função e executar as outras partes do programa caso o arquivo tenha sido lido
			{
				tipoDeArqAberto = 1;
				menuPrincipal(quantidadeDeRegistros, tamanhoVet, tipoDeArqAberto, registros, nomeArqAberto);
				opcao = 0;
			}
			break;
		
		case 2: // faz a leitura de um arquivo Tipado
			if (leituraTipado(registros, tamanhoVet, quantidadeDeRegistros, nomeArqAberto) == 0) // condicicional q vai chamar a função e executar as outras partes do programa caso o arquivo tenha sido lido
			{
				tipoDeArqAberto = 2;
				menuPrincipal(quantidadeDeRegistros, tamanhoVet, tipoDeArqAberto, registros, nomeArqAberto);
				opcao = 0;
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