from AthenaCommon.Include import include

#
# GepOutputReader was designed to read clusters and jets produced by the 
# TrigL0GepPerf package. Note that the same algorithms should be run 
# by the TrigL0GepPerf package for the requested collections to be available. 
# Only 'CaloCal', 'Calo420', and 'Calo422' topoclusters are provided by default.
# Default available options:
#
#  Topoclusters: topoclAlgs = ['CaloCal','Calo420','Calo422']
#  Pileup suppression: puSupprAlgs = ['', 'Vor', 'SK', 'VorSK']
#  Jet reconstruction: jetAlgs = ['AntiKt4']
# 
# Jet containers present in the original AOD can also be retrieved 
# by passing the container names to the list aodJetContainers.
#

def setupGepOutputReaderSequence( 
    produceCaloCellsMap,
    produceHist, 
    produceNtuples,    
    topoclAlgs = ['Calo422'], 
    puSupprAlgs = [''],
    jetAlgs = ['AntiKt4'],
    aodJetContainers=['AntiKt4TruthWZJets'],
    getCellsInfo = False,
    getEventInfo = True,
    getJetConstituentsInfo = True,
    getJetSeedsInfo = False,
    topoclEtGeVCuts=[0]
    ):
    
    from AthenaCommon.AlgSequence import AlgSequence
    topSequence = AlgSequence()

    from AthenaCommon import CfgMgr
    from GepOutputReaderConf import CaloCellsReader
    from GepOutputReaderConf import WriteOutputTree
    from GepOutputReaderConf import WriteOutputHist

    if(produceCaloCellsMap):
        # noise tool
        from CaloTools.CaloNoiseToolDefault import CaloNoiseToolDefault
        theCaloNoiseTool = CaloNoiseToolDefault('db', 'CaloNoiseTool')
        from AthenaCommon.AppMgr import ToolSvc
        ToolSvc += theCaloNoiseTool
        topSequence += CaloCellsReader("CaloCellsReader", CaloNoiseTool=theCaloNoiseTool)
   
    clusters = []
    jets = []
    # clusters and jets produced by TrigL0GepPerf
    for topoMaker in topoclAlgs:
        for puSupAlg in puSupprAlgs:        
            for topoEtCut in topoclEtGeVCuts:
                cl_label = topoMaker+puSupAlg+'Cut'+str(topoEtCut)+'GeV'
                cl_name = cl_label+"TopoClusters"
                clusters.append( cl_name )
                for jetAlg in jetAlgs:
                    if( jetAlg == 'AntiKt4'):
                        if( topoMaker=='Calo420' or topoMaker=='Calo422' ):
                            jetAlg = 'AntiKt4emtopo' 
                        else:
                            jetAlg = 'AntiKt4lctopo'
                    if( jetAlg == 'AntiKt2'):
                        if( topoMaker=='Calo420' or topoMaker=='Calo422' ):
                            jetAlg = 'AntiKt2emtopo' 
                        else:
                            jetAlg = 'AntiKt2lctopo'
                    if( jetAlg == 'AntiKt10'):
                        if( topoMaker=='Calo420' or topoMaker=='Calo422' ):
                            jetAlg = 'AntiKt10emtopo' 
                        else:
                            jetAlg = 'AntiKt10lctopo'
                    
                    jet_name = jetAlg+cl_label+"Jets"
                    jets.append( jet_name )

    
    # jets read directly from the original AOD
    for aodJet in aodJetContainers:
        jets.append( aodJet )


    if(produceNtuples):
        topSequence += CfgMgr.WriteOutputTree('Write ntuples', 
                                              ClustersList=clusters, 
                                              JetsList=jets, 
                                              GetEventInfo=getEventInfo, 
                                              GetCellsInfo=getCellsInfo,
                                              GetJetConstituentsInfo=getJetConstituentsInfo, 
                                              GetJetSeedsInfo=getJetSeedsInfo)
    if(produceHist):
        topSequence += CfgMgr.WriteOutputHist('Write histograms', 
                                              ClustersList=clusters, 
                                              JetsList=jets,
                                              GetJetConstituentsInfo=getJetConstituentsInfo, 
                                              GetJetSeedsInfo=getJetSeedsInfo)

    
