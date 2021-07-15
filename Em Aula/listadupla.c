#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//-------------------------------------------------------//
//    Tipos necessários para implementação de Listas     //
// Estratégia - single linkage (singularmente encadeada) //
//-------------------------------------------------------//

typedef struct NoLista *PtrNoLista;

// tipo NoLista
typedef struct NoLista{
  // chave (int)
  int codigo;
  char nome[50];
  char sexo;
  float altura;
  float peso;

  // ptr proximo No
  PtrNoLista proximo;
  PtrNoLista anterior;
}NoLista;

// tipo Lista
typedef struct{
  // ptr inicio e fim (No)
  PtrNoLista inicio;
  PtrNoLista final;
  // contador (int)
  int qtdeElementos;
}ListaOrdenada;


//  >iniciar
void iniciaListaOrdenada(ListaOrdenada *lista){
  lista->inicio = NULL;
  lista->final = NULL;
  lista->qtdeElementos=0;
}//Função para iniciar a lista ordenada

//  >estaVazia
bool estaVaziaListaOrdenada(ListaOrdenada *lista){
  return (lista->inicio == NULL);
}// Função para verificar se a lista está vazia

//  >inserir
void inserirListaOrdenada(ListaOrdenada *lista, int codigo, char *nome,
                          char sexo, float altura, float peso){
  // Cria um PtrNoLista (novo)
//  printf("%s\n",nome);
  PtrNoLista novo = (PtrNoLista) malloc(sizeof(NoLista));
  novo->codigo = codigo;
  strcpy(novo->nome,nome);
  novo->sexo = sexo;
  novo->altura = altura;
  novo->peso = peso;

  //primeira inserção ou elemento menor q primeiro da lista
  if(estaVaziaListaOrdenada(lista) || codigo <= lista->inicio->codigo){
    // proximo do novo nó aponta para o nulo (inicio)
    novo->anterior = NULL;
    novo->proximo = lista->inicio;
    // inicio aponta para o novo nó
    lista->inicio = novo;

  }else{
    // Criando o auxiliar para percorrer a lista
    PtrNoLista percorre = lista->inicio;
    // percorrendo até verificar a posição de inserção
    while(percorre->proximo != NULL && codigo > percorre->proximo->codigo){
      percorre = percorre->proximo;
    }//while
      // proximo do novo aponta para o proximo do percorre
      novo->proximo = percorre->proximo;
      novo->anterior = percorre;
      // percorre aponta para o novo
      percorre->proximo = novo;
    //  novo->proximo->anterior = novo;
  }// else

  if(novo->proximo == NULL){
    lista->final = novo;
  }else{
    novo->proximo->anterior = novo;
  }//else

  lista->qtdeElementos++;
}// Função para inserir um elemento na lista ordenada


//  >remover
int removerListaOrdenada(ListaOrdenada *lista, int codigo){
  int ret = -999;

  // A - remocao em lista vazia (nao remove ninguem)
  // B - remover um elemento menor que o 1º (nao remove)
  // C - remover um elemento maior que o ultimo (nao remove)
  if(estaVaziaListaOrdenada(lista) || codigo < lista->inicio->codigo || codigo > lista->final->codigo){
    printf("maior que final\n");
    printf("nao remove\n");
    return ret;
  }//if

  // D - remover o primeiro elemento (desenfileirar)
  if(codigo == lista->inicio->codigo){
    PtrNoLista aux = lista->inicio;
    ret = aux->codigo;
    lista->inicio = lista->inicio->proximo;
    lista->inicio->anterior = NULL;
    free(aux);
    lista->qtdeElementos--;
    return ret;
  }//if

  // E - remover o ultimo elemento (desenfileirar)
  if(codigo == lista->final->codigo){
    PtrNoLista aux = lista->final;
    ret = aux->codigo;
    lista->final = lista->final->anterior;
    lista->final->proximo = NULL;
    free(aux);
    lista->qtdeElementos--;
    return ret;
  }//if

  // F - elemento a ser removido não é o 1º (percorrer)
  PtrNoLista percorre = lista->inicio;
  while(percorre->proximo != NULL && (codigo > percorre->proximo->codigo)){
    percorre=percorre->proximo;
  }//while
  //  d1 - não acha o elemento depois de percorrer
  if(percorre->proximo == NULL || (codigo < percorre->proximo->codigo)){
    printf("Elemento não encontrado\n");
    return ret;
  }else{
    //  d2 - acha o elemento depois de percorrer
    PtrNoLista aux = percorre->proximo;
    ret = aux->codigo;
    percorre->proximo = aux->proximo;
    aux->proximo->anterior = percorre;
    free(aux);
    lista->qtdeElementos--;
    return ret;
  }//else
}// Função para remover um elemento da lista



bool procurarListaOrdenada2(ListaOrdenada *lista, int codigo){
  if(estaVaziaListaOrdenada(lista)) {
    return false;
  }//if

  PtrNoLista percorre = lista->inicio;

  while(percorre != NULL && codigo > percorre ->codigo){
    percorre = percorre -> proximo;
  }//while

  if(percorre == NULL || percorre->codigo > codigo){
    return false;
  }else{
    printf("%d, %s, %c, %.2f, %.2f\n",percorre->codigo, percorre->nome,
                    percorre->sexo, percorre->altura, percorre->peso);
    return true;
  }//else
} // Função para procurar um elemento na lista ordenada de maneira inteligente

int tamanhoListaOrdenada(ListaOrdenada *lista){
  return (lista->qtdeElementos);
}// Função para verificar o tamanho da lista

//  >destruir
void destruir(ListaOrdenada *lista){
  while(true){
    if(estaVaziaListaOrdenada(lista)){
      break;
    }//if
    if(tamanhoListaOrdenada(lista) > 1){
      PtrNoLista aux = lista->inicio;
      lista->inicio = lista->inicio->proximo;
      free(aux);
      lista->qtdeElementos--;
    }else{
      PtrNoLista aux = lista->inicio;
      lista->inicio = NULL;
      lista->final == NULL;
      free(aux);
      lista->qtdeElementos--;
    }//else
  }//Loop para remover todos os elementos
  return;
}//Função para destruir a lista



/*
  >maximo
  >minimo
*/

// >tamanho
/*
  >proximo
  >anterior
*/

// >imprimir
void imprimirListaOrdenada(ListaOrdenada *lista){
if(!estaVaziaListaOrdenada(lista)){
  //ponteiro auxiliar
  PtrNoLista percorre;
  printf("Lista:\n");
  for (percorre = lista->inicio;percorre != NULL;percorre = percorre-> proximo){
    printf("{%d, %s, %c, %.2f, %.2f}\n",percorre->codigo, percorre->nome,
                    percorre->sexo, percorre->altura, percorre->peso);
  }//for
  printf("\n");
}else{
  printf("Lista Vazia\n");
}
}//Imprimir lista ordenada

void imprimirListaOrdenadaInverso(ListaOrdenada *lista){
  if(!estaVaziaListaOrdenada(lista)){
  //ponteiro auxiliar
  PtrNoLista percorre;
  printf("Lista:\n");
  for (percorre = lista->final;percorre != NULL;percorre = percorre-> anterior){
    printf("{%d, %s, %c, %.2f, %.2f}\n",percorre->codigo, percorre->nome,
                    percorre->sexo, percorre->altura, percorre->peso);
  }//for
  printf("\n");
}else{
  printf("Lista Vazia\n");
}
}//Imprimir lista ordenada



int main(int argc, char const *argv[]) {

  char nome[50] = "gerson";
  ListaOrdenada lista; //instancia
  iniciaListaOrdenada(&lista); //inicializa

  if(estaVaziaListaOrdenada(&lista))
    printf("ta vazia sim\n");

  inserirListaOrdenada(&lista, 10, nome, 'm', 52.4, 150);
  imprimirListaOrdenada(&lista);
    imprimirListaOrdenadaInverso(&lista);
  inserirListaOrdenada(&lista,4, nome, 'm', 52.4, 150);
  imprimirListaOrdenada(&lista);
    imprimirListaOrdenadaInverso(&lista);
  inserirListaOrdenada(&lista,7, nome, 'm', 52.4, 150);
  imprimirListaOrdenada(&lista);
    imprimirListaOrdenadaInverso(&lista);
  inserirListaOrdenada(&lista,8, nome, 'm', 52.4, 150);
  imprimirListaOrdenada(&lista);
    imprimirListaOrdenadaInverso(&lista);
  inserirListaOrdenada(&lista,9, nome, 'm', 52.4, 150);
  imprimirListaOrdenada(&lista);
    imprimirListaOrdenadaInverso(&lista);

printf("%d\n",removerListaOrdenada(&lista,10));
printf("qtd: %d\n",tamanhoListaOrdenada(&lista) );
    imprimirListaOrdenada(&lista);
    imprimirListaOrdenadaInverso(&lista);

    if(procurarListaOrdenada2(&lista, 12)){
        printf("elemento na lista\n");
    }else{
      printf("nao esta na lista\n");
    }

    destruir(&lista);
    imprimirListaOrdenada(&lista);
    imprimirListaOrdenadaInverso(&lista);



  // int vetor[] = {8, 90, 6, 10};
  //
  // for (int i = 0; i < 4; i++) {
  //   if(procurarListaOrdenada(&lista, vetor[i])){
  //     printf("Encontrei o elemento %d\n",vetor[i]);
  //   }else{
  //     printf("Nao encontrei o elemento\n");
  //   }//if
  //   if(procurarListaOrdenada2(&lista, vetor[i])){
  //     printf("Encontrei o elemento %d\n",vetor[i]);
  //   }else{
  //     printf("Nao encontrei o elemeno\n");
  //   }//if
  // }
  //
  // procurarListaOrdenada(&lista, 8);
  // procurarListaOrdenada2(&lista, 90);

  return 0;

}//main
