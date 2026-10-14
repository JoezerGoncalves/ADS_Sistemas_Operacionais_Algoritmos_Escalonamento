
#include <stdio.h>
#include <string.h>

typedef struct {

    char nome[20];      
    int burst;//Temp de uso da CPU
    int temp_chegada;   
    int temp_restante;  
    int concluido;      

}Processos;

void algoritmoRoundRobin(Processos p[], int n) {
    int tempo = 1;// inicia em 1 porque o tempo de chegada começa em 1
    int concluidos = 0;
    int i = 0; // para começar no primeiro indice do vetor

    printf("\n=== ROUND-ROBIN (QUANTUM = %d) ===\n", QUANTUM);

    while(concluidos < n){ // enquanto o numero de processos for maior do que os processos concluídos o loop continua

        if(p[i].temp_chegada <= tempo && p[i].temp_restante > 0){

            int tempo_executar;
            if(p[i].temp_restante > QUANTUM){
                tempo_executar = QUANTUM;
            }else{
                tempo_executar = p[i].temp_restante;
            }

            printf("Tempo %d: Executando %s por %d\n",tempo, p[i].nome, tempo_executar);

            p[i].temp_restante = p[i].temp_restante - tempo_executar;
            tempo = tempo + tempo_executar;

            if(p[i].temp_restante == 0){
                p[i].concluido = 1;
                concluidos++;
                printf("  %s finalizou.\n", p[i].nome);
            }
        }
        i++;//para passar pro próximo indice
        if (i == n) {
            i = 0;//quando indice chegar na ultima posição do vetor ele volta pro indice 0
        }
    }

    printf("\nTodos os processos foram concluidos.\n");
}

int main(void){
    int n;

    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    Processos processos[n];

    for(int i = 0; i < n; i++){
        printf("\nProcesso %d:\n", i + 1);
        printf("Nome do processo: ");
        scanf("%19s", processos[i].nome);

        printf("Tempo de uso na CPU : ");
        scanf("%d", &processos[i].burst);

        processos[i].temp_chegada = i + 1;
        processos[i].temp_restante = processos[i].burst;
        processos[i].concluido = 0;
    }

    printf("\nProcessos cadastrados:\n");
    for(int i = 0; i < n; i++){
        printf("Nome: %s / Chegada: %d / Restante: %d\n",
            processos[i].nome, processos[i].temp_chegada, processos[i].temp_restante);
    }

    algoritmoRoundRobin(processos, n);

    return 0;
}
