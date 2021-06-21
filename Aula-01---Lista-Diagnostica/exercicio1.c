/*
*@file exercicio1.c
*@author Andre Luis de Oliveira
*@date 21/06/2021
*@brief Lista diagn�stica de programa��o

*/

void calculaHorasMinutos(int totalMinutos, int* minutos, int* horas);

int main(){
  //Declarando vari�veis
  int totalMinutos;
  int minutos;
  int horas;
  //Solicitando total de minutos
  printf("Digite a quantidade total de minutos: ");
  scanf("%d",&totalMinutos);
  //Chamando fun��o
  calculaHorasMinutos(totalMinutos,&minutos,&horas);
  //Exibindo resultados
  printf("\nHoras: %d\n",horas);
  printf("Minutos: %d\n",minutos);

  return 0;
}//main


void calculaHorasMinutos(int totalMinutos, int* minutos, int* horas){
  (*horas) = 0;
  (*minutos) = totalMinutos;

  while((*minutos) >= 60){
    (*horas)++;
    (*minutos) = (*minutos) - 60;
  }//while

  return;
}//Fun��o para separar horas e minutos
