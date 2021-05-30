import matplotlib.pyplot as plt
import numpy as np
file=open("datos.txt","r")

data,derror=list(),list()
speedup,suerror=list(),list()
efpar,eperror=list(),list()
for line in file:
    #print(line)
    words=line.split()
    data.append(float(words[0]))
    derror.append(float(words[-1]))


for ii in range(len(data)):
    speedup.append(data[0]/data[ii])
    fact=abs((derror[0]/data[0])**2+(derror[ii]/data[ii])**2-2*(derror[0]*derror[ii])/(data[0]*data[ii]))
    error=abs(data[0]/data[ii])*(np.sqrt(fact))
    suerror.append(3*error)

for ii in range(len(speedup)):
    efpar.append(speedup[ii]/(ii+1))
    eperror.append((suerror[ii])/(ii+1))
    

rang=range(1,len(data)+1)
x=np.arange(1,len(data),0.1)


fig,ax=plt.subplots()
ax.grid()
ax.errorbar(rang, speedup,yerr=suerror, marker='.',ls="--",capsize=2.5,ecolor="purple", color='black',label="Medida")
ax.plot(x,x,"-",color="red",label="Teórica")
ax.set_ylabel("Speedup")
ax.set_xlabel("Número de procesos")
ax.set_title("SU VS N (Maquina con 8 cores)")
ax.legend()
ax.axvline(8, color='r', ls="dotted")
fig.savefig("speed.pdf")


fig,ax=plt.subplots()
ax.grid()
ax.errorbar(rang, efpar,yerr=eperror, marker='.',ls="--",capsize=2.5,ecolor="purple", color='black',label="Medida")
ax.plot(x,0*x+1,"-",color="red",label="Teórica")
ax.axvline(8, color='r', ls="dotted")
ax.set_ylabel("Eficiencia paralela")
ax.set_xlabel("Número de procesos")
ax.set_title("EP VS N (Maquina con 8 cores)")
ax.legend()
ax.set_ylim(0,2)
fig.savefig("efpar.pdf")

