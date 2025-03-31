#ifndef TRIGL0GEPPERF_GEPTAUALG_H
#define TRIGL0GEPPERF_GEPTAUALG_H 1

#include "AthAnalysisBaseComps/AthAnalysisAlgorithm.h"
#include "GaudiKernel/ToolHandle.h"

#include "TrigL0GepPerf/CustomCaloCell.h"
#include "TrigL0GepPerf/CaloCellsHandler.h"
#include "CaloInterface/ICalorimeterNoiseTool.h"
#include "CaloEvent/CaloCellContainer.h"
#include "CaloEvent/CaloCell.h"

#include "StoreGate/ReadHandleKey.h"
#include "xAODTrigL1Calo/JGTowerContainer.h"
//#include "xAODTrigL1Calo/TriggerTowerContainer.h"
#include <TH1.h>
#include <TH2.h>

#include <string>
#include <iostream>
#include <cmath>

#include "TTree.h"


class GepTauAlg: public ::AthAnalysisAlgorithm {

public:
  GepTauAlg( const std::string& name, ISvcLocator* pSvcLocator );
  ~GepTauAlg();

  virtual StatusCode initialize() override;   
  virtual StatusCode execute() override; 
  virtual StatusCode finalize() override; 
  
  //void PrintCellinfo (Gep::CustomCaloCell cell,const std::map<unsigned int, Gep::CustomCaloCell> *caloCellsMap);
  bool isInAllowedSampling(int sampling, std::vector<int> list_of_samplings);
  
  //virtual StatusCode readCell(const std::map<unsigned int, Gep::CustomCaloCell> &caloCellsMap, TH2F &supercellMapTWR, TH2F &cellMapEM2 );
  StatusCode Clustering(const std::map<unsigned int, Gep::CustomCaloCell> caloCellsMap, Gep::CustomCaloCell seedCell, double &emtauET, float window_w, float window_h, unsigned int layer);

  StatusCode Recentering(const std::map<unsigned int, Gep::CustomCaloCell> caloCellsMap, Gep::CustomCaloCell &Original_seedCell, TH2D *cellMapEM, int offsetL, int offsetR, int sd_x, int sd_y );

  StatusCode IDCheck(const std::map<unsigned int, Gep::CustomCaloCell> caloCellsMap, unsigned int cellID, int layer);
private: 
  
  
	float m_seed_threshold = 4.0;
	std::vector<int> m_allowed_seed_samplings = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	bool m_cellsFilledOnce = false;

	std::string m_tauAlg;
	ToolHandle<ICalorimeterNoiseTool> m_noiseTool;
	double m_towerEtCut;
	double m_seedEtCut;
	
	const mutable CaloCell_ID* m_ccIdHelper;
	bool m_getEventInfo = true;

	CaloCellsHandler m_cch;
	
	TTree* mytree;
	
	long long unsigned int eventNumber= 0;
	std::vector<float> *cellEta = nullptr;   //elementary cell info
	std::vector<float> *cellPhi = nullptr;
	std::vector<float> *cellEt = nullptr;
	std::vector<int> *cellLayer = nullptr;
	
	std::vector<float> *clusteret = nullptr;  //cluster constructed to get recoEt
	std::vector<float> *clusterEta = nullptr;
	std::vector<float> *clusterPhi = nullptr;
	std::vector<int> *clusterLayer = nullptr;
	std::vector<float> *clusterSigma = nullptr;
	
	std::vector<float> *truthTauEt = nullptr; //visible truth tau 
	std::vector<float> *truthTauEta = nullptr;
 	std::vector<float> *truthTauPhi = nullptr;
 	
 	std::vector<float> *towerEt = nullptr;   //trig tower in 0.1 * 0.1
 	std::vector<float> *towerEta_index = nullptr;
 	std::vector<float> *towerPhi_index = nullptr;
 	
 	std::vector<float> *seedet = nullptr;    //seed info
 	std::vector<float> *seedEta = nullptr;
 	std::vector<float> *seedPhi = nullptr;
	
	std::vector<float> *fCoreInner = nullptr;//isolation (inner and outer window sum) from jets
	std::vector<float> *fCoreOuter = nullptr;
	std::vector<float> *fCore = nullptr;
	
	std::vector<float> *recon_tau_ET = nullptr; //final reconstructed Et of tau candidates
	float bkg_leadJet = 0;
	
	TH2D *cellMapEM0;
	TH2D *cellMapEM1;
	TH2D *cellMapEM2;
	TH2D *cellMapEM3;
	TH2D *cellMapEM4;
	TH2D *cellMapEM7;
	
	int runNumber=0;
	//int eventNumbe=0;
	
	int globalCounter = 0;
	int clusterCt = 0;

  
 
};

#endif //> !TRIGL0GEPPERF_GEPTAUALG_H
