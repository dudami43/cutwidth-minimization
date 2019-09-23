import pandas as pd

arq = open('resultados finais/grasp.txt', 'r')
lines = arq.readlines()

nomes, valores_grasp, tempos_grasp = list(), list(), list()
for i in range(len(lines)//14):
    nomes.append(lines[i*14])
    final = lines[i*14 + 12].split(',')
    valores_grasp.append(final[0])
    tempos_grasp.append(final[1][:-1])

arq = open('resultados finais/simulated_annealing.txt', 'r')
lines = arq.readlines()
valores_sa, tempos_sa = list(), list()
for i in range(len(lines)//14):
    final = lines[i*14 + 12].split(',')
    valores_sa.append(final[0])
    tempos_sa.append(final[1][:-1])

arq = open('resultados finais/smart15.txt', 'r')
lines = arq.readlines()
valores_ils, tempos_ils = list(), list()
for i in range(len(lines)//14):
    final = lines[i*14 + 12].split(',')
    valores_ils.append(final[0])
    tempos_ils.append(final[1][:-1])

results = {
    'Instância': nomes, 
    'GRASP': valores_grasp, 
    'Tempo(GRASP)': tempos_grasp, 
    'SA': valores_sa, 
    'Tempo(SA)': tempos_sa, 
    'ILS': valores_ils, 
    'Tempo(ILS)': tempos_ils
}

df = pd.DataFrame(results, columns=['Instância', 'GRASP', 'Tempo(GRASP)', 'SA', 'Tempo(SA)', 'ILS', 'Tempo(ILS)'])

export_csv = df.to_csv ('resultados finais/tabela.csv', index = None, header = True) #Don't forget to add '.csv' at the end of the path

print(df)
