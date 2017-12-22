#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int peoesJogador1[4] = {}; //peoes eh referente a sua posicao no tabuleiro
int peoesJogador2[4] = {};
int percursoPeoes1[4] = {}; //percursos funcionarao como um contador, sendo incrementado pelo valor do dado
int percursoPeoes2[4] = {};

//int peoesRetaFinal[4] = {}; // unused

int peoesNoInicio1 = 4, peoesNoInicio2 = 4; //peoes iniciais cada jogador comeca com 4 vai decrementando a medida que sao inseridos no tabuleiro

int jogador1Inicio = 1; // 1a casa do amarelo = 1
int jogador2Inicio = 14;// 1a casa do azul = 14
// unused: 1a casa do vermelho = 27
// unused: 1a casa do verde = 40


int tabuleiro [53]; //O tabuleiro tem 52 casas, usando 53 para melhorar a indexacao
int tabEspecial1[8]; // Caminho especial tem 7 casas, usando 8 para indexar do 1
int tabEspecial2[8];

string JOGADOR1 ("Jogador 1");
string JOGADOR2 ("Jogador 2");

bool vitoriaJogador1 = false;
bool vitoriaJogador2 = false;
bool jogador1CompletouVolta = false;
bool jogador2CompletouVolta = false;


int jogarDado() {
    int dice=0;
    srand( (unsigned)time(NULL) ); // essa funcao utiliza um "time" para aleatoriedade, sem ela, a funcao dah sempre um mesmo valor aleatorio
    dice = 1+rand() %6;
    return dice;
}

bool verificaVoltaJogador(string jogador, int peao, int origem, int dado, int peoesJogador[], int percursoDoPeao) {
    if (percursoDoPeao + dado >= 52) {
        int excedente = (percursoDoPeao + dado) - 52 + 1;  // +1 pq a indexacao vai comecar do 1
        tabuleiro[origem] = 0;

		if (jogador == JOGADOR1 && !jogador1CompletouVolta) {
			tabEspecial1[excedente] = 1;
			peoesJogador[peao] = excedente;
			printf("Boa! Voce tem um peao no tabuleiro especial, o peao esta na casa E%d. Voce esta prestes a vencer!\n", excedente);
			jogador1CompletouVolta = true;
			return true;
		}
		else if (jogador == JOGADOR2 && !jogador2CompletouVolta) {
			tabEspecial2[excedente] = 2;
			peoesJogador[peao] = excedente;
			printf("Ma noticia! O adversario tem um peao no tabuleiro especial, o peao esta na casa E%d. Ele esta prestes a vencer!\n", excedente);
			jogador2CompletouVolta = true;
			return true;
		}
    }
    return false;
}

bool verificaVitoriaJogador(string jogador, int numJogador, int peao, int origem, int destino, int peoesJogador[]) {
    if (jogador == JOGADOR1 && jogador1CompletouVolta) {
    	if (destino == 7) {
    		vitoriaJogador1 = true;
    		return true;
		}
		else if (destino < 7) {
			tabEspecial1[origem] = 0; // limpa a posicao anterior
			tabEspecial1[destino] = numJogador;
			peoesJogador[peao] = destino;
	    	printf("Voce moveu-se em direcao a vitoria, mas ainda esta na casa E%d\n", destino);
	    	return false;
		}
		else printf("Voce moveu-se em direcao a vitoria, mas ultrapassou a meta. Movimento cancelado\n");
	}
    else if (jogador == JOGADOR2 && jogador2CompletouVolta) {
    	if (destino == 7) {
    		vitoriaJogador2 = true;
    		return true;
		}
		else if (destino < 7) {
			tabEspecial2[origem] = 0; // limpa a posicao anterior
			tabEspecial2[destino] = numJogador;
			peoesJogador[peao] = destino;
	    	printf("O adversario moveu-se em direcao a vitoria, mas ainda esta na casa E%d\n", destino);
	    	return false;
		}
		else printf("O adversario moveu-se em direcao a vitoria, mas ultrapassou a meta. Movimento cancelado\n");
	}
	return false;
}

void imprimeTabuleiro() {
    printf("\nInformacoes sobre o tabuleiro: \n");
    for (int i = 1; i <= 53; i++) {
        printf("%d ", tabuleiro[i]);
    }
    printf("\n");
}


void jogadaInicial(string jogador, int numJogador, int peao, int dado, int peoesJogador[], int percursoPeoesJogador[],
			int jogadorInicio, int peoesNoInicio) {

	int origem = peoesJogador[peao];
	int destino = origem + dado;

	if (dado != 1 && dado != 6)
        printf("O dado do jogador %d deu %d, ele nao vai poder sair com o peao, deve passar a vez\n\n", numJogador, dado);

    else if (dado == 1) {
        tabuleiro[jogadorInicio] = numJogador;
        peoesJogador[peao] = jogadorInicio;
        percursoPeoesJogador[peao] = 1;
        peoesNoInicio --;
        printf("O dado do jogador %d deu 1, ele vai poder sair com o peao, o peao esta na casa %d\n\n", numJogador, dado);
    	}

	else if (dado == 6) {
        tabuleiro[jogadorInicio] = numJogador;
        peoesJogador[peao] = jogadorInicio;
        percursoPeoesJogador[peao] = 1;
        peoesNoInicio --;
        printf("O dado do jogador %d deu 6, ele vai poder sair com o peao, o peao esta na casa %d e ele ganha uma jogada extra\n", numJogador, peoesJogador1[peao]);
        printf("Jogada extra... \n\n");
    }
}

bool confirmacao() {
	int confirmacao;
	printf("Escreva: 1 (sim) ou 0 (nao)\n");
	scanf("%d", &confirmacao);

	while (confirmacao != 0 && confirmacao != 1) {
		printf("Opcao invalida\nEscreva: 1 (sim) ou 0 (nao)\n");
		scanf("%d", &confirmacao);
		}

	if (confirmacao == 1)	return true;
	else return false;
}

void verificaCasa(string jogador, int numJogador, int peao, int origem, int destino, int dado, int peoesJogador[], int percursoPeoesJogador[]) {

	if (tabuleiro[destino] != 0) { // detecta casa ocupada
		if (tabuleiro[destino] == numJogador) { // presença aliada
			printf("mas a casa %d esta ocupada por uma peça aliada. Deseja formar uma torre ou cancelar o movimento?\n", destino);
			if (!confirmacao()) {
				tabuleiro[origem] = 0; // limpa a posicao anterior
	    		tabuleiro[destino] = numJogador*11; // preenche a posicao atual no tabuleiro (com uma torre)
	    		percursoPeoesJogador[peao] = percursoPeoesJogador[peao] + dado;
	    		peoesJogador[peao] = destino;
	    		printf("Torre formada na casa %d\n", destino);
			}
		}
		else if (tabuleiro[destino] != numJogador && tabuleiro[destino] < 10) { // presença adversaria
	    	printf("mas a casa %d esta ocupada por uma peca adversaria, ela sera destruida\n", destino);
	    	tabuleiro[origem] = 0; // limpa a posicao anterior
	    	tabuleiro[destino] = numJogador; // substitui a peca adversaria
	    	percursoPeoesJogador[peao] = percursoPeoesJogador[peao] + dado;
	    	peoesJogador[peao] = destino;
		}
		else { // cancelar movimento (torre aliada ou adversaria)
			printf("mas a casa %d esta ocupada por uma torre, sua peca esta bloqueada (movimento cancelado)\n", destino);
		}

	}
	else {
		tabuleiro[origem] = 0; // limpa a posicao anterior
		tabuleiro[destino] = numJogador;
	    percursoPeoesJogador[peao] = percursoPeoesJogador[peao] + dado;
	    peoesJogador[peao] = destino;
	}
}


void jogadaNormal(string jogador, int numJogador, int peao, int dado, int peoesJogador[], int percursoPeoes[]) {

	int origem = peoesJogador[peao];
	int destino = origem + dado;

	if (verificaVitoriaJogador(jogador, numJogador, peao, origem, destino, peoesJogador)) return;
	else if (verificaVoltaJogador(jogador, peao, origem, dado, peoesJogador, percursoPeoes[peao])) return;
    else if (jogador == JOGADOR1 && !jogador1CompletouVolta)
        if (destino >= 52) {
            int excedente = destino - 52 + 1;  // +1 pq a indexacao vai comecar do 1
            destino = excedente;
            }
    else if (jogador == JOGADOR2 && !jogador2CompletouVolta)
        if (destino >= 52) {
            int excedente = destino - 52 + 1;  // +1 pq a indexacao vai comecar do 1
            destino = excedente;
            }

	if (dado != 6) {
	    printf("O dado do jogador %d deu %d, o peao esta na casa %d\n", numJogador, dado, destino);
	    verificaCasa(jogador, numJogador, peao, origem, destino, dado, peoesJogador, percursoPeoes); // verifica a casa de destino
	    printf("\n");
	}
    else {
		printf("O dado do jogador %d deu 6, o peao esta na casa %d e ele ganha uma jogada extra\n", numJogador, destino);
	    verificaCasa(jogador, numJogador, peao, origem, destino, dado, peoesJogador, percursoPeoes); // verifica a casa de destino
        if (peoesJogador[peao] != origem) printf("Jogada extra... \n\n");
	}
}


int lerPeaoJogador() {
			int peao;
			printf("Qual peao voce deseja mover?\nEscreva: 1, 2, 3 ou 4\n");
			scanf("%d", &peao);

			while (peao != 1 && peao != 2 && peao != 3 && peao != 4) {
				printf("Opcao invalida\nEscreva: 1, 2, 3 ou 4\n");
				scanf("%d", &peao);
			}
			return peao--;
}

void jogador1Joga() {
    if (peoesNoInicio1 == 4)   //primeira jogada do jogador1 (tabuleiro vazio)
        printf("Voce precisa tirar 1 ou 6 no dado para conseguir sair com um peao, boa sorte!\n");

    int dado = jogarDado();
    printf("O seu dado foi %d\n", dado);

    int peao = lerPeaoJogador();

    if (peoesJogador1[peao] == 0)   //primeira jogada do peao
    	jogadaInicial(JOGADOR1, 1, peao, dado, peoesJogador1, percursoPeoes1, jogador1Inicio, peoesNoInicio1);
	else jogadaNormal(JOGADOR1, 1, peao, dado, peoesJogador1, percursoPeoes1);

	if (dado == 6 && !vitoriaJogador1) jogador1Joga();
    }


int peaoP2 = 0;
void jogador2Joga() {
    if (peoesNoInicio2 == 4)   //primeira jogada do jogador1 (tabuleiro vazio)
        printf("Agora eh a vez do seu adversario\n");

    int peao = peaoP2;
    int dado = jogarDado();

    if (peoesJogador2[peao] == 0)   //primeira jogada do peao
    	jogadaInicial(JOGADOR2, 2, peao, dado, peoesJogador2, percursoPeoes2, jogador2Inicio, peoesNoInicio2);
	else jogadaNormal(JOGADOR2, 2, peao, dado, peoesJogador2, percursoPeoes2);

	//if (dado == 6 && !vitoriaJogador2) jogador2Joga();
	//else
	peaoP2++;

	if(peaoP2 == 5) peaoP2 = 1;
    }

int main() {

// peoes serao representados no tabuleiro pelo numero do jogador (onde 1 eh humano e 2 eh o computador)
// dois numeros iguais indica uma torre em uma casa

		bool vencedor = false;

		while (!vencedor) {
        	jogador1Joga();
        	if (!vitoriaJogador1) jogador2Joga();
        	imprimeTabuleiro();
        	if (vitoriaJogador1 | vitoriaJogador2) vencedor = true;
    	}

		if (vitoriaJogador1) printf("Voce ganhou, parabéns! :)\n");
		else printf("Sinto muito, voce perdeu :(\n");

        return 0;
    }
