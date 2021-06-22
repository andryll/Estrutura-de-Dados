/*
*@file exercicio1.c
*@author Andre Luis de Oliveira
*@date 05/05/2021
*@brief Exercicios sobre Arquivos
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main(){
  setlocale(LC_ALL,"");//Mudando a localização
  //Declarando variáveis e abrindo Arquivos
  FILE *arq, *arq2;
  int linhas = 0;
  char c = 0;

  //Abrindo arquivo de leitura
  arq = fopen("textoe2.txt","r"); //Abrindo arquivo em modo leitura
  if(arq == NULL){//Erro caso o arquivo não exista
    printf("Erro ao abrir arquivo\n");
    exit(1);//Finalizando o programa
  }else//Mensagem de sucesso caso abra.
    printf("Arquivo de leitura aberto com sucesso!\n");

    printf("\n");

  //Abrindo arquivo de escrita
  arq2 = fopen("textoe2_saida.txt","w"); //Abrindo arquivo em modo escrita
  if(arq == NULL){//Erro caso não seja possível criar o arquivo
    printf("Erro ao criar o arquivo\n");
    exit(1);//Finalizando o programa
  }else//Mensagem de sucesso caso seja criado.
    printf("Arquivo de escrita criado com sucesso!\n");

  //Lento conteudo do arquivo e escrevendo trocando as vogais/contando as linhas
  while((c=fgetc(arq)) != EOF){
    //Contando as linhas
    if(c == '\n')
      linhas++;
    //Verificando se o caractere é uma vogal e colocando ele no arquivo de saída
    if(c != 'a' && c != 'A' && c != 'A' && c != 'e' && c != 'E' && c != 'i'
                && c != 'I' && c != 'o' && c != 'O' && c != 'u' && c != 'U')
      fputc(c,arq2);
    //Se for vogal, será colocado um * no lugar
    else
      fputc('*',arq2);
}//while

printf("\nO arquivo possui %d linhas!\n\n",linhas);


//Fechando arquivos
fclose(arq);
fclose(arq2);

  return 0;
}//main
