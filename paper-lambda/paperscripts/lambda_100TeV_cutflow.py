#!/usr/bin/python

import math
import yoda
from tabulate import tabulate
from matplotlib import pyplot as plt

##################################################################

root = "../plotdata/noPU_100TeV/"

lvalues = [ -7, -5, -3, -1, 0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.8, 2, 3, 5, 7, 9 ]
regimes = ['res', 'inter','boost']
regimeLong = { 'res': "Resolved", 'inter': "Intermediate", 'boost': "Boosted"}

Cnum = ['C0', 'C1a', 'C1b', 'C1c', 'C1d', 'C1e', 'C2' ]

lumi = 10000.0
sysErr = 0.0 # 10%

def fname(lval):
	return "diHiggs_LAM"+str(lval).replace(".","_")+"/"

######################### Read in cutflows #########################

cutflows = {}
for lvalue in lvalues:
	for regime in regimes:
		filename = root + fname(lvalue) + "histo_CF_"+regime+".yoda" 

		## Load and sort data objects
		aos = yoda.read(filename)
		for aopath, ao in aos.iteritems():
			if type(ao) != yoda.Histo1D:
				print "Error: AnalysisObject is not a Histo1D"
				quit();

			# Add cutflow
			cutflow = []
			for bin in ao.bins:
				cutflow.append(bin.sumW)
			cutflows[fname(lvalue)+regime] = cutflow

######################### Make plots #########################

colours = ['r', 'b', 'g', 'm', 'c', 'y', 'k']
for regime in regimes:
	fig, ax = plt.subplots()
	ax.set_ylabel("$\sigma_{HH}$")
	ax.set_xlabel("$\lambda$")
	ax.set_yscale('log')
	ax.xaxis.grid(True)
	ax.yaxis.grid(True)
	
	icol=0
	#axes.set_xlim([xmin,xmax])
	fig.suptitle(regimeLong[regime] + " topology (100TeV)")
	ax.set_ylim([1E0,2E4])
	for cut in range(0,len(Cnum)):
		xsec = []
		for lvalue in lvalues:
			xsec.append(cutflows[fname(lvalue)+regime][cut])
		ax.plot(lvalues, xsec, color=colours[icol], label=Cnum[cut])
		icol = icol + 1
	legend = ax.legend(loc='best', shadow=True)
	fig.savefig(regime+'_xSec_100TeV.pdf')

chi2tab_all = [] # All chi2 tables
for regime in regimes:
	table = []
	for lvalue in lvalues:
		table.append(cutflows[fname(lvalue)+regime])

	# Table for printing
	tab_trans = [list(i) for i in zip(*table)]
	tab = tabulate(tab_trans, lvalues,numalign="center", floatfmt=".2E")
	print("\n"+regime + " cutflow:")
	print(tab)

	# Now chi2
	chi2table = []
	for lvalue in lvalues:
		chi2vals = []
		for cut in range(0,len(Cnum)):
			SigLam = cutflows[fname(lvalue)+regime][cut] # Cross-section at lambda
			SigSM = cutflows[fname(1)+regime][cut]		 # Cross-section at lambda=1

			if SigLam != 0: # Intermediate has a unfilled cut
				err = math.sqrt(SigLam/lumi)
				chi2 = pow(SigSM-SigLam,2)/(pow(err,2)+ pow(sysErr*SigSM,2))
				chi2vals.append(chi2)
			else: 
				chi2vals.append(-1)
		chi2table.append(chi2vals)

	chi2tab_trans = [list(i) for i in zip(*chi2table)]
	chi2tab_all.append(chi2tab_trans[len(Cnum)-1]) # Append final cutflow 

# Prepare chi2 plots
fig, ax = plt.subplots()
ax.set_ylabel("$\chi^2$")
ax.set_xlabel("$\lambda$")
ax.set_ylim([0,10])
fig.suptitle("$\chi^2$ profile for all topologies $\sqrt{s}=100$ TeV L="+str(lumi)+"fb$^{-1}$ SysErr="+str(sysErr*100) + "%")

# Print out final values
ireg=0
labelname=["Resolved", "Intermediate", "Boosted"]
for chi2plot in chi2tab_all:
	ax.plot(lvalues, chi2plot, label=labelname[ireg])
	ireg=ireg+1

# Now add the legend with some customizations.
legend = ax.legend(loc='best', shadow=True)
fig.savefig('chi2_100TeV_sys'+str(sysErr).replace(".","_")+'.pdf')
