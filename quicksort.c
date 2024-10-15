#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // Para usar gettimeofday
#include <time.h>     // Para usar time()

#define NUM_EXECUCOES 5 // Número de execuções para cada tamanho de vetor

unsigned long int comparacoes = 0; // Alterado para unsigned long int

// Função de comparação para qsort (conta as comparações)
int compare(const void *a, const void *b)
{
    comparacoes++; // Conta cada comparação
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
    {
        return 0;
    }
    else if (int_a < int_b)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Função que preenche o vetor com números aleatórios
void preencherVetorAleatorio(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Preenche o vetor com números aleatórios entre 0 e 999
        arr[i] = rand() % 1000;
    }
}

// Função que preenche o vetor de forma ordenada crescente
void preencherVetorOrdenado(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i; // Preenche o vetor com valores de 0 até n-1
    }
}

// Função que preenche o vetor de forma ordenada decrescente
void preencherVetorOrdenadoDecrescente(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - 1 - i; // Preenche o vetor com valores de n-1 até 0
    }
}

int main()
{
    // Exemplo de tamanhos de vetor
    int size[] = {
        100,
        500,
        1000,
        2500,
        5000,
        7500,
        10000,
        15000,
        20000,
        40000,
        45000,
        50000,
        60000,
        75000,
        80000,
        90000,
        95000,
        100000,
        500000,
        1000000,
        50000000,
        75000000,
        90000000,
        100000000, 500000000};

    // Variáveis para medir o tempo
    struct timeval inicio, fim;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Exibe cabeçalho da tabela
    printf("Estatísticas de cada execução:\n");
    printf("Tamanho | Comparações | Tempo (s)\n");
    printf("-------------------------------------\n");

    // Executar várias vezes para obter a média
    for (int i = 0; i < sizeof(size) / sizeof(size[0]); i++)
    {
        // Variáveis para calcular a média para cada tamanho
        unsigned long int comparacoes_total = 0;
        long long tempo_total = 0; // Tempo total em microssegundos

        for (int j = 0; j < NUM_EXECUCOES; j++)
        {
            int *arr = (int *)malloc(size[i] * sizeof(int)); // Aloca memória para o vetor
            if (arr == NULL)
            {
                perror("Falha na alocação de memória");
                exit(EXIT_FAILURE);
            }

            // Preencher vetor ordenado
            preencherVetorOrdenadoDecrescente(arr, size[i]);

            // Resetando contagem de comparações para cada execução
            comparacoes = 0;

            gettimeofday(&inicio, NULL);

            // Executa o qsort
            qsort(arr, size[i], sizeof(int), compare);

            // Pega o tempo após o qsort terminar
            gettimeofday(&fim, NULL);

            // Calcula o tempo de execução em microssegundos
            long long tempo_execucao = (fim.tv_sec - inicio.tv_sec) * 1000000LL + (fim.tv_usec - inicio.tv_usec);
            tempo_total += tempo_execucao;
            comparacoes_total += comparacoes; // Adiciona as comparações

            // Exibe as estatísticas para a execução atual
            printf("%7d | %12lu | %11.6f\n", size[i], comparacoes, tempo_execucao / 1000000.0); // Exibe em segundos

            free(arr); // Libera a memória alocada
        }

        // Calcula médias para as cinco execuções
        printf("Média   | %12lu | %11.6f\n", comparacoes_total / NUM_EXECUCOES, tempo_total / (NUM_EXECUCOES * 1000000.0)); // Exibe em segundos
        printf("-------------------------------------\n");
    }

    return 0;
}
