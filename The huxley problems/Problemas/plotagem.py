import matplotlib.pyplot as plt
import numpy as np

# Parâmetros
theta = -np.pi / 6  # -π/6 radianos
r = 1  # Raio

# Criar figura e eixos polares
fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})

# Plotar o ponto
ax.plot(theta, r, 'ro')  # 'ro' = marcador vermelho (red circle)

# Ajustar o gráfico
ax.set_title(r'Coordenada Polar: $\theta = -\frac{\pi}{6}$', va='bottom')
ax.set_rmax(1.5)  # Ajusta o máximo do eixo radial

plt.show()