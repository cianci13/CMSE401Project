/*
 *   Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration
 */

#include "TrigL0GepPerf/CustomJet.h"
#include "TrigL0GepPerf/ConeJetMaker.h"
#include <iostream>
#include <fstream>

double deltaR (double eta_1, double eta_2, double phi_1, double phi_2);

void Gep::ConeJetMaker::sortSeeds()
{

  std::sort(m_seeds.begin(), m_seeds.end(), 
  [](const TLorentzVector &a, const TLorentzVector &b)
  { 
    return a.Pt() > b.Pt(); 
  }
  );
}

void Gep::ConeJetMaker::setSeeds(const xAOD::JetContainer *seeds)
{
  for (auto seed : *seeds) {
    TLorentzVector vec;  
    if (seed->pt() > 0) {
      vec.SetPtEtaPhiM(seed->pt(), seed->eta(), seed->phi(), 0.);
      m_seeds.push_back(vec);
    }     
  }

}

void Gep::ConeJetMaker::setSeeds(const xAOD::JetRoIContainer *seeds)
{
  for (auto seed : *seeds) {
    TLorentzVector vec;
     if (seed->et8x8() > 0) {
      vec.SetPtEtaPhiM(seed->et8x8(), seed->eta(), seed->phi(), 0.);
      m_seeds.push_back(vec);
    }    
  }
 
}

void Gep::ConeJetMaker::setSeeds(const xAOD::CaloClusterContainer *seeds)
{
  for (auto seed : *seeds)
  {
    TLorentzVector vec;
    if (seed->et() > 0)
    {
      vec.SetPtEtaPhiM(seed->et(), seed->eta(), seed->phi(), 0.);  // pt = et
      m_seeds.push_back(vec);
    }
  }
  
}

void Gep::ConeJetMaker::mergeNearBySeeds(float dRmin)
{
  //std::cout << "Size before merging: " << m_seeds.size() << std::endl;
  Gep::ConeJetMaker::sortSeeds();
  
  std::vector<TLorentzVector> newSeeds;
  std::vector<int> indices_to_skip; 

  int outer_index(0);
  for (auto seed1: m_seeds){
    //std::cout << "Outer index = " << outer_index << std::endl;
    // if seed has already been checked, move to the next one
    if (std::find(indices_to_skip.begin(), indices_to_skip.end(), outer_index) != indices_to_skip.end()){
      outer_index++;
      continue;
    }
    //std::cout << " Pt seed1 = " << seed1.Pt() << std::endl;
    std::vector<TLorentzVector> seeds_to_check;

    // find all other seeds within dRmin 
    int inner_index(0);
    for (auto seed2: m_seeds){
      //std::cout << "Inner index = " << inner_index << std::endl;
      // if seed has already been checked, move to the next one
      if (std::find(indices_to_skip.begin(), indices_to_skip.end(), inner_index) != indices_to_skip.end()){
      inner_index++;
      //std::cout << "Found in indices_to_skip, moving on. " << std::endl;
      continue;
      }
      
      float dR = seed1.DeltaR(seed2);
      //std::cout << "dR = " << dR << std::endl;
      if(dR < dRmin){
        //std::cout << "dR < min dR " << std::endl;
        // this considers seed1 as well (dR=0)
        seeds_to_check.push_back(seed2);
        indices_to_skip.push_back(inner_index);
        //std::cout << " Pt seed to check = " << seed2.Pt() << std::endl;
      }  
      inner_index++;    
    }
    
    //std::cout << "I'm checking " << seeds_to_check.size() << " seeds. " << std::endl;
    // keep only seed with highest Et
    auto maxElementIndex = std::max_element(seeds_to_check.begin(), seeds_to_check.end(),
    []( const TLorentzVector &a, const TLorentzVector &b) {
      return a.Pt() < b.Pt();
    } );
    
    TLorentzVector vec_max= *maxElementIndex;
    //std::cout << "Max Pt seed = " << vec_max.Pt() << std::endl;

    // store seed with max Et in new vector 
    newSeeds.push_back(vec_max);
    
    outer_index++;
  }
  m_seeds = newSeeds;
  //std::cout << "Size after merging: " << m_seeds.size() << std::endl;
}


std::vector<Gep::CustomJet> Gep::ConeJetMaker::makeJet( const std::vector<Gep::CustomTopoCluster> &clusters)
{
  std::vector<Gep::CustomJet> jets;
  //int N_SEED_MAX = 10;
  //int N_JETS_MAX = N_SEED_MAX;
  //int N_CLUSTER_MAX = 40;

  //int seed_counter {0};
  for (auto seed : m_seeds)
  {
    //if (seed_counter == N_SEED_MAX) break;
    //seed_counter++;

    float seedEt = seed.Et();

    // skip seeds with Et below threshold
    if(seedEt < m_seedEtThreshold) continue; 
    float seedEta = seed.Eta();
    float seedPhi = seed.Phi();
    
    Gep::CustomJet jet;

    jet.radius = m_jetR;
    jet.seedEta = seedEta;
    jet.seedPhi = seedPhi;
    jet.seedEt = seedEt;

    TLorentzVector jetVec;
    float px{0}, py{0}, pz{0}, pt{0};
    float ex{0}, ey{0}, ez{0}, et{0};
    //int clusterIndex {0};
    
    //build jet with clusters within dR from seed
    //int cluster_counter{0};
    for (const auto &cl: clusters) {
      //if (cluster_counter == N_CLUSTER_MAX) break;
      //cluster_counter++;

      float dR_seed_cl = deltaR(seedEta, cl.vec.Eta(), seedPhi, cl.vec.Phi());

      if (dR_seed_cl < m_jetR) {
        jetVec += cl.vec;        
        px += cl.vec.Px();
	      py += cl.vec.Py();
	      pz += cl.vec.Pz();
        pt += cl.vec.Pt();
        
        
        ex += cl.vec.Et()* cos(cl.vec.Phi());
        ey += cl.vec.Et() * sin(cl.vec.Phi());
        ez += cl.vec.Et() * sinh(cl.vec.Eta());
        et += cl.vec.Et();
     
        //jet.constituentsIndices.push_back(clusterIndex);
        jet.constituentsIndices.push_back(cl.containerIndex);
      }
      //clusterIndex++;
    }

    //std::cout << " et = " << et << " pt = " << pt << "tlv pt = " << jetVec.Pt() << "tlv et = " << jetVec.Et() << std::endl;
    //std::cout << " ex = " << ex << " px = " << px << "tlv px = " << jetVec.Px() << std::endl;
    //std::cout << " ey = " << ey << " py = " << py << "tlv py = " << jetVec.Py() << std::endl;
    //std::cout << " ez = " << ez << " pz = " << pz << "tlv pz = " << jetVec.Pz() << std::endl;
    float jet_phi = asin(ey/et);
    float jet_eta = asinh(ez/et);
    //std::cout << " phi = " << jet_phi << " tlv phi = " << jetVec.Phi() << std::endl;
    //std::cout << " eta = " << jet_eta << " tlv eta = " << jetVec.Eta() << std::endl;

    // skip cone jets with 0 constituents
    if (jet.constituentsIndices.size()==0) continue;
    

    // recombination scheme
    if (m_recombScheme == "EScheme") {
      // default option: add four-vectors of constituents
      jet.vec = jetVec;
    }
    else if (m_recombScheme == "SeedScheme") {
      // massless jet, correct pt, re-using seed (eta,phi)
      float m = 0;
      float pt = std::sqrt(px*px + py*py);
      jet.vec.SetPtEtaPhiM(pt, seedEta, seedPhi, m);
    }
    else if (m_recombScheme == "ApproxEtScheme") {
      // seed scheme with approximate et
      float m = 0;
      jet.vec.SetPtEtaPhiM(et, seedEta, seedPhi, m);
    }
    else {
      std::cerr << "Error: " << m_recombScheme << " is not a valid recombination scheme.\n";
      std::exit(1);
    }

    jets.push_back(jet);
  }

  /////// Store data for HLS testbench /////////
  /*
  std::ofstream indata_seeds("indata_seeds"+m_recombScheme+".txt", std::ios::out | std::ios::app);
  std::ofstream indata_cls("indata_clusters"+m_recombScheme+".txt", std::ios::out | std::ios::app);
  std::ofstream outdata_jets("outdata_jets"+m_recombScheme+".txt", std::ios::out | std::ios::app);



  for (int i = 0; i < m_seeds.size(); i++)
  {
    if (i == N_SEED_MAX) break;
    auto seed = m_seeds.at(i);
    if (seed.Et() < m_seedEtThreshold)
      continue;
    std::cout << seed.Et() << " " << seed.Eta() << " " << seed.Phi() << std::endl;
    indata_seeds << seed.Et() << " " << seed.Eta() << " " << seed.Phi() << "\n";
  }
  indata_seeds << "\n";
  indata_seeds.close();

  for (int i = 0; i < clusters.size(); i++)
  {
    if (i == N_CLUSTER_MAX) break;
    auto cluster = clusters.at(i);
    indata_cls << cluster.vec.Et() << " " << cluster.vec.Eta() << " " << cluster.vec.Phi() << "\n";
  }
  indata_cls << "\n";
  indata_cls.close();

  for(int i=0; i<jets.size(); i++){
    if(i == N_JETS_MAX) break;
    auto jet = jets.at(i);
    outdata_jets << jet.vec.Et() << " " << jet.vec.Eta() << " " << jet.vec.Phi() << "\n";
  }
  outdata_jets << "\n";
  outdata_jets.close();
  */

  return jets;
}



double deltaR (double eta1, double eta2, double phi1, double phi2) {
  double deltaPhi = TVector2::Phi_mpi_pi(phi1 - phi2);
  double deltaEta = eta1 - eta2;
  return std::sqrt( deltaEta*deltaEta + deltaPhi*deltaPhi );
}
