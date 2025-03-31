#ifndef GEPOUTPUTREADER_WRITEOUTPUTHISTALG_H
#define GEPOUTPUTREADER_WRITEOUTPUTHISTALG_H 1

#include "AthAnalysisBaseComps/AthAnalysisAlgorithm.h"


#include "TH1D.h"


#include "xAODEventInfo/EventInfo.h"

#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterAuxContainer.h"
#include "xAODCaloEvent/CaloCluster.h"

#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertex.h"

#include "CaloEvent/CaloClusterMoment.h"
#include "CaloEvent/CaloClusterMomentStore.h"


class WriteOutputHist: public ::AthAnalysisAlgorithm {
 public:
  WriteOutputHist( const std::string& name, ISvcLocator* pSvcLocator );
  virtual ~WriteOutputHist();

                                        //IS EXECUTED:
  virtual StatusCode  initialize();     //once, before any input is loaded
  //virtual StatusCode  beginInputFile(); //start of each input file, only metadata loaded
  //virtual StatusCode  firstExecute();   //once, after first eventdata is loaded (not per file)
  virtual StatusCode  execute();        //per event
  //virtual StatusCode  endInputFile();   //end of each input file
  //virtual StatusCode  metaDataStop();   //when outputMetaStore is populated by MetaDataTools
  virtual StatusCode  finalize();       //once, after all events processed


  ///Other useful methods provided by base class are:
  ///evtStore()        : ServiceHandle to main event data storegate
  ///inputMetaStore()  : ServiceHandle to input metadata storegate
  ///outputMetaStore() : ServiceHandle to output metadata storegate
  ///histSvc()         : ServiceHandle to output ROOT service (writing TObjects)
  ///currentFile()     : TFile* to the currently open input file
  ///retrieveMetadata(...): See twiki.cern.ch/twiki/bin/view/AtlasProtected/AthAnalysisBase#ReadingMetaDataInCpp


 private:

  std::vector<std::string> ClustList;
  std::vector<std::string> JetList;
  bool m_getJetConstituentsInfo = true;
  bool m_getJetSeedsInfo = false;

  //TruthTaus
  TH1D* h_truthTau_et;
  TH1D* h_truthTau_eta;
  TH1D* h_truthTau_phi;
  //TH1D* h_truthTau_totalpt;

  //std::vector<float> truthTauEt; //visible truth tau
	//std::vector<float> truthTauEta;
 	//std::vector<float> truthTauPhi;

  //Clusters
  std::map<TString,TH1D*> h_cluster_et;
  std::map<TString,TH1D*> h_cluster_eta;
  std::map<TString,TH1D*> h_cluster_phi;
  std::map<TString,TH1D*> h_cluster_Nclusters;
  std::map<TString,TH1D*> h_cluster_Ncells;
  std::map<TString,TH1D*> h_cluster_Ncells_fromMom;
  std::map<TString,TH1D*> h_matchedToCluster_truthTauPt;
  std::map<TString,TH1D*> h_matchedToOneCluster_truthTauPt;
  std::map<TString,TH1D*> h_matchedEfficiency_truthTauPt;
  std::map<TString,TH1D*> h_matchedToOneEfficiency_truthTauPt;
  std::map<TString,TH1D*> h_matchedToCluster_seedEt;
  std::map<TString,TH1D*> h_matchedToCluster_minClusterDeltaR;
  std::map<TString,TH1D*> h_matchedToCluster_seedDeltaR;
  std::map<TString,TH2D*> h_matchedToCluster_seedEtVsTruthTauPt;
  std::map<TString,TH1D*> h_matchedToCluster_seedEtOverTruthTauPt;
  std::map<TString,TH1D*> h_matchedToCluster_closestDeltaR;
  std::map<TString,TH2D*> h_matchedToCluster_closestDeltaRvsTruthTauPt;
  std::map<TString,TH1D*> h_notMatched_truthTauPt;
  std::map<TString,TH2D*> h_notMatched_truthTauEtaVsPhi;

  //Jets
  std::map<TString,TH1D*> h_jet_pt;
  std::map<TString,TH1D*> h_jet_eta;
  std::map<TString,TH1D*> h_jet_phi;
  std::map<TString,TH1D*> h_jet_m;
  std::map<TString,TH1D*> h_jet_Njets;
  std::map<TString,TH1D*> h_jet_nConstituents;
  std::map<TString,TH1D*> h_jetConst_et;
  std::map<TString,TH1D*> h_jetConst_eta;
  std::map<TString,TH1D*> h_jetConst_phi;
  std::map<TString,TH1D*> h_jetSeed_et;
  std::map<TString,TH1D*> h_jetSeed_eta;
  std::map<TString,TH1D*> h_jetSeed_phi;

};

#endif //> !GEPOUTPUTREADER_WRITEOUTPUTHISTALG_H
