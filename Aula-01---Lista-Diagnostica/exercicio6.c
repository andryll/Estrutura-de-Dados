/*
*@file exercicio6.c
*@author Andre Luis de Oliveira
*@date 22/06/2021
*@brief Lista diagn�stica de programa��o
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

//Definindo estrutura da carta
typedef struct{
  char valor;
  char naipe;
  bool foiJogada;
}Carta;

//Cabe�alho das fun��es
void criaBaralho(Carta baralho[4][13]);
void mostrarBaralho(Carta baralho[4][13]);
void mostraTopo(Carta baralho[4][13]);
void mostraFundo(Carta baralho[4][13]);
void cartasNaoJogadas(Carta baralho[4][13]);
void comprarCartasAleatorias(Carta baralho[4][13]);
void embaralharBaralho(Carta baralho[4][13]);
void comprarCartasTopo(Carta baralho[4][13]);

int main(){
  setlocale(LC_ALL,"");//Mudando a localiza��o
  //Declarando vari�veis
  Carta baralho[4][13];
  int opcao = -1;

  //Criando baralho inicial
  criaBaralho(baralho);
  embaralharBaralho(baralho);
  printf("Seu baralho foi criado com sucesso!\n");

  //Mostrando menu
  printf("----------------------------------------------------\n");
  printf("1 - Reiniciar baralho\n");
  printf("2 - Mostrar baralho\n");
  printf("3 - Embaralhar cartas\n");
  printf("4 - Comprar cartas do topo\n");
  printf("5 - Comprar cartas aleat�rias\n");
  printf("6 - Ver a quantidade de cartas n�o jogadas\n");
  printf("7 - Ver o topo do baralho\n");
  printf("8 - Ver o fundo do baralho\n");
  printf("9 - Sair do programa\n");
  printf("---------------------------------------------------\n");

  //Recebendo op��o do menu e verificando se � valida
  do{
    printf("Digite a op��o desejada: ");
    do {
      scanf("%d",&opcao);
      if(opcao < 1 || opcao >9)
        printf("Op��o inv�lida! Por favor digite novamente: ");
    } while(opcao < 1 || opcao >9);

    //Switch com as op��es
    switch (opcao) {
      case 1:
        criaBaralho(baralho);
        embaralharBaralho(baralho);
        printf("\nBaralho reiniciado com sucesso!\n\n");
      break;

      case 2:
        printf("\nBaralho:\n");
        mostrarBaralho(baralho);
        printf("\n");

      break;

      case 3:
        embaralharBaralho(baralho);
        printf("\nBaralho embaralhado com sucesso!\n\n");
      break;

      case 4:
        comprarCartasTopo(baralho);
      break;

      case 5:
        comprarCartasAleatorias(baralho);
      break;

      case 6:
        cartasNaoJogadas(baralho);
      break;

      case 7:
        mostraTopo(baralho);
      break;

      case 8:
        mostraFundo(baralho);
      break;

      case 9:
        printf("\nFinalizando programa!\n\n");
      break;
    }//switch
}while(opcao != 9);
  return 0;
}//main


void criaBaralho(Carta baralho[4][13]){
  //Criando vari�veis com os naipes e os valores
  char naipes[4] = {'E', 'C', 'P', 'O'};
  char valor[13] = {'A','2','3','4','5','6','7','8','9','D','Q','J','K'};

//Atribuindo os naipes e os valores �s cartas do baralho
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++) {
      baralho[i][j].naipe = naipes[i];
      baralho[i][j].valor = valor[j];
      baralho[i][j].foiJogada = false;
    }//for interno
  }//for externo
}//Fun��o para criar baralho

void mostrarBaralho(Carta baralho[4][13]){
  //Percorre todo o baralho para mostrar todas as cartas
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++) {
      printf("%c%c  ",baralho[i][j].valor, baralho[i][j].naipe);
    }//for interno
    printf("\n");
  }//for externo
}//Fun��o para mostrar o baralho criado

void mostraTopo(Carta baralho[4][13]){
  //Mostra a primeira carta n�o jogada do baralho
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++) {
      if(baralho[i][j].foiJogada == false){
        printf("\nA carta do topo � %c%c \n\n",baralho[i][j].valor, baralho[i][j].naipe);
        return;
      }//if
    }//for interno
  }//for externo
}//Fun��o para mostrar a carta do topo

void mostraFundo(Carta baralho[4][13]){
  //Mostra a �ltima carta n�o jogada do baralho
  for(int i = 3; i >= 0; i--){
    for (int j = 12; j >= 0; j--) {
      if(baralho[i][j].foiJogada == false){
        printf("\nA carta do fundo � %c%c \n\n",baralho[i][j].valor, baralho[i][j].naipe);
        return;
      }//if
    }//for interno
  }//for externo
}//Fun��o para mostrar a carta do fundo

void cartasNaoJogadas(Carta baralho[4][13]){
  //Mostra a quantidade de cartas n�o jogadas do baralho
  int contador = 0;
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++) {
      if(baralho[i][j].foiJogada == false){
        contador++;
      }//if
    }//for interno
  }//for externo
  printf("\nH� %d cartas dispon�veis para jogo.\n\n",contador);
}//Fun��o para contar as cartas n�o jogadas

void comprarCartasAleatorias(Carta baralho[4][13]){
  //Recebe um numero desejado e compra essa quantia de cartas aleat�rias
  //n�o jogadas
  int n;
  int l, c;
  int contador = 0;
  printf("\nQuantas cartas aleat�rias o jogador deseja comprar? \n");
  scanf("%d",&n);
  setbuf(stdin,NULL);

  time_t t;
  srand((unsigned) time(&t));

  printf("Cartas compradas: ");

  while (contador != n){
    l = rand() % 4;
    c = rand() % 13;

    if(baralho[l][c].foiJogada == false){
      baralho[l][c].foiJogada = true;
      printf("%c%c ",baralho[l][c].valor, baralho[l][c].naipe);
      contador++;
    }//if
  }//while
  printf("\n\n");
}//Fun��o para comprar cartas aleatorias


void embaralharBaralho(Carta baralho[4][13]){
  //Troca as posi��es de todas as cartas com o uso de uma carta auxiliar
  Carta temp;
  int l, c;

  time_t t;
  srand((unsigned) time(&t));

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      l = rand() % 4;
      c = rand() % 13;

      temp.naipe = baralho[i][j].naipe;
      temp.valor = baralho[i][j].valor;
      temp.foiJogada = baralho[i][j].foiJogada;
      
      baralho[i][j].naipe = baralho[l][c].naipe;
      baralho[i][j].valor = baralho[l][c].valor;
      baralho[i][j].foiJogada = baralho[l][c].foiJogada;

      baralho[l][c].naipe = temp.naipe;
      baralho[l][c].valor = temp.valor;
      baralho[l][c].foiJogada = temp.foiJogada;
    }//for interno
  }//for externo
}//Fun��o para embaralhar

void comprarCartasTopo(Carta baralho[4][13]){
  //Compra uma quantidade n de cartas do topo n�o jogadas
  int n;
  int contador = 0;

  printf("\nQuantas cartas do topo o jogador deseja comprar? \n");
  scanf("%d",&n);
  setbuf(stdin,NULL);

  printf("Cartas compradas: \n");

  for(int i = 0; i < 4; i++){
    if(contador == n) break;
    for (int j = 0; j < 13; j++) {
      if(contador == n) break;
      if(baralho[i][j].foiJogada == false){
        baralho[i][j].foiJogada = true;
        printf("%c%c ",baralho[i][j].valor, baralho[i][j].naipe);
        contador++;
      }//if
    }//for interno
  }//for externo
printf("\n\n");
}//Fun��o para comprar cartas do topo do baralho
