/*
*@file exercicio4.c
*@author Andre Luis de Oliveira
*@date 21/06/2021
*@brief Lista diagn�stica de programa��o

*/

void preencheVetor(int* vetor, int n);

int main(){
  //Declarando vari�veis

  int n;
  int *vetor;
  //Solicitando tamanho do vetor
  printf("Digite o tamanho do vetor: ");
  do {
    scanf("%d",&n);
    if(n<=0)
      printf("So s�o aceitos valores positivos! Digite novamente: ");
  }while(n<=0);

  //Alocando vetor do tamanho escolhido
  vetor = (int*) calloc(n, sizeof(int));

  //Chamando fun��o para preencher vetor
  preencheVetor(vetor, n);

  //Exibindo vetor
  printf("\nVetor Criado: {");
  //Loop para exibir todos os valores
  for (int i = 0; i < n; i++) {
    if(i != n - 1)
      printf("%d, ", vetor[i]);
    else
      printf("%d}.\n\n", vetor[i]);
  }//for

  //Liberando memoria do vetor
  free(vetor);

  return 0;
}//main

void preencheVetor(int* vetor, int n){
  printf("\nPor favor digite os valores desejados do vetor.\n");
  //Loop para percorrer todas as posi��es
  for (int i = 0; i < n; i++) {
    printf("Posicao %d: ", i + 1);
    scanf("%d",&vetor[i]);
  }//for
  return;
}//Fun��o para preencher o vetor
