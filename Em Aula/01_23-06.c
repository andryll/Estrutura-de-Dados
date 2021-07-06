#include <stdio.h>
#include <stdbool.h>
#define TAMANHO 5


typedef struct{
  //array (objetos / inteiros)
  int array[TAMANHO]; //5 posições na pilha
  //topo
  int topo;//indexacao
  //...informacoes
  int qtdeElementos; //quantidade de elementos na pilha
}PilhaEstatica;

//inicialização da pilha
void iniciaPilhaEstatica(PilhaEstatica *p){
  //...
  p->topo = 0;
  p->qtdeElementos = 0;
}

//vazia
bool estaVaziaPilhaEstatica(PilhaEstatica *p){
  return(p->topo == 0);
}

//cheia
bool estaCheiaPilhaEstatica(PilhaEstatica *p){
  return(p->topo == TAMANHO);
}

int tamanhoPilhaEstatica(PilhaEstatica *p){
  return(p->qtdeElementos);
}

//inserção(emplihar)
void empilharPilhaEstatica(PilhaEstatica *p, int x){
  //Se a pilha nao estiver cheia
  if(estaCheiaPilhaEstatica(p) == false){
    //insiro o novo elemento na posição apontada por topo
    p->array[p->topo] = x;
    //incremento o topo (prox posicao)
    p->topo++;
    //incrementa a qtde de elementos
    p->qtdeElementos++;
  }else{
  //Senao
    //warning (nao foi possivel fazer a inserção)
    printf("Warning: nao foi possivel inserir - pilha cheia\n");
  }//else
}

void imprimirPilhaEstatica(PilhaEstatica *p){
  //for - percorre todas as posicoes validas e preenchidas da pilha (topo)
  printf("Pilha: {");
  for (int i = 0; i < p->topo; i++) {
    printf("%d ",p->array[i]);
  }
  printf("}\n");
}

int desempilharPilhaEstatica(PilhaEstatica *p){
  int ret = -99; //Valor de controle (-99)
  //Se a pilha não estiver vazia
  if(!estaVaziaPilhaEstatica(p)) {
  //tirar o ultimo elemento que foi colocado
  ret = p->array[p->topo - 1];
  //decrementar o topo
  p->topo--;
  //decrementar a quantidade de elementos
  p->qtdeElementos--;
  //senão
}else{
  //Warning
  printf("Warning - nao foi possivel remover, porque a pilha esta vazia!\n");
}
  //retornar o elemento
  return(ret);
}

/*
  inicialização
  inserção
  remoção
  topo
  estavazia
  estacheia
  tamanho
*/

int main(int argc, char const *argv[]) {

  PilhaEstatica pilha;
  //como inicializar?
  iniciaPilhaEstatica(&pilha);
  imprimirPilhaEstatica(&pilha);

  empilharPilhaEstatica(&pilha, 47);
  imprimirPilhaEstatica(&pilha);

  empilharPilhaEstatica(&pilha, 2);
  imprimirPilhaEstatica(&pilha);

  empilharPilhaEstatica(&pilha, 9);
  imprimirPilhaEstatica(&pilha);

  empilharPilhaEstatica(&pilha, 1);
  imprimirPilhaEstatica(&pilha);

  empilharPilhaEstatica(&pilha, 2);
  imprimirPilhaEstatica(&pilha);

  empilharPilhaEstatica(&pilha, 3);
  imprimirPilhaEstatica(&pilha);

  //vazia ou nao
  if(estaVaziaPilhaEstatica(&pilha)){
    printf("Esta vazia!\n");
  }else{
    printf("Nao esta vazia!\n");
  }

  // //cheia ou nao
  // if(estaCheiaPilhaEstatica(&pilha)){
  //   printf("Esta cheia!\n");
  // }else{
  //   printf("Nao esta cheia!\n");
  // }


  printf("Tamanho = %d\n",tamanhoPilhaEstatica(&pilha));

  int aux;
  for (int i = 0; i < 6; i++) {
    aux = desempilharPilhaEstatica(&pilha);
    printf("Elemento retornado = %d\n",aux );
    imprimirPilhaEstatica(&pilha);
  }


  return 0;
}//main
