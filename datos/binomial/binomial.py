# Sacado de https://scipy.github.io/old-wiki/pages/Cookbook/Matplotlib/LaTeX_Examples.html

import matplotlib.pyplot as plt
import pylab
import numpy as np
import math
from pylab import arange,pi,sin,cos,sqrt,savefig

golden_mean = (math.sqrt(5)-1.0)/2.0        # Aesthetic ratio
fig_width = 3+3/8 			 		    # width  in inches
fig_height = fig_width*golden_mean          # height in inches
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

print("Calcula Histograma de la magnetizacion")

data = np.genfromtxt("magnetizacion_vsiteracion_T2.300000_N32.txt",  delimiter = ' ')

magnetizacion = data

### PLOT  ###

### Histograma de size ###
pylab.figure(1)
pylab.clf()
plt.hist(magnetizacion[4000:5000], bins='auto') 
#plt.plot((10.6, 10.6), (0, 800), 'r')
#plt.plot((9.4,9.4), (0, 800), 'r')
#pylab.xlim(0,20)
#plt.ylim(0,800)
plt.xlabel('magnetizacion')
plt.ylabel('Frecuencia')
plt.savefig('histo_magnetizacion_T2.3.eps', format='eps', dpi=300, bbox_inches='tight')
