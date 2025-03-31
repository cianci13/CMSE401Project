/*
 *   Copyright (C) 2002-2022 CERN for the benefit of the ATLAS collaboration
 */

#include "TrigL0GepPerf/ClusterEtCutAlg.h"

#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterAuxContainer.h"
#include "xAODCaloEvent/CaloCluster.h"



ClusterEtCutAlg::ClusterEtCutAlg( const std::string& name, ISvcLocator* pSvcLocator ) :
  AthAnalysisAlgorithm( name, pSvcLocator ),
  m_topoclLabel ("TopoclLabel")
{
  declareProperty("TopoclLabel", m_topoclLabel, "Topoclusters label");
  declareProperty("TopoclEtGeVCuts", m_topoclEtGeVCuts, "List of topoclusters Et cuts [GeV]");

}


StatusCode ClusterEtCutAlg::execute() {
  ATH_MSG_DEBUG ("Executing " << name() << "...");


  // Retrieve input cluster container
  std::string topoclName = m_topoclLabel + "TopoClusters";
  const xAOD::CaloClusterContainer* clusters = nullptr;
  CHECK(evtStore()->retrieve(clusters,topoclName));
  ATH_MSG_DEBUG("Retrieve " << topoclName);

  for (const auto &etGeVCut: m_topoclEtGeVCuts) {

    // Create the new container and its auxiliary store
    auto goodClusters = std::make_unique < xAOD::CaloClusterContainer>();
    auto goodClustersAux = std::make_unique<xAOD::CaloClusterAuxContainer>();
    goodClusters->setStore(goodClustersAux.get()); //< Connect the two

    for (auto clus: *clusters) {
      // Skip clusters below energy cut 
      if (clus->et()/1.e3 < etGeVCut) continue;

      xAOD::CaloCluster* goodClus = new xAOD::CaloCluster();
      goodClusters->push_back(goodClus);
      *goodClus = *clus;
    }

    std::string goodClustersName = m_topoclLabel + "Cut" + std::to_string(static_cast<int>(etGeVCut)) + "GeVTopoClusters";
    std::string goodClustersNameAux = goodClustersName + "Aux.";

    ATH_MSG_DEBUG("Storing " << goodClustersName);
    CHECK(evtStore()->record(std::move(goodClusters), goodClustersName));
    CHECK(evtStore()->record(std::move(goodClustersAux), goodClustersNameAux));
  }


  return StatusCode::SUCCESS;
}
