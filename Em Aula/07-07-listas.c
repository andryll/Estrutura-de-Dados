#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//-------------------------------------------------------//
//    Tipos necessários para implementação de Listas     //
// Estratégia - single linkage (singularmente encadeada) //
//-------------------------------------------------------//

typedef struct NoLista *PtrNoLista;

// tipo NoLista
typedef struct NoLista{
  // chave (int)
  int x;
  // ptr proximo No
  PtrNoLista proximo;
}NoLista;

// tipo Lista
typedef struct{
  // ptr inicio (No)
  PtrNoLista inicio;
  // contador (int)
  int qtdeElementos;
}ListaOrdenada;


//  >iniciar
void iniciaListaOrdenada(ListaOrdenada *lista){
  lista->inicio = NULL;
  lista->qtdeElementos=0;
}//Função para iniciar a lista ordenada

//  >estaVazia
bool estaVaziaListaOrdenada(ListaOrdenada *lista){
  return (lista->inicio == NULL);
}// Função para verificar se a lista está vazia

//  >inserir
void inserirListaOrdenada(ListaOrdenada *lista, int x){
  // Cria um PtrNoLista (novo)
  PtrNoLista novo = (PtrNoLista) malloc(sizeof(NoLista));
  novo->x = x;

  //primeira inserção ou elemento menor q primeiro da lista
  if(estaVaziaListaOrdenada(lista) || x <= lista->inicio->x){
    // proximo do novo nó aponta para o nulo (inicio)
    novo->proximo = lista->inicio;
    // inicio aponta para o novo nó
    lista->inicio = novo;
  }else{
    // Criando o auxiliar para percorrer a lista
    PtrNoLista percorre = lista->inicio;
    // percorrendo até verificar a posição de inserção
    while(percorre->proximo != NULL && x > percorre->proximo->x){
      percorre = percorre->proximo;
    }//while
      // proximo do novo aponta para o proximo do percorre
      novo->proximo = percorre->proximo;
      // percorre aponta para o novo
      percorre->proximo = novo;
  }// else
  lista->qtdeElementos++;
}// Função para inserir um elemento na lista ordenada

//  >remover
int removerListaOrdenada(ListaOrdenada *lista, int x){
  int ret = -999;

  // A - remocao em lista vazia (nao remove ninguem)
  // B - remover um elemento menor que o 1º (nao remove)
  if(estaVaziaListaOrdenada(lista) || x < lista->inicio->x){
    return ret;
  }//if

  // C - remover o primeiro elemento (desenfileirar)
  if(x == lista->inicio->x){
    PtrNoLista aux = lista->inicio;
    ret = aux->x;
    lista->inicio = lista->inicio->proximo;
    free(aux);
    lista->qtdeElementos--;
    return ret;
  }//if

  // D - elemento a ser removido não é o 1º (percorrer)
  PtrNoLista percorre - lista->inicio;
  while(percorre->proximo != NULL && (x > percorre->proximo->x)){
    percorre=percorre-proximo;
  }//while
  //  d1 - não acha o elemento depois de percorrer
  if(perocrre->proximo == NULL || (x < percorre->proximo->x)){
    printf("Elemento não encontrado\n");
    return ret;
  }else{
    //  d2 - acha o elemento depois de percorrer
    PtrNoLista aux = percorre->proximo;
    ret = aux->x;
    lista->inicio = lista

  }//else
}// Função para remover um elemento da lista

//  >pesquisar
bool procurarListaOrdenada(ListaOrdenada *lista, int x){
  PtrNoLista percorre;
  for(percorre = lista->inicio;percorre != NULL;percorre = percorre->proximo){
    if(percorre->x == x){
      return true;
    }//if
  } //for
  return false;
} // Função para procurar um elemento na lista ordenada

bool procurarListaOrdenada2(ListaOrdenada *lista, int x){
  if(estaVaziaListaOrdenada(lista)) {
    return false;
  }//if

  PtrNoLista percorre = lista->inicio;

  while(percorre != NULL && x > percorre ->x){
    percorre = percorre -> proximo;
  }//while

  if(percorre == NULL || percorre->x > x){
    return false;
  }//if

  return true;
} // Função para procurar um elemento na lista ordenada de maneira inteligente

//  >destruir



/*
  >maximo
  >minimo
*/

// >tamanho
int tamanhoListaOrdenada(ListaOrdenada *lista){
  return (lista->qtdeElementos);
}// Função para verificar o tamanho da lista
/*
  >proximo
  >anterior
*/

// >imprimir
void imprimirListaOrdenada(ListaOrdenada *lista){
  //ponteiro auxiliar
  PtrNoLista percorre;
  printf("Lista = {");
  for (percorre = lista->inicio;percorre != NULL;percorre = percorre-> proximo){
    printf("%d ",percorre->x);
  }//for
  printf("}.\n");
}//Imprimir lista ordenada



int main(int argc, char const *argv[]) {

  ListaOrdenada lista; //instancia
  iniciaListaOrdenada(&lista); //inicializa

  if(estaVaziaListaOrdenada(&lista))
    printf("ta vazia sim\n");

  inserirListaOrdenada(&lista,10);
  imprimirListaOrdenada(&lista);
  inserirListaOrdenada(&lista,4);
  imprimirListaOrdenada(&lista);
  inserirListaOrdenada(&lista,7);
  imprimirListaOrdenada(&lista);
  inserirListaOrdenada(&lista,8);
  imprimirListaOrdenada(&lista);
  inserirListaOrdenada(&lista,9);
  imprimirListaOrdenada(&lista);

  printf("Numero de elementos: %d\n",tamanhoListaOrdenada(&lista));

  int vetor[] = {8, 90, 6, 10};

  for (int i = 0; i < 4; i++) {
    if(procurarListaOrdenada(&lista, vetor[i])){
      printf("Encontrei o elemento %d\n",vetor[i]);
    }else{
      printf("Nao encontrei o elemento\n");
    }//if
    if(procurarListaOrdenada2(&lista, vetor[i])){
      printf("Encontrei o elemento %d\n",vetor[i]);
    }else{
      printf("Nao encontrei o elemeno\n");
    }//if
  }

  procurarListaOrdenada(&lista, 8);
  procurarListaOrdenada2(&lista, 90);

  return 0;

}//main
