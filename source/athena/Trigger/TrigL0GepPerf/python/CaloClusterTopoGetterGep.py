# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration

#
# Edited from CaloRec/python/CaloClusterTopoGetter.py
# Purpose: Define default calibrated topo cluster algo and corrections,
#          define EM scale clusters with given cellThreshold value
#

from AthenaCommon.Logging import logging
from RecExConfig.Configured import Configured
from RecExConfig.ObjKeyStore import objKeyStore
from AthenaCommon.JobProperties import jobproperties as jp
import traceback

from CaloUtils.CaloUtilsConf import CaloLCClassificationTool, CaloLCWeightTool, CaloLCOutOfClusterTool, CaloLCDeadMaterialTool

from CaloClusterCorrection.CaloClusterCorrectionConf import CaloClusterLocalCalib
from CaloClusterCorrection.CaloClusterCorrectionConf import CaloClusterCellWeightCalib

from CaloRec.CaloRecConf import CaloTopoClusterMaker, CaloTopoClusterSplitter, CaloClusterMomentsMaker, CaloClusterMaker, CaloClusterSnapshot, CaloClusterMomentsMaker_DigiHSTruth
from CaloRec import CaloRecFlags
from CaloRec.CaloTopoClusterFlags import jobproperties
from AthenaCommon.SystemOfUnits import deg, GeV, MeV
from AthenaCommon.AlgSequence import AlgSequence
from AthenaCommon.GlobalFlags import globalflags
from RecExConfig.RecFlags import rec

from CaloTools.CaloNoiseToolDefault import CaloNoiseToolDefault
theCaloNoiseTool = CaloNoiseToolDefault()
from AthenaCommon.AppMgr import ToolSvc
ToolSvc += theCaloNoiseTool


def addSnapshot(corrName,contName):
    from AthenaCommon.AlgSequence import AlgSequence
    topSequence = AlgSequence()
    mlog = logging.getLogger('CaloClusterTopoGetterGep:addSnapshot')
    corrTools=topSequence.CaloTopoCluster.ClusterCorrectionTools
    newCorrTools=[]
    found=False
    for t in corrTools:
        newCorrTools.append(t)
        if (t.getName()==corrName):
            newSnapshot=CaloClusterSnapshot("Snapshot_"+corrName,OutputName=contName)
            newCorrTools.append(newSnapshot)
            found=True
    if not found:
        mlog.error("Did not find cluster correction tool %s" % corrName)
    else:
        mlog.info("Added cluster snapshot after correction tool %s" % corrName)
        topSequence.CaloTopoCluster.ClusterCorrectionTools=newCorrTools
        topSequence.CaloTopoCluster+=newSnapshot
    return


class CaloClusterTopoGetterGep ( Configured ):

    def __init__( self ):

        self._outputType = "CaloClusterContainer" # the main (AOD) object type
        super(CaloClusterTopoGetterGep,self).__init__()
        
        if jobproperties.CaloTopoClusterFlags.doTopoClusterLocalCalib() or jobproperties.CaloTopoClusterFlags.doCellWeightCalib():
            _outputKey = "CaloCalTopoClusters" # the main (AOD) object key
            _output = { self._outputType : ["CaloCalTopoClusters","CaloTopoCluster"],
                        "CaloClusterAuxContainer" : ["CaloTopoClusterAux.","CaloCalTopoClustersAux."],
                        "CaloClusterCellLinkContainer" : ["CaloCalTopoClusters_links","CaloTopoCluster_links"]
                    }
        else:
            _outputKey = self._outputKey # the main (AOD) object key
            _output = { self._outputType : self._outputKey,
                        "CaloClusterAuxContainer" : self._outputKey+"Aux.",
                        "CaloClusterCellLinkContainer" : self._outputKey+"_links"
                    }

    def configure(self):
        mlog = logging.getLogger( 'CaloClusterTopoGetterGep::configure :' )
        mlog.info ('scheduled to output %s',self.output())


        # configure cell weight calibration
        if jobproperties.CaloTopoClusterFlags.doCellWeightCalib():
            from CaloClusterCorrection.CaloClusterCorrectionConf import H1WeightToolCSC12Generic
            from CaloClusterCorrection.StandardCellWeightCalib   import H1Calibration, getCellWeightTool
            CellWeights = CaloClusterCellWeightCalib("CellWeights")
            # -- configure weight tool
            finder = jobproperties.CaloTopoClusterFlags.cellWeightRefFinder.get_Value()
            size   = jobproperties.CaloTopoClusterFlags.cellWeightRefSize.get_Value()
            signal = jobproperties.CaloTopoClusterFlags.cellWeightRefSignal.get_Value()
            WeightTool  = getCellWeightTool(finder,size,signal)
            # -- connect weight tool
            CellWeights.CellSignalWeightTool    = WeightTool
            CellWeights                        += WeightTool
            #-- default properties
            CellWeights.Direction               = "AbsSignal"   #-- use absolute cell energies for eta/phi calculation 
            CellWeights.BelowThresholdLikeAll   = True          #-- treat clusters below thresholds the same as all others
            CellWeights.BelowThresholdDirection = "AbsSignal"   #-- alternative direction calculation for below threshold clusters,
                                                                #   ignored if BelowThresholdLikeAll = True
            CellWeights.EnergyThreshold         = 0.0*MeV       #-- threshold for possible change of direction calculation
            CellWeights.IgnoreGeoWeights        = False         #-- ignore geometrical cell signal weights if True
            
        # now configure local hadronic calibration
        if jobproperties.CaloTopoClusterFlags.doTopoClusterLocalCalib():
            # tools used by tools

            LCClassify   = CaloLCClassificationTool("LCClassify")
            LCClassify.ClassificationKey   = "EMFracClassify"
            LCClassify.UseSpread = False
            LCClassify.MaxProbability = 0.5
            # add the moments EM_PROBABILITY, HAD_WEIGHT, OOC_WEIGHT, DM_WEIGHT to the AOD:
            LCClassify.StoreClassificationProbabilityInAOD = True
            LCClassify.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute()
    
            LCWeight = CaloLCWeightTool("LCWeight")
            LCWeight.CorrectionKey       = "H1ClusterCellWeights"
            LCWeight.SignalOverNoiseCut  = 2.0
            LCWeight.CaloNoiseTool       = theCaloNoiseTool
            LCWeight.UseHadProbability   = True

            LCOut     = CaloLCOutOfClusterTool("LCOut")
            LCOut.CorrectionKey       = "OOCCorrection"
            LCOut.UseEmProbability    = False
            LCOut.UseHadProbability   = True
            
            LCOutPi0  = CaloLCOutOfClusterTool("LCOutPi0")
            LCOutPi0.CorrectionKey    = "OOCPi0Correction"
            LCOutPi0.UseEmProbability  = True
            LCOutPi0.UseHadProbability = False
            
            
            LCDeadMaterial   = CaloLCDeadMaterialTool("LCDeadMaterial")
            LCDeadMaterial.HadDMCoeffKey       = "HadDMCoeff2"
            LCDeadMaterial.ClusterRecoStatus   = 0
            LCDeadMaterial.WeightModeDM        = 2 
            LCDeadMaterial.UseHadProbability   = True
            LCDeadMaterial.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute()
            # correction tools using tools
            LocalCalib = CaloClusterLocalCalib ("LocalCalib")
            LocalCalib.ClusterClassificationTool     = [LCClassify]
            LocalCalib.ClusterRecoStatus             = [1,2]
            LocalCalib.LocalCalibTools               = [LCWeight]
            LocalCalib.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute()
            
            LocalCalib += LCClassify
            LocalCalib += LCWeight
            
            OOCCalib   = CaloClusterLocalCalib ("OOCCalib")
            OOCCalib.ClusterRecoStatus   = [1,2]
            OOCCalib.LocalCalibTools     = [LCOut]
            OOCCalib.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute()
            
            OOCCalib += LCOut
    
            OOCPi0Calib   = CaloClusterLocalCalib ("OOCPi0Calib")
            OOCPi0Calib.ClusterRecoStatus   = [1,2]
            OOCPi0Calib.LocalCalibTools     = [LCOutPi0]
    
            OOCPi0Calib.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute()
    
            OOCPi0Calib += LCOutPi0
            
            DMCalib    = CaloClusterLocalCalib ("DMCalib")
            DMCalib.ClusterRecoStatus   = [1,2]
            DMCalib.LocalCalibTools      = [LCDeadMaterial]

            DMCalib.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute()
            
            DMCalib += LCDeadMaterial

        # correction tools not using tools
        TopoMoments = CaloClusterMomentsMaker ("TopoMoments")
        TopoMoments.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute() 
        TopoMoments.MaxAxisAngle = 20*deg
        TopoMoments.CaloNoiseTool = theCaloNoiseTool
        TopoMoments.UsePileUpNoise = True
        TopoMoments.TwoGaussianNoise = jobproperties.CaloTopoClusterFlags.doTwoGaussianNoise()
        TopoMoments.MinBadLArQuality = 4000
        TopoMoments.MomentsNames = ["AVG_LAR_Q"
                                    ,"AVG_TILE_Q"
                                    ,"BAD_CELLS_CORR_E"
                                    ,"BADLARQ_FRAC"
                                    ,"CELL_SIGNIFICANCE"
                                    ,"CELL_SIG_SAMPLING"
                                    ,"CENTER_LAMBDA"
                                    ,"CENTER_MAG"
                                    ,"CENTER_X"
                                    ,"CENTER_Y"
                                    ,"CENTER_Z"
                                    ,"DELTA_ALPHA" 
                                    ,"DELTA_PHI"
                                    ,"DELTA_THETA"
                                    ,"ENG_BAD_CELLS"
                                    ,"ENG_FRAC_CORE" 
                                    ,"ENG_FRAC_EM" 
                                    ,"ENG_FRAC_MAX" 
                                    ,"ENG_POS"
                                    ,"FIRST_ENG_DENS" 
                                    ,"FIRST_ETA"
                                    ,"FIRST_PHI" 
                                    ,"ISOLATION"
                                    ,"LATERAL"
                                    ,"LONGITUDINAL"
                                    ,"MASS"
                                    ,"N_BAD_CELLS"
                                    ,"N_BAD_CELLS_CORR"
                                    ,"PTD"
                                    ,"SECOND_ENG_DENS" 
                                    ,"SECOND_LAMBDA"
                                    ,"SECOND_R" 
                                    ,"SIGNIFICANCE"]

        doDigiTruthFlag = False
        try:
            from Digitization.DigitizationFlags import digitizationFlags
            doDigiTruthFlag = digitizationFlags.doDigiTruth()
        except:
            log = logging.getLogger('CaloClusterTopoGetterGep')
            log.info('Unable to import DigitizationFlags in CaloClusterTopoGetterGep. Expected in AthenaP1')

        if doDigiTruthFlag:
          TopoMoments_Truth = CaloClusterMomentsMaker_DigiHSTruth ("TopoMoments_Truth")
          TopoMoments_Truth.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute() 
          TopoMoments_Truth.MaxAxisAngle = 20*deg
          TopoMoments_Truth.CaloNoiseTool = theCaloNoiseTool
          TopoMoments_Truth.UsePileUpNoise = True
          TopoMoments_Truth.TwoGaussianNoise = jobproperties.CaloTopoClusterFlags.doTwoGaussianNoise()
          TopoMoments_Truth.MinBadLArQuality = 4000
          TopoMoments_Truth.MomentsNames = ["FIRST_PHI_DigiHSTruth"
                                      ,"FIRST_ETA_DigiHSTruth"
                                      ,"SECOND_R_DigiHSTruth"
                                      ,"SECOND_LAMBDA_DigiHSTruth"
                                      ,"DELTA_PHI_DigiHSTruth"
                                      ,"DELTA_THETA_DigiHSTruth"
                                      ,"DELTA_ALPHA_DigiHSTruth"
                                      ,"CENTER_X_DigiHSTruth"
                                      ,"CENTER_Y_DigiHSTruth"
                                      ,"CENTER_Z_DigiHSTruth"
                                      ,"CENTER_MAG_DigiHSTruth"
                                      ,"CENTER_LAMBDA_DigiHSTruth"
                                      ,"LATERAL_DigiHSTruth"
                                      ,"LONGITUDINAL_DigiHSTruth"
                                      ,"ENG_FRAC_CORE_DigiHSTruth"
                                      ,"FIRST_ENG_DENS_DigiHSTruth"
                                      ,"SECOND_ENG_DENS_DigiHSTruth"
                                      ,"ISOLATION_DigiHSTruth"
                                      ,"BAD_CELLS_CORR_E_DigiHSTruth"
                                      ,"ENG_POS_DigiHSTruth"
                                      ,"SIGNIFICANCE_DigiHSTruth"
                                      ,"CELL_SIGNIFICANCE_DigiHSTruth"
                                      ,"CELL_SIG_SAMPLING_DigiHSTruth"
                                      ,"AVG_LAR_Q_DigiHSTruth"
                                      ,"AVG_TILE_Q_DigiHSTruth"
                                      ,"ENERGY_DigiHSTruth"
                                      ,"PHI_DigiHSTruth"
                                      ,"ETA_DigiHSTruth"
                                      ]



        # only add HV related moments if it is offline.
        from IOVDbSvc.CondDB import conddb
        if not conddb.isOnline:
            from LArRecUtils.LArHVScaleRetrieverDefault import LArHVScaleRetrieverDefault
            TopoMoments.LArHVScaleRetriever=LArHVScaleRetrieverDefault()
            TopoMoments.MomentsNames += ["ENG_BAD_HV_CELLS"
                                         ,"N_BAD_HV_CELLS"
                                         ]

        theCaloClusterSnapshot=CaloClusterSnapshot(OutputName="CaloTopoCluster",SetCrossLinks=True)

            
        # maker tools
        TopoMaker = CaloTopoClusterMaker("TopoMaker"+self._outputKey)
        
        # run on calo cells without the CaloCellGetter
        TopoMaker.CellsName = "AllCalo"

        TopoMaker.CalorimeterNames=["LAREM",
                                    "LARHEC",
                                    "LARFCAL",
                                    "TILE"]
        # cells from the following samplings will be able to form
        # seeds. By default no sampling is excluded
        TopoMaker.SeedSamplingNames = ["PreSamplerB", "EMB1", "EMB2", "EMB3",
                                       "PreSamplerE", "EME1", "EME2", "EME3",
                                       "HEC0", "HEC1","HEC2", "HEC3",
                                       "TileBar0", "TileBar1", "TileBar2",
                                       "TileExt0", "TileExt1", "TileExt2",
                                       "TileGap1", "TileGap2", "TileGap3",
                                       "FCAL0", "FCAL1", "FCAL2"] 
        TopoMaker.CaloNoiseTool=theCaloNoiseTool
        TopoMaker.UseCaloNoiseTool=True
        TopoMaker.UsePileUpNoise=True
        TopoMaker.NeighborOption = "super3D"
        TopoMaker.RestrictHECIWandFCalNeighbors  = False
        TopoMaker.RestrictPSNeighbors  = True
        TopoMaker.CellThresholdOnEorAbsEinSigma     =  self._cellThreshold
        TopoMaker.NeighborThresholdOnEorAbsEinSigma =  2.0
        TopoMaker.SeedThresholdOnEorAbsEinSigma     =  4.0
        #timing
        TopoMaker.SeedCutsInT = jobproperties.CaloTopoClusterFlags.doTimeCut()

        # note E or AbsE 
        #
        # the following property must be set to TRUE in order to make double
        # sided cuts on the seed and the cluster level 
        #
        TopoMaker.SeedCutsInAbsE                 = True
        TopoMaker.ClusterEtorAbsEtCut            = 0.0*MeV
        #
        # by default neighbor and cell thresholds are on AbsE. Set the following
        # properties to FALSE in order to switch to cuts on E 
        #
        #TopoMaker.NeighborCutsInAbsE              = False
        #TopoMaker.CellCutsInAbsE                 = False
        # the following Et thresholds are ignored in case UsePileUpNoise
        # is TRUE
        #
        # CellThresholdOnAbsEt = 0.0*MeV
        # NeighborThresholdOnAbsEt = 100.0*MeV
        # SeedThresholdOnEtorAbsEt = 200.0*MeV

        
        # use 2-gaussian or single gaussian noise for TileCal
        TopoMaker.TwoGaussianNoise = jobproperties.CaloTopoClusterFlags.doTwoGaussianNoise()
        

        TopoSplitter = CaloTopoClusterSplitter("TopoSplitter"+self._outputKey)
        # cells from the following samplings will be able to form local
        # maxima. The excluded samplings are PreSamplerB, EMB1,
        # PreSamplerE, EME1, all Tile samplings, all HEC samplings and the
        # two rear FCal samplings.
        #
        TopoSplitter.SamplingNames = ["EMB2", "EMB3",
                                      "EME2", "EME3",
                                      "FCAL0"]
        # cells from the following samplings will also be able to form
        # local maxima but only if they are not overlapping in eta and phi
        # with local maxima in previous samplings from the primary list.
        #
        TopoSplitter.SecondarySamplingNames = ["EMB1","EME1",
                                               "TileBar0","TileBar1","TileBar2",
                                               "TileExt0","TileExt1","TileExt2",
                                               "HEC0","HEC1","HEC2","HEC3",
                                               "FCAL1","FCAL2"]
        TopoSplitter.ShareBorderCells = True
        TopoSplitter.RestrictHECIWandFCalNeighbors  = False
        TopoSplitter.WeightingOfNegClusters = jobproperties.CaloTopoClusterFlags.doTreatEnergyCutAsAbsolute()


        #
        # the following options are not set, since these are the default
        # values
        #
        # NeighborOption                = "super3D",
        # NumberOfCellsCut              = 4,
        # EnergyCut                     = 500*MeV,
        
        # cluster maker
        CaloTopoCluster = CaloClusterMaker (self._outputKey)
        if jobproperties.CaloTopoClusterFlags.doTopoClusterLocalCalib():
            CaloTopoCluster.ClustersOutputName = "CaloCalTopoClusters"
        else:
            CaloTopoCluster.ClustersOutputName = self._outputKey
        CaloTopoCluster.ClusterMakerTools = [TopoMaker, TopoSplitter]
            
        from CaloClusterCorrection.CaloClusterBadChannelListCorr import CaloClusterBadChannelListCorr
        BadChannelListCorr = CaloClusterBadChannelListCorr()
        CaloTopoCluster.ClusterCorrectionTools += [BadChannelListCorr]
        
        CaloTopoCluster.ClusterCorrectionTools += [TopoMoments]

        if doDigiTruthFlag:
          CaloTopoCluster.ClusterCorrectionTools += [TopoMoments_Truth]

        CaloTopoCluster += TopoMaker
        CaloTopoCluster += TopoSplitter
        CaloTopoCluster += BadChannelListCorr
        CaloTopoCluster += TopoMoments
        if doDigiTruthFlag:
          CaloTopoCluster += TopoMoments_Truth
        
        if jobproperties.CaloTopoClusterFlags.doClusterVertexFraction():
            from CaloTrackUtils.CaloTrackUtilsConf import CaloClusterVertexFractionMaker
            MyCaloClusterVertexFractionMaker = CaloClusterVertexFractionMaker(name            = "CaloClusterVertexFractionMaker",
                                                                              VxContainerName = "VxPrimaryCandidate",
                                                                              dRMatchMax      = 0.17 )
            CaloTopoCluster.ClusterCorrectionTools += [ MyCaloClusterVertexFractionMaker]
            CaloTopoCluster += MyCaloClusterVertexFractionMaker
        
        if jobproperties.CaloTopoClusterFlags.doCalibHitMoments() and rec.doTruth():
            from CaloCalibHitRec.CaloCalibHitRecConf import CaloCalibClusterMomentsMaker2
            TopoCalibMoments = CaloCalibClusterMomentsMaker2 ("TopoCalibMoments"+self._outputKey)
            TopoCalibMoments.MomentsNames = ["ENG_CALIB_TOT"
                                             ,"ENG_CALIB_OUT_L"
                                             ,"ENG_CALIB_EMB0"
                                             ,"ENG_CALIB_EME0"
                                             ,"ENG_CALIB_TILEG3"
                                             ,"ENG_CALIB_DEAD_TOT"
                                             ,"ENG_CALIB_DEAD_EMB0"
                                             ,"ENG_CALIB_DEAD_TILE0"
                                             ,"ENG_CALIB_DEAD_TILEG3"
                                             ,"ENG_CALIB_DEAD_EME0"
                                             ,"ENG_CALIB_DEAD_HEC0"
                                             ,"ENG_CALIB_DEAD_FCAL"
                                             ,"ENG_CALIB_DEAD_LEAKAGE"
                                             ,"ENG_CALIB_DEAD_UNCLASS"
                                             ,"ENG_CALIB_FRAC_EM"
                                             ,"ENG_CALIB_FRAC_HAD"
                                             ,"ENG_CALIB_FRAC_REST"]

            TopoCalibMoments.CalibrationHitContainerNames = ["LArCalibrationHitInactive"
                                                             ,"LArCalibrationHitActive"
                                                             ,"TileCalibHitActiveCell"
                                                             ,"TileCalibHitInactiveCell"]
            TopoCalibMoments.DMCalibrationHitContainerNames = ["LArCalibrationHitDeadMaterial"
                                                               ,"TileCalibHitDeadMaterial"]
            CaloTopoCluster.ClusterCorrectionTools += [TopoCalibMoments]
            CaloTopoCluster += TopoCalibMoments
            

        CaloTopoCluster.ClusterCorrectionTools += [theCaloClusterSnapshot]
        CaloTopoCluster += theCaloClusterSnapshot

        if jobproperties.CaloTopoClusterFlags.doCellWeightCalib():
            CaloTopoCluster.ClusterCorrectionTools += [
                CellWeights.getFullName() ]
            CaloTopoCluster += CellWeights
            
        if jobproperties.CaloTopoClusterFlags.doTopoClusterLocalCalib():
            CaloTopoCluster.ClusterCorrectionTools += [
                LocalCalib,
                OOCCalib,
                OOCPi0Calib,
                DMCalib]

            CaloTopoCluster += LocalCalib
            CaloTopoCluster += OOCCalib
            CaloTopoCluster += OOCPi0Calib
            CaloTopoCluster += DMCalib
                                            
            
        #
        # pool/cool part
        #
        if jobproperties.CaloTopoClusterFlags.doTopoClusterLocalCalib():
            from CaloRec import CaloClusterTopoCoolFolder
            if globalflags.DetDescrVersion().startswith("Rome"):
                CaloTopoCluster.LocalCalib.LCClassify.MaxProbability = 0.85
                CaloTopoCluster.LocalCalib.LCClassify.UseNormalizedEnergyDensity = False 
            else:   
                CaloTopoCluster.LocalCalib.LCClassify.MaxProbability = 0.50
                CaloTopoCluster.LocalCalib.LCClassify.UseNormalizedEnergyDensity = True


        self._handle = CaloTopoCluster

        objKeyStore.addManyTypesTransient(self.output())

        from AthenaCommon.AlgSequence import AlgSequence
        topSequence = AlgSequence()
        topSequence += CaloTopoCluster


        return True
 
    def handle(self):
        return self._handle

    def output(self):
        return self._output

    def outputKey(self):
        return self._outputKey

    def outputType(self):
        return self._outputType
                                                       



def make_CaloClusterTopoGetterGep ( name,
                                       cellThreshold,
                                       outputKey ):

    cls= type (name, (CaloClusterTopoGetterGep,),{})
    cls._cellThreshold = cellThreshold
    cls._outputKey = outputKey + 'TopoClusters'
    return cls

def _make_topogetter (*args, **kw):
    g = make_CaloClusterTopoGetterGep (*args, **kw)
    globals()[g.__name__] = g
    return g


_make_topogetter ("CaloClusterTopo422Getter", 2.0, 'Calo422')
_make_topogetter ("CaloClusterTopo420Getter", 0.0, 'Calo420')


