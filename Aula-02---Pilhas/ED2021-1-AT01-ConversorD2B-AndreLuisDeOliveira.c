/*
*@file ED2021-1-AT01-ConversorD2B-AndreLuisDeOliveira.c
*@author Andre Luis de Oliveira
*@date 06/07/2021
*@brief Conversor de decimal para bin�rio usando pilhas
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

//Cabe�alho das fun��es
int decBin(int num);

//////////CABE�ALHO PILHA EST�TICA//////////////
void iniciaPilhaEstatica(PilhaEstatica *pe);
bool estaVaziaPilhaEstatica(PilhaEstatica *pe);
bool estaCheiaPilhaEstatica(PilhaEstatica *pe);
int tamanhoPilhaEstatica(PilhaEstatica *pe);
void empilharPilhaEstatica(PilhaEstatica *pe, int num);
int desempilharPilhaEstatica(PilhaEstatica *pe);

////////CABE�ALHO PILHA DIN�MICA///////////////
void iniciaPilhaDinamica(PilhaDinamica *pd);
int tamanhoPilhaDinamica(PilhaDinamica *pd);
bool estaVaziaPilhaDinamica(PilhaDinamica *pd);
void empilharPilhaDinamica(PilhaDinamica *pd, int x);
int desempilharPilhaDinamica(PilhaDinamica *pd);
void destruirPilhaDinamica(PilhaDinamica *pd);


int main(int argc, char const *argv[]) {
  //Erro para parametros inv�lidos
  if(argc != 3){
    printf("Erro! Quantidade de argumentos inv�lida! Finalizando programa.\n");
    exit(1);
  }//if

  // Declarando vari�veis
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
  //Verifica��o de erro na abertura ou cria��o do arquivo
  if(arq == NULL || arq2 == NULL){
    printf("Erro ao manipular os arquivos. Finalizando o programa.\n");
    return 0;
  }//if

  //Recebendo a op��o de pilha do arquivo
  opcao_de_pilha = fgetc(arq);

  //Switch com os casos das op��es
  switch(opcao_de_pilha){
    //Caso da pilha est�tica
    case 'e':
    case 'E':
      //Iniciando pilha est�tica
      iniciaPilhaEstatica(&pe);
      //Loop para salvar os decimais na pilha at� o fim do arquivo
      while(true){
        //Recebe a vari�vel do arquivo
        fscanf(arq,"%f",&aux2);
        //Verifica se o n�mero colocado no texto � inteiro
        aux = aux2;
        if(aux == -99999)
          break;
        if(aux2 - (float)aux == 0){//Se for inteiro, empilha
          empilharPilhaEstatica(&pe, aux);
          aux = -99999;
        }else{//Se n�o for, exibe erro e finaliza o programa
          fprintf(arq2, "N�o h� um n�mero inteiro");
          printf("O arquivo n�o cont�m um n�mero inteiro. Finalizando o programa\n");
          return 0;
        }//else
        //Afirmando que o arquivo n�o est� vazio
        arquivoNaoVazio = true;
        //Verifica se o arquivo chegou ao fim e finaliza o loop
        if(feof(arq))
          break;
      }//while

      // Convertendo para bin�rio e salvando no arquivo de sa�da enquanto a
      // pilha n�o estiver vazia
      while(!estaVaziaPilhaEstatica(&pe)){
        fprintf(arq2,"%d \n",decBin(desempilharPilhaEstatica(&pe)));
      }//while

      break;

    //Caso da pilha din�mica
    case 'd':
    case 'D':
      //Iniciando pilha din�mica
      iniciaPilhaDinamica(&pd);
      //Loop para salvar os decimais na pilha at� o fim do arquivo
      while(true){
        //Recebe a vari�vel do arquivo
        fscanf(arq,"%f",&aux2);
        //Verifica se o n�mero colocado no texto � inteiro
        aux = aux2;
        if(aux == -99999)
          break;
        if(aux2 - (float)aux == 0){//Se for inteiro, empilha
          empilharPilhaDinamica(&pd, aux);
        aux2 = -99999;
        }else{//Se n�o for, exibe erro e finaliza o programa
          fprintf(arq2, "N�o h� um n�mero inteiro");
          printf("O arquivo n�o cont�m um n�mero inteiro. Finalizando o programa\n");
          return 0;
        }//else
        //Afirmando que o arquivo n�o est� vazio
        arquivoNaoVazio = true;
        //Verifica se o arquivo chegou ao fim e finaliza o loop
        if(feof(arq))
        break;
      }//while

      // Convertendo para bin�rio e salvando no arquivo de sa�da enquanto a
      // pilha n�o estiver vazia
      while(!estaVaziaPilhaDinamica(&pd)){
        fprintf(arq2,"%d \n",decBin(desempilharPilhaDinamica(&pd)));
      }//while

      //Destruindo pilha caso sobre algum elemento
      if(!estaVaziaPilhaDinamica(&pd))
        destruirPilhaDinamica(&pd);

      break;

    default:
    //Erro caso a letra especificada no arquivo n�o seja "e" ou "d"
    fprintf(arq2, "Op��o inv�lida!");
      printf("O arquivo cont�m uma op��o inv�lida. Finalizando o programa\n");
      return 0;

      break;
  }//switch

  //Mensagem de sucesso se a lista n�o estiver vazia
  if(arquivoNaoVazio){
    printf("Os numeros foram convertidos com sucesso!\n");
  }else{//Caso esteja vazia
    fprintf(arq2, "O arquivo n�o possu�a n�meros para serem convertidos\n");
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
}//Fun��o recursiva para converter decimal para bin�rio


//////// FUN��ES DA PILHA EST�TICA /////////
void iniciaPilhaEstatica(PilhaEstatica *pe){
  pe->topo = 0;
  pe->qtdeElementos = 0;
}// Fun��o para iniciar a pilha est�tica

bool estaVaziaPilhaEstatica(PilhaEstatica *pe){
  return(pe->topo == 0);
}// Fun��o para verificar se a pilha est� vazia

bool estaCheiaPilhaEstatica(PilhaEstatica *pe){
  return(pe->topo == TAMANHO);
}// Fun��o para verificar se a pilha est� cheia

int tamanhoPilhaEstatica(PilhaEstatica *pe){
  return(pe->qtdeElementos);
}// Fun��o para verificar a quantidade de elementos na pilha

void empilharPilhaEstatica(PilhaEstatica *pe, int num){
  //Caso a pilha n�o esteja cheia, empilha o elemento
  if(!estaCheiaPilhaEstatica(pe)){
    pe->elemento[pe->topo] = num;
    pe->topo++;
    pe->qtdeElementos++;

  }else{//Caso contr�rio, exibe erro
    printf("Pilha cheia. N�o � poss�vel inserir o elemento\n");
  }// else
}// Fun��o para inserir elemento na pilha est�tica

int desempilharPilhaEstatica(PilhaEstatica *pe){
  // Vari�vel auxiliar
  int ret = -999;
  //Caso a pilha n�o esteja vazia, desempilha elemento
  if(!estaVaziaPilhaEstatica(pe)){
    ret = pe->elemento[pe->topo - 1];
    pe->topo--;
    pe->qtdeElementos--;

}else{//Caso contr�rio, exibe erro
  printf("Pilha vazia. N�o � poss�vel remover o elemento\n");
}// else
  //Retorna o elemento desempilhado
  return(ret);
}// Fun��o para retirar um elemento da pilha



/////////////FUN��ES DA PILHA DIN�MICA////////////////////
void iniciaPilhaDinamica(PilhaDinamica *pd){
  pd->topo = NULL;
  pd->qtdeElementos = 0;
}//Fun��o para iniciar a pilha din�mica

int tamanhoPilhaDinamica(PilhaDinamica *pd){
  return (pd->qtdeElementos);
}//Fun��o para verificar o tamanho da pilha

bool estaVaziaPilhaDinamica(PilhaDinamica *pd){
  return(pd->topo == NULL);
}//Fun��o para verificar se a pilha est� vazia

void empilharPilhaDinamica(PilhaDinamica *pd, int x){
    //Declarando vari�vel auxiliar
    PtrNoPilha aux;
    //Aloca mem�ria para a vari�vel e salva seu valor
    aux = (PtrNoPilha) malloc(sizeof(PtrNoPilha));
    aux->elemento = x;
    aux->proximo = pd->topo;
    pd->topo = aux;
    pd->qtdeElementos++;
}//Fun��o para empilhar um elemento

int desempilharPilhaDinamica(PilhaDinamica *pd){
  //Declarando vari�vel auxiliar
  int ret = -99;
  //Se n�o estiver vazia, desempilha o elemento
  if(!estaVaziaPilhaDinamica(pd)){
  //Declarando vari�vel auxiliar
  PtrNoPilha aux;
  //Desloca o topo para o pr�ximo elemento e desaloca a memoria do topo antigo
  aux = pd->topo;
  ret = aux->elemento;
  pd->topo = pd->topo->proximo;
  free(aux);
  pd->qtdeElementos--;

}else{//Caso contr�rio, exibe erro
  printf("Pilha vazia. N�o � poss�vel remover o elemento\n");
}//else
  //Retorna o valor desempilhado
  return(ret);
}//Fun��o para desempilhar um elemento e desalocar a mem�ria dele

void destruirPilhaDinamica(PilhaDinamica *pd){
  //Se n�o estiver vazia, desempilha o elemento
  if(!estaVaziaPilhaDinamica(pd)){
    //Declarando vari�vel auxiliar
    PtrNoPilha aux;
    //Criando loop para desempilhar enquanto o topo n�o for nulo
    while(pd->topo != NULL){
    //Desloca o topo para o pr�ximo elemento e desaloca a memoria do topo antigo
      aux = pd->topo;
      pd->topo = pd->topo->proximo;
      free(aux);
      pd->qtdeElementos--;
    }//while
    //Mensagem de sucesso
    printf("Pilha destru�da com sucesso!\n");

  }else{ //Caso contr�rio, exibe erro
    printf("Pilha vazia. N�o � poss�vel destruir\n");
  }//else
}//Fun��o para destruir a pilha din�mica
