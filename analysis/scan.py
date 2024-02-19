import numpy as np
import ROOT as rt
import sys
if len(sys.argv)==2:
  tag=sys.argv[1]
else:
  tag = "scan3"
pad={"scan2":{420742084209:4,
            421042114212:3,
            421342144215:2,
            421642174218:5,
            4219:1,
            42204222:0.75,
            4221:0.5,
            4223:5,
    },
    "scan3":{4234:5,
        4235:4,
        4236:3,
        4237:2,
        4238:1,
        42394242:0.75,
        42404241:0.5,
        },
    "scan4":{4246:5,
            4247:4,
            4248:3,
            4249:2,
            4250:1,
            42514254:0.75,
            42524253:0.5,
            },
    "scan5":{
        4506:5,
        45044505:4,
        4507:3,
        4508:2,
        4509:1,
        4510:0.5,
        }
}
calib_run = {4173 :["MCP_sum","3D_W1","3D_W2","3D_W3"],
        4175 :["HS_W"],
        4176 :["L_1"],
        4177 :["HS_1"],
        4178 :["L_3"],
        4179 :["HS_3"],
        4180 :["L_4"],
        4181 :["HS_2"],
        4182 :["L_2"],
        }
deposit_rate = {"MCP_sum":73.66,
                "3D_W1":1.38,
                "3D_W2":0.82,
                "3D_W3":0.82,
                "HS_W":82.14,
                "HS_1":82.36,
                "HS_2":82.32,
                "HS_3":78.3,
                "L_1":71.2,
                "L_2":71.33,
                "L_3":67.66,
                "L_4":68.14,
                }
scan=[]
for run in pad[tag].keys():
    intADC=rt.TFile(f"/u/user/dream08/dev/TB2023/analysis/Energy/Energy_EvtPed_Run_{run}.root",'read')
    o=rt.TFile(f"Energy/scan_{run}.root","recreate")
    o.cd()
    for i in intADC.GetListOfKeys():
        name=i.GetName()
        if(not "Energy_Scaled_cut" in name):
            continue
        #for target in calib_run[run]:
        #    if target in name:
        
        h=intADC.Get(name)
        h.Fit("gaus")
        g=h.GetFunction("gaus")
        mean=g.GetParameter(1)
        sigma=g.GetParameter(2)
        meanE=g.GetParError(1)
        sigmaE=g.GetParError(2)
        propE=np.sqrt(pow(100/mean*sigmaE,2)+pow(-sigma*100/pow(mean,2)*meanE,2))
        scan.append([name,run,pad[tag][run],mean,sigma,propE])
        h.Write()
    o.Close()
    intADC.Close()
valC=[]
valS=[]
valsum=[]
for i in scan:
    #print("float "+i[0],i[1],"=",i[2],i[3])
    if("C_Energy" in i[0]):
        valC.append([1/np.sqrt(i[2]),i[3],100*i[4]/i[3],i[5]])
    if("S_Energy" in i[0]):
        valS.append([1/np.sqrt(i[2]),i[3],100*i[4]/i[3],i[5]])
    if("Sum_Energy" in i[0]):
        valsum.append([1/np.sqrt(i[2]),i[3],100*i[4]/i[3],i[5]])

import matplotlib.pyplot as plt    
    
valC=np.array(valC)
valS=np.array(valS)
valsum=np.array(valsum)
plt.figure()

parC=np.polyfit(valC[:,0],valC[:,2],1)
parS=np.polyfit(valS[:,0],valS[:,2],1)
parsum=np.polyfit(valsum[:,0],valsum[:,2],1)
print(parC)
print(parS)
print(parsum)
plt.errorbar(valC[:,0],valC[:,2],yerr=valC[:,3],fmt='o',label=f"C {parC[0]:0.2f}",alpha=0.7,color="C0")
plt.errorbar(valS[:,0],valS[:,2],yerr=valS[:,3],fmt='o',label=f"S {parS[0]:0.2f}",alpha=0.7,color="C1")
plt.errorbar(valsum[:,0],valsum[:,2],yerr=valsum[:,3],fmt='o',label=f"sum {parsum[0]:0.2f}",alpha=0.7,color="C2")
plt.xlabel("1/$\sqrt{E}$")
plt.ylabel("energy resolution %")
polyC=np.poly1d(parC)
polyS=np.poly1d(parS)
polysum=np.poly1d(parsum)
plt.plot(np.unique(valC[:,0]),polyC(np.unique(valC[:,0])),ls="--",alpha=0.5,color="C0")
plt.plot(np.unique(valS[:,0]),polyS(np.unique(valS[:,0])),ls="--",alpha=0.5,color="C1")
plt.plot(np.unique(valsum[:,0]),polysum(np.unique(valsum[:,0])),ls="--",alpha=0.5,color="C2")
plt.grid()
#plt.yscale("log")
plt.legend()
plt.title(tag)
plt.savefig(f"{tag}.png")
print(f"{tag}.png saved")
"""
plt.errorbar(valC[:,0],valC[:,1],yerr=valC[:,2],fmt='o',label="C",alpha=0.7,color="C0")
plt.errorbar(valS[:,0],valS[:,1],yerr=valS[:,2],fmt='o',label="S",alpha=0.7,color="C1")
plt.errorbar(valsum[:,0],valsum[:,1],yerr=valsum[:,2],fmt='o',label="sum",alpha=0.7,color="C2")


"""
