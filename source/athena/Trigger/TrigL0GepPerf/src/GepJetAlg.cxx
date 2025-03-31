/*
 *   Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration
 */

#include "TrigL0GepPerf/GepJetAlg.h"

// Base class
#include "TrigL0GepPerf/IJetMaker.h"

// *** Include derived jet algorithm classes ***
#include "TrigL0GepPerf/ModAntikTJetMaker.h"
#include "TrigL0GepPerf/ConeJetMaker.h"

#include "xAODEventInfo/EventInfo.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterAuxContainer.h"
#include "xAODCaloEvent/CaloCluster.h"

#include "xAODTrigger/JetRoI.h"
#include "xAODTrigger/JetRoIAuxContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#include "xAODTrigger/JetRoIContainer.h"




GepJetAlg::GepJetAlg( const std::string& name, ISvcLocator* pSvcLocator ) :
  AthAnalysisAlgorithm( name, pSvcLocator ),
  m_jetAlg ("JetAlg"),
  m_topoclLabel ("TopoclLabel")
{
  declareProperty("JetAlg", m_jetAlg, "Custom jet algorithm label. New custom jets will be named m_jetAlg + m_topoclLabel +\"Jets\".");
  declareProperty("TopoclLabel", m_topoclLabel, "Topoclusters label");
}



StatusCode GepJetAlg::execute() {
  ATH_MSG_DEBUG ("Executing " << name() << "...");


  // get clusters
  std::string topoclName = m_topoclLabel + "TopoClusters";
  const xAOD::CaloClusterContainer* clusters = nullptr;
  CHECK(evtStore()->retrieve(clusters,topoclName));

 
  // fill custom clusters
  std::vector<Gep::CustomTopoCluster> customClusters;
  int index {0};
  for( auto iClus: *clusters ){
    Gep::CustomTopoCluster clus;
    clus.containerIndex = index;
    clus.vec.SetPxPyPzE(iClus->p4().Px(), iClus->p4().Py(),
                        iClus->p4().Pz(), iClus->e());
    customClusters.push_back(clus);
    ++index;
  }

  // order custom topoclusters
  std::sort(customClusters.begin(), customClusters.end(),
            [](const Gep::CustomTopoCluster &a, const Gep::CustomTopoCluster &b)
            {
              return a.vec.Et() > b.vec.Et();
            });
  

  // run jet algorithm
  std::unique_ptr<Gep::IJetMaker> jetMaker{};

  // -------------------------------------------------
  // *** instantiate custom jet algorithm classes ***

  if ( m_jetAlg=="ModAntikT" ) {
    auto customJetAlg = std::make_unique<Gep::ModAntikTJetMaker>();
    jetMaker = std::move(customJetAlg);
  }
  
  else if ( m_jetAlg=="Cone4SeedjRJ" ) {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4);
    const xAOD::JetRoIContainer * seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }

  else if (m_jetAlg == "Cone4SeedjRJ5GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 5.e3);
    const xAOD::JetRoIContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedjRJ20GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 20.e3);
    const xAOD::JetRoIContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedjRJ30GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 30.e3);
    const xAOD::JetRoIContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedjRJ35GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 35.e3);
    const xAOD::JetRoIContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedjRJ40GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 40.e3);
    const xAOD::JetRoIContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedjRJ45GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 45.e3);
    const xAOD::JetRoIContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedjRJ50GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 50.e3);
    const xAOD::JetRoIContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "jRoundJetsPerf"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedOffAntiKt5GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 5.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt4EMTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedOffAntiKt20GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 20.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt4EMTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedOffAntiKt30GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 30.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt4EMTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedOffAntiKt35GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 35.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt4EMTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedOffAntiKt40GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 40.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt4EMTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedOffAntiKt45GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 45.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt4EMTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone4SeedOffAntiKt50GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 50.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt4EMTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  
  // Cone4SeedTopo: cone jets built using topoclusters as seed.
  // An Et cut can be applied on top of the Et cut on the topoclusters container.
  else if (m_jetAlg.find("Cone4SeedTopo5GeV") != std::string::npos)
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 5.e3);
    coneJetMaker->setSeeds(clusters);
    if (m_jetAlg.find("Merg1") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.1);
    }
    if (m_jetAlg.find("Merg2") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.2);
    }
    if (m_jetAlg.find("Merg3") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.3);
    }
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg.find("Cone4SeedTopoSeedScheme5GeV") != std::string::npos)
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 5.e3, "SeedScheme");
    coneJetMaker->setSeeds(clusters);
    if (m_jetAlg.find("Merg1") != std::string::npos)
    {
      coneJetMaker->mergeNearBySeeds(0.1);
    }
    if (m_jetAlg.find("Merg2") != std::string::npos)
    {
      coneJetMaker->mergeNearBySeeds(0.2);
    }
    if (m_jetAlg.find("Merg3") != std::string::npos)
    {
      coneJetMaker->mergeNearBySeeds(0.3);
    }
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg.find("Cone4SeedTopoApproxEtScheme5GeV") != std::string::npos)
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 5.e3, "ApproxEtScheme");
    coneJetMaker->setSeeds(clusters);
    if (m_jetAlg.find("Merg1") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.1);
    }
    if (m_jetAlg.find("Merg2") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.2);
    }
    if (m_jetAlg.find("Merg3") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.3);
    }
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg.find("Cone4SeedTopo10GeV") != std::string::npos)
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 10.e3);
    coneJetMaker->setSeeds(clusters);
    if (m_jetAlg.find("Merg1") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.1);
    }
    if (m_jetAlg.find("Merg2") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.2);
    }
    if (m_jetAlg.find("Merg3") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.3);
    }
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg.find("Cone4SeedTopo15GeV") != std::string::npos)
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 15.e3);
    coneJetMaker->setSeeds(clusters);
    if (m_jetAlg.find("Merg1") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.1);
    }
    if (m_jetAlg.find("Merg2") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.2);
    }
    if (m_jetAlg.find("Merg3") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.3);
    }
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg.find("Cone4SeedTopo20GeV") != std::string::npos)
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 20.e3);
    coneJetMaker->setSeeds(clusters);
    if (m_jetAlg.find("Merg1") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.1);
    }
    if (m_jetAlg.find("Merg2") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.2);
    }
    if (m_jetAlg.find("Merg3") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.3);
    }
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg.find("Cone4SeedTopo30GeV") != std::string::npos)
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.4, 30.e3);
    coneJetMaker->setSeeds(clusters);
    if (m_jetAlg.find("Merg1") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.1);
    }
    if (m_jetAlg.find("Merg2") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.2);
    }
    if (m_jetAlg.find("Merg3") != std::string::npos) {
      coneJetMaker->mergeNearBySeeds(0.3);
    }
    jetMaker = std::move(coneJetMaker);
  }
  // TopoJets: the jet is built using only the seed cluster. 
  // An Et cut can be applied on top of the Et cut on the topoclusters container.
  else if (m_jetAlg == "Topo0GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.00001);
    coneJetMaker->setSeeds(clusters);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Topo10GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.00001, 20.e3);
    coneJetMaker->setSeeds(clusters);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Topo20GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(0.00001, 20.e3);
    coneJetMaker->setSeeds(clusters);
    jetMaker = std::move(coneJetMaker);
  }

  // Large R jets 
  else if (m_jetAlg == "Cone10SeedOffAntiKt0GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(1., 0.);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt10LCTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone10SeedOffAntiKt10GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(1., 10.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt10LCTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone10SeedOffAntiKt20GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(1., 20.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt10LCTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }
  else if (m_jetAlg == "Cone10SeedOffAntiKt30GeV")
  {
    auto coneJetMaker = std::make_unique<Gep::ConeJetMaker>(1., 30.e3);
    const xAOD::JetContainer *seeds = 0;
    CHECK(evtStore()->retrieve(seeds, "AntiKt10LCTopoJets"));
    coneJetMaker->setSeeds(seeds);
    jetMaker = std::move(coneJetMaker);
  }

  //---------------------------------------------------

  
  if ( !jetMaker ) {
    ATH_MSG_ERROR( "JetMaker is a null pointer." );
    return StatusCode::FAILURE;
  }
  ATH_MSG_DEBUG( "Running " << jetMaker->getName() << " jet algorithm." );


 
  std::vector<Gep::CustomJet> customJets = jetMaker->makeJet( customClusters );
  

  // if no jets were found, skip event
  //if( customJets.empty() ){
  //  return StatusCode::SUCCESS;
  //}

  // create the new container and its auxiliary store
  auto athenaJets = std::make_unique<xAOD::JetContainer>();
  auto athenaJetsAux = std::make_unique<xAOD::JetAuxContainer>();

  athenaJets->setStore(athenaJetsAux.get()); //< connect the two


  // store custom jets in athena format
  for(const auto& iJet: customJets){

    std::unique_ptr<xAOD::Jet> athenaJet{new xAOD::Jet()};
    xAOD::Jet* ijet = athenaJet.get();
    athenaJets->push_back(std::move(athenaJet));

    xAOD::JetFourMom_t P4;
    P4.SetPt(iJet.vec.Pt());
    P4.SetEta(iJet.vec.Eta());
    P4.SetPhi(iJet.vec.Phi());
    P4.SetM(iJet.vec.M());

    ijet->setJetP4( P4 );

    ijet->setAttribute("RCut", iJet.radius);
    ijet->setAttribute("SeedEta", iJet.seedEta); // < custom attributes
    ijet->setAttribute("SeedPhi", iJet.seedPhi); //
    ijet->setAttribute("SeedEt", iJet.seedEt); //

    for (const auto& i: iJet.constituentsIndices) {
      ijet->addConstituent(clusters->at(i));
    }

  }

  std::string jetsName = m_jetAlg + m_topoclLabel + "Jets";
  std::string jetsNameAux = jetsName + "Aux.";

  ATH_MSG_DEBUG( "Storing " << jetsName );
  CHECK( evtStore()->record(std::move(athenaJets),jetsName) );
  CHECK( evtStore()->record(std::move(athenaJetsAux),jetsNameAux) );


  return StatusCode::SUCCESS;
}
