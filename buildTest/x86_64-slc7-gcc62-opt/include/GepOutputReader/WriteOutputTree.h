#ifndef WRITEOUTPUTTREE_WRITEOUTPUTTREE_H
#define WRITEOUTPUTTREE_WRITEOUTPUTTREE_H 1

#include "AthAnalysisBaseComps/AthAnalysisAlgorithm.h"
//#include "CaloInterface/ICalorimeterNoiseTool.h"

#include "TTree.h"



class WriteOutputTree: public ::AthAnalysisAlgorithm {
 public:
  WriteOutputTree( const std::string& name, ISvcLocator* pSvcLocator );
  virtual ~WriteOutputTree();

  ///uncomment and implement methods as required

                                        //IS EXECUTED:
  virtual StatusCode  initialize();     //once, before any input is loaded
  //virtual StatusCode  beginInputFile(); //start of each input file, only metadata loaded
  //virtual StatusCode  firstExecute();   //once, after first eventdata is loaded (not per file)
  virtual StatusCode  execute();        //per event
  //virtual StatusCode  endInputFile();   //end of each input file
  //virtual StatusCode  metaDataStop();   //when outputMetaStore is populated by MetaDataTools
  virtual StatusCode  finalize();       //once, after all events processed

  virtual StatusCode RetrieveEventInfo();
  virtual StatusCode RetrieveCells();
  virtual StatusCode RetrieveClusters();
  virtual StatusCode RetrieveJets();
  virtual StatusCode RetrieveTruthTaus();
  virtual StatusCode RetrieveTruthMETs();
  virtual StatusCode RetrieveRecoTaus();

  ///Other useful methods provided by base class are:
  ///evtStore()        : ServiceHandle to main event data storegate
  ///inputMetaStore()  : ServiceHandle to input metadata storegate
  ///outputMetaStore() : ServiceHandle to output metadata storegate
  ///histSvc()         : ServiceHandle to output ROOT service (writing TObjects)
  ///currentFile()     : TFile* to the currently open input file
  ///retrieveMetadata(...): See twiki.cern.ch/twiki/bin/view/AtlasProtected/AthAnalysisBase#ReadingMetaDataInCpp


 private:

  //Alg properties
  std::vector<std::string> ClustList;
  std::vector<std::string> JetList;
  //ToolHandle<ICalorimeterNoiseTool> m_noiseTool;
  bool m_getEventInfo = true;
  bool m_getCellsInfo = true;
  bool m_getJetConstituentsInfo = true;
  bool m_getJetSeedsInfo = false;
  std::vector<TString> m_cl_list;
  std::vector<TString> m_jet_list;

  TTree* m_tree = nullptr;


  //Event info
  int distFrontBunchTrain;
  int bcid;
  int eventNumber;
  int runNumber;
  float weight;
  float mu;
  std::vector<float> mcEventWeights;

   //Reco Taus
  std::vector<float> m_recoTau_pt;
  std::vector<float> m_recoTau_ptFinalCalib;
  std::vector<float> m_recoTau_phi;
  std::vector<float> m_recoTau_eta;
  std::vector<float> m_recoTau_m;
  std::vector<float> m_recoTau_nTaus;
  std::vector<float> nTracksCharged;
  std::vector<float> nTracksIsolation;
  std::vector<float> nAllTracks;

  //TruthTaus
  std::vector<float> truthTauEt; //visible truth tau
	std::vector<float> truthTauEta;
 	std::vector<float> truthTauPhi;

  std::vector<float> m_truthTau_pt; 
  std::vector<float> m_truthTau_neutrinopt;
  std::vector<float> m_truthTau_neutrinoeta;
  std::vector<float> m_truthTau_neutrinophi;
  std::vector<float> m_truthTau_totalpt;
  std::vector<float> m_truthTau_eta; 
  std::vector<float> m_truthTau_phi; 
  std::vector<float> m_truthTau_nTaus;
  std::vector<int> m_truthTau_nProng; 
  std::vector<int> m_truthTau_nChargedMeson; 
  std::vector<int> m_truthTau_nNeutralMeson; 
  std::vector<bool> m_truthTau_isHadronic; 
  std::vector<bool> m_truthTau_isLeptonicEle; 
  std::vector<bool> m_truthTau_outgoingTau; 
  std::map<TString, std::vector<int>> m_truthTau_nMatchedCluster; 
  std::map<TString, std::vector<std::vector<float>>> m_truthTau_matchedClusters_et; 
  std::map<TString, std::vector<std::vector<float>>> m_truthTau_matchedClusters_dR; 
  std::map<TString, std::vector<std::vector<float>>> m_truthTau_matchedClusters_EngFracEM; 

  //METs
  std::vector<float> m_truthMET_met; 
  std::vector<float> m_truthMET_phi; 

  //Cells
  std::vector<float> cells_e;
  std::vector<float> cells_eta;
  std::vector<float> cells_phi;
  //std::vector<float> cells_et;
  std::vector<float> cells_time;
  std::vector<unsigned int> cells_quality;
  std::vector<unsigned int> cells_provenance;
  //std::vector<float> cells_totalNoise;

  //Clusters
  std::map<TString, std::vector<float>> m_cl_et;
  std::map<TString, std::vector<float>> m_cl_eta;
  std::map<TString, std::vector<float>> m_cl_phi;
  std::map<TString, std::vector<float>> m_cl_EngFracEM;
  std::map<TString, std::vector<float>> m_cl_m;
  std::map<TString, std::vector<int>> m_cl_Ncells;


  //Jets
  std::map<TString, std::vector<float>> m_jet_pt;
  std::map<TString, std::vector<float>> m_jet_phi;
  std::map<TString, std::vector<float>> m_jet_eta;
  std::map<TString, std::vector<float>> m_jet_m;
  std::map<TString, std::vector<int>> m_jet_nConstituents;

  std::map<TString, std::vector<std::vector<float>>> m_jetConst_et;
  std::map<TString, std::vector<std::vector<float>>> m_jetConst_phi;
  std::map<TString, std::vector<std::vector<float>>> m_jetConst_eta;
  std::map<TString, std::vector<float>> m_jetSeed_et;
  std::map<TString, std::vector<float>> m_jetSeed_phi;
  std::map<TString, std::vector<float>> m_jetSeed_eta;
};

#endif //> !WRITEOUTPUTTREE_WRITEOUTPUTTREE_H
