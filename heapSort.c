#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para trocar dois elementos
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para manter a propriedade do heap (max-heap)
void heapify(int arr[], int n, int i) {
    int largest = i; // Inicializa o maior como raiz
    int left = 2 * i + 1; // Filho à esquerda
    int right = 2 * i + 2; // Filho à direita

    // Verifica se o filho à esquerda existe e é maior que a raiz
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Verifica se o filho à direita existe e é maior que a raiz
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Se o maior não for a raiz, troca e continua o heapify
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Função principal do heap sort
void heapSort(int arr[], int n) {
    // Construa o heap (rearranja o array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Um a um, remove os elementos do heap
    for (int i = n - 1; i > 0; i--) {
        // Mova a raiz atual para o final
        swap(&arr[0], &arr[i]);

        // Chama heapify na árvore reduzida
        heapify(arr, i, 0);
    }
}

// Função para medir o tempo de execução
double tempoExecucao(void (*func)(int[], int), int arr[], int n) {
    clock_t inicio = clock();
    func(arr, n); // Chama a função de ordenação
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC; // Retorna o tempo decorrido em segundos
}

int main() {
    // Lista de tamanhos de vetores
    int space[] = {100, 500, 1000, 2500, 5000, 7500, 10000, 15000, 20000, 40000, 45000, 50000, 75000, 80000, 90000, 95000, 100000, 500000, 1000000, 50000000, 75000000, 90000000, 100000000};
    int n = sizeof(space) / sizeof(space[0]);

    for (int c = 0; c < n; c++) {
        printf("%d |", space[c]);
        
        for (int i = 0; i < 5; i++) {
            // Cria o vetor de tamanho space[c]
            int* vetor = (int*)malloc(space[c] * sizeof(int));

            // Preenche o vetor com valores aleatórios
            for (int j = 0; j < space[c]; j++) {
                vetor[j] = rand() % 100000;
            }

            // Mede o tempo de execução do heap sort
            double tempo = tempoExecucao(heapSort, vetor, space[c]);

            printf(" %f |", tempo);

            // Libera a memória alocada
            free(vetor);
        }
        printf("\n");
    }

    return 0;
}
