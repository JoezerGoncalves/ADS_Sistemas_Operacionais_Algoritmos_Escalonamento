#include <limits.h>
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

    printf("Quantos processos deseja simular: ");
    scanf(" %d",&n);

    Processos p[n]; //vetor de processos com tamanho informado

    for(int i = 0; i < n; i++) {

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
    //  --- Simulação da linha do tempo ---

    printf("\n==================================================\n");
    printf("        TIMELINE DE EXECUCAO - SRT (Passo a Passo)\n");
    printf("==================================================\n");

    // Variáveis para controlar o tempo e quantos processos já terminaram
    int tempo_atual = 0;
    int concluido = 0;

    while(concluido < n) {

        int ind_menor = -1; // variavel para guardar a posição do vetor(-1 pois nao existe nenhum)
        int min_temp_restante = INT_MAX; //variavel começa com o maior nº possivel  para que qualquer tempo seja maior que ele

        for(int i = 0; i < n; i++) {

                if (p[i].temp_chegada <= tempo_atual && p[i].concluido == 0) {

                    if (p[i].temp_restante < min_temp_restante) {

                        min_temp_restante = p[i].temp_restante;
                        ind_menor = i;

                    }else if (p[i].temp_restante == min_temp_restante) {
                        if (ind_menor == -1 || p[i].temp_chegada < p[ind_menor].temp_chegada) {
                            ind_menor = i;
                        }
                    }

                }
            }



    }


    return 0;
}