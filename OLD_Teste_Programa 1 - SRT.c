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

void imprimirEstado(Processo p[], int n, int tempo, int executando)
{
    printf("\n====================================\n");
    printf("Tempo %d\n", tempo);

    printf("Prontos: ");

    int encontrou = 0;

    int i;
	for (i = 0; i < n; i++)
    {
        if (p[i].chegada <= tempo &&
            !p[i].concluido &&
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
        printf("CPU: %s (rest=%d)\n",
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

    int n;

    printf("Quantidade de processos: ");
    scanf("%d", &n);
    
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

    int finalizados = 0;
    int tempo = 0;

    while (finalizados < n)
    {
        int menor = -1;
		
		int i;
        for (i = 0; i < n; i++)
        {
            if (p[i].chegada <= tempo &&
                p[i].restante > 0)
            {
                if (menor == -1 ||
                    p[i].restante < p[menor].restante)
                {
                    menor = i;
                }
            }
        }

        imprimirEstado(p, n, tempo, menor);

        if (menor != -1)
        {
            p[menor].restante--;

            if (p[menor].restante == 0)
            {
                p[menor].concluido = 1;
                finalizados++;
            }
        }

        tempo++;
    }

    printf("\nTodos os processos finalizaram.\n");

    return 0;
}
