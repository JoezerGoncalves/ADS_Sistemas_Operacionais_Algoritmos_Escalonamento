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

    printf("Quntos processos deseja simular: ");
    scanf(" %d",&n);

    Processos p[n];

    for(int i=0;i<n;i++) {

        printf("Processo: %d\n",i+1);
        printf("Nome do processo: ");
        scanf(" %s",&p[i].nome);
        printf("Tempo de burst(Uso da CPU): ");
        scanf(" %d",&p[i].burst);
        printf("Tempo de chegada: ");
        scanf(" %d",&p[i].temp_chegada);

        p[i].temp_restante = p[i].burst;
        p[i].concluido = 0;
    }


    return 0;
}