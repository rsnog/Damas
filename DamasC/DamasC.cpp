// DamasC.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <string.h>
#include <conio.h>
#define linha 9
#define coluna 9
#pragma warning(disable : 4996)
using namespace std;
int origemLinha, origemColuna, destinoLinha, destinoColuna, jogador, jogadorAnterior, pecasP, pecasB, empate;
char referenciaC[9] = { ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
char referenciaL[9] = { ' ', '8', '7', '6', '5', '4', '3', '2', '1' };
char tabReferencia[linha][coluna];
char peca = tabReferencia[origemLinha][origemColuna];
char pecaDestino = tabReferencia[destinoLinha][destinoColuna];
bool proximo;
string retorno;

void copiarMatrix(char t[][coluna]); //COPIA MATRIZ INICIAL PARA A QUE SERÁ UTILIZADA, INICIALIZA VARIÁVEIS
void mostraTabuleiro(); //MOSTRA O TABULEIRO ATUALIZADO
string jogada(); //INICIALIZA AS VERIFICAÇÕES DOS PARÂMETROS DE JOGADA
string regra1(string cstr); //VEZ DE JOGAR			  
string regra2(string cstr); //MOVIMENTO VÁLIDO 1 PEÇA
string regra3(string cstr); //VERIFICA PROMOÇÃO
string regra4(string cstr); //VERIFICA TOMAR PEÇA 1 MOVIMENTO
string regra5(string cstr); //VERIFICA TOMAR PEÇA DAMA
string regra6(string cstr); //MOVIMENTO VÁLIDO DAMA
string move1Peca(string cstr); //EFETIVA A MOVIMENTAÇÃO DE UMA PEÇA
string moveDama(string cstr); //EFETIVA A MOVIMENTAÇÃO DA DAMA
string tomar1Peca(string cstr); //EFETIVA TOMAR UMA PEÇA
string tomarDama(string cstr); //EFETIVA TOMAR DA DAMA

//MAIN
int main()
{
	setlocale(LC_ALL, "");
	string movimento;

	char tabuleiro[linha][coluna] = {
	{ ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' },
	{ '8', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.' },
	{ '7', '.', 'x', '.', '.', '.', '.', '.', '.' },
	{ '6', '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '5', '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '4', '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '3', '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '2', '.', '.', '.', '.', '.', '.', '.', '.' },
	{ '1', 'O', 'o', 'o', 'o', 'o', 'o', 'o', 'o' }
	};
	copiarMatrix(tabuleiro);

	while (1) {
		proximo = false;
		mostraTabuleiro();
		movimento = jogada();
		if (movimento == "FIM")
		{
			break;
		}
		else if (movimento == "NOVO")
		{
			system("cls");
			cout << "\n\n   Um novo jogo será iniciado !!!\n" << endl;
			system("PAUSE");
			copiarMatrix(tabuleiro);
		}
		else if (empate == 10)
		{
			system("cls");
			cout << "\n\n   Jogo empatado !!!\n   Um novo jogo será iniciado !!!\n" << endl;
			system("PAUSE");
			copiarMatrix(tabuleiro);
		}
		else if (pecasB == 0)
		{
			system("cls");
			cout << "\n\n   O jogador 2 venceu !!!\n   Obrigado por jogar !!!\n" << endl;
			cout << "\n\n   Um novo jogo será iniciado !!!\n" << endl;
			system("PAUSE");
			copiarMatrix(tabuleiro);
		}
		else if (pecasP == 0)
		{
			system("cls");
			cout << "\n\n   O jogador 1 venceu !!!\n   Obrigado por jogar !!!\n" << endl;
			cout << "\n\n   Um novo jogo será iniciado !!!\n" << endl;
			system("PAUSE");
			copiarMatrix(tabuleiro);
		}
		else if (movimento == "erro")
		{
			system("cls");
			cout << "\n\n   Jogada inválida !!!\n   Jogue novamente !!!\n" << endl;
			system("PAUSE");
		}
		else if (movimento == "jogador")
		{
			system("cls");
			cout << "\n\n   Jogada inválida !!!\n   É a vez do jogador " << jogador << " !!!\n" << endl;
			system("PAUSE");
		}
		else if (movimento == "promovido")
		{
			int jogadorP;
			if (jogador == 1)
			{
				jogadorP = 2;
			}
			else
			{
				jogadorP = 1;
			}
			system("cls");
			cout << "\n\n   Peça promovida !!!\n   Parabéns jogador " << jogadorP << " !!!\n" << endl;
			system("PAUSE");
		}
		else if (movimento == "tomar1" || movimento == "tomar2" || movimento == "tomarD2" || movimento == "tomarD2")
		{
			system("cls");
			cout << "\n\n   Peça a ser tomada !!!\n   É a vez do jogador " << jogador << " !!!\n" << endl;
			system("PAUSE");
		}
	}

	system("cls");
	cout << "\n\n  Obrigado por jogar !!!\n  Volte Sempre!!! \n" << endl;
	system("PAUSE");
	return 0;
}

//COPIA MATRIZ INICIAL PARA A QUE SERÁ UTILIZADA, INICIALIZA VARIÁVEIS
void copiarMatrix(char t[][coluna]) { //COPIA MATRIZ INICIAL PARA A QUE SERÁ UTILIZADA, INICIALIZA VARIÁVEIS
	jogador = 1, jogadorAnterior = 2, empate = 0;
	for (size_t i = 0; i < linha; ++i)
	{
		for (size_t j = 0; j < coluna; ++j)
			tabReferencia[i][j] = t[i][j];
	}
}

//MOSTRA O TABULEIRO ATUALIZADO
void mostraTabuleiro() {
	system("cls");
	cout << "\n";
	int i, j;
	pecasP = 0, pecasB = 0;
	for (i = 0; i < linha; ++i)
	{
		cout << "  ";
		for (j = 0; j < coluna; ++j) {
			cout << tabReferencia[i][j] << " ";
			if (tabReferencia[i][j] == 'x' || tabReferencia[i][j] == 'X')
			{
				pecasP++;
			}
			if (tabReferencia[i][j] == 'o' || tabReferencia[i][j] == 'O')
			{
				pecasB++;
			}
		}
		cout << "\n";
	}
	cout << "\n";
	cout << " Jogador: " << jogador << "\n\n";
	//cout << "ORIGEM: " << tabReferencia[origemLinha][origemColuna] << " DESTINO:" << tabReferencia[destinoLinha][destinoColuna] << "\n";
	//cout << "ORIGEM: " << peca << " DESTINO:" << pecaDestino << "\n";
	cout << " Peças Brancas: " << pecasB << " -" << " Peças Pretas: " << pecasP << "\n\n";
	//cout << origemLinha << " " << origemColuna << " " << destinoLinha << " " << destinoColuna << "\n\n";
}

//INICIALIZA AS VERIFICAÇÕES DOS PARÂMETROS DE JOGADA
string jogada() {
	string input = "";
	origemLinha = 0, origemColuna = 0, destinoLinha = 0, destinoColuna = 0;
	cout << " Digite 'FIM' para sair do jogo ou 'NOVO' para novo jogo ... \n";
	cout << " Digite a origem e o destino da jogada '3A4B' (LINHA/COLUNA): ";
	getline(cin, input);

	char *cstr = new char[input.length() + 1];
	strcpy(cstr, input.c_str());
	for (size_t i = 0; i < input.length(); i++)
	{
		cstr[i] = toupper(cstr[i]);
	}
	input = cstr;

	if (input == "FIM")
	{
		return input;
	}
	if (input == "NOVO")
	{
		return input;
	}

	if (input.length() == 4)
	{
		for (size_t j = 0; j < 9; j++)
		{
			if (cstr[0] == referenciaL[j])
			{
				origemLinha = j;
			}
			if (cstr[1] == referenciaC[j])
			{
				origemColuna = j;
			}
			if (cstr[2] == referenciaL[j])
			{
				destinoLinha = j;
			}
			if (cstr[3] == referenciaC[j])
			{
				destinoColuna = j;
			}
		}
		pecaDestino = tabReferencia[destinoLinha][destinoColuna];
		if (origemLinha == 0 || origemColuna == 0 || destinoLinha == 0 || destinoColuna == 0 || pecaDestino != '.')
		{
			input = "erro";
		}

		if (input != "erro")
		{
			input = regra1(input);
		}
	}
	else
	{
		input = "erro";
		return input;
	}
	if (proximo == true && jogador == 1)
	{
		jogador = 2;
		jogadorAnterior = 1;
	}
	else if (proximo == true && jogador == 2)
	{
		jogador = 1;
		jogadorAnterior = 2;
	}
	return input;
}

//VEZ DE JOGAR
string regra1(string cstr) {
	retorno = cstr;
	peca = tabReferencia[origemLinha][origemColuna];
	if (jogador == 1 && peca == 'o')
	{
		retorno = regra2(cstr);
	}
	else if (jogador == 2 && peca == 'x')
	{
		retorno = regra2(cstr);
	}
	else if (jogador == 1 && peca == 'O')
	{
		retorno = regra6(cstr);
	}
	else if (jogador == 2 && peca == 'X')
	{
		retorno = regra6(cstr);
	}
	else
	{
		retorno = "jogador";
	}
	return retorno;
}

//MOVIMENTO VÁLIDO 1 PEÇA
string regra2(string cstr) {
	retorno = cstr;
	peca = tabReferencia[origemLinha][origemColuna];
	pecaDestino = tabReferencia[destinoLinha][destinoColuna];
	if (jogador == 1 && peca == 'o' && (destinoLinha == origemLinha - 1) && (((destinoColuna == origemColuna - 1) || destinoColuna == origemColuna + 1)) && pecaDestino == '.')
	{
		retorno = move1Peca(retorno);
	}
	else if (jogador == 1 && peca == 'o' && (destinoLinha == origemLinha - 2 || destinoLinha == origemLinha + 2) && pecaDestino == '.')
	{
		retorno = tomar1Peca(cstr);
	}
	else if (jogador == 1)
	{
		retorno = "erro";
	}
	if (jogador == 2 && peca == 'x' && (destinoLinha == origemLinha + 1) && (((destinoColuna == origemColuna - 1) || destinoColuna == origemColuna + 1)) && pecaDestino == '.')
	{
		retorno = move1Peca(retorno);
	}
	else if (jogador == 2 && peca == 'x' && (destinoLinha == origemLinha - 2 || destinoLinha == origemLinha + 2) && pecaDestino == '.')
	{
		retorno = tomar1Peca(cstr);
	}
	else if (jogador == 2)
	{
		retorno = "erro";
	}
	return retorno;
}

//VERIFICA PROMOÇÃO
string regra3(string cstr) {
	retorno = cstr;
	if (jogador == 1 && destinoLinha == 1)
	{
		tabReferencia[destinoLinha][destinoColuna] = 'O';
		retorno = "promovido";
	}
	else if (jogador == 2 && destinoLinha == 8)
	{
		tabReferencia[destinoLinha][destinoColuna] = 'X';
		retorno = "promovido";
	}
	return retorno;
}

//VERIFICA TOMAR PEÇA 1 MOVIMENTO
string regra4(string cstr) {
	retorno = cstr;
	if (jogador == 1)
	{
		for (size_t i = 0; i < linha; ++i)
		{
			for (size_t j = 0; j < coluna; ++j) {
				if (tabReferencia[i][j] == 'o' && ((((tabReferencia[i - 1][j + 1] == 'x' || tabReferencia[i - 1][j - 1] == 'x') || (tabReferencia[i - 1][j + 1] == 'X' || tabReferencia[i - 1][j - 1] == 'X')) && (tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.')) || (((tabReferencia[i + 1][j + 1] == 'x' && tabReferencia[i + 1][j - 1] == 'x') || (tabReferencia[i + 1][j + 1] == 'X' && tabReferencia[i + 1][j - 1] == 'X')) && (tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.'))))
				{
					proximo = false;
					retorno = "tomar1";
				}
			}
		}
	}
	if (jogador == 2)
	{
		for (size_t i = 0; i < linha; ++i)
		{
			for (size_t j = 0; j < coluna; ++j) {
				if (tabReferencia[i][j] == 'x' && ((((tabReferencia[i + 1][j + 1] == 'o' || tabReferencia[i + 1][j - 1] == 'o') || (tabReferencia[i + 1][j + 1] == 'O' || tabReferencia[i + 1][j - 1] == 'O')) && (tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.')) || (((tabReferencia[i - 1][j + 1] == 'O' || tabReferencia[i - 1][j - 1] == 'O')) && (tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.'))))
				{
					proximo = false;
					retorno = "tomar2";
				}
			}
		}
	}
	return retorno;
}

//VERIFICA TOMAR PEÇA DAMA
string regra5(string cstr) {
	retorno = cstr;
	peca = tabReferencia[origemLinha][origemColuna];
	pecaDestino = tabReferencia[destinoLinha][destinoColuna];
	if (jogador == 1 && peca == 'O')
	{
		for (size_t i = 0; i < linha; ++i)
		{
			for (size_t j = 0; j < coluna; ++j)
			{
				if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i + 1][j - 1] == 'x' || tabReferencia[i + 1][j - 1] == 'X' || tabReferencia[i + 1][j + 1] == 'x' || tabReferencia[i + 1][j + 1] == 'X'))
					&& ((tabReferencia[i + 2][j + 2] == '.' && j + 2 >= 1 && j + 2 <= 8) || (tabReferencia[i + 2][j - 2] == '.' && j - 2 >= 1 && j - 2 <= 8)))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i + 2][j - 2] == 'x' || tabReferencia[i + 2][j - 2] == 'X' || tabReferencia[i + 2][j - 2] == 'x' || tabReferencia[i + 2][j + 2] == 'X'))
					&& ((tabReferencia[i + 3][j + 3] == '.' && j + 3 >= 1 && j + 3 <= 8) || (tabReferencia[i + 3][j - 3] == '.' && j - 3 >= 1 && j - 3 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i + 3][j - 3] == 'x' || tabReferencia[i + 3][j - 3] == 'X' || tabReferencia[i + 3][j - 3] == 'x' || tabReferencia[i + 3][j + 3] == 'X'))
					&& ((tabReferencia[i + 4][j + 4] == '.' && j + 4 >= 1 && j + 4 <= 8) || (tabReferencia[i + 4][j - 4] == '.' && j - 4 >= 1 && j - 4 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i + 4][j - 4] == 'x' || tabReferencia[i + 4][j - 4] == 'X' || tabReferencia[i + 4][j - 4] == 'x' || tabReferencia[i + 4][j + 4] == 'X'))
					&& ((tabReferencia[i + 5][j + 5] == '.' && j + 5 >= 1 && j + 5 <= 8) || (tabReferencia[i + 5][j - 5] == '.'&& j - 5 >= 1 && j - 5 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.'))
					&& ((tabReferencia[i + 3][j + 3] == '.' || tabReferencia[i + 3][j - 3] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i + 5][j - 5] == 'x' || tabReferencia[i + 5][j - 5] == 'X' || tabReferencia[i + 5][j - 5] == 'x' || tabReferencia[i + 5][j + 5] == 'X'))
					&& ((tabReferencia[i + 6][j + 6] == '.' && j + 6 >= 1 && j + 6 <= 8) || (tabReferencia[i + 6][j - 6] == '.' && j - 6 >= 1 && j - 6 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.'))
					&& ((tabReferencia[i + 3][j + 3] == '.' || tabReferencia[i + 3][j - 3] == '.'))
					&& ((tabReferencia[i + 4][j + 4] == '.' || tabReferencia[i + 4][j - 4] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i + 6][j - 6] == 'x' || tabReferencia[i + 6][j - 6] == 'X' || tabReferencia[i + 6][j - 6] == 'x' || tabReferencia[i + 6][j + 6] == 'X'))
					&& ((tabReferencia[i + 7][j + 7] == '.' && j + 7 >= 1 && j + 7 <= 8) || (tabReferencia[i + 7][j - 7] == '.' && j - 7 >= 1 && j - 7 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.'))
					&& ((tabReferencia[i + 3][j + 3] == '.' || tabReferencia[i + 3][j - 3] == '.'))
					&& ((tabReferencia[i + 4][j + 4] == '.' || tabReferencia[i + 4][j - 4] == '.'))
					&& ((tabReferencia[i + 5][j + 5] == '.' || tabReferencia[i + 5][j - 5] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				//INVERSO
				if (tabReferencia[i][j] == 'O' && ((tabReferencia[i - 1][j - 1] == 'x' || tabReferencia[i - 1][j - 1] == 'X' || tabReferencia[i - 1][j + 1] == 'x' || tabReferencia[i - 1][j + 1] == 'X')) && ((tabReferencia[i - 2][j + 2] == '.' && j + 2 >= 1 && j + 2 <= 8) || (tabReferencia[i - 2][j - 2] == '.' && j - 2 >= 1 && j - 2 <= 8)))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i - 2][j - 2] == 'x' || tabReferencia[i - 2][j - 2] == 'X' || tabReferencia[i - 2][j - 2] == 'x' || tabReferencia[i - 2][j + 2] == 'X'))
					&& ((tabReferencia[i - 3][j + 3] == '.' && j + 3 >= 1 && j + 3 <= 8) || (tabReferencia[i - 3][j - 3] == '.' && j - 3 >= 1 && j - 3 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i - 3][j - 3] == 'x' || tabReferencia[i - 3][j - 3] == 'X' || tabReferencia[i - 3][j - 3] == 'x' || tabReferencia[i - 3][j + 3] == 'X'))
					&& ((tabReferencia[i - 4][j + 4] == '.' && j + 4 >= 1 && j + 4 <= 8) || (tabReferencia[i - 4][j - 4] == '.' && j - 4 >= 1 && j - 4 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i - 4][j - 4] == 'x' || tabReferencia[i - 4][j - 4] == 'X' || tabReferencia[i - 4][j - 4] == 'x' || tabReferencia[i - 4][j + 4] == 'X'))
					&& ((tabReferencia[i - 5][j + 5] == '.' && j + 5 >= 1 && j + 5 <= 8) || (tabReferencia[i - 5][j - 5] == '.' && j - 5 >= 1 && j - 5 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.'))
					&& ((tabReferencia[i - 3][j + 3] == '.' || tabReferencia[i - 3][j - 3] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i - 5][j - 5] == 'x' || tabReferencia[i - 5][j - 5] == 'X' || tabReferencia[i - 5][j - 5] == 'x' || tabReferencia[i - 5][j + 5] == 'X'))
					&& ((tabReferencia[i - 6][j + 6] == '.' && j + 6 >= 1 && j + 6 <= 8) || (tabReferencia[i - 6][j - 6] == '.' && j - 6 >= 1 && j - 6 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.'))
					&& ((tabReferencia[i - 3][j + 3] == '.' || tabReferencia[i - 3][j - 3] == '.'))
					&& ((tabReferencia[i - 4][j + 4] == '.' || tabReferencia[i - 4][j - 4] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
				else if (tabReferencia[i][j] == 'O'
					&& ((tabReferencia[i - 6][j - 6] == 'x' || tabReferencia[i - 6][j - 6] == 'X' || tabReferencia[i - 6][j - 6] == 'x' || tabReferencia[i - 6][j + 6] == 'X'))
					&& ((tabReferencia[i - 7][j + 7] == '.' && j + 7 >= 1 && j + 7 <= 8) || (tabReferencia[i - 7][j - 7] == '.' && j - 7 >= 1 && j - 7 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.'))
					&& ((tabReferencia[i - 3][j + 3] == '.' || tabReferencia[i - 3][j - 3] == '.'))
					&& ((tabReferencia[i - 4][j + 4] == '.' || tabReferencia[i - 4][j - 4] == '.'))
					&& ((tabReferencia[i - 5][j + 5] == '.' || tabReferencia[i - 5][j - 5] == '.')))
				{
					proximo = false;
					retorno = "tomarD1";
				}
			}
		}
	}

	if (jogador == 2 && peca == 'X')
	{
		for (size_t i = 0; i < linha; ++i)
		{
			for (size_t j = 0; j < coluna; ++j)
			{
				if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i + 1][j - 1] == 'o' || tabReferencia[i + 1][j - 1] == 'O' || tabReferencia[i + 1][j + 1] == 'o' || tabReferencia[i + 1][j + 1] == 'O'))
					&& ((tabReferencia[i + 2][j + 2] == '.' && j + 2 >= 1 && j + 2 <= 8) || (tabReferencia[i + 2][j - 2] == '.' && j - 2 >= 1 && j - 2 <= 8)))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i + 2][j - 2] == 'o' || tabReferencia[i + 2][j - 2] == 'O' || tabReferencia[i + 2][j - 2] == 'o' || tabReferencia[i + 2][j + 2] == 'O'))
					&& ((tabReferencia[i + 3][j + 3] == '.' && j + 3 >= 1 && j + 3 <= 8) || (tabReferencia[i + 3][j - 3] == '.' && j - 3 >= 1 && j - 3 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i + 3][j - 3] == 'o' || tabReferencia[i + 3][j - 3] == 'O' || tabReferencia[i + 3][j - 3] == 'o' || tabReferencia[i + 3][j + 3] == 'O'))
					&& ((tabReferencia[i + 4][j + 4] == '.' && j + 4 >= 1 && j + 4 <= 8) || (tabReferencia[i + 4][j - 4] == '.' && j - 4 >= 1 && j - 4 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i + 4][j - 4] == 'o' || tabReferencia[i + 4][j - 4] == 'O' || tabReferencia[i + 4][j - 4] == 'o' || tabReferencia[i + 4][j + 4] == 'O'))
					&& ((tabReferencia[i + 5][j + 5] == '.' && j + 5 >= 1 && j + 5 <= 8) || (tabReferencia[i + 5][j - 5] == '.'&& j - 5 >= 1 && j - 5 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.'))
					&& ((tabReferencia[i + 3][j + 3] == '.' || tabReferencia[i + 3][j - 3] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i + 5][j - 5] == 'o' || tabReferencia[i + 5][j - 5] == 'O' || tabReferencia[i + 5][j - 5] == 'o' || tabReferencia[i + 5][j + 5] == 'O'))
					&& ((tabReferencia[i + 6][j + 6] == '.' && j + 6 >= 1 && j + 6 <= 8) || (tabReferencia[i + 6][j - 6] == '.' && j - 6 >= 1 && j - 6 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.'))
					&& ((tabReferencia[i + 3][j + 3] == '.' || tabReferencia[i + 3][j - 3] == '.'))
					&& ((tabReferencia[i + 4][j + 4] == '.' || tabReferencia[i + 4][j - 4] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i + 6][j - 6] == 'o' || tabReferencia[i + 6][j - 6] == 'O' || tabReferencia[i + 6][j - 6] == 'o' || tabReferencia[i + 6][j + 6] == 'O'))
					&& ((tabReferencia[i + 7][j + 7] == '.' && j + 7 >= 1 && j + 7 <= 8) || (tabReferencia[i + 7][j - 7] == '.' && j - 7 >= 1 && j - 7 <= 8))
					&& ((tabReferencia[i + 1][j + 1] == '.' || tabReferencia[i + 1][j - 1] == '.'))
					&& ((tabReferencia[i + 2][j + 2] == '.' || tabReferencia[i + 2][j - 2] == '.'))
					&& ((tabReferencia[i + 3][j + 3] == '.' || tabReferencia[i + 3][j - 3] == '.'))
					&& ((tabReferencia[i + 4][j + 4] == '.' || tabReferencia[i + 4][j - 4] == '.'))
					&& ((tabReferencia[i + 5][j + 5] == '.' || tabReferencia[i + 5][j - 5] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				//INVERSO
				if (tabReferencia[i][j] == 'X' 
					&& ((tabReferencia[i - 1][j - 1] == 'o' || tabReferencia[i - 1][j - 1] == 'O' || tabReferencia[i - 1][j + 1] == 'o' || tabReferencia[i - 1][j + 1] == 'O')) 
					&& ((tabReferencia[i - 2][j + 2] == '.' && j + 2 >= 1 && j + 2 <= 8) || (tabReferencia[i - 2][j - 2] == '.' && j - 2 >= 1 && j - 2 <= 8)))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i - 2][j - 2] == 'o' || tabReferencia[i - 2][j - 2] == 'O' || tabReferencia[i - 2][j - 2] == 'o' || tabReferencia[i - 2][j + 2] == 'O'))
					&& ((tabReferencia[i - 3][j + 3] == '.' && j + 3 >= 1 && j + 3 <= 8) || (tabReferencia[i - 3][j - 3] == '.' && j - 3 >= 1 && j - 3 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i - 3][j - 3] == 'o' || tabReferencia[i - 3][j - 3] == 'O' || tabReferencia[i - 3][j - 3] == 'o' || tabReferencia[i - 3][j + 3] == 'O'))
					&& ((tabReferencia[i - 4][j + 4] == '.' && j + 4 >= 1 && j + 4 <= 8) || (tabReferencia[i - 4][j - 4] == '.' && j - 4 >= 1 && j - 4 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i - 4][j - 4] == 'o' || tabReferencia[i - 4][j - 4] == 'O' || tabReferencia[i - 4][j - 4] == 'o' || tabReferencia[i - 4][j + 4] == 'O'))
					&& ((tabReferencia[i - 5][j + 5] == '.' && j + 5 >= 1 && j + 5 <= 8) || (tabReferencia[i - 5][j - 5] == '.' && j - 5 >= 1 && j - 5 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.'))
					&& ((tabReferencia[i - 3][j + 3] == '.' || tabReferencia[i - 3][j - 3] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i - 5][j - 5] == 'o' || tabReferencia[i - 5][j - 5] == 'O' || tabReferencia[i - 5][j - 5] == 'o' || tabReferencia[i - 5][j + 5] == 'O'))
					&& ((tabReferencia[i - 6][j + 6] == '.' && j + 6 >= 1 && j + 6 <= 8) || (tabReferencia[i - 6][j - 6] == '.' && j - 6 >= 1 && j - 6 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.'))
					&& ((tabReferencia[i - 3][j + 3] == '.' || tabReferencia[i - 3][j - 3] == '.'))
					&& ((tabReferencia[i - 4][j + 4] == '.' || tabReferencia[i - 4][j - 4] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
				else if (tabReferencia[i][j] == 'X'
					&& ((tabReferencia[i - 6][j - 6] == 'o' || tabReferencia[i - 6][j - 6] == 'O' || tabReferencia[i - 6][j - 6] == 'o' || tabReferencia[i - 6][j + 6] == 'O'))
					&& ((tabReferencia[i - 7][j + 7] == '.' && j + 7 >= 1 && j + 7 <= 8) || (tabReferencia[i - 7][j - 7] == '.' && j - 7 >= 1 && j - 7 <= 8))
					&& ((tabReferencia[i - 1][j + 1] == '.' || tabReferencia[i - 1][j - 1] == '.'))
					&& ((tabReferencia[i - 2][j + 2] == '.' || tabReferencia[i - 2][j - 2] == '.'))
					&& ((tabReferencia[i - 3][j + 3] == '.' || tabReferencia[i - 3][j - 3] == '.'))
					&& ((tabReferencia[i - 4][j + 4] == '.' || tabReferencia[i - 4][j - 4] == '.'))
					&& ((tabReferencia[i - 5][j + 5] == '.' || tabReferencia[i - 5][j - 5] == '.')))
				{
					proximo = false;
					retorno = "tomarD2";
				}
			}
		}
	}
	return retorno;
}

//MOVIMENTO VÁLIDO DAMA
string regra6(string cstr) {
	retorno = cstr;
	peca = tabReferencia[origemLinha][origemColuna];
	pecaDestino = tabReferencia[destinoLinha][destinoColuna];
	if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha - 1) && (((destinoColuna == origemColuna - 1) || destinoColuna == origemColuna + 1)) && pecaDestino == '.')
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha - 2) && (((destinoColuna == origemColuna - 2) || destinoColuna == origemColuna + 2)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha - 3) && (((destinoColuna == origemColuna - 3) || destinoColuna == origemColuna + 3)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha - 4) && (((destinoColuna == origemColuna - 4) || destinoColuna == origemColuna + 4)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha - 5) && (((destinoColuna == origemColuna - 5) || destinoColuna == origemColuna + 5)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha - 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha - 4][origemColuna + 4] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha - 6) && (((destinoColuna == origemColuna - 6) || destinoColuna == origemColuna + 6)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha - 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha - 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha - 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha - 5][origemColuna + 5] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha - 7) && (((destinoColuna == origemColuna - 7) || destinoColuna == origemColuna + 7)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha - 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha - 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha - 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha - 5][origemColuna + 5] == '.')) && ((tabReferencia[origemLinha - 6][origemColuna - 6] == '.') || (tabReferencia[origemLinha - 6][origemColuna + 6] == '.')))
	{
		retorno = moveDama(cstr);
	} //INVERSO
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha + 1) && (((destinoColuna == origemColuna - 1) || destinoColuna == origemColuna + 1)) && pecaDestino == '.')
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha + 2) && (((destinoColuna == origemColuna - 2) || destinoColuna == origemColuna + 2)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha + 3) && (((destinoColuna == origemColuna - 3) || destinoColuna == origemColuna + 3)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha + 4) && (((destinoColuna == origemColuna - 4) || destinoColuna == origemColuna + 4)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha + 5) && (((destinoColuna == origemColuna - 5) || destinoColuna == origemColuna + 5)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha + 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha + 4][origemColuna + 4] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha + 6) && (((destinoColuna == origemColuna - 6) || destinoColuna == origemColuna + 6)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha + 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha + 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha + 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha + 5][origemColuna + 5] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1 && peca == 'O' && (destinoLinha == origemLinha + 7) && (((destinoColuna == origemColuna - 7) || destinoColuna == origemColuna + 7)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha + 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha + 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha + 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha + 5][origemColuna + 5] == '.')) && ((tabReferencia[origemLinha + 6][origemColuna - 6] == '.') || (tabReferencia[origemLinha + 6][origemColuna + 6] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 1)
	{
		retorno = tomarDama(cstr);
	}

	if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha - 1) && (((destinoColuna == origemColuna - 1) || destinoColuna == origemColuna + 1)) && pecaDestino == '.')
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha - 2) && (((destinoColuna == origemColuna - 2) || destinoColuna == origemColuna + 2)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha - 3) && (((destinoColuna == origemColuna - 3) || destinoColuna == origemColuna + 3)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha - 4) && (((destinoColuna == origemColuna - 4) || destinoColuna == origemColuna + 4)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha - 5) && (((destinoColuna == origemColuna - 5) || destinoColuna == origemColuna + 5)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha - 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha - 4][origemColuna + 4] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha - 6) && (((destinoColuna == origemColuna - 6) || destinoColuna == origemColuna + 6)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha - 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha - 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha - 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha - 5][origemColuna + 5] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha - 7) && (((destinoColuna == origemColuna - 7) || destinoColuna == origemColuna + 7)) && pecaDestino == '.' && ((tabReferencia[origemLinha - 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha - 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha - 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha - 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha - 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha - 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha - 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha - 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha - 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha - 5][origemColuna + 5] == '.')) && ((tabReferencia[origemLinha - 6][origemColuna - 6] == '.') || (tabReferencia[origemLinha - 6][origemColuna + 6] == '.')))
	{
		retorno = moveDama(cstr);
	} //INVERSO
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha + 1) && (((destinoColuna == origemColuna - 1) || destinoColuna == origemColuna + 1)) && pecaDestino == '.')
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha + 2) && (((destinoColuna == origemColuna - 2) || destinoColuna == origemColuna + 2)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha + 3) && (((destinoColuna == origemColuna - 3) || destinoColuna == origemColuna + 3)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha + 4) && (((destinoColuna == origemColuna - 4) || destinoColuna == origemColuna + 4)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha + 5) && (((destinoColuna == origemColuna - 5) || destinoColuna == origemColuna + 5)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha + 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha + 4][origemColuna + 4] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha + 6) && (((destinoColuna == origemColuna - 6) || destinoColuna == origemColuna + 6)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha + 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha + 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha + 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha + 5][origemColuna + 5] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2 && peca == 'X' && (destinoLinha == origemLinha + 7) && (((destinoColuna == origemColuna - 7) || destinoColuna == origemColuna + 7)) && pecaDestino == '.' && ((tabReferencia[origemLinha + 1][origemColuna - 1] == '.') || (tabReferencia[origemLinha + 1][origemColuna + 1] == '.')) && ((tabReferencia[origemLinha + 2][origemColuna - 2] == '.') || (tabReferencia[origemLinha + 2][origemColuna + 2] == '.')) && ((tabReferencia[origemLinha + 3][origemColuna - 3] == '.') || (tabReferencia[origemLinha + 3][origemColuna + 3] == '.')) && ((tabReferencia[origemLinha + 4][origemColuna - 4] == '.') || (tabReferencia[origemLinha + 4][origemColuna + 4] == '.')) && ((tabReferencia[origemLinha + 5][origemColuna - 5] == '.') || (tabReferencia[origemLinha + 5][origemColuna + 5] == '.')) && ((tabReferencia[origemLinha + 6][origemColuna - 6] == '.') || (tabReferencia[origemLinha + 6][origemColuna + 6] == '.')))
	{
		retorno = moveDama(cstr);
	}
	else if (jogador == 2)
	{
		retorno = tomarDama(cstr);
	}
	return retorno;
}

//EFETIVA A MOVIMENTAÇÃO DE UMA PEÇA
string move1Peca(string cstr) {
	retorno = regra4(cstr);
	if (jogador == 1 && retorno != "tomar1" && jogador != jogadorAnterior)
	{
		try
		{
			if (peca == 'O')
			{
				tabReferencia[origemLinha][origemColuna] = '.';
				tabReferencia[destinoLinha][destinoColuna] = 'O';
				retorno = regra4(cstr);
				if (retorno != "tomar1" && jogador == jogadorAnterior)
				{
					proximo = false;
				}
				else if (jogador != jogadorAnterior)
				{
					retorno = " ";
					proximo = true;
				}
			}
			else
			{
				tabReferencia[origemLinha][origemColuna] = '.';
				tabReferencia[destinoLinha][destinoColuna] = 'o';
				retorno = regra3(cstr);
				retorno = regra4(cstr);
				if (retorno != "tomar1" && jogador == jogadorAnterior)
				{
					proximo = false;
				}
				else if (jogador != jogadorAnterior)
				{
					retorno = " ";
					proximo = true;
				}

			}
		}
		catch (const std::exception&)
		{
			retorno = "erro";
			return retorno;
		}
	}
	else if (jogador == 2 && retorno != "tomar2" && jogador != jogadorAnterior)
	{
		try
		{
			if (peca == 'X')
			{
				tabReferencia[origemLinha][origemColuna] = '.';
				tabReferencia[destinoLinha][destinoColuna] = 'X';
				retorno = regra4(cstr);
				if (retorno != "tomar2" && jogador == jogadorAnterior)
				{
					proximo = false;
				}
				else if (jogador != jogadorAnterior)
				{
					retorno = " ";
					proximo = true;
				}
			}
			else
			{
				tabReferencia[origemLinha][origemColuna] = '.';
				tabReferencia[destinoLinha][destinoColuna] = 'x';
				retorno = regra3(cstr);
				retorno = regra4(cstr);
				if (retorno != "tomar2" && jogador == jogadorAnterior)
				{
					proximo = false;
				}
				else if (jogador != jogadorAnterior)
				{
					retorno = " ";
					proximo = true;
				}
			}

		}
		catch (const std::exception&)
		{
			retorno = "erro";
			return retorno;
		}
	}
	return retorno;
}

//EFETIVA A MOVIMENTAÇÃO DA DAMA
string moveDama(string cstr) {
	retorno = regra5(cstr);
	if (jogador == 1 && retorno != "tomarD1" && jogador != jogadorAnterior)
	{
		try
		{
			tabReferencia[origemLinha][origemColuna] = '.';
			tabReferencia[destinoLinha][destinoColuna] = 'O';
			retorno = regra5(cstr);
			if (retorno != "tomarD1" && jogador == jogadorAnterior)
			{
				proximo = false;
			}
			else if (jogador != jogadorAnterior)
			{
				retorno = " ";
				proximo = true;
			}
			empate++;
		}
		catch (const std::exception&)
		{
			retorno = "erro";
			return retorno;
		}
	}
	else if (jogador == 2 && retorno != "tomarD2" && jogador != jogadorAnterior)
	{
		try
		{
			tabReferencia[origemLinha][origemColuna] = '.';
			tabReferencia[destinoLinha][destinoColuna] = 'X';
			retorno = regra5(cstr);
			if (retorno != "tomarD2" && jogador == jogadorAnterior)
			{
				proximo = false;
			}
			else if (jogador != jogadorAnterior)
			{
				retorno = " ";
				proximo = true;
			}
			empate++;
		}
		catch (const std::exception&)
		{
			retorno = "erro";
			return retorno;
		}
	}
	return retorno;
}

//EFETIVA TOMAR UMA PEÇA
string tomar1Peca(string cstr) {
	//retorno = regra4(cstr);
	if (jogador == 1)
	{
		try
		{
			tabReferencia[origemLinha][origemColuna] = '.';
			tabReferencia[destinoLinha][destinoColuna] = 'o';
			if (destinoLinha == origemLinha - 2 && destinoColuna == origemColuna - 2)
			{
				tabReferencia[origemLinha - 1][origemColuna - 1] = '.';
			}
			else if (destinoLinha == origemLinha - 2 && destinoColuna == origemColuna + 2)
			{
				tabReferencia[origemLinha - 1][origemColuna + 1] = '.';
			}
			else if (destinoLinha == origemLinha + 2 && destinoColuna == origemColuna - 2)
			{
				tabReferencia[origemLinha + 1][origemColuna - 1] = '.';
			}
			else if (destinoLinha == origemLinha + 2 && destinoColuna == origemColuna + 2)
			{
				tabReferencia[origemLinha + 1][origemColuna + 1] = '.';
			}
			retorno = regra3(cstr);
			retorno = regra4(cstr);
			if (retorno != "tomar1" && jogador == jogadorAnterior)
			{
				proximo = false;
			}
			else if (jogador != jogadorAnterior)
			{
				retorno = " ";
				proximo = true;
			}
		}
		catch (const std::exception&)
		{
			retorno = "erro";
			return retorno;
		}
	}
	else if (jogador == 2)
	{
		try
		{
			tabReferencia[origemLinha][origemColuna] = '.';
			tabReferencia[destinoLinha][destinoColuna] = 'x';
			if (destinoLinha == origemLinha - 2 && destinoColuna == origemColuna - 2)
			{
				tabReferencia[origemLinha - 1][origemColuna - 1] = '.';
			}
			else if (destinoLinha == origemLinha - 2 && destinoColuna == origemColuna + 2)
			{
				tabReferencia[origemLinha - 1][origemColuna + 1] = '.';
			}
			else if (destinoLinha == origemLinha + 2 && destinoColuna == origemColuna - 2)
			{
				tabReferencia[origemLinha + 1][origemColuna - 1] = '.';
			}
			else if (destinoLinha == origemLinha + 2 && destinoColuna == origemColuna + 2)
			{
				tabReferencia[origemLinha + 1][origemColuna + 1] = '.';
			}
			retorno = regra3(cstr);
			retorno = regra4(cstr);
			if (retorno != "tomar2" && jogador == jogadorAnterior)
			{
				proximo = false;
			}
			else if (jogador != jogadorAnterior)
			{
				retorno = " ";
				proximo = true;
			}
		}
		catch (const std::exception&)
		{
			retorno = "erro";
			return retorno;
		}
	}
	return retorno;
}

//EFETIVA TOMAR DA DAMA
string tomarDama(string cstr) {
	retorno = regra5(cstr);
	//?????????????????????
	return retorno;
}