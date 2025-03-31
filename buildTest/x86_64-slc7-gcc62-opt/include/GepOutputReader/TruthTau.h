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


class TruthTau {
  public:
    // Tau var
    float pt = -99.; 
    float eta = -99.; 
    float phi = -99.;  
    TLorentzVector p4 = {TLorentzVector(0.,0.,0.,0.)}; 
    TLorentzVector total_p4 = {TLorentzVector(0.,0.,0.,0.)}; 
    TLorentzVector tauNeutrino_p4 = {TLorentzVector(0.,0.,0.,0.)}; 

    // Decay tags
    int n_track = 0; 
    int n_charged_meson = 0; 
    int n_neutral_meson = 0; 
    int n_lepton = 0; 
    bool is_hadronic = false; 
    bool is_leptonic_ele = false; 
    bool outgoing_tau = false; 

    // Matched TC var, keyed by cl_name
    std::map<TString, int> n_matchedCluster; 
    std::map<TString, std::vector<float>> matchedClusters_et; 
    std::map<TString, std::vector<float>> matchedClusters_dR; 
    std::map<TString, std::vector<float>> matchedClusters_EngFracEM; 

    // Methods
    void set_tau(TLorentzVector TLV) {
      p4 = TLV; 
      pt = p4.Pt(); 
      eta = p4.Eta(); 
      phi = p4.Phi(); 
    }

    void process_decays(const xAOD::TruthParticle_v1 *tau) {
      const xAOD::TruthVertex *decayVtx = tau->decayVtx(); 
      const xAOD::TruthParticle *Outparticle;
      for (unsigned int v = 0;  v < decayVtx->nOutgoingParticles(); ++v ) {
        Outparticle = decayVtx->outgoingParticle(v); 
        if (Outparticle->status()==3) continue;
        switch (abs(Outparticle->pdgId())) {
          case 11: // e
            is_leptonic_ele = true; 
            n_lepton ++; 
            break; 
          case 13: // mu
            n_lepton ++; 
            break; 
          case 15: // tau
            outgoing_tau = true; 
            break; 
          case 16: // tau nu
            tauNeutrino_p4.SetPtEtaPhiM(Outparticle->pt(), Outparticle->eta(), Outparticle->phi(), 0); 
            set_tau(total_p4 - tauNeutrino_p4); 
            break; 
          case 111: // pi0
            n_neutral_meson ++; 
            break; 
          case 211: // pi+-
            is_hadronic = true; 
            n_charged_meson ++; 
            break; 
          case 311: // K0
            n_neutral_meson ++; 
            break; 
          case 321: // K+-
            is_hadronic = true; 
            n_charged_meson ++; 
            break; 
        }
        if (abs(Outparticle->charge())==1){
          n_track ++; 
        }
      }
    }

    void set_matched_topoclusters(std::string cl_name, const xAOD::CaloClusterContainer *clusters, float dR_max, float cluster_et_min = 0.){
      n_matchedCluster[cl_name] = 0; 
      matchedClusters_et[cl_name] = {}; 
      matchedClusters_dR[cl_name] = {}; 
      matchedClusters_EngFracEM[cl_name] = {}; 
      for (auto iClust : *clusters){
        float cluster_et = iClust->et(); 
        float deltaR = TMath::Sqrt( ((eta-iClust->eta())*(eta-iClust->eta())) + ((phi-iClust->phi())*(phi-iClust->phi())) );
        if (deltaR < dR_max && cluster_et > cluster_et_min){
          matchedClusters_et[cl_name].push_back(cluster_et); 
          matchedClusters_dR[cl_name].push_back(deltaR); 
          n_matchedCluster[cl_name] ++; 
          matchedClusters_EngFracEM[cl_name].push_back(iClust->getMomentValue(xAOD::CaloCluster_v1::MomentType(701))); //ENG_FRAC_EM 
        }
      }
    }

    // Constructor
    TruthTau(const xAOD::TruthParticle_v1 *tau) {
      pt = tau->pt(); 
      eta = tau->eta(); 
      phi = tau->phi(); 
      total_p4.SetPtEtaPhiM(pt, eta, phi, 1776); 
      p4 = total_p4; 
    }
};
