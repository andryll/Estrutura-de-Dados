/*
*@file exercicio3.c
*@author Andre Luis de Oliveira
*@date 21/06/2021
*@brief Lista diagn�stica de programa��o

Escreva uma fun��o recursiva para calcular o valor de um n�mero inteiro de base
x elevada a um expoente inteiro y.
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int x_elevado_y(int x, int y);

int main(){
  setlocale(LC_ALL,"");//Mudando Localiza��o
  //Declarando vari�veis
  int x;
  int y;
  int resultado;
  //Solicitando valores
  printf("Calcular x^y\n");
  printf("Digite o x: ");
  scanf("%d",&x);
  printf("Digite o y: ");
  scanf("%d",&y);
  //Chamando a fun��o
  resultado = x_elevado_y(x,y);
  //Exibindo resultados
  printf("\n%d^%d = %d\n",x,y,resultado);

  return 0;
}//main

int x_elevado_y(int x, int y){
  if (y == 1)
    return x;
  else
    return x * x_elevado_y(x, y - 1);
}//Fun��o recursiva x^y
