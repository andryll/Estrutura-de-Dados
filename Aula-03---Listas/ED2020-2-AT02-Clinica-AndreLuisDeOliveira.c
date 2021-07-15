/*
*@file ED2020-2-AT02-Clinica-AndreLuisDeOliveira.c
*@author Andre Luis de Oliveira
*@date 15/07/2021
*@brief Gerenciador de cadastro de cl�nica
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define TAMANHO 50


///////////////////////////////////////////////////////////////////////////////
//                                 STRUCTS                                   //
///////////////////////////////////////////////////////////////////////////////

typedef struct NoLista *PtrNoLista;

// struct NoLista
typedef struct NoLista{
  // Informa��es
  int codigo;
  char nome[TAMANHO];
  char sexo;
  float altura;
  float peso;
  // ponteiros para outros n�s
  PtrNoLista proximo;
  PtrNoLista anterior;
}NoLista;

// struct Lista
typedef struct{
  // ponteiros do inicio e fim
  PtrNoLista inicio;
  PtrNoLista final;
  // contador
  int qtdeElementos;
}ListaOrdenada;



///////////////////////////////////////////////////////////////////////////////
//                           CABE�ALHO DE FUN��ES                            //
///////////////////////////////////////////////////////////////////////////////

void iniciaListaOrdenada(ListaOrdenada *lista);
bool estaVaziaListaOrdenada(ListaOrdenada *lista);
void inserirListaOrdenada(ListaOrdenada *lista, int codigo, char *nome,
                          char sexo, float altura, float peso);
bool procurarListaOrdenada(ListaOrdenada *lista, int codigo, FILE *arq);
int tamanhoListaOrdenada(ListaOrdenada *lista);
void destruirListaOrdenada(ListaOrdenada *lista);
void imprimirListaOrdenada(ListaOrdenada *lista, FILE *arq);
void imprimirListaOrdenadaInverso(ListaOrdenada *lista, FILE *arq);



///////////////////////////////////////////////////////////////////////////////
//                                   MAIN                                    //
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  // Erro para parametros inv�lidos
  if(argc != 3){
    printf("Erro! Quantidade de argumentos inv�lida! Finalizando programa.\n");
    exit(1);
  }//if

  // Declarando vari�veis
  FILE* arq;
  FILE* arq2;
  ListaOrdenada lista;
  NoLista aux;
  char c;
  bool success = true;

  //Abrindo arquivo desejado e criando arquivo de escrita
  arq = fopen(argv[1],"r");
  arq2 = fopen(argv[2],"w");
  //Verifica��o de erro na abertura ou cria��o do arquivo
  if(arq == NULL || arq2 == NULL){
    printf("Erro ao manipular os arquivos. Finalizando o programa.\n");
    return 0;
  }//if

  // Iniciando lista
  iniciaListaOrdenada(&lista);

  // Verificando arquivo vazio ou desformatado
  c = fgetc(arq);
  if(c != '{'){ // Se n�o come�ar com a chave, est� desformatado
    printf("Arquivo vazio ou desformatado.\n");
    fprintf(arq2, "Arquivo inv�lido.\n");
    success = false;
  }//if

  //Lendo os valores no arquivo
  while(true){

    // Quando c for diferente de '{', quebra o loop
    if(c != '{') break;

    // Lendo codigo
    fscanf(arq,"%d,",&aux.codigo);

    // Limpando dados do nome anterior
    memset(aux.nome, 0,sizeof(aux.nome));

    // Lendo nome
    for (int i = 0; i < TAMANHO; i++) {
      c = fgetc(arq);
      if(c == ','){
        break;
      }else{
        aux.nome[i]=c;
      }// else
    }// for

    //Lendo sexo, peso e altura
    fscanf(arq,"%c,%f,%f}\n",&aux.sexo,&aux.peso,&aux.altura);

    //Adcionando os valores � lista
    inserirListaOrdenada(&lista, aux.codigo, aux.nome, aux.sexo, aux.altura, aux.peso);

    // conferindo o proximo primeiro caractere
    c = fgetc(arq);
  }// while

  // Op��o desejada ficou salva na vari�vel c
  // switch com as op��es
  switch (c) {

    // Caso tenha dado erro anteriormente, o switch j� � quebrado
    if(!success) break;

    case '1': // imprimir os registros em ordem crescente
      imprimirListaOrdenada(&lista, arq2);
    break;


    case '2': // imprimir os registros em ordem decrescente
      imprimirListaOrdenadaInverso(&lista, arq2);
    break;


    case '3': // consultar paciente
      // Recebendo c�digo desejado para pesquisa
      fscanf(arq,"%d",&aux.codigo);
      // Verificando se est� na lista
      if(procurarListaOrdenada(&lista, aux.codigo, arq2)){
        printf("O paciente solicitado esta na lista\n");
      }else{
        printf("O paciente solicitado nao foi encontrado\n");
        fprintf(arq2, "Paciente n�o encontrado.\n");
      }// else
    break;


    default: // op��o inv�lida
      fprintf(arq2, "Op��o inv�lida!\n");
      success = false;
    break;
  }// switch

  // Desalocando lista
  destruirListaOrdenada(&lista);

  // Fechando arquivos
  fclose(arq);
  fclose(arq2);

  // Exibindo mensagem de sucesso ou de erro
  if(success){
    printf("A operacao foi realizada com sucesso!\n");
  }else{
    printf("Houve algum erro nas operacoes.\n");
  }// else

  return 0;
}// main



///////////////////////////////////////////////////////////////////////////////
//                           FUN��ES DAS LISTAS                              //
///////////////////////////////////////////////////////////////////////////////

void iniciaListaOrdenada(ListaOrdenada *lista){
  lista->inicio = NULL;
  lista->final = NULL;
  lista->qtdeElementos=0;
}//Fun��o para iniciar a lista ordenada


bool estaVaziaListaOrdenada(ListaOrdenada *lista){
  return (lista->inicio == NULL);
}// Fun��o para verificar se a lista est� vazia


void inserirListaOrdenada(ListaOrdenada *lista, int codigo, char *nome,
                          char sexo, float altura, float peso){
  // Cria um PtrNoLista com as informa��es
  PtrNoLista novo = (PtrNoLista) malloc(sizeof(NoLista));
  // atribui os valores para o novo n�
  novo->codigo = codigo;
  strcpy(novo->nome,nome);
  novo->sexo = sexo;
  novo->altura = altura;
  novo->peso = peso;

  //primeira inser��o ou elemento menor q primeiro da lista
  if(estaVaziaListaOrdenada(lista) || codigo <= lista->inicio->codigo){
    // anterior aponta para o nulo
    novo->anterior = NULL;
    // proximo do novo n� aponta para o nulo (inicio)
    novo->proximo = lista->inicio;
    // inicio aponta para o novo n�
    lista->inicio = novo;

  }else{
    // Criando o auxiliar para percorrer a lista
    PtrNoLista percorre = lista->inicio;
    // percorrendo at� verificar a posi��o de inser��o
    while(percorre->proximo != NULL && codigo > percorre->proximo->codigo){
      percorre = percorre->proximo;
    }//while
      // proximo do novo aponta para o proximo do percorre
      novo->proximo = percorre->proximo;
      // anterior do novo aponta pro percorre
      novo->anterior = percorre;
      // percorre aponta para o novo
      percorre->proximo = novo;
  }// else

  if(novo->proximo == NULL){
    // se o novo for o ultimo da lista, proximo aponta por NULL
    lista->final = novo;
  }else{ // senao, o anterior do proximo aponta pro novo
    novo->proximo->anterior = novo;
  }//else

  // incrementa quantidade
  lista->qtdeElementos++;
}// Fun��o para inserir um elemento na lista ordenada


bool procurarListaOrdenada(ListaOrdenada *lista, int codigo, FILE *arq){
  // Se estiver vazia, nao procura
  if(estaVaziaListaOrdenada(lista)) {
    return false;
  }//if

  // inicia o percorre no inicio
  PtrNoLista percorre = lista->inicio;

  // percorre a lista enquanto o percorre for menor que o requerido
  while(percorre != NULL && codigo > percorre ->codigo){
    percorre = percorre -> proximo;
  }//while

  if(percorre == NULL || percorre->codigo > codigo){
    // se o percorre encontrou o NULL ou um numero maior que o codigo, = false
    return false;
  }else{ // caso contr�rio, encontrou o numero
    // escreve o paciente desejado no arquivo
    fprintf(arq,"Paciente encontrado:\n");
    fprintf(arq,"{%d, %s, %c, %.2f, %.2f}\n",percorre->codigo, percorre->nome,
                             percorre->sexo, percorre->peso, percorre->altura);
    return true;
  }//else
} // Fun��o para procurar um elemento na lista ordenada de maneira inteligente


int tamanhoListaOrdenada(ListaOrdenada *lista){
  return (lista->qtdeElementos);
}// Fun��o para verificar o tamanho da lista


void destruirListaOrdenada(ListaOrdenada *lista){
  while(true){ // Loop para destruir todos os n�s
    if(estaVaziaListaOrdenada(lista)){ // a lista ficou vazia, quebra o loop
      break;
    }//if

    //inicia o aux no inicio
    PtrNoLista aux = lista->inicio;

    // libera o aux
    free(aux);

    // decrementa contador
    lista->qtdeElementos--;

    if(tamanhoListaOrdenada(lista) > 1){
      // se houver mais de um elemento, muda o inicio para o proximo
      lista->inicio = lista->inicio->proximo;

    }else{ // caso s� reste um elemento
      // inicio e final aponta pro NULL
      lista->inicio = NULL;
      lista->final == NULL;
    }//else

  }//Loop para remover todos os elementos
  return;
}//Fun��o para destruir a lista


void imprimirListaOrdenada(ListaOrdenada *lista, FILE *arq){
if(!estaVaziaListaOrdenada(lista)){
  //ponteiro auxiliar
  PtrNoLista percorre;

  fprintf(arq,"Lista:\n");

  // percorre passa por toda a lista em ordem crescente enquanto nao for NULL
  for (percorre = lista->inicio;percorre != NULL;percorre = percorre-> proximo){
    //escreve o percorre no arquivo
    fprintf(arq,"{%d, %s, %c, %.1f, %.1f}\n",percorre->codigo, percorre->nome,
                    percorre->sexo, percorre->peso, percorre->altura);
  }//for

  fprintf(arq,"\n");

}else{ // caso a lista esteja vazia, escreve lista vazia
  fprintf(arq,"Lista Vazia\n");
}// else
}//Imprimir lista ordenada


void imprimirListaOrdenadaInverso(ListaOrdenada *lista, FILE *arq){
  if(!estaVaziaListaOrdenada(lista)){
  //ponteiro auxiliar
  PtrNoLista percorre;

  fprintf(arq,"Lista:\n");

  // percorre passa por toda a lista em ordem decrescente enquanto nao for NULL
  for (percorre = lista->final;percorre != NULL;percorre = percorre-> anterior){
    //escreve o percorre no arquivo
    fprintf(arq,"{%d, %s, %c, %.1f, %.1f}\n",percorre->codigo, percorre->nome,
                    percorre->sexo, percorre->peso, percorre->altura);
  }//for

  fprintf(arq,"\n");

}else{ // caso a lista esteja vazia, escreve lista vazia
  fprintf(arq,"Lista Vazia\n");
}// else
}//Imprimir lista ordenada
