# Sacado de https://scipy.github.io/old-wiki/pages/Cookbook/Matplotlib/LaTeX_Examples.html

import matplotlib.pyplot as plt
import pylab
import numpy as np
import math

golden_mean = (math.sqrt(5)-1.0)/2.0       # Aesthetic ratio
fig_width = 3+3/8 			                   # width  in inches
fig_height = fig_width*golden_mean         # height in inches
fig_size =  [fig_width,fig_height]

params = {'backend': 'ps',
          'axes.titlesize': 8,
          'axes.labelsize': 9,
          'axes.linewidth': 0.5, 
          'axes.grid': True,
          'axes.labelweight': 'normal',  
          'font.family': 'serif',
          'font.size': 8.0,
          'font.weight': 'normal',
          'text.color': 'black',
          'xtick.labelsize': 8,
          'ytick.labelsize': 8,
          'text.usetex': True,
          'legend.fontsize': 8,
          'figure.dpi': 300,
          'figure.figsize': fig_size,
          'savefig.dpi': 300,
         }

pylab.rcParams.update(params)

###  DATA  ###

data1 = np.genfromtxt('correlacion_N32_T5.txt', delimiter = '\t')

n = 32

ro = data1
iteracion = np.linspace(0,len(ro),len(ro))
unidad_red = n*n

###  PLOT  ###

pylab.figure(1)
pylab.clf()

plt.plot(iteracion/1,ro,'bo',markersize=2,zorder=3,label='N=32 T=5 ') 
#plt.plot(magnetizacion[::100],'ro',markersize=3,zorder=3,label='magnetizacion') 

pylab.xlabel('Iteracion~/~size red')
pylab.ylabel('correlation')
pylab.legend()
#pylab.ylim(1.00, 1.014)
#pylab.ylim(1.00, 1.04)
#pylab.yticks(np.arange(1,1.04,0.01))
#pylab.xlim(0.0, 1.1)
#pylab.xticks(np.arange(0,1.1,0.2))
#pylab.xlim(0, 8)
#lgd=plt.legend(numpoints=1,handlelength=0.8) 
#lgd.set_visible(True)
plt.legend(loc='best',labelspacing=-0.1,borderpad=0.3,handletextpad=0.5,fontsize=6,numpoints=1)
pylab.savefig('correlacion_N32_T5.eps', format='eps', dpi=300, bbox_inches='tight')
