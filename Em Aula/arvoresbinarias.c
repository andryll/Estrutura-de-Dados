#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Tipos
//-----------------------------------------------------------------------------

//NoArvore* PtrNoArvore -> PtrNoArvore* (**NoArvore)
typedef struct NoArvore* PtrNoArvore;

// NoArvore (struct)
typedef struct NoArvore{
  // info
  int x;
  // ponteiro p filho esquerda
  PtrNoArvore esquerda;
  // ponteiro p filho direita
  PtrNoArvore direita;
} NoArvore;

//-----------------------------------------------------------------------------
// Fun��es
//-----------------------------------------------------------------------------

// inicia arvore
void iniciaArvore(PtrNoArvore *node){
  (*node) = NULL;
}// Fun��o para iniciar a �rvore

// esta vazia
bool estaVaziaArvore(PtrNoArvore *node){
  return (*node) == NULL;
}// Fun��o para verificar se est� vazia

// inserir
bool insereArvore(PtrNoArvore *node, int x){
  // criterio de parada (sucesso)
  if((*node) == NULL){
    (*node) = (PtrNoArvore)malloc(sizeof(NoArvore));
    (*node)->x = x;
    (*node)->direita = (*node)->esquerda = NULL;
    return true;
  }// elemento inserido com sucesso

  // criterio de parada fracasso (false)
  if((*node) -> x == x){
    printf("Erro. Chave j� existente.\n");
    return false;
  }// elemento ja existente

  // percorre a arvore (via recurs�o)
  if(x > (*node) -> x){
    // valor > valor node->direita
    return (insereArvore(&(*node)->direita, x));
  }else{
    // valor < valor node->esquerda
    return (insereArvore(&(*node)->esquerda, x));
  }// recurs�o
}// Fun��o recursiva para inserir elemento na �rvore


// remocao
// destrutor
// tamanho
// min/max

// preOrdem
void percursoPreOrdem(PtrNoArvore *node){
  if((*node) == NULL) return;
  //imprime o valor do no
  printf("%d ",(*node)->x);
  // recursivo no esquerda
 percursoPreOrdem(&(*node)->esquerda);
 // recursivo no direita
 percursoPreOrdem(&(*node)->direita);
}//Fun��o recursiva pre ordem de impressao


// posOrdem
void percursoPosOrdem(PtrNoArvore *node){
  if((*node) == NULL) return;
  // recursivo no esquerda
  percursoPosOrdem(&(*node)->esquerda);
  // recursivo no direita
  percursoPosOrdem(&(*node)->direita);
  //imprime o valor do no
  printf("%d ",(*node)->x);
}//Fun��o recursiva pos ordem de impressao

// emOrdem
void percursoEmOrdem(PtrNoArvore *node){
  if((*node) == NULL) return;
  // recursivo no esquerda
  percursoEmOrdem(&(*node)->esquerda);
  //imprime o valor do no
  printf("%d ",(*node)->x);
  // recursivo no direita
  percursoEmOrdem(&(*node)->direita);
}//Fun��o recursiva Em ordem de impressao

// emOrdemContraria
void percursoEmOrdemContraria(PtrNoArvore *node){
  if((*node) == NULL) return;
  // recursivo no direita
  percursoEmOrdemContraria(&(*node)->direita);
  //imprime o valor do no
  printf("%d ",(*node)->x);
  // recursivo no esquerda
  percursoEmOrdemContraria(&(*node)->esquerda);
}//Fun��o recursiva Em ordem Contraria de impressao

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int main(int argc, char const *argv[]) {

  PtrNoArvore raiz;

  //inicializacao
  iniciaArvore(&raiz);

  if(estaVaziaArvore(&raiz)){
    printf("Arvore Vazia\n");
  }// if

  insereArvore(&raiz, 5);
  insereArvore(&raiz, 4);
  insereArvore(&raiz, 3);
  insereArvore(&raiz, 2);
  insereArvore(&raiz, 7);
  insereArvore(&raiz, 6);
  insereArvore(&raiz, 8);
  insereArvore(&raiz, 9);

  if(!estaVaziaArvore(&raiz)){
    printf("Arvore nao Vazia\n");
  }// if

  printf("Percurso PreOrdem = ");
  percursoPreOrdem(&raiz);
  printf("\n");

  printf("Percurso PosOrdem = ");
  percursoPosOrdem(&raiz);
  printf("\n");

  printf("Percurso EmOrdem = ");
  percursoEmOrdem(&raiz);
  printf("\n");

  printf("Percurso EmOrdem2 = ");
  percursoEmOrdemContraria(&raiz);
  printf("\n");

  return 0;
}//main
