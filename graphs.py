import numpy as np
import matplotlib.pyplot as plt

# objetive function
ils = np.array([27, 27, 24, 26, 22, 23, 27, 27, 26, 27])
sa = np.array([27, 27, 27, 27, 27, 27, 27, 27, 27, 25])
grasp = np.array([15, 14, 14, 13, 16, 14, 17, 13, 15, 15, 15])

# time
#ils = np.array([0.623047913,0.615358620,0.617936913,0.850333418,0.617621557,0.618744397,0.678033620,0.688204204,0.688279620,0.683572074])
#sa = np.array([19.498041826,19.730346615,20.136175567,19.628962226,19.816157062,20.014666675,20.230360326,19.335969313,20.097981627,19.345286029])
#grasp = np.array([16.561013909,14.321600927,16.627203014,16.038694689,14.509302808,15.333934729,15.238818004,16.441438305,16.369450682,16.429305464])

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
ax.set_title('Resultados de cada heurística para a instância will57,\n com 10 execuções')
#ax.set_title('Tempo médio cada heurística para a instância Grid9x18')
ax.yaxis.grid(True)
for i in range(len(cw)):
    plt.plot(x_pos[i], cw[i], 'bo')

# Save the figure and show
plt.tight_layout()
plt.savefig('hb_obj.png')
plt.show()
