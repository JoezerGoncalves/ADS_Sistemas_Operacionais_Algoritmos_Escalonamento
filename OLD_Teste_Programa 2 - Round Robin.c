#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    char nome[10];
    int chegada;
    int burst;
    int restante;
    int concluido;
} Processo;

void mostrarEstado(Processo p[], int n, int tempo, int executando)
{
    printf("\n====================================\n");
    printf("Tempo %d\n", tempo);

    printf("Prontos: ");

    int encontrou = 0;
	
	int i;
    for (i = 0; i < n; i++)
    {
        if (p[i].chegada <= tempo &&
            p[i].restante > 0 &&
            i != executando)
        {
            printf("%s(rest=%d) ",
                   p[i].nome,
                   p[i].restante);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum");

    printf("\n");

    if (executando != -1)
    {
        printf("CPU: %s(rest=%d)\n",
               p[executando].nome,
               p[executando].restante);
    }
    else
    {
        printf("CPU: Ociosa\n");
    }
}

int main()
{
    Processo p[MAX];

    int fila[100];
    int inicio = 0;
    int fim = 0;

    int n;
    int quantum;

    printf("Quantidade de processos: ");
    scanf("%d", &n);

    printf("Quantum: ");
    scanf("%d", &quantum);
	
	int i;
    for (i = 0; i < n; i++)
    {
        printf("\nProcesso %d\n", i + 1);

        printf("Nome: ");
        scanf("%s", p[i].nome);

        printf("Tempo de chegada: ");
        scanf("%d", &p[i].chegada);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].restante = p[i].burst;
        p[i].concluido = 0;
    }

    int tempo = 0;
    int finalizados = 0;

    while (finalizados < n)
    {
        int i;
		for (i = 0; i < n; i++)
        {
            if (p[i].chegada == tempo)
            {
                fila[fim++] = i;
            }
        }

        if (inicio == fim)
        {
            mostrarEstado(p, n, tempo, -1);
            tempo++;
            continue;
        }

        int atual = fila[inicio++];

        int execucao =
            (p[atual].restante < quantum)
            ? p[atual].restante
            : quantum;

        int q;
		for (q = 0; q < execucao; q++)
        {
            mostrarEstado(p, n, tempo, atual);

            p[atual].restante--;
            tempo++;
			
			int i;
			for (i = 0; i < n; i++)
            {
                if (p[i].chegada == tempo)
                {
                    fila[fim++] = i;
                }
            }
        }

        if (p[atual].restante > 0)
        {
            fila[fim++] = atual;
        }
        else
        {
            p[atual].concluido = 1;
            finalizados++;
        }
    }

    printf("\nTodos os processos finalizaram.\n");

    return 0;
}
