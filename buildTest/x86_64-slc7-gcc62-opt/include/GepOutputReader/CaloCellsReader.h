#ifndef CALOCELLSREADER_CALOCELLSREADERALG_H
#define CALOCELLSREADER_CALOCELLSREADERALG_H 1

#include "AthAnalysisBaseComps/AthAnalysisAlgorithm.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterAuxContainer.h"
#include "xAODCaloEvent/CaloCluster.h"
#include "CaloInterface/ICalorimeterNoiseTool.h"
#include "CaloDetDescr/CaloDetDescrManager.h"
#include "CaloIdentifier/CaloCell_ID.h"

class CaloCellsReader: public ::AthAnalysisAlgorithm {
 public:
  CaloCellsReader( const std::string& name, ISvcLocator* pSvcLocator );
  virtual ~CaloCellsReader();

  ///uncomment and implement methods as required

                                        //IS EXECUTED:
  virtual StatusCode  initialize();     //once, before any input is loaded
  //virtual StatusCode  beginInputFile(); //start of each input file, only metadata loaded
  virtual StatusCode  firstExecute();   //once, after first eventdata is loaded (not per file)
  virtual StatusCode  execute();        //per event
  //virtual StatusCode  endInputFile();   //end of each input file
  //virtual StatusCode  metaDataStop();   //when outputMetaStore is populated by MetaDataTools
  virtual StatusCode  finalize();       //once, after all events processed

  virtual StatusCode getNeighbours(const CaloCellContainer* allcells, const CaloCell* acell, std::vector<unsigned int> neighbours);


 private:

  ToolHandle<ICalorimeterNoiseTool> m_noiseTool;
  const CaloCell_ID* m_ccIdHelper;

  TTree* m_tree = 0;

  std::vector<float> truthTauEt; //visible truth tau
	std::vector<float> truthTauEta;
 	std::vector<float> truthTauPhi;

  std::vector<float> cells_eta;
  std::vector<float> cells_phi;
  std::vector<float> cells_sinTh;
  std::vector<float> cells_cosTh;
  std::vector<float> cells_cosPhi;
  std::vector<float> cells_sinPhi;
  std::vector<float> cells_cotTh;
  std::vector<float> cells_x;
  std::vector<float> cells_y;
  std::vector<float> cells_z;

  std::vector<float> cells_etaMin;
  std::vector<float> cells_etaMax;
  std::vector<float> cells_phiMin;
  std::vector<float> cells_phiMax;
  std::vector<float> cells_etaGranularity;
  std::vector<float> cells_phiGranularity;
  std::vector<int>   cells_layer;

  std::vector<unsigned int> cells_ID;
  std::vector<float> cells_totalNoise;
  std::vector<float> cells_electronicNoise;
  std::vector<std::string> cells_detName;
  std::vector<unsigned int> cells_sampling;
  std::vector<bool> cells_badcell;

  std::vector<bool> cells_IsEM;
  std::vector<bool> cells_IsEM_Barrel;
  std::vector<bool> cells_IsEM_EndCap;
  std::vector<bool> cells_IsEM_BarrelPos;
  std::vector<bool> cells_IsEM_BarrelNeg;
  std::vector<bool> cells_IsFCAL;
  std::vector<bool> cells_IsHEC;
  std::vector<bool> cells_IsTile;

  //std::vector<std::vector<unsigned int>> neighbours;

};

#endif //> !CALOCELLSREADER_CALOCELLSREADERALG_H
