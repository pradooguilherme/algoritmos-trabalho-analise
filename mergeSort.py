import numpy as np
import time

space = [100, 500, 1000, 2500, 5000, 7500, 10000, 15000, 20000, 40000, 45000, 50000, 75000, 80000, 90000, 95000, 100000, 500000, 1000000, 50000000, 75000000, 90000000, 100000000]
for c in range(0, len(space)):
    print(f'{space[c]} |', end='')
    for i in range(0, 5):
        # Cria um vetor numpy de exemplo
        vetor = np.random.randint(0, 100000, size=space[c])

        # Marca o tempo de início
        inicio = time.time()

        # Ordena o vetor utilizando o numpy sort com merge sort
        vetor_ordenado = np.sort(vetor, kind='mergesort')

        # Marca o tempo de fim
        fim = time.time()

        # Calcula o tempo decorrido
        tempo_decorrido = fim - inicio
        print(f'{tempo_decorrido} |', end='')
    print('')
