/*
*@file ED2021-1-AT01-ConversorD2B-AndreLuisDeOliveira.c
*@author Andre Luis de Oliveira
*@date 06/07/2021
*@brief Conversor de decimal para binário usando pilhas
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 100

///Structs
typedef struct{
  int elemento [TAMANHO];
  int topo;
  int qtdeElementos;
}PilhaEstatica;

typedef struct NoPilha *PtrNoPilha;

typedef struct NoPilha{
  int elemento;
  PtrNoPilha proximo;
}NoPilha;

typedef struct{
  PtrNoPilha topo;
  int qtdeElementos;
}PilhaDinamica;

//Cabeçalho das funções
int decBin(int num);

//////////CABEÇALHO PILHA ESTÁTICA//////////////
void iniciaPilhaEstatica(PilhaEstatica *pe);
bool estaVaziaPilhaEstatica(PilhaEstatica *pe);
bool estaCheiaPilhaEstatica(PilhaEstatica *pe);
int tamanhoPilhaEstatica(PilhaEstatica *pe);
void empilharPilhaEstatica(PilhaEstatica *pe, int num);
int desempilharPilhaEstatica(PilhaEstatica *pe);

////////CABEÇALHO PILHA DINÂMICA///////////////
void iniciaPilhaDinamica(PilhaDinamica *pd);
int tamanhoPilhaDinamica(PilhaDinamica *pd);
bool estaVaziaPilhaDinamica(PilhaDinamica *pd);
void empilharPilhaDinamica(PilhaDinamica *pd, int x);
int desempilharPilhaDinamica(PilhaDinamica *pd);
void destruirPilhaDinamica(PilhaDinamica *pd);


int main(int argc, char const *argv[]) {
  //Erro para parametros inválidos
  if(argc != 3){
    printf("Erro! Quantidade de argumentos inválida! Finalizando programa.\n");
    exit(1);
  }//if

  // Declarando variáveis
  FILE* arq;
  FILE* arq2;
  PilhaEstatica pe;
  PilhaDinamica pd;
  char opcao_de_pilha;
  int aux = -99999;
  float aux2 = -99999;
  bool arquivoNaoVazio = false;

  //Abrindo arquivo desejado e criando arquivo de escrita
  arq = fopen(argv[1],"r");
  arq2 = fopen(argv[2],"w");
  //Verificação de erro na abertura ou criação do arquivo
  if(arq == NULL || arq2 == NULL){
    printf("Erro ao manipular os arquivos. Finalizando o programa.\n");
    return 0;
  }//if

  //Recebendo a opção de pilha do arquivo
  opcao_de_pilha = fgetc(arq);

  //Switch com os casos das opções
  switch(opcao_de_pilha){
    //Caso da pilha estática
    case 'e':
    case 'E':
      //Iniciando pilha estática
      iniciaPilhaEstatica(&pe);
      //Loop para salvar os decimais na pilha até o fim do arquivo
      while(true){
        //Recebe a variável do arquivo
        fscanf(arq,"%f",&aux2);
        //Verifica se o número colocado no texto é inteiro
        aux = aux2;
        if(aux == -99999)
          break;
        if(aux2 - (float)aux == 0){//Se for inteiro, empilha
          empilharPilhaEstatica(&pe, aux);
          aux = -99999;
        }else{//Se não for, exibe erro e finaliza o programa
          fprintf(arq2, "Não há um número inteiro");
          printf("O arquivo não contém um número inteiro. Finalizando o programa\n");
          return 0;
        }//else
        //Afirmando que o arquivo não está vazio
        arquivoNaoVazio = true;
        //Verifica se o arquivo chegou ao fim e finaliza o loop
        if(feof(arq))
          break;
      }//while

      // Convertendo para binário e salvando no arquivo de saída enquanto a
      // pilha não estiver vazia
      while(!estaVaziaPilhaEstatica(&pe)){
        fprintf(arq2,"%d \n",decBin(desempilharPilhaEstatica(&pe)));
      }//while

      break;

    //Caso da pilha dinâmica
    case 'd':
    case 'D':
      //Iniciando pilha dinâmica
      iniciaPilhaDinamica(&pd);
      //Loop para salvar os decimais na pilha até o fim do arquivo
      while(true){
        //Recebe a variável do arquivo
        fscanf(arq,"%f",&aux2);
        //Verifica se o número colocado no texto é inteiro
        aux = aux2;
        if(aux == -99999)
          break;
        if(aux2 - (float)aux == 0){//Se for inteiro, empilha
          empilharPilhaDinamica(&pd, aux);
        aux2 = -99999;
        }else{//Se não for, exibe erro e finaliza o programa
          fprintf(arq2, "Não há um número inteiro");
          printf("O arquivo não contém um número inteiro. Finalizando o programa\n");
          return 0;
        }//else
        //Afirmando que o arquivo não está vazio
        arquivoNaoVazio = true;
        //Verifica se o arquivo chegou ao fim e finaliza o loop
        if(feof(arq))
        break;
      }//while

      // Convertendo para binário e salvando no arquivo de saída enquanto a
      // pilha não estiver vazia
      while(!estaVaziaPilhaDinamica(&pd)){
        fprintf(arq2,"%d \n",decBin(desempilharPilhaDinamica(&pd)));
      }//while

      //Destruindo pilha caso sobre algum elemento
      if(!estaVaziaPilhaDinamica(&pd))
        destruirPilhaDinamica(&pd);

      break;

    default:
    //Erro caso a letra especificada no arquivo não seja "e" ou "d"
    fprintf(arq2, "Opção inválida!");
      printf("O arquivo contém uma opção inválida. Finalizando o programa\n");
      return 0;

      break;
  }//switch

  //Mensagem de sucesso se a lista não estiver vazia
  if(arquivoNaoVazio){
    printf("Os numeros foram convertidos com sucesso!\n");
  }else{//Caso esteja vazia
    fprintf(arq2, "O arquivo não possuía números para serem convertidos\n");
    printf("A lista estava vazia! Finalizando o programa.\n");
  }//else

  //Fechando arquivos
  fclose(arq);
  fclose(arq2);

  return 0;
}//main

int decBin(int num){
  //Caso base
  if(num == 0){
    return num;
  }else{
    //Caso recursivo
    return (num%2) + (10*decBin(num/2));
  }//else
}//Função recursiva para converter decimal para binário


//////// FUNÇÕES DA PILHA ESTÁTICA /////////
void iniciaPilhaEstatica(PilhaEstatica *pe){
  pe->topo = 0;
  pe->qtdeElementos = 0;
}// Função para iniciar a pilha estática

bool estaVaziaPilhaEstatica(PilhaEstatica *pe){
  return(pe->topo == 0);
}// Função para verificar se a pilha está vazia

bool estaCheiaPilhaEstatica(PilhaEstatica *pe){
  return(pe->topo == TAMANHO);
}// Função para verificar se a pilha está cheia

int tamanhoPilhaEstatica(PilhaEstatica *pe){
  return(pe->qtdeElementos);
}// Função para verificar a quantidade de elementos na pilha

void empilharPilhaEstatica(PilhaEstatica *pe, int num){
  //Caso a pilha não esteja cheia, empilha o elemento
  if(!estaCheiaPilhaEstatica(pe)){
    pe->elemento[pe->topo] = num;
    pe->topo++;
    pe->qtdeElementos++;

  }else{//Caso contrário, exibe erro
    printf("Pilha cheia. Não é possível inserir o elemento\n");
  }// else
}// Função para inserir elemento na pilha estática

int desempilharPilhaEstatica(PilhaEstatica *pe){
  // Variável auxiliar
  int ret = -999;
  //Caso a pilha não esteja vazia, desempilha elemento
  if(!estaVaziaPilhaEstatica(pe)){
    ret = pe->elemento[pe->topo - 1];
    pe->topo--;
    pe->qtdeElementos--;

}else{//Caso contrário, exibe erro
  printf("Pilha vazia. Não é possível remover o elemento\n");
}// else
  //Retorna o elemento desempilhado
  return(ret);
}// Função para retirar um elemento da pilha



/////////////FUNÇÕES DA PILHA DINÂMICA////////////////////
void iniciaPilhaDinamica(PilhaDinamica *pd){
  pd->topo = NULL;
  pd->qtdeElementos = 0;
}//Função para iniciar a pilha dinâmica

int tamanhoPilhaDinamica(PilhaDinamica *pd){
  return (pd->qtdeElementos);
}//Função para verificar o tamanho da pilha

bool estaVaziaPilhaDinamica(PilhaDinamica *pd){
  return(pd->topo == NULL);
}//Função para verificar se a pilha está vazia

void empilharPilhaDinamica(PilhaDinamica *pd, int x){
    //Declarando variável auxiliar
    PtrNoPilha aux;
    //Aloca memória para a variável e salva seu valor
    aux = (PtrNoPilha) malloc(sizeof(PtrNoPilha));
    aux->elemento = x;
    aux->proximo = pd->topo;
    pd->topo = aux;
    pd->qtdeElementos++;
}//Função para empilhar um elemento

int desempilharPilhaDinamica(PilhaDinamica *pd){
  //Declarando variável auxiliar
  int ret = -99;
  //Se não estiver vazia, desempilha o elemento
  if(!estaVaziaPilhaDinamica(pd)){
  //Declarando variável auxiliar
  PtrNoPilha aux;
  //Desloca o topo para o próximo elemento e desaloca a memoria do topo antigo
  aux = pd->topo;
  ret = aux->elemento;
  pd->topo = pd->topo->proximo;
  free(aux);
  pd->qtdeElementos--;

}else{//Caso contrário, exibe erro
  printf("Pilha vazia. Não é possível remover o elemento\n");
}//else
  //Retorna o valor desempilhado
  return(ret);
}//Função para desempilhar um elemento e desalocar a memória dele

void destruirPilhaDinamica(PilhaDinamica *pd){
  //Se não estiver vazia, desempilha o elemento
  if(!estaVaziaPilhaDinamica(pd)){
    //Declarando variável auxiliar
    PtrNoPilha aux;
    //Criando loop para desempilhar enquanto o topo não for nulo
    while(pd->topo != NULL){
    //Desloca o topo para o próximo elemento e desaloca a memoria do topo antigo
      aux = pd->topo;
      pd->topo = pd->topo->proximo;
      free(aux);
      pd->qtdeElementos--;
    }//while
    //Mensagem de sucesso
    printf("Pilha destruída com sucesso!\n");

  }else{ //Caso contrário, exibe erro
    printf("Pilha vazia. Não é possível destruir\n");
  }//else
}//Função para destruir a pilha dinâmica
