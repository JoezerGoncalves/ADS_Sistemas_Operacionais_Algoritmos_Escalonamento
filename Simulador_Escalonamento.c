#include <stdio.h>
#include <string.h>
#include <limits.h>  // Necessário para usar INT_MAX

#define QUANTUM 2    // Definição do Quantum fixo

// Definição da estrutura (molde) de um Processo
typedef struct {
    char nome[20];      // Nome do processo (ex: P1, P2)
    int burst;          // Tempo total que o processo precisa na CPU
    int temp_chegada;   // Momento exato em que o processo entra no sistema
    int temp_restante;  // Quanto tempo falta para o processo terminar (vai diminuindo)
    int concluido;      // Flag: 0 = em execução/espera, 1 = já terminou
} Processos;


// FUNÇÃO DO ALGORITMO ROUND ROBIN (Sua implementação)
void algoritmoRoundRobin(Processos p[], int n) {
    int tempo = 0;
    int concluidos = 0;
    int i = 0; // para começar no primeiro indice do vetor

    // Reseta o estado dos processos antes de iniciar
    for(int idx = 0; idx < n; idx++) {
        p[idx].temp_restante = p[idx].burst;
        p[idx].concluido = 0;
    }

    printf("\n=== ROUND ROBIN (QUANTUM = %d) ===\n", QUANTUM);

    while(concluidos < n){ // enquanto o numero de processos for maior do que os processos concluídos o loop continua

        if(p[i].temp_chegada <= tempo && p[i].temp_restante > 0){

            int tempo_executar;
            if(p[i].temp_restante > QUANTUM){
                tempo_executar = QUANTUM;
            }else{
                tempo_executar = p[i].temp_restante;
            }

            printf("Tempo %d: Executando %s por %d\n", tempo, p[i].nome, tempo_executar);

            p[i].temp_restante = p[i].temp_restante - tempo_executar;
            tempo = tempo + tempo_executar;

            if(p[i].temp_restante == 0 && p[i].concluido == 0){
                p[i].concluido = 1;
                concluidos++;
                printf("  %s finalizou.\n", p[i].nome);
            }
        }else{
            // 2. Se o processo ainda não chegou, verificamos se há QUALQUER outro processo pronto
            int nenhum_pronto = 1;
            for(int j = 0; j < n; j++){
                if (p[j].temp_chegada <= tempo && p[j].temp_restante > 0) {
                    nenhum_pronto = 0;
                    break;
                }
            }

            // Se ninguém chegou ainda, a CPU fica ociosa e o relógio avança 1 segundo
            if(nenhum_pronto) {
                printf("Tempo %d: CPU Ociosa\n", tempo);
                tempo++;
                continue; // Volta pro início do while sem avançar o 'i'
            }
        }
        i++;//para passar pro próximo indice
        if (i == n) {
            i = 0;//quando indice chegar na ultima posição do vetor ele volta pro indice 0
        }
    }

    printf("\nTodos os processos foram concluidos.\n");
}


// FUNÇÃO DO ALGORITMO SRT (Shortest Remaining Time - Sua implementação)
void simularSRT(Processos p[], int n) {
    int tempo_atual = 0;
    int concluido = 0;

    // Reseta o estado dos processos (garante que possamos rodar de novo sem dar erro)
    for(int i = 0; i < n; i++) {
        p[i].temp_restante = p[i].burst;
        p[i].concluido = 0;
    }

    printf("\n==================================================\n");
    printf("        TIMELINE DE EXECUCAO - SRT (Passo a Passo)\n");
    printf("==================================================\n");

    // O laço principal roda até que todos os processos sejam concluídos
    while(concluido < n) {
        int ind_menor = -1; // Começa com -1 (significa "nenhum processo escolhido ainda")
        int min_temp_restante = INT_MAX; // Começa com o número mais alto possível para qualquer tempo ser menor que ele

        // 1. BUSCA: Procura quem tem o menor tempo restante
        for(int i = 0; i < n; i++) {
            // O processo pode ser avaliado se: já chegou (chegada <= tempo) E não terminou (concluido == 0)
            if (p[i].temp_chegada <= tempo_atual && p[i].concluido == 0) {

                // Se o tempo restante dele for menor que o menor tempo encontrado até agora
                if (p[i].temp_restante < min_temp_restante) {
                    min_temp_restante = p[i].temp_restante; // Atualiza o menor tempo
                    ind_menor = i; // Guarda a posição (índice) desse processo

                }
                // DESEMPATE: Se os tempos forem iguais, escolhe quem chegou primeiro
                else if (p[i].temp_restante == min_temp_restante) {
                    if (ind_menor == -1 || p[i].temp_chegada < p[ind_menor].temp_chegada) {
                        ind_menor = i;
                    }
                }
            }
        }

        // 2. EXIBIÇÃO: Mostra o cenário na tela
        printf("\n[ Tempo: %d -> %d ]\n", tempo_atual, tempo_atual + 1);

        if (ind_menor == -1) {
            printf("  [CPU] Ociosa\n"); // Nenhum processo disponível
        } else {
            // Imprime o processo escolhido para a CPU
            printf("  [CPU] Executando: %s (Restavam %d unid.)\n", p[ind_menor].nome, p[ind_menor].temp_restante);

            // Imprime a Fila de Prontos (quem está esperando)
            printf("  [Fila de Prontos]: ");
            int primeiro_da_fila = 1; // Variável para colocar vírgula bonita
            int tem_alguem = 0;       // Variável para saber se a fila está vazia

            for (int i = 0; i < n; i++) {
                // Entram na fila: chegaram, não terminaram E não são o que está na CPU
                if (i != ind_menor && p[i].temp_chegada <= tempo_atual && p[i].concluido == 0) {
                    if (!primeiro_da_fila) printf(", ");
                    printf("%s (%d)", p[i].nome, p[i].temp_restante);
                    primeiro_da_fila = 0;
                    tem_alguem = 1;
                }
            }
            if (!tem_alguem) printf("-"); // Se fila vazia, imprime traço
            printf("\n");

            // 3. A CPU trabalha por 1 unidade de tempo
            p[ind_menor].temp_restante--;

            // 4. Se o tempo zerou, processo concluído
            if (p[ind_menor].temp_restante == 0) {
                p[ind_menor].concluido = 1;
                concluido++; // Aumenta o contador para o laço While poder terminar
                printf("  >>> %s CONCLUIDO!\n", p[ind_menor].nome);
            }
        }
        // 5. Avança o tempo do sistema em 1
        tempo_atual++;
    }
    printf("\nSimulacao SRT finalizada! Tempo total: %d unidades.\n", tempo_atual);
}


// FUNÇÃO PRINCIPAL (MAIN)
int main(void) {
    int n, opcao = 0;

    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    Processos processos[n];

    for(int i = 0; i < n; i++){
        printf("\nProcesso %d:\n", i + 1);
        printf("Nome do processo: ");
        scanf("%19s", processos[i].nome);

        printf("Tempo de uso na CPU (Burst): ");
        scanf("%d", &processos[i].burst);

        printf("Tempo de chegada: ");
        scanf("%d", &processos[i].temp_chegada);

        processos[i].temp_restante = processos[i].burst;
        processos[i].concluido = 0;
    }

    // Loop de validação para garantir que o usuário digite apenas 1 ou 2
    while(opcao != 1 && opcao != 2) {
        printf("\nEscolha qual algoritmo quer usar:\n");
        printf("1 para Round Robin\n");
        printf("2 para SRT\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        if(opcao != 1 && opcao != 2) {
            printf("Opcao invalida, escolha novamente!\n");
        }
    }

    // Executa a opção escolhida através do switch
    switch(opcao) {
        case 1:
            algoritmoRoundRobin(processos, n);
            break;
        case 2:
            simularSRT(processos, n);
            break;
    }

    return 0;
}