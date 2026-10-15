#include <limits.h>  // Necessário para usar INT_MAX (o maior número inteiro possível)
#include <stdio.h>
#include <string.h>

// Definição da estrutura (molde) de um Processo
typedef struct {
    char nome[10];      // Nome do processo (ex: P1, P2)
    int burst;          // Tempo total que o processo precisa na CPU
    int temp_chegada;   // Momento exato em que o processo entra no sistema
    int temp_restante;  // Quanto tempo falta para o processo terminar (vai diminuindo)
    int concluido;      // Flag: 0 = em execução/espera, 1 = já terminou
} Processo;


// FUNÇÃO AUXILIAR DO ROUND ROBIN: Acha o próximo processo em ordem circular

int achar_proximo_rr(Processo p[], int n, int tempo_atual, int atual) {
    // Se 'atual' for -1 (ninguém na CPU), começamos a busca do índice 0.
    // Senão, começamos a buscar a partir do próximo processo (atual + 1).
    int inicio;
    if (atual == -1) {
        inicio = 0;
    } else {
        inicio = atual;
    }

    // Laço que dá uma "volta completa" no vetor de processos
    for (int i = 1; i <= n; i++) {
        // A matemática do módulo (%) faz a fila ser circular.
        // Se o atual for o último, ele volta para o 0.
        int idx = (inicio + i) % n;

        // Se o processo achado já chegou e não terminou, ele é o próximo!
        if (p[idx].temp_chegada <= tempo_atual && p[idx].concluido == 0) {
            return idx;
        }
    }
    return -1; // Se ninguém foi achado, retorna -1 (CPU Ociosa)
}


// FUNÇÃO DO ALGORITMO SRT (Shortest Remaining Time)

void simularSRT(Processo p[], int n) {
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

            // 3.  A CPU trabalha por 1 unidade de tempo
            p[ind_menor].temp_restante--;

            // 4. Se o tempo zerou, processo concluído
            if (p[ind_menor].temp_restante == 0) {
                p[ind_menor].concluido = 1;
                concluido++; // Aumenta o contador para o laço While poder terminar
                printf("  >>> %s CONCLUIDO!\n", p[ind_menor].nome);
            }
        }
        // 5.  Avança o tempo do sistema em 1
        tempo_atual++;
    }
    printf("\nSimulacao SRT finalizada! Tempo total: %d unidades.\n", tempo_atual);
}


// FUNÇÃO DO ALGORITMO ROUND ROBIN

void simularRoundRobin(Processo p[], int n, int quantum) {
    int tempo_atual = 0;
    int concluido = 0;
    int idx_atual = -1;     // Guarda quem está na CPU
    int tempo_no_cpu = 0;   // Conta quanto tempo o processo atual já usou a CPU neste ciclo

    // Reseta o estado dos processos
    for(int i = 0; i < n; i++) {
        p[i].temp_restante = p[i].burst;
        p[i].concluido = 0;
    }

    printf("\n==================================================\n");
    printf("       TIMELINE DE EXECUCAO - ROUND ROBIN (Q=%d)\n", quantum);
    printf("==================================================\n");

    while(concluido < n) {
        // 1. Quando a CPU está ociosa, OU o quantum estourou, OU o processo atual acabou
        if (idx_atual == -1 || tempo_no_cpu == quantum || p[idx_atual].concluido == 1) {

            // Chama a função auxiliar para achar o próximo da fila circular
            int novo_idx = achar_proximo_rr(p, n, tempo_atual, idx_atual);

            if (novo_idx != -1) {
                // Se trocou de processo, reseta o contador de tempo na CPU
                if (novo_idx != idx_atual) tempo_no_cpu = 0;
                idx_atual = novo_idx;
            } else {
                idx_atual = -1; // CPU Ociosa
            }
        }

        // 2. EXIBIÇÃO: Mostra o cenário
        printf("\n[ Tempo: %d -> %d ]\n", tempo_atual, tempo_atual + 1);

        if (idx_atual == -1) {
            printf("  [CPU] Ociosa\n");
        } else {
            // Mostra quem está na CPU. O formato "CPU: 2/4" mostra que ele está no segundo tick de 4 possíveis do quantum
            printf("  [CPU] Executando: %s (Restam %d unid. no total. CPU: %d/%d)\n",
                   p[idx_atual].nome, p[idx_atual].temp_restante, tempo_no_cpu + 1, quantum);

            // Impressão da Fila de Prontos (idêntica ao SRT)
            printf("  [Fila de Prontos]: ");
            int primeiro_da_fila = 1;
            int tem_alguem = 0;
            for (int i = 0; i < n; i++) {
                if (i != idx_atual && p[i].temp_chegada <= tempo_atual && p[i].concluido == 0) {
                    if (!primeiro_da_fila) printf(", ");
                    printf("%s (%d)", p[i].nome, p[i].temp_restante);
                    primeiro_da_fila = 0;
                    tem_alguem = 1;
                }
            }
            if (!tem_alguem) printf("-");
            printf("\n");

            // 3. A CPU trabalha por 1 unidade
            p[idx_atual].temp_restante--;
            tempo_no_cpu++; // Soma 1 no tempo que ele está usando o quantum

            // 4. Se o tempo restante zerou
            if (p[idx_atual].temp_restante == 0) {
                p[idx_atual].concluido = 1;
                concluido++;
                printf("  >>> %s CONCLUIDO!\n", p[idx_atual].nome);
            }
        }
        // 5.Avança o tempo
        tempo_atual++;
    }
    printf("\nSimulacao Round Robin finalizada! Tempo total: %d unidades.\n", tempo_atual);
}


int main(void) {
    int n, opcao, quantum;

    printf("Bem-vindo ao Simulador de Escalonamento de Processos!\n\n");

    // 1. Pergunta o algoritmo ANTES de pedir os dados
    printf("Escolha o algoritmo que deseja simular:\n");
    printf("1 - SRT (Shortest Remaining Time)\n");
    printf("2 - Round Robin\n");
    printf("Opcao: ");
    scanf(" %d", &opcao);

    if (opcao != 1 && opcao != 2) {
        printf("Opcao invalida! Encerrando.\n");
        return 1; // Encerra o programa com erro
    }

    // 2. Quantos processos e os dados de cada um
    printf("\nQuantos processos deseja simular: ");
    scanf(" %d", &n);

    Processo p[n]; // Cria o vetor de processos

    for(int i = 0; i < n; i++) {
        printf("\n--- Processo: %d ---\n", i+1);
        printf("Nome do processo (ex: P1): ");
        scanf(" %s", p[i].nome); // Sem o '&' porque string em C já é um ponteiro
        printf("Tempo de uso da CPU (Burst time): ");
        scanf(" %d", &p[i].burst);
        printf("Tempo de chegada (Arrival time): ");
        scanf(" %d", &p[i].temp_chegada);
    }

    // 3.  Chama a função escolhida no menu
    switch(opcao) {
        case 1:
            simularSRT(p, n); // Se 1, roda SRT
            break;
        case 2:
            // Se 2, pede o parâmetro extra (Quantum) e roda Round Robin
            printf("\nDigite o valor do QUANTUM (tempo maximo de CPU por ciclo): ");
            scanf(" %d", &quantum);
            simularRoundRobin(p, n, quantum);
            break;
    }

    return 0; // Fim do programa com sucesso
}