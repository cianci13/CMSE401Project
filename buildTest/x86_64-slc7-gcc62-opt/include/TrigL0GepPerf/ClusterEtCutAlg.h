/*
 *   Copyright (C) 2002-2022 CERN for the benefit of the ATLAS collaboration
 */

#ifndef TRIGL0GEPPERF_CLUSTERETCUTALG_H
#define TRIGL0GEPPERF_CLUSTERETCUTALG_H 1

#include "AthAnalysisBaseComps/AthAnalysisAlgorithm.h"
#include "GaudiKernel/ToolHandle.h"

#include "TrigL0GepPerf/CustomTopoCluster.h"
#include "TrigL0GepPerf/CustomJet.h"

#include <string>


class ClusterEtCutAlg: public ::AthAnalysisAlgorithm {

 public:
  ClusterEtCutAlg( const std::string& name, ISvcLocator* pSvcLocator );
  virtual StatusCode  execute() override; 

 private:

  std::string m_topoclLabel;
  std::vector<float> m_topoclEtGeVCuts;  

};

#endif //> !TRIGL0GEPPERF_CLUSTERETCUTALG_H
