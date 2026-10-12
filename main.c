#include <stdio.h>
#include <string.h>

typedef struct {

    char nome[20];      //Nome do processo
    int burst;          //Temp de uso da CPU
    int temp_chegada;   //Temp de chegada
    int temp_restante;  //Temp de preocessamento restante
    int concluido;      //Marcador para saber se processo finalizou

}Processos;

int  main(void) {
    int n;

    printf("Quntos processos deseja simular: \n");
    scanf("%d",&n);

    Processos p[n];

    for(int i=0;i<n;i++) {
        printf("Process: %d",i+1);




    }


    return 0;
}