#include <stdio.h>
#include <stdlib.h>//true / false
#include <stdbool.h>//malloc / sizeof / free

//NoPilha -> PtrNoPilha
typedef struct NoPilha *PtrNoPilha;

// NoPilha
typedef struct NoPilha{
  // int x (chave)
  int x;
  // prt -> proximo
  PtrNoPilha proximo;
}NoPilha;

// Pilha Dinamica
typedef struct{
  // ptr para o primeiro elemento (mais recente)
  PtrNoPilha topo;
  // contagem do numero de elementos dentro da pilha
  int qtdeElementos;
}PilhaDinamica;

//inicializar
void iniciaPilhaDinamica(PilhaDinamica *p){
  // iniciando o ptr topo para nulo
  p->topo = NULL;
  //iniciamos o contador para zero
  p -> qtdeElementos = 0;
}

int tamanhoPilhaDinamica(PilhaDinamica *p){
  return (p->qtdeElementos);
}

// esta vazia
bool estaVaziaPilhaDinamica(PilhaDinamica *p){
  // 1. qtde == 0
  // return(p->qtdeElementos == 0);
  // 2. topo = NULL
  return(p->topo == NULL);
}

void empilhaPilhaDinamica(PilhaDinamica *p, int x){

    // criar um novo n�, alocar memoria dele
    PtrNoPilha aux;
    aux = (PtrNoPilha) malloc(sizeof(PtrNoPilha));
    // copiar o dado para o novo n�
    aux->x = x;
    // proximo do novo n�, aponta pro topo
    aux->proximo = p->topo;
    // topo aponta pro novo n�
    p->topo = aux;
    // contador incrementa(qtde)
    p->qtdeElementos++;
}

void imprimirPilhaDinamica(PilhaDinamica *p){
  printf("Pilha = {");
  // come�ar no topo
  // pegando o proximo atual
  // ate chegar no NULL
  // em cada uma das situacoes (mostra o valor atual)
  PtrNoPilha temp;

  for(temp = p->topo; temp != NULL; temp = temp->proximo){
    printf("%d ",temp->x);
  }
  printf("}\n");
}

// remover
int desempilhaPilhaDinamica(PilhaDinamica *p){
  int ret = -99;

  // Se a pilha n�o est� vazia, eu posso remover

  if(!estaVaziaPilhaDinamica(p)){
  // criar ptr auxiliar
  PtrNoPilha aux;
  // ptr recebe o valor topo
  aux = p->topo;
  // copiar o dado pra ser retornado
  ret = aux->x;
  // atualiza os ponteiros
  // topo aponta para o topo->proximo
  p->topo = p->topo->proximo;
  // desaloca a memoria
  free(aux);
  // decrementa o contador
  p->qtdeElementos--;
  // Senao -> warning
}else{
  printf("Warning: n�o foi poss�vel remover\n");
}
  return(ret);
}

// destruir (homework)
void destruirPilhaDinamica(PilhaDinamica *p){
  if(!estaVaziaPilhaDinamica(p)){
    // criar ptr auxiliar
    PtrNoPilha aux;
    //repete o eliminar enquanto o topo n�o for NULL
    while(p->topo != NULL){
      // ptr recebe o valor topo
      aux = p->topo;

      // topo aponta para o topo->proximo
      p->topo = p->topo->proximo;
      // desaloca a memoria
      free(aux);
      // decrementa o contador
      p->qtdeElementos--;
    };
    printf("Pilha destru�da com sucesso!\n");
  // Senao -> warning
  }else{
    printf("Warning: n�o foi poss�vel destruir\n");
  }
}


// consultar o topo (homework)
void consultarTopoPilhaDinamica(PilhaDinamica *p){
  if(!estaVaziaPilhaDinamica(p)){
    printf("Topo: %d\n",p->topo->x );
  }else{
    printf("Warning: a pilha est� vazia\n");
  }
}


int main(int argc, char const *argv[]) {

  PilhaDinamica pilha;
  //inicializar a estrutura?
  iniciaPilhaDinamica(&pilha);
  imprimirPilhaDinamica(&pilha);

  empilhaPilhaDinamica(&pilha, 1);
  imprimirPilhaDinamica(&pilha);

  empilhaPilhaDinamica(&pilha, 2);
  imprimirPilhaDinamica(&pilha);

  empilhaPilhaDinamica(&pilha, 3);
  imprimirPilhaDinamica(&pilha);

  if(!estaVaziaPilhaDinamica(&pilha)){
    printf("nao esta vazia Rogerinho!\n");
  }

  consultarTopoPilhaDinamica(&pilha);

  printf("Tamanho = %d\n",tamanhoPilhaDinamica(&pilha));

  destruirPilhaDinamica(&pilha);
  imprimirPilhaDinamica(&pilha);

  printf("issae\n");
  return 0;
}
