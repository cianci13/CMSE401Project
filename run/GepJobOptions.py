# In order to run on 21.9 samples you need the following settings. These can be added in a preInclude.py file or pasted at the top of joboptions file.
from AthenaCommon.GlobalFlags import globalflags
globalflags.DataSource.set_Value_and_Lock("geant4")
DetDescrVersion="ATLAS-P2-ITK-23-00-03" #ATLAS-P2-ITK-22-02-00"
ConditionsTag="OFLCOND-MC15c-SDR-14-03"
globalflags.DetDescrVersion.set_Value_and_Lock(DetDescrVersion)
include("InDetSLHC_Example/preInclude.NoTRT_NoBCM_NoDBM.py")
include("InDetSLHC_Example/preInclude.SLHC_Setup.py")
include("InDetSLHC_Example/preInclude.SLHC_Setup_Strip_GMX.py")
include("InDetSLHC_Example/preInclude.SLHC_Calorimeter_mu200.py")

# Run over all events
theApp.EvtMax=-1

jps.AthenaCommonFlags.AccessMode = "POOLAccess"
# Give path to input file.
jps.AthenaCommonFlags.FilesInput = ["AOD.26811025._000007.pool.root.1"]
#"/eos/user/s/stkazako/mc15_14TeV.800290.Py8EG_A14NNPDF23LO_jetjet_JZ0WithSW.recon.AOD.e8185_s3595_s3600_r12065/AOD.22568942._000010.pool.root.1" ]
#/eos/user/s/stkazako/mc15_14TeV.800290.Py8EG_A14NNPDF23LO_jetjet_JZ0WithSW.recon.AOD.e8185_s3595_s3600_r12065/AOD_4_6_10_13_19_30to32_34_37_39_40.pool.root.1" ]

# Register the output files. The upper-case stream names are used in the code in GepOutputReader. The names of the ROOT files can be changed.
produceCaloCellsMap = 0
produceHist = 0
produceNtuples = 1

if(produceCaloCellsMap):
    jps.AthenaCommonFlags.HistOutputs = ["STREAM_CALOMAP:CaloCellsMap.root"]
if(produceHist):
    jps.AthenaCommonFlags.HistOutputs = ["STREAM_HIST:myfile_hist.root"]
if(produceNtuples):
    jps.AthenaCommonFlags.HistOutputs = ["STREAM_TREE:ztautautree.root"]

# Flags for ntuple information
getCellsInfo = 1
getEventInfo = 1
getJetConstituentsInfo = 0

# Choose the algorithms to run
topoclAlgs=['Calo422', 'Calo420', 'CaloCal']
puSupprAlgs=['', 'SK']
jetAlgs=[]
#jetAlgs=['AntiKt4','Cone4SeedTopoApproxEtScheme5GeVMerg3']

svcMgr.THistSvc.MaxFileSize = -1 #disable check for perf improvement

# Add the respective sequences to the main sequence.
from AthenaCommon.AlgSequence import AlgSequence
athAlgSeq = AlgSequence()

from TrigL0GepPerf.L0GepSimulationSequence import setupL0GepSimulationSequence
setupL0GepSimulationSequence( topoclAlgs=topoclAlgs,
                              jetAlgs=jetAlgs,
                              puSupprAlgs=puSupprAlgs )

from GepOutputReader.GepOutputReaderSequence import setupGepOutputReaderSequence
setupGepOutputReaderSequence( produceCaloCellsMap=produceCaloCellsMap,
                              produceHist=produceHist,
                              produceNtuples=produceNtuples,
                              topoclAlgs=topoclAlgs,
                              jetAlgs=jetAlgs,
                              puSupprAlgs=puSupprAlgs,
                              getCellsInfo=getCellsInfo,
                              getEventInfo=getEventInfo, 
                              getJetConstituentsInfo=getJetConstituentsInfo)

# Set the detector information.
from RecExConfig import AutoConfiguration
AutoConfiguration.ConfigureSimulationOrRealData()
AutoConfiguration.ConfigureConditionsTag()
from AthenaCommon.DetFlags import DetFlags
DetFlags.all_setOff()
DetFlags.detdescr.Calo_setOn()
include("RecExCond/AllDet_detDescr.py")
