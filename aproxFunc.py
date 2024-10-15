import numpy as np
from scipy.optimize import curve_fit

import matplotlib.pyplot as plt

# Função que queremos ajustar: O(n * log(n))
def func(x, a, b):
    return a*x*np.log(x) + b

# Gerando alguns dados de exemplo
x_data = np.array([100,
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
100000000])
y_data = np.array([0.0032,
0.0168,
0.0382,
0.0996,
0.2216,
0.5054,
0.3594,
0.4788,
0.5444,
1.0774,
1.0268,
1.1386,
1.4042,
1.8564,
2.0012,
2.1866,
2.3228,
2.4490,
13.8492,
28.5608,
1.749006000,
3.327362000,
4.034463000,
4.828876000,])

# Ajustando a função aos dados
popt, pcov =curve_fit(func, x_data, y_data)

# Parâmetros ajustados
a, b= popt
print(a, ' | ', b, ' | ')

# Função linear para comparação: f(x) = y
def linear_func(x, c, d):
    return c * x + d 

# Ajustando a função linear aos dados
popt_linear, _ = curve_fit(linear_func, x_data, y_data)

# Gerando novos dados para além dos passados no eixo x_data
x_new = np.linspace(min(x_data), max(x_data) * 1.5, 100)

# Plotando a função ajustada para os novos dados
plt.plot(x_new, func(x_new, *popt), color='green', linestyle='-', label='Quick Sort$')
plt.plot(x_new, linear_func(x_new, *popt_linear), color='purple', linestyle='--', label='Projeção: $f(x) = y$')
# Plotando a função linear ajustada
plt.plot(x_data, linear_func(x_data, *popt_linear), color='blue', linestyle='--', label='Ajuste: $f(x) = y$')
# Plotando os dados e a função ajustada
plt.scatter(x_data, y_data, label='Dados')
plt.plot(x_data, func(x_data, *popt), color='red', label='Ajuste: $O(n^2)$')
plt.xlabel('n')
plt.ylabel('f(n)')
#plt.ylim(min(y_data) * 0.1, max(y_data) * 1.0)
plt.legend()
plt.title('$Quick Sort Pior Caso$')
plt.savefig('aproxLogN.png')