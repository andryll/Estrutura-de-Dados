/*
*@file exercicio5.c
*@author Andre Luis de Oliveira
*@date 21/06/2021
*@brief Lista diagn�stica de programa��o
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct{
  char nome[5][25];
  char estilo[5][20];
  int integrantes[5];
  int ranking[5];
}Bandas; //Struct das Bandas

//Cabe�alho das fun��es
void PreencherBandas(Bandas* banda);
void ExibirBandas(Bandas* banda);
void BuscarBanda(Bandas* banda);

int main(){
  setlocale(LC_ALL,"");//Mudando a localiza��o
  //Declarando vari�veis
  Bandas banda;

  //Chamando as Fun��es
  PreencherBandas(&banda);
  printf("\n\n");
  ExibirBandas(&banda);
  printf("\n\n");
  BuscarBanda(&banda);

  return 0;
}//main

void PreencherBandas(Bandas* banda){
  for (int i = 0; i < 5; i++) {
    //Loop para preencher todas as 5 bandas
    printf("Preencher dados da sua %d� banda favorita.\n",i+1);
    //Recebendo nome
    printf("Nome: ");
    fgets(banda->nome[i],25,stdin);
    banda->nome[i][strcspn(banda->nome[i],"\n")]='\0';
    setbuf(stdin,NULL);

    //Recebendo estilo musical
    printf("Estilo: ");
    fgets(banda->estilo[i],25,stdin);
    banda->estilo[i][strcspn(banda->estilo[i],"\n")]='\0';
    setbuf(stdin,NULL);

    //Recebendo quantidade de integrantes
    printf("N�mero de integrantes: ");
    scanf("%d",&banda->integrantes[i]);
    setbuf(stdin,NULL);

    //Declarando ranking
    banda->ranking[i] = i + 1;
    printf("\n");
  }//for
  return;
}//Fun��o para preencher as bandas

void ExibirBandas(Bandas* banda){
  printf("Ranking de Bandas.\n\n");
  //Loop para exibir todas as bandas
  for (int i = 0; i < 5; i++) {
    printf("Ranking: %d\n",banda->ranking[i]);
    printf("Nome: %s\n",banda->nome[i]);
    printf("Estilo: %s\n",banda->estilo[i]);
    printf("N� de integrantes: %d\n\n",banda->integrantes[i]);
  }//for
  return;
}//Fun��o para exibir todas as bandas

void BuscarBanda(Bandas* banda){
  int i = 0;
  //Solicitando o ranking desejado
 printf("Digite a posi��o do ranking que deseja buscar: ");
 do {
   scanf("%d",&i);
   setbuf(stdin,NULL);
   if(i<1 || i>5)
    printf("S� s�o aceitos valores de 1 a 5. Por favor digite novamente: ");
 } while(i<1 || i>5);

 //Exibindo banda do ranking desejado
 printf("Voc� buscou pela banda na %d� posi��o no ranking.\n",i);
 printf("Nome: %s\n",banda->nome[i-1]);
 printf("Estilo: %s\n",banda->estilo[i-1]);
 printf("N� de integrantes: %d\n\n",banda->integrantes[i-1]);

return;
}//Fun��o paar buscar uma banda espec�fica no ranking
