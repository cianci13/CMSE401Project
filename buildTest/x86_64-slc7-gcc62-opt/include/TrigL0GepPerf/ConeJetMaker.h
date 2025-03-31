/*
 *   Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration
 */

#ifndef TRIGL0GEPPERF_CONEJETMAKER_H
#define TRIGL0GEPPERF_CONEJETMAKER_H

#include <string>
#include <TLorentzVector.h>

#include "xAODTrigger/JetRoI.h"
#include "xAODTrigger/JetRoIAuxContainer.h"
#include "xAODTrigger/JetRoIContainer.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterAuxContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"

#include "TrigL0GepPerf/IJetMaker.h"
#include "TrigL0GepPerf/CustomJet.h"
#include "TrigL0GepPerf/CustomTopoCluster.h"


namespace Gep
{
  //template <typename T>
  class ConeJetMaker : public Gep::IJetMaker
  {
  public:

  ConeJetMaker(float jetR, float seedEtThreshold = 5.e3 /*MeV*/, std::string recombScheme = "ApproxEtScheme") : 
      m_jetR(jetR),
      m_seedEtThreshold(seedEtThreshold),
      m_recombScheme(recombScheme)
    {}

    std::string getName() const { return "ConeJet"; }
    std::vector<Gep::CustomJet> makeJet(const std::vector<Gep::CustomTopoCluster> &clusters);
    void mergeNearBySeeds(float dRmin);
    void setSeeds(const xAOD::JetContainer *seeds);
    void setSeeds(const xAOD::JetRoIContainer *seeds);
    void setSeeds(const xAOD::CaloClusterContainer *seeds);
    void sortSeeds();
    float getJetR() { return m_jetR; }
    float getSeedEtThreshold() { return m_seedEtThreshold; }
    std::string getRecombScheme() { return m_recombScheme; }

    std::vector<TLorentzVector> m_seeds;

  private:
    float m_jetR;
    float m_seedEtThreshold;
    std::string m_recombScheme;
    //const mutable xAOD::JetRoIContainer *m_seeds;
    // const mutable xAOD::JetContainer *m_seeds;

   
    //T m_seeds;
  };

}

#endif //TRIGL0GEPPERF_CONEJETMAKER_H
