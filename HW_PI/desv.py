import numpy as np
for jj in range(1,12):
    datos=list()
    for ii in range(5):
        fil=open("data{:}.txt".format(ii),"r")
        for line in fil:
            words=line.split()
            if (int(words[0])==jj):
                datos.append(float(words[-1]))
            
    prom=np.sum(datos)/5
    desv=np.std(datos)
    print(prom,desv)
