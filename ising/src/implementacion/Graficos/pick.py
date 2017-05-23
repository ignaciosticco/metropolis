# Sacado de https://scipy.github.io/old-wiki/pages/Cookbook/Matplotlib/LaTeX_Examples.html
import pylab
import numpy as np
import matplotlib.pyplot as plt
import math
import scipy
from scipy import stats

golden_mean = (math.sqrt(5)-1.0)/2.0        # Aesthetic ratio
fig_width = 3+3/8 			    # width  in inches
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
#################### DATA ##############################

##def fzeta(a,b,c):
##	f=a/(b*c)
##	return f

def fzeta(a,b):
		f=a/b
		return f
comp_ns=np.zeros(14)
proba=np.zeros(14)

#print (comp_ns)

data = np.genfromtxt('pick_site_equi.txt')
x = data[:,0]
	
#print (len(ns))
#print (len(nsc))
	

pick = [go.Histogram(x=x)]

py.iplot(pick, filename='basic histogram')		
	
	
#################### PLOT specification ###############################
"""plt.plot(logs,logproba,'ko',markersize=2,label='k',zorder=3)
pylab.ylabel('log(p-pc)')
pylab.xlabel('log(s)')
#pylab.ylim(2, 18)
pylab.xlim(1.5, 3)
#pylab.show()
coef_fit=np.polyfit(logs,logproba,1)
plt.hold(True)
x=np.linspace(1.5,3,100)
y=coef_fit[0]*x+coef_fit[1]
plt.plot(x,y)
print (coef_fit[0])
def rsquared(x, y):
     Return R^2 where x and y are array-like.

    slope, intercept, r_value, p_value, std_err = scipy.stats.linregress(x, y)
    return r_value**2
print (rsquared(logs,logproba))

pylab.savefig('fig_5.eps', format='eps', bbox_inches='tight')


	for j in range(1,16):	
		plt.plot(zeta[j],f[j],'ko',markersize=1,label='k',zorder=3)
	
pylab.ylabel('f(z)')
pylab.xlabel('z')
#pylab.ylim(2, 18)
pylab.xlim(-5, 5)
#pylab.show()
pylab.savefig('fig_5.eps', format='eps', bbox_inches='tight')"""
"""