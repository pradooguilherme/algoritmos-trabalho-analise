#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função de ordenação por seleção
void selectionSort(int arr[], int n, unsigned long int *swapCount) {
    int i, j, minIdx;
    *swapCount = 0; // Inicializa o contador de trocas

    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Troca o elemento mínimo encontrado com o elemento na posição i
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            (*swapCount)++; // Incrementa o contador de trocas
        }
    }
}

// Função para gerar um array aleatório
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000; // Preenche com números aleatórios
    }
}

int main() {
    srand(time(0)); // Inicializa o gerador de números aleatórios

    int sizes[] = {11111, 12457, 15678, 18240, 19202, 22156, 33400, 40000, 55600, 67890, 77800, 90003, 100234};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        printf("Ordenando array de tamanho %d:\n", n);

        for (int j = 0; j < 5; j++) {
            // Aloca memória para o array
            int *arr = (int *)malloc(n * sizeof(int));
            if (arr == NULL) {
                perror("Erro ao alocar memória");
                return EXIT_FAILURE;
            }
            unsigned long int swapCount = 0; // Contador de trocas

            // Gera um array aleatório
            generateRandomArray(arr, n);

            // Medir o tempo de execução
            clock_t start = clock();
            selectionSort(arr, n, &swapCount);
            clock_t end = clock();

            double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Tempo de execução na %dª vez: %f segundos, Trocas: %lu\n", j, time_taken, swapCount);

            // Libera a memória alocada
            free(arr);
        }

        printf("=======================================\n");
    }

    return 0;
}