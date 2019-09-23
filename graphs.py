import numpy as np
import matplotlib.pyplot as plt

# objetive function
# ils = np.array([12, 12, 12, 11, 13, 12, 11, 11, 12, 12])
# sa = np.array([11, 9, 10, 10, 9, 11, 10, 10, 10, 10])
# grasp = np.array([7, 7, 7, 7, 7, 7, 7, 7, 7, 7])

# time
ils = np.array([0.029682795, 0.033090071, 0.026068379, 0.026570250, 0.024878934, 0.040473048, 0.044437668, 0.035759985, 0.038910128, 0.036845952])
sa = np.array([0.933908235,0.904623546,0.947468873,0.977612243,1.031136168,1.025418928,1.037667986,1.011749513,0.916951541,0.931902331])
grasp = np.array([0.355543827,0.385749168,0.350252360,0.370451595,0.365448040,0.404355507,0.3660348357,0.3522808707,0.3804527007,0.411762780])

# Calculate the average
ils_mean = np.mean(ils)
sa_mean = np.mean(sa)
grasp_mean = np.mean(grasp)

# Calculate the standard deviation
ils_std = np.std(ils)
sa_std = np.std(sa)
grasp_std = np.std(grasp)

# Define labels, positions, bar heights and error bar heights
labels = ['ILS', 'SA', 'GRASP']
x_pos = np.arange(len(labels))
CTEs = [ils_mean, sa_mean, grasp_mean]
error = [ils_std, sa_std, grasp_std]
cw = [np.amin(ils), np.amin(sa), np.amin(grasp)]

# Build the plot
fig, ax = plt.subplots()
ax.errorbar(x_pos, CTEs,
            yerr=error,
            fmt='ro',
            alpha=0.5,
            ecolor='black',
            capsize=10, marker=".")
ax.set_ylabel('Função objetivo')
ax.set_xticks(x_pos)
ax.set_xticklabels(labels)
ax.set_title('Resultados de cada heurística para a instância p100_24_34, com 10 execuções')
ax.yaxis.grid(True)
for i in range(len(cw)):
    plt.plot(x_pos[i], cw[i], 'bo')

# Save the figure and show
plt.tight_layout()
plt.savefig('error_bars.png')
plt.show()
