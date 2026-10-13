
#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct {

    char nome[20];      //Nome do processo
    int burst;          //Temp de uso da CPU
    int temp_chegada;   //Temp de chegada
    int temp_restante;  //Temp de preocessamento restante
    int concluido;      //Marcador para saber se processo finalizou

}Processos;

int main(void) {
    int n, tq;
    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    Processos processos[n];

    for (int i = 0; i < n; i++) {
        printf("Processo %d:\n", i + 1);
        printf("Nome do processo: ");
        scanf("%19s", processos[i].nome);

        printf("Tempo de uso da CPU(burst time)");
        scanf("%d", &processos[i].burst);

        printf("Tempo de chegada: ");
        scanf("%d", &processos[i].temp_chegada);

        processos[i].temp_restante = processos[i].burst;
        processos[i].concluido = 0;
    }

    printf("Processos cadastrados:\n");
    for (int i = 0; i < n; i++) {
        printf("Processo: %d / Nome: %s / Chegada: %d / Restante %d / Concluido: %d\n",
            i+1, processos[i].nome, processos[i].temp_chegada, processos[i].temp_restante,
            processos[i].concluido);
    }
    
}
