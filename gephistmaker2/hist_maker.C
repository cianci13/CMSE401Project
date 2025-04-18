#pragma link C class vector<vector<float> >+;

class TrigObj {
  public:
    float et = -99.; 
    float eta = -99.; 
    float phi = -99.; 
    float EngFracEM = -99.; 

    TrigObj(){
    }
};

float DeltaR(float eta1, float phi1, float eta2, float phi2){
  return pow(pow(eta1-eta2,2) + pow(phi1-phi2,2),.5); 
}

tuple<float, float, float> NearbyEt(TrigObj seedObj, vector<TrigObj> surroundings){
  float core_et = 0; 
  float ring1_et = 0; 
  float ring2_et = 0; 
  for (TrigObj nearbyCluster : surroundings){
    float deltaR = DeltaR(seedObj.eta, seedObj.phi, nearbyCluster.eta, nearbyCluster.phi); 
    if (deltaR < 0.1){
      core_et += nearbyCluster.et;
    } else if (0.1 <= deltaR < 0.2){
      ring1_et += nearbyCluster.et;
    } else if (0.2 <= deltaR < 0.3){
      ring2_et += nearbyCluster.et;
    }
  }
  return tuple<float, float, float>{core_et, ring1_et, ring2_et}; 
}

bool TauTrigger(TrigObj seedObj, vector<TrigObj> surroundings, float min_et, float min_C_all, float max_R1_all, float max_R2_all, float min_EngFracEM, float max_EngFracEM){
  float core_et, ring1_et, ring2_et; 
  tie(core_et, ring1_et, ring2_et) = NearbyEt(seedObj, surroundings); 
  float total_nearby_et = core_et + ring1_et + ring2_et; 
  if (seedObj.et < min_et) return false; // Et cut
  if (core_et/total_nearby_et < min_C_all) return false; // Core isolation cut
  if (ring1_et/total_nearby_et > max_R1_all) return false; // Ring1 isolation cut
  if (ring2_et/total_nearby_et > max_R2_all) return false; // Ring2 isolation cut
  if (!((min_EngFracEM <= seedObj.EngFracEM) && (seedObj.EngFracEM <= max_EngFracEM))) return false; 
  return true; 
}

void hist_maker(){
  // Params
  string dir = "/msu/data/t3work13/dcianciolo/gepOutput2/gep/run/"; 
  const string tree_file_name = dir + "outputGEPNtuple128mini.root"; 
  //const string tree_file_name = dir + "user.xinfei.GepOutputReader_mc15_14TeV.800281.Py8EG_AZ_Ztautau.recon.AOD.e8379_s3735_s3738_r13046_v4_agg.root"; 
  const string hist_file_name = dir + "128hists.root"; 
  const string clustList[] = {
	  "Calo422Cut0GeVTopoClusters", 
//	  "Calo422SKCut0GeVTopoClusters", 
//	  "Calo420Cut0GeVTopoClusters", 
//	  "Calo420SKCut0GeVTopoClusters", 
//	  "CaloCalCut0GeVTopoClusters", 
//	  "CaloCalSKCut0GeVTopoClusters", 
  };
  const string decayTagList[] = {
	  "_decayTagAll", 
//	  "_had", 
//	  "_had1Prong", 
//	  "_had3Prong", 
  }; 
  const string DRrangeList[] = {
//	  "_0-1dR", 
//	  "_0-15dR", 
//	  "_0-2dR", 
	  "_0-3dR", 
//	  "_1-2dR", 
//	  "_2-3dR", 
  };
  /*const string ptRangeList[] = {
          "_0-10pt",
          "_10-20pt",
          "_20-30pt",
          "_30-40pt",
          "_40-50pt",
          "_50-Infpt",  
  };*/
  /*const string etaRangeList[] = {
          "_0-025eta",
	  "_025-05eta",
	  "_05-075eta",
	  "_075-1eta",
	  "_1-125eta",
          "_125-15eta",
  	  "_15-175eta",
	  "_175-2eta",
          "_2-25eta",
  };*/
  const string ptRangeList[] = {
    "_0-6.5pt",
    "_6.5-12pt",
    "_12-29pt",
    "_29-infpt",
  };
  const string etaRangeList[] = {
    "_0-2eta",
    "_2-25eta",
    "_25-infeta",
  };

  const string neutralMesonList[] = {"", "_0neutral", "_1neutral", "_2neutral", "_3neutral", "_4neutral", "_5neutral"};
  const string chargedMesonList[] = {"_1charged", "_3charged", "_5charged",};

  map<string, pair<float, float>> ptPairs;
  /*pair<float, float> pair6(0.0, 10000.0);
  pair<float, float> pair7(10000.0, 20000.0);
  pair<float, float> pair8(20000.0, 30000.0);
  pair<float, float> pair9(30000.0, 40000.0);
  pair<float, float> pair10(40000.0, 50000.0);
  pair<float, float> pair11(50000.0, 10000000.0);
  ptPairs["_0-10pt"] = pair6;
  ptPairs["_10-20pt"] = pair7;
  ptPairs["_20-30pt"] = pair8;
  ptPairs["_30-40pt"] = pair9;
  ptPairs["_40-50pt"] = pair10;
  ptPairs["_50-Infpt"] = pair11;*/
  pair<float, float> pair6(0.0, 6500.0);
  pair<float, float> pair7(6500.0, 12000.0);
  pair<float, float> pair8(12000.0, 29000.0);
  pair<float, float> pair9(29000.0, 10000000.0);
  ptPairs["_0-6.5pt"] = pair6;
  ptPairs["_6.5-12pt"] = pair7;
  ptPairs["_12-29pt"] = pair8;
  ptPairs["_29-infpt"] = pair9;
  /*map<string, pair<float, float>> etaPairs;  
  pair<float, float> pair12(0.0, 0.25);
  pair<float, float> pair13(0.25, 0.5);
  pair<float, float> pair14(0.5, 0.75);
  pair<float, float> pair15(0.75, 1.0);
  pair<float, float> pair16(1.0, 1.25);
  pair<float, float> pair17(1.25, 1.5);
  pair<float, float> pair18(1.5, 1.75);
  pair<float, float> pair19(1.75, 2.0);
  pair<float, float> pair20(2.0, 2.5);
  etaPairs["_0-025eta"] = pair12;
  etaPairs["_025-05eta"] = pair13;
  etaPairs["_05-075eta"] = pair14;
  etaPairs["_075-1eta"] = pair15;
  etaPairs["_1-125eta"] = pair16;
  etaPairs["_125-15eta"] = pair17;
  etaPairs["_15-175eta"] = pair18;
  etaPairs["_175-2eta"] = pair19;
  etaPairs["_2-25eta"] = pair20;*/
  map<string, pair<float, float>> etaPairs;
  pair<float, float> pair12(0.0, 2.0);
  pair<float, float> pair13(2.0, 2.5);
  pair<float, float> pair14(2.5, 50);
  etaPairs["_0-2eta"] = pair12;
  etaPairs["_2-25eta"] = pair13;
  etaPairs["_25-infeta"] = pair14;
  map<string, pair<float, float>> dR_s2f; 
  dR_s2f["_0-1dR"] = pair(0., 0.1); 
  dR_s2f["_0-15dR"] = pair(0., 0.15); 
  dR_s2f["_0-2dR"] = pair(0., 0.2); 
  dR_s2f["_0-3dR"] = pair(0., 0.3); 
  dR_s2f["_1-2dR"] = pair(0.1, 0.2); 
  dR_s2f["_2-3dR"] = pair(0.2, 0.3); 
	  
  int numVisualizations = 0;  

  map<string, int> charged_meson_vals;
  charged_meson_vals["_1charged"] = 1;
  charged_meson_vals["_3charged"] = 3;
  charged_meson_vals["_5charged"] = 5;

  map<string, int> neutral_meson_vals;
  neutral_meson_vals["_0neutral"] = 0;
  neutral_meson_vals["_1neutral"] = 1;
  neutral_meson_vals["_2neutral"] = 2;
  neutral_meson_vals["_3neutral"] = 3;
  neutral_meson_vals["_4neutral"] = 4;
  neutral_meson_vals["_5neutral"] = 5;
  neutral_meson_vals[""] = 50;

// Read TTree
  TFile *tree_file = new TFile(tree_file_name.c_str()); 
  TTree *tree = (TTree*) tree_file->Get("ntuple"); 
//  tree->MakeClass(); 

  // Init vectors to get values from TTree
  vector<float> *recoTau_pt = 0;
  vector<float> *recoTau_eta = 0;
  vector<float> *recoTau_phi = 0;
  vector<float> *recoTau_et = 0;
  vector<float> *recoTau_nTaus = 0;
  vector<float> *truthTau_pt = 0; 
  vector<float> *truthTau_totalpt = 0; 
  vector<float> *truthTau_neutrinopt = 0; 
  vector<float> *truthTau_neutrinoeta = 0; 
  vector<float> *truthTau_neutrinophi = 0; 
  vector<float> *truthTau_eta = 0; 
  vector<float> *truthTau_phi = 0;
  vector<int> *truthTau_nProng = 0; 
  vector<int> *truthTau_nChargedMeson = 0; 
  vector<int> *truthTau_nNeutralMeson = 0; 
  vector<int> *truthTau_isHadronic = 0; 
  vector<int> *truthTau_isLeptonicEle = 0;
  tree->SetBranchAddress("recoTau_pt", &recoTau_pt);
  tree->SetBranchAddress("recoTau_et", &recoTau_et);
  tree->SetBranchAddress("recoTau_eta", &recoTau_eta);
  tree->SetBranchAddress("recoTau_phi", &recoTau_phi); 
  tree->SetBranchAddress("recoTau_nTaus", &recoTau_nTaus);
  tree->SetBranchAddress("truthTau_pt", &truthTau_pt); 
  tree->SetBranchAddress("truthTau_totalpt", &truthTau_totalpt);  
  tree->SetBranchAddress("truthTau_neutrinopt", &truthTau_neutrinopt);  
  tree->SetBranchAddress("truthTau_neutrinoeta", &truthTau_neutrinoeta);  
  tree->SetBranchAddress("truthTau_neutrinophi", &truthTau_neutrinophi);  
  tree->SetBranchAddress("truthTau_eta", &truthTau_eta); 
  tree->SetBranchAddress("truthTau_phi", &truthTau_phi); 
  tree->SetBranchAddress("truthTau_nProng", &truthTau_nProng); 
  tree->SetBranchAddress("truthTau_nChargedMeson", &truthTau_nChargedMeson); 
  tree->SetBranchAddress("truthTau_nNeutralMeson", &truthTau_nNeutralMeson); 
  tree->SetBranchAddress("truthTau_matchednChargedMeson", &truthTau_matchednChargedMeson); 
  tree->SetBranchAddress("truthTau_matchednNeutralMeson", &truthTau_matchednNeutralMeson); 
  tree->SetBranchAddress("truthTau_isHadronic", &truthTau_isHadronic); 
  tree->SetBranchAddress("truthTau_isLeptonicEle", &truthTau_isLeptonicEle); 


  gInterpreter->GenerateDictionary("vector<vector<float> >", "vector"); // Generate dict for vector<vector<float>>
  map<string, vector<float>*> clusters_et; 
  map<string, vector<float>*> clusters_eta; 
  map<string, vector<float>*> clusters_phi; 
  map<string, vector<float>*> clusters_EngFracEM; 
  map<string, vector<vector<float>>*> truthTau_matchedTC_et; 
  map<string, vector<vector<float>>*> truthTau_matchedTC_dR; 
  map<string, vector<vector<float>>*> truthTau_matchedTC_EngFracEM; 
  for (string cl_name : clustList){
    clusters_et[cl_name] = 0; 
    clusters_eta[cl_name] = 0; 
    clusters_phi[cl_name] = 0; 
    clusters_EngFracEM[cl_name] = 0; 
    truthTau_matchedTC_et[cl_name] = 0; 
    truthTau_matchedTC_dR[cl_name] = 0; 
    truthTau_matchedTC_EngFracEM[cl_name] = 0; 
    //tree->SetBranchAddress((cl_name+"_et").c_str(), &(clusters_et[cl_name])); 
    //tree->SetBranchAddress((cl_name+"_eta").c_str(), &(clusters_eta[cl_name])); 
    //tree->SetBranchAddress((cl_name+"_phi").c_str(), &(clusters_phi[cl_name])); 
    //tree->SetBranchAddress((cl_name+"_EngFracEm").c_str(), &(clusters_EngFracEM[cl_name])); 
    tree->SetBranchAddress(("truthTau_"+cl_name+"_matchedClusters_et").c_str(), &(truthTau_matchedTC_et[cl_name])); 
    tree->SetBranchAddress(("truthTau_"+cl_name+"_matchedClusters_dR").c_str(), &(truthTau_matchedTC_dR[cl_name])); 
    //tree->SetBranchAddress(("truthTau_"+cl_name+"_matchedClusters_EngFracEM").c_str(), &(truthTau_matchedTC_EngFracEM[cl_name])); 
  }

  // Init hist root file
  TFile *hist_file = new TFile(hist_file_name.c_str(), "recreate"); 
 
  // Init hists
  const string trigVars[] = {
	  "_etCut", 
	  "_engFracEmCut", 
	  "_coreCut", 
	  "_ring1Cut", 
	  "_ring2Cut", 
  }; 
  map<string, vector<string>> trigCuts; 
  trigCuts["_etCut"] = (vector<string>){"2e3", "3e3", "5e3"}; 
  trigCuts["_engFracEmCut"] = (vector<string>){"0.00", "0.33", "0.67"}; 
  trigCuts["_coreCut"] = (vector<string>){"0.3", "0.5", "0.7"}; 
  trigCuts["_ring1Cut"] = (vector<string>){"0.3", "0.5", "0.7"}; 
  trigCuts["_ring2Cut"] = (vector<string>){"0.3", "0.5", "0.7"}; 
  int pt_nbin = 120; 
  int pt_binmin = 0; 
  int pt_binmax = 120; 
  TH1F* h_truthTau_recoZMass; 
  TH1F* h_truthTotalTau_recoZMass; 
  h_truthTau_recoZMass = new TH1F("h_truthTau_recoZMass", ";reco Z mass (GeV);", 120, 0, 120); 
  h_truthTotalTau_recoZMass = new TH1F("h_truthTotalTau_recoZMass", ";reco Z mass (GeV);", 120, 0, 120); 
  map<string, TH1F*> h_recoTau_pt;
  map<string, TH1F*> h_recoTau_eta;
  map<string, TH1F*> h_recoTau_phi;
  map<string, TH1F*> h_recoTau_nTaus;
  map<string, TH1F*> h_truthTau_pt; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_pt_trig; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_pt_trigEffi; 
  map<string, TH1F*> h_truthTau_totalpt;
  map<string, TH1F*> h_truthTau_neutrinopt;
  map<string, TH1F*> h_truthTau_neutrinoeta;
  map<string, TH1F*> h_truthTau_neutrinophi;
  map<string, TH1F*> h_truthTau_visiblePtFraction; 
  map<string, TH1F*> h_truthTau_neutrinoPtFraction; 
  map<string, TH2F*> h_truthTau_totalptVsVisiblePtFraction; 
  map<string, TH2F*> h_truthTau_totalptVsNeutrinoPtFraction; 
  map<string, TH1F*> h_truthTau_eta; 
  map<string, TH1F*> h_truthTau_phi; 
  map<string, TH2F*> h_truthTau_chargedMesonVsNeutralMeson; 
  for (string decayTag : decayTagList){
    if (decayTag=="_decayTagAll"){
      h_recoTau_pt[decayTag] = new TH1F(("h_recoTau_pt"+decayTag).c_str(), "", 60, 2, 120);
      h_recoTau_eta[decayTag] = new TH1F(("h_recoTau_eta"+decayTag).c_str(), "", 100, -4, 4);
      h_recoTau_phi[decayTag] = new TH1F(("h_recoTau_phi"+decayTag).c_str(), "", 100, -3.5, 3.5);
      h_recoTau_nTaus[decayTag] = new TH1F(("h_recoTau_nTaus" + decayTag).c_str(), "", 100, 0, 50);
    }
    h_truthTau_pt[decayTag] = new TH1F(("h_truthTau_pt"+decayTag).c_str(), (decayTag+";tau pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
    for (string trigVar : trigVars){
    for (string trigCut : trigCuts[trigVar]){
      h_truthTau_pt_trig[decayTag][trigVar][trigCut] = new TH1F(("h_truthTau_pt_trig"+decayTag+trigVar+"_"+trigCut).c_str(), (decayTag+";tau pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
      h_truthTau_pt_trigEffi[decayTag][trigVar][trigCut] = new TH1F(("h_truthTau_pt_trigEffi"+decayTag+trigVar+"_"+trigCut).c_str(), (decayTag+";tau pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
    }
    }
    h_truthTau_totalpt[decayTag] = new TH1F(("h_truthTau_totalpt"+decayTag).c_str(), (decayTag+";tau total pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
    h_truthTau_neutrinopt[decayTag] = new TH1F(("h_truthTau_neutrinopt"+decayTag).c_str(), (decayTag+";tau neutrino pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
    h_truthTau_neutrinoeta[decayTag] = new TH1F(("h_truthTau_neutrinoeta"+decayTag).c_str(), (decayTag+";tau neutrino eta;").c_str(), 100, -4, 4); 
    h_truthTau_neutrinophi[decayTag] = new TH1F(("h_truthTau_neutrinophi"+decayTag).c_str(), (decayTag+";tau neutrino pt [GeV];").c_str(), 100, -3.5, 3.5); 
    h_truthTau_visiblePtFraction[decayTag] = new TH1F(("h_truthTau_visiblePtFraction"+decayTag).c_str(), (decayTag+";tau visible/total pt;").c_str(), 110, 0, 1.1); 
    h_truthTau_neutrinoPtFraction[decayTag] = new TH1F(("h_truthTau_neutrinoPtFraction"+decayTag).c_str(), (decayTag+";tau neutrino/total pt;").c_str(), 110, 0, 1.1); 
    h_truthTau_totalptVsVisiblePtFraction[decayTag] = new TH2F(("h_truthTau_totalptVsVisiblePtFraction"+decayTag).c_str(), (decayTag+";tau total pt [GeV];tau visible/total pt").c_str(), pt_nbin, pt_binmin, pt_binmax, 110, 0, 1.1); 
    h_truthTau_totalptVsNeutrinoPtFraction[decayTag] = new TH2F(("h_truthTau_totalptVsNeutrinoPtFraction"+decayTag).c_str(), (decayTag+";tau total pt [GeV];tau neutrino/total pt").c_str(), pt_nbin, pt_binmin, pt_binmax, 110, 0, 1.1); 
    h_truthTau_eta[decayTag] = new TH1F(("h_truthTau_eta"+decayTag).c_str(), (decayTag+";tau eta;").c_str(), 80, -4, 4); 
    h_truthTau_phi[decayTag] = new TH1F(("h_truthTau_phi"+decayTag).c_str(), (decayTag+";tau phi;").c_str(), 70, -3.5, 3.5); 
    h_truthTau_ptWithCut[decayTag] = new TH1F(("h_truthTau_ptWithCut"+decayTag).c_str(), "", pt_nbin, pt_binmin, pt_binmax);
    h_truthTau_chargedMesonVsNeutralMeson[decayTag] = new TH2F(("h_truthTau_chargedMesonVsNeutralMeson"+decayTag).c_str(), (decayTag+";nChargedMeson;nNeutralMeson").c_str(), 8, 0, 8, 8, 0, 8); 
  }
  TH1F *h_truthTau_nProng = new TH1F("h_truthTau_nProng", ";tau N track;", 8, 0, 8); 
  TH1F *h_truthTau_nChargedMeson = new TH1F("h_truthTau_nChargedMeson", ";tau N charged meson;", 8, 0, 8); 
  TH1F *h_truthTau_nNeutralMeson = new TH1F("h_truthTau_nNeutralMeson", ";tau N neutral meson;", 8, 0, 8); 
  TH1F *h_truthTau_isHadronic = new TH1F("h_truthTau_isHadronic", ";tau isHad;", 2, 0, 2); 
  TH1F *h_truthTau_isLeptonicEle = new TH1F("h_truthTau_isLeptonicEle", ";tau isLepEle;", 2, 0, 2); 
  
  map<string, map<string, TH1F*>> h_truthTau_psiDR; 
  map<string, map<string, TH1F*>> h_truthTau_integratedTCet; 
  map<string, map<string, TH1F*>> h_truthTau_TCetSpread; 
  map<string, map<string, TH1F*>> h_truthTau_TCet_p0; 
  map<string, map<string, TH1F*>> h_truthTau_TCet_p05; 
  map<string, map<string, TH1F*>> h_truthTau_TCet_p1; 
  map<string, map<string, TH1F*>> h_truthTau_TCet_p15; 
  map<string, map<string, TH1F*>> h_truthTau_TCet_p2; 
  map<string, map<string, TH1F*>> h_truthTau_TCet_p25; 
  map<string, map<string, map<int, TH1F*>>> h_truthTau_TCetFraction_C_ALL; 
  map<string, map<string, map<int, TH1F*>>> h_truthTau_TCetFraction_R1_ALL; 
  map<string, map<string, map<int, TH1F*>>> h_truthTau_TCetFraction_R2_ALL; 
  map<string, map<string, map<int, TH1F*>>> h_truthTau_TCetFraction_R1_C; 
  map<string, map<string, map<int, TH1F*>>> h_truthTau_TCetFraction_R2_C; 
  map<string, map<string, map<int, TH1F*>>> h_truthTau_TCetFraction_R2_CR1; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_nMatchedTC; 
  map<string, map<string, map<string, map<int, TH1F*>>>> h_truthTau_aveEngFracEM; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_matchedTC_et; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_matchedTC_dR; 
  map<string, map<string, map<string, map<int, TH1F*>>>> h_truthTau_matchedTC_EngFracEM; 
  map<string, map<string, map<string, TH2F*>>> h_truthTau_matchedTC_etVsDR; 
  map<string, map<string, map<string, TH2F*>>> h_truthTau_matched_tauPtVsDR; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_matched_tauPt; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_matchedTo1_tauPt; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_matchedEfficiency_tauPt; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_matchedTo1Efficiency_tauPt; 
map<string, map<string, map<string, TH1F*>>> h_truthTau_seedTC_et; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_seedTC_etFraction; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_seedTC_dR; 
  map<string, map<string, map<string, map<int, TH1F*>>>> h_truthTau_seedTC_EngFracEM; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_nextSeedTC_et; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_nextSeedTC_etFraction; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_nextSeedTC_dR; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_closestTC_et; 
  map<string, map<string, map<string, TH1F*>>> h_truthTau_closestTC_dR; 
  for (string cl_name : clustList){
    for (string decayTag : decayTagList){
      h_truthTau_psiDR[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_psiDR"+decayTag).c_str(), (cl_name+decayTag+";tau psi_dR;").c_str(), 90, 0, 0.3); 
      h_truthTau_integratedTCet[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_integratedTCet"+decayTag).c_str(), (cl_name+decayTag+";dR;integrated et").c_str(), 6, 0, 0.3); 
      h_truthTau_TCetSpread[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_TCetSpread"+decayTag).c_str(), (cl_name+decayTag+";dR;TC et [GeV]").c_str(), 6, 0, 0.3); 
      h_truthTau_TCet_p0[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_TCet_p0"+decayTag).c_str(), (cl_name+decayTag+";TC et [GeV];").c_str(), 60, 0, 60); 
      h_truthTau_TCet_p05[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_TCet_p05"+decayTag).c_str(), (cl_name+decayTag+";TC et [GeV];").c_str(), 60, 0, 60); 
      h_truthTau_TCet_p1[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_TCet_p1"+decayTag).c_str(), (cl_name+decayTag+";TC et [GeV];").c_str(), 60, 0, 60); 
      h_truthTau_TCet_p15[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_TCet_p15"+decayTag).c_str(), (cl_name+decayTag+";TC et [GeV];").c_str(), 60, 0, 60); 
      h_truthTau_TCet_p2[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_TCet_p2"+decayTag).c_str(), (cl_name+decayTag+";TC et [GeV];").c_str(), 60, 0, 60); 
      h_truthTau_TCet_p25[cl_name][decayTag] = new TH1F(("h_truthTau_"+cl_name+"_TCet_p25"+decayTag).c_str(), (cl_name+decayTag+";TC et [GeV];").c_str(), 60, 0, 60); 
      for (int nPi0 = -1; nPi0 < 3; nPi0++){
        h_truthTau_TCetFraction_C_ALL[cl_name][decayTag][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_TCetFraction_C_over_ALL_"+to_string(nPi0)+"pi0"+decayTag).c_str(), (cl_name+decayTag+";TC et Fraction;").c_str(), 55, 0, 1.1); 
        h_truthTau_TCetFraction_R1_ALL[cl_name][decayTag][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_TCetFraction_R1_over_ALL_"+to_string(nPi0)+"pi0"+decayTag).c_str(), (cl_name+decayTag+";TC et Fraction;").c_str(), 55, 0, 1.1); 
        h_truthTau_TCetFraction_R2_ALL[cl_name][decayTag][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_TCetFraction_R2_over_ALL_"+to_string(nPi0)+"pi0"+decayTag).c_str(), (cl_name+decayTag+";TC et Fraction;").c_str(), 55, 0, 1.1); 
        h_truthTau_TCetFraction_R1_C[cl_name][decayTag][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_TCetFraction_R1_over_C_"+to_string(nPi0)+"pi0"+decayTag).c_str(), (cl_name+decayTag+";TC et Fraction;").c_str(), 50, 0, 5); 
        h_truthTau_TCetFraction_R2_C[cl_name][decayTag][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_TCetFraction_R2_over_C_"+to_string(nPi0)+"pi0"+decayTag).c_str(), (cl_name+decayTag+";TC et Fraction;").c_str(), 50, 0, 5); 
        h_truthTau_TCetFraction_R2_CR1[cl_name][decayTag][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_TCetFraction_R2_over_CR1_"+to_string(nPi0)+"pi0"+decayTag).c_str(), (cl_name+decayTag+";TC et Fraction;").c_str(), 50, 0, 5); 
      }
    }
  }
  for (string cl_name : clustList){
    for (string decayTag : decayTagList){
      for (string DRrange : DRrangeList){
        h_truthTau_nMatchedTC[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_nMatchedTC"+DRrange+decayTag).c_str(), (cl_name+decayTag+DRrange+";nMatchedTC;").c_str(), 10, 0, 10); 
	for (int nPi0 = -1; nPi0 < 3; nPi0++){
          h_truthTau_aveEngFracEM[cl_name][decayTag][DRrange][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_aveEngFracEM"+DRrange+"_"+to_string(nPi0)+"pi0"+decayTag).c_str(), (cl_name+decayTag+DRrange+";ave. EngFracEM;").c_str(), 55, 0, 1.1); 
          h_truthTau_matchedTC_EngFracEM[cl_name][decayTag][DRrange][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_matchedTC"+DRrange+"_"+to_string(nPi0)+"pi0"+decayTag+"_EngFracEM").c_str(), (cl_name+decayTag+DRrange+";matchedTC EngFracEM;").c_str(), 55, 0, 1.1); 
          h_truthTau_seedTC_EngFracEM[cl_name][decayTag][DRrange][nPi0] = new TH1F(("h_truthTau_"+cl_name+"_seedTC"+DRrange+"_"+to_string(nPi0)+"pi0"+decayTag+"_EngFracEM").c_str(), (cl_name+decayTag+DRrange+";seedTC EngFracEM;").c_str(), 55, 0, 1.1); 
	}
        h_truthTau_matchedTC_et[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_matchedTC"+DRrange+decayTag+"_et").c_str(), (cl_name+decayTag+DRrange+";matchedTC et [GeV];").c_str(), 60, 0, 60); 
        h_truthTau_matchedTC_dR[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_matchedTC"+DRrange+decayTag+"_dR").c_str(), (cl_name+decayTag+DRrange+";matchedTC dR;").c_str(), 60, 0, 0.3); 
        h_truthTau_matchedTC_etVsDR[cl_name][decayTag][DRrange] = new TH2F(("h_truthTau_"+cl_name+"_matchedTC"+DRrange+decayTag+"_etVsDR").c_str(), (cl_name+decayTag+DRrange+";matchedTC et[GeV];matchedTC dR").c_str(), 60, 0, 60, 30, 0, 0.2); 
        h_truthTau_matched_tauPtVsDR[cl_name][decayTag][DRrange] = new TH2F(("h_truthTau_"+cl_name+"_matched"+DRrange+decayTag+"_tauPtVsDR").c_str(), (cl_name+decayTag+DRrange+";tau pt [GeV];matchedTC dR").c_str(), 60, 0, 60, 30, 0, 0.2); 
        h_truthTau_matched_tauPt[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_matched"+DRrange+decayTag+"_tauPt").c_str(), (cl_name+decayTag+DRrange+";matched tau pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
        h_truthTau_matchedTo1_tauPt[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_matchedTo1"+DRrange+decayTag+"_tauPt").c_str(), (cl_name+decayTag+DRrange+";matchedTo1 tau pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax);
        h_truthTau_matchedEfficiency_tauPt[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_matchedEfficiency"+DRrange+decayTag+"_tauPt").c_str(), (cl_name+decayTag+DRrange+";matched effi tau pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
        h_truthTau_matchedTo1Efficiency_tauPt[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_matchedTo1Efficiency"+DRrange+decayTag+"_tauPt").c_str(), (cl_name+decayTag+DRrange+";matchedTo1 effi tau pt [GeV];").c_str(), pt_nbin, pt_binmin, pt_binmax); 
        h_truthTau_seedTC_et[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_seedTC"+DRrange+decayTag+"_et").c_str(), (cl_name+decayTag+DRrange+";seedTC et [GeV];").c_str(), 60, 0, 80);  
        h_truthTau_seedTC_etFraction[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_seedTC"+DRrange+decayTag+"_etFraction").c_str(), (cl_name+decayTag+DRrange+";seedTC et/tau pt;").c_str(), 110, 0, 1.1);  
        h_truthTau_seedTC_dR[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_seedTC"+DRrange+decayTag+"_dR").c_str(), (cl_name+decayTag+DRrange+";seedTC dR;").c_str(), 60, 0, 0.3); 
        h_truthTau_nextSeedTC_et[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_nextSeedTC"+DRrange+decayTag+"_et").c_str(), (cl_name+decayTag+DRrange+";nextSeedTC et [GeV];").c_str(), 60, 0, 40);  
        h_truthTau_nextSeedTC_etFraction[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_nextSeedTC"+DRrange+decayTag+"_etFraction").c_str(), (cl_name+decayTag+DRrange+";nextSeedTC et/tau pt;").c_str(), 100, 0, 1);  
        h_truthTau_nextSeedTC_dR[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_nextSeedTC"+DRrange+decayTag+"_dR").c_str(), (cl_name+decayTag+DRrange+";nextSeedTC dR;").c_str(), 60, 0, 0.3); 
        h_truthTau_closestTC_et[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_closestTC"+DRrange+decayTag+"_et").c_str(), (cl_name+decayTag+DRrange+";closestTC et [GeV];").c_str(), 60, 0, 60);  
        h_truthTau_closestTC_dR[cl_name][decayTag][DRrange] = new TH1F(("h_truthTau_"+cl_name+"_closestTC"+DRrange+decayTag+"_dR").c_str(), (cl_name+decayTag+DRrange+";closestTC dR;").c_str(), 60, 0, 0.3); 
      }
    }
  }

  const string trigTags[] = {
    "trigTagAll", 
    "trig", 
    "nontrig", 
  };

  /*const float et_cuts[] = {2e3, 3e3, 5e3}; 
  const float engFracEM_cuts[] = {0., 0.33, 0.67}; 
  const float core_cuts[] = {0.4, 0.5, 0.6}; 
  const float ring1_cuts[] = {0.2, 0.4, 0.6}; 
  const float ring2_cuts[] = {0.4, 0.5, 0.6}; */
  map<string, map<string, TH1F*>> h_clusters_et;
  map<string, map<string, TH1F*>> h_clusters_eta;
  map<string, map<string, TH1F*>> h_clusters_phi;
  map<string, map<string, TH1F*>> h_clusters_EngFracEM;
  map<string, map<string, TH1F*>> h_clusters_et_over_core;
  map<string, map<string, TH1F*>> h_clusters_C_over_all;
  map<string, map<string, TH1F*>> h_clusters_R1_over_all;
  map<string, map<string, TH1F*>> h_clusters_R2_over_all;
  map<string, map<string, TH1F*>> h_clusters_R1_over_C;
  map<string, map<string, TH1F*>> h_clusters_R2_over_C;
  map<string, map<string, TH1F*>> h_clusters_R2_over_CR1;
  map<string, TH1F*> h_clusters_trigEffi_et;
  for (string cl_name : clustList){
    for (string trigTag : trigTags){
      h_clusters_et[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_et").c_str(), (cl_name+"_"+trigTag+";Cluster et [GeV];").c_str(), 80, 0, 30); 
      h_clusters_eta[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_eta").c_str(), (cl_name+"_"+trigTag+";Cluster eta;").c_str(), 100, -5, 5); 
      h_clusters_phi[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_phi").c_str(), (cl_name+"_"+trigTag+";Cluster phi;").c_str(), 70, -3.5, 3.5); 
      h_clusters_EngFracEM[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_EngFracEM").c_str(), (cl_name+"_"+trigTag+";Cluster EngFracEM;").c_str(), 110, 0, 1.1); 
      h_clusters_et_over_core[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_et_over_core").c_str(), (cl_name+"_"+trigTag+";Cluster et/core;").c_str(), 110, 0, 1.1); 
      h_clusters_C_over_all[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_C_over_all").c_str(), (cl_name+"_"+trigTag+";Cluster et C/all;").c_str(), 110, 0, 1.1); 
      h_clusters_R1_over_all[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_R1_over_all").c_str(), (cl_name+"_"+trigTag+";Cluster et R1/all;").c_str(), 110, 0, 1.1); 
      h_clusters_R2_over_all[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_R2_over_all").c_str(), (cl_name+"_"+trigTag+";Cluster et R2/all;").c_str(), 110, 0, 1.1); 
      h_clusters_R1_over_C[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_R1_over_C").c_str(), (cl_name+"_"+trigTag+";Cluster et R1/C;").c_str(), 100, 0, 5); 
      h_clusters_R2_over_C[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_R2_over_C").c_str(), (cl_name+"_"+trigTag+";Cluster et R2/C;").c_str(), 100, 0, 5); 
      h_clusters_R2_over_CR1[cl_name][trigTag] = new TH1F(("h_"+cl_name+"_"+trigTag+"_R2_over_CR1").c_str(), (cl_name+"_"+trigTag+";Cluster et R2/CR1;").c_str(), 100, 0, 5); 
    }
    h_clusters_trigEffi_et[cl_name] = new TH1F(("h_"+cl_name+"_trigEffi_et").c_str(), (cl_name+";Cluster et [GeV];").c_str(), 80, 0, 30); 
  }

  // Event loop
  int nEvent = tree->GetEntries(); 
  for (int i=0; i<nEvent; i++) {
    printf("\rProcessing event: %i/%i (%.2f%%)", i+1, nEvent, 100.*(i+1)/nEvent); 
    tree->GetEntry(i);

    // Reco taus
    for (int j=0; j<recoTau_pt->size(); j++) {
	h_recoTau_pt["_decayTagAll"]->Fill(recoTau_pt->at(j)*1e-3);
        h_recoTau_eta["_decayTagAll"]->Fill(recoTau_eta->at(j));
        h_recoTau_phi["_decayTagAll"]->Fill(recoTau_phi->at(j));
        h_recoTau_et->Fill(recoTau_et->at(j)*1e-3);
        h_recoTau_pteta->Fill(recoTau_pt->at(j)*1e-3, recoTau_eta->at(j));
        h_ptFinalCalib->Fill(ptFinalCalib->at(j)*1e-3);
        h_nTracksIsolation->Fill(nTracksIsolation->at(j));
        h_nTracksCharged->Fill(nTracksCharged->at(j));
        h_nPi0s->Fill(nPi0s->at(j));
    }
    /*if(i < numVisualizations) {
    	//if(truthTau_pt->size() >= 2) {

	//TH2F* truthHist = new TH2F("truthHist", ";phi;eta", 60, -0.3, 0.3, 60, -0.3, 0.3);
	std::string histName = "recoHist" + std::to_string(i);
    	TH2F* recoHist = new TH2F(histName.c_str(), ";phi;eta", 100, -4, 4, 100, -4, 4);
    
	std::string canvName = "superimposedCanvas" + std::to_string(i);
    	std::string fileName = dir + "visualizations/superImp" + std::to_string(i);
	if(nMatchedTaus->size() > 0) {
            fileName = fileName + "nMatchedTaus" + std::to_string(nMatchedTaus->at(0)) + ".png";
        }
        else {
            fileName += "noTruths.png";
        }

        for(int j=0; j<recoTau_pt->size(); j++) {
            recoHist->Fill(recoTau_phi->at(j), recoTau_eta->at(j), recoTau_pt->at(j)*1e-3);    
            //std::cout << "filling reco phi " << recoTau_phi->at(j) << " eta " << recoTau_eta->at(j) << " pt " << recoTau_pt->at(j) << std::endl;
        }     

	double x[truthTau_phi->size()], y[truthTau_phi->size()];

	for(int j=0; j<truthTau_phi->size(); j++) {
	    //truthHist->Fill(truthTau_phi->at(j), truthTau_eta->at(j), truthTau_pt->at(j)*1e-3);
	    x[j] = truthTau_phi->at(j);
            y[j] = truthTau_eta->at(j);
	    //std::cout << "filling truth phi " << truthTau_phi->at(j) << " eta " << truthTau_eta->at(j) << " pt " << truthTau_pt->at(j) << std::endl;
	}

	TGraph* truthGraph = new TGraph(truthTau_phi->size(), x, y);
    	TCanvas* canvas = new TCanvas(canvName.c_str(), canvName.c_str(), 50, 50, 700, 700);

    	gStyle->SetOptStat(0);

    	//truthHist->Draw("CONT");
        recoHist->Draw("CONT");
	truthGraph->SetMarkerColor(kRed);
	truthGraph->SetMarkerSize(1.5);
	truthGraph->Draw("* SAME");

    	canvas->SaveAs(fileName.c_str());
    	canvas->Close();

    	//delete truthHist;
    	delete recoHist;
    	delete canvas;
        //}
    }*/
    h_recoTau_nTaus["_decayTagAll"]->Fill(recoTau_nTaus->at(0));
    int nTaus = 0; 

    // Truth Taus
    TLorentzVector truthTau_p4[2] = {TLorentzVector(0,0,0,0), TLorentzVector(0,0,0,0)}; 
    TLorentzVector truthVisibleTau_p4[2] = {TLorentzVector(0,0,0,0), TLorentzVector(0,0,0,0)}; 
    for (int j=0; j<truthTau_pt->size(); j++) {
      // Truth tau cuts
      float pt = truthTau_pt->at(j); 
      float totalpt = truthTau_totalpt->at(j); 
      float neutrinopt = truthTau_neutrinopt->at(j); 
      float neutrinoeta = truthTau_neutrinoeta->at(j); 
      float neutrinophi = truthTau_neutrinophi->at(j); 
      float eta = truthTau_eta->at(j); 
      float phi = truthTau_phi->at(j); 
      if (truthTau_pt->size()==2) {
        truthTau_p4[j].SetPtEtaPhiM(pt, eta, phi, 1776);
        truthVisibleTau_p4[j].SetPtEtaPhiM(neutrinopt, neutrinoeta, neutrinophi, 0);
	truthVisibleTau_p4[j] += truthTau_p4[j]; 
      }
      //if (pt<15000) continue; // Tau pt cut 
      //if (abs(eta)>2.5) continue; // Tau eta cut 
      nTaus ++; 

      // Vars
      bool isHadronic = truthTau_isHadronic->at(j); 
bool isLeptonicEle = truthTau_isLeptonicEle->at(j); 
      int nProng = truthTau_nProng->at(j); 
      int nChargedMeson = truthTau_nChargedMeson->at(j); 
      int nNeutralMeson = truthTau_nNeutralMeson->at(j); 
      map<string, map<string, map<string, int>>> nMatchedTC; 
      map<string, map<string, map<string, float>>> sumEngFracEM; 
      map<string, map<string, map<string, float>>> seedTC_et; 
      map<string, map<string, map<string, float>>> seedTC_dR; 
      map<string, map<string, map<string, float>>> seedTC_EngFracEM; 
      map<string, map<string, map<string, float>>> nextSeedTC_et; 
      map<string, map<string, map<string, float>>> nextSeedTC_dR; 
      map<string, map<string, map<string, float>>> closestTC_et; 
      map<string, map<string, map<string, float>>> closestTC_dR; 
      for (string cl_name : clustList) {
	for (string decayTag : decayTagList) {
          for (string DRrange : DRrangeList) {
	    nMatchedTC[cl_name][decayTag][DRrange] = 0; 
	    seedTC_et[cl_name][decayTag][DRrange] = -99.; 
	    seedTC_dR[cl_name][decayTag][DRrange] = 99.; 
	    seedTC_EngFracEM[cl_name][decayTag][DRrange] = 99.; 
	    nextSeedTC_et[cl_name][decayTag][DRrange] = -99.; 
	    nextSeedTC_dR[cl_name][decayTag][DRrange] = 99.; 
	    closestTC_et[cl_name][decayTag][DRrange] = -99.; 
	    closestTC_dR[cl_name][decayTag][DRrange] = 99.; 
	  }
	}
      }
      // Truth tau fill
      for (string decayTag : decayTagList) {
	if (
	    (decayTag=="_decayTagAll")
	    || (decayTag=="_had" && isHadronic==1) 
	    || (decayTag=="_had1Prong" && isHadronic==1 && nProng==1) 
	    || (decayTag=="_had3Prong" && isHadronic==1 && nProng==3) 
	    ) {
          h_truthTau_pt[decayTag]->Fill(pt*1e-3);
          h_truthTau_totalpt[decayTag]->Fill(totalpt*1e-3); 
          h_truthTau_neutrinopt[decayTag]->Fill(neutrinopt*1e-3); 
          h_truthTau_neutrinoeta[decayTag]->Fill(neutrinoeta); 
          h_truthTau_neutrinophi[decayTag]->Fill(neutrinophi); 
          h_truthTau_visiblePtFraction[decayTag]->Fill(pt/totalpt); 
          h_truthTau_neutrinoPtFraction[decayTag]->Fill(neutrinopt/totalpt); 
          h_truthTau_totalptVsVisiblePtFraction[decayTag]->Fill(totalpt*1e-3, pt/totalpt); 
          h_truthTau_totalptVsNeutrinoPtFraction[decayTag]->Fill(totalpt*1e-3, neutrinopt/totalpt); 
          h_truthTau_eta[decayTag]->Fill(eta);
 	  h_truthTau_phi[decayTag]->Fill(phi); 
          h_truthTau_chargedMesonVsNeutralMeson[decayTag]->Fill(nChargedMeson, nNeutralMeson); 
	}
      }
      h_truthTau_nProng->Fill(nProng); 
      h_truthTau_nChargedMeson->Fill(nChargedMeson); 
      h_truthTau_nNeutralMeson->Fill(nNeutralMeson); 
      h_truthTau_isHadronic->Fill(isHadronic); 
      h_truthTau_isLeptonicEle->Fill(isLeptonicEle); 

      // TC matching
      // Clusters
      for (string cl_name : clustList){
        TrigObj seedCluster = TrigObj(); 
	float top_et = -99; 
        vector<TrigObj> clusters = {}; 
        for (int j=0; j<clusters_et[cl_name]->size(); j++){
          TrigObj cluster = TrigObj(); 
    	  cluster.et = clusters_et[cl_name]->at(j); 
  	  cluster.eta = clusters_eta[cl_name]->at(j); 
  	  cluster.phi = clusters_phi[cl_name]->at(j); 
  	  cluster.EngFracEM = clusters_EngFracEM[cl_name]->at(j); 
  	  clusters.push_back(cluster); 
	  float dR = DeltaR(cluster.eta, cluster.phi, eta, phi); 
	  if ((dR < 0.3)&&(cluster.et > top_et)){
	    top_et = cluster.et; 
	    seedCluster = cluster; 
	  }
        }
	for (string trigVar : trigVars){
	  for (string trigCut : trigCuts[trigVar]){
	    if (trigVar=="_etCut"){
	      if (!TauTrigger(seedCluster, clusters, stof(trigCut), 0, 1, 1, 0, 1)) continue; 
	    } else if (trigVar=="_engFracEmCut"){
	      if (!TauTrigger(seedCluster, clusters, 0, 0, 1, 1, stof(trigCut), stof(trigCut)+0.33)) continue; 
	    } else if (trigVar=="_coreCut"){
	      if (!TauTrigger(seedCluster, clusters, 0, stof(trigCut), 1, 1, 0, 1)) continue; 
	    } else if (trigVar=="_ring1Cut"){
	      if (!TauTrigger(seedCluster, clusters, 0, 0, stof(trigCut), 1, 0, 1)) continue; 
	    } else if (trigVar=="_ring2Cut"){
	      if (!TauTrigger(seedCluster, clusters, 0, 0, 1, stof(trigCut), 0, 1)) continue; 
	    }
	    h_truthTau_pt_trig["_decayTagAll"][trigVar][trigCut]->Fill(pt*1e-3); 
	  }
	}
	/*if (TauTrigger(seedCluster, clusters, 2e3, 0.5, 1, 0.5)){
	  h_truthTau_pt_trig["_decayTagAll"]->Fill(pt*1e-3); 
	}*/
  
        // Clust alg loop
	vector<float> v_clust_et = truthTau_matchedTC_et[cl_name]->at(j); 
	vector<float> v_clust_dR = truthTau_matchedTC_dR[cl_name]->at(j); 
	vector<float> v_clust_EngFracEM = truthTau_matchedTC_EngFracEM[cl_name]->at(j); 

	float sum_et_dR = 0.; 
	float sum_et = 0.; 
	float et_ring_sums[7] = {0, 0, 0, 0, 0, 0, 0}; 

	// TC loop
	for (int k=0; k<v_clust_et.size(); k++) {
	  float clust_et = v_clust_et.at(k); 
	  float clust_dR = v_clust_dR.at(k); 
	  float clust_EngFracEM = v_clust_EngFracEM.at(k); 
	  sum_et_dR += clust_et * clust_dR; 
	  sum_et += clust_et; 
	  if (clust_et < 1000) continue; // TC et cut
	  et_ring_sums[6] += clust_et; 
	  if (clust_dR<0.05) et_ring_sums[0] += clust_et; 
	  else if (clust_dR<0.1) et_ring_sums[1] += clust_et; 
	  else if (clust_dR<0.15) et_ring_sums[2] += clust_et; 
	  else if (clust_dR<0.2) et_ring_sums[3] += clust_et; 
	  else if (clust_dR<0.25) et_ring_sums[4] += clust_et; 
	  else if (clust_dR<0.3) et_ring_sums[5] += clust_et; 

	  // dR matching criteria loop
	  for (string DRrange : DRrangeList) {
	    float minDR = dR_s2f[DRrange].first; 
	    float maxDR = dR_s2f[DRrange].second; 
  	    if (clust_dR<minDR || clust_dR>maxDR) continue; // TC dR matching
	    for (string decayTag : decayTagList) {
	      if (
	          (decayTag=="_decayTagAll")
		  || (decayTag=="_had" && isHadronic==1)
		  || (decayTag=="_had1Prong" && isHadronic==1 && nProng==1)
		  || (decayTag=="_had3Prong" && isHadronic==1 && nProng==3)
		  ) {
		  nMatchedTC[cl_name][decayTag][DRrange] ++; 
		  h_truthTau_integratedTCet[cl_name][decayTag]->Fill(clust_dR, clust_et); 
	          h_truthTau_matchedTC_et[cl_name][decayTag][DRrange]->Fill(clust_et*1e-3); 
	          h_truthTau_matchedTC_dR[cl_name][decayTag][DRrange]->Fill(clust_dR); 
		  for (int nPi0 = -1; nPi0 < 3; nPi0++){
	            if (nPi0==-1 || nPi0==nNeutralMeson || (nPi0==2 && nNeutralMeson>2)){
	              h_truthTau_matchedTC_EngFracEM[cl_name][decayTag][DRrange][nPi0]->Fill(clust_EngFracEM); 
		    }
		  }
		  sumEngFracEM[cl_name][decayTag][DRrange] += clust_EngFracEM; 
	          h_truthTau_matchedTC_etVsDR[cl_name][decayTag][DRrange]->Fill(clust_et*1e-3, clust_dR);
	          h_truthTau_matched_tauPtVsDR[cl_name][decayTag][DRrange]->Fill(pt*1e-3, clust_dR); 

		// Seed and next seed search
		if (clust_et > seedTC_et[cl_name][decayTag][DRrange]) {
	          nextSeedTC_et[cl_name][decayTag][DRrange] = seedTC_et[cl_name][decayTag][DRrange]; 
		  seedTC_et[cl_name][decayTag][DRrange] = clust_et; 
	          nextSeedTC_dR[cl_name][decayTag][DRrange] = seedTC_dR[cl_name][decayTag][DRrange]; 
		  seedTC_dR[cl_name][decayTag][DRrange] = clust_dR; 
		  seedTC_EngFracEM[cl_name][decayTag][DRrange] = clust_EngFracEM; 
		} else if (clust_et > nextSeedTC_et[cl_name][decayTag][DRrange]) {
		  nextSeedTC_et[cl_name][decayTag][DRrange] = clust_et; 
		  nextSeedTC_dR[cl_name][decayTag][DRrange] = clust_dR; 
		}

		// Closest search
		if (clust_dR < closestTC_dR[cl_name][decayTag][DRrange]){
		  closestTC_et[cl_name][decayTag][DRrange] = clust_et; 
		  closestTC_dR[cl_name][decayTag][DRrange] = clust_dR; 
	        }
	      }
	    }
	  }
	}
	for (string decayTag : decayTagList) {
	  if (
	      (decayTag=="_decayTagAll")
	      || (decayTag=="_had" && isHadronic==1)
	      || (decayTag=="_had1Prong" && isHadronic==1 && nProng==1)
	      || (decayTag=="_had3Prong" && isHadronic==1 && nProng==3)
	  ) {
	    h_truthTau_psiDR[cl_name][decayTag]->Fill(sum_et_dR/sum_et); 
	    h_truthTau_TCetSpread[cl_name][decayTag]->Fill(0., et_ring_sums[0]/(et_ring_sums[6]+1e-5)); 
	    h_truthTau_TCetSpread[cl_name][decayTag]->Fill(0.05, et_ring_sums[1]/(et_ring_sums[6]+1e-5)); 
	    h_truthTau_TCetSpread[cl_name][decayTag]->Fill(0.1, et_ring_sums[2]/(et_ring_sums[6]+1e-5)); 
	    h_truthTau_TCetSpread[cl_name][decayTag]->Fill(0.15, et_ring_sums[3]/(et_ring_sums[6]+1e-5)); 
	    h_truthTau_TCetSpread[cl_name][decayTag]->Fill(0.2, et_ring_sums[4]/(et_ring_sums[6]+1e-5)); 
	    h_truthTau_TCetSpread[cl_name][decayTag]->Fill(0.25, et_ring_sums[5]/(et_ring_sums[6]+1e-5)); 
	    h_truthTau_TCet_p0[cl_name][decayTag]->Fill(et_ring_sums[0]*1e-3); 
	    h_truthTau_TCet_p05[cl_name][decayTag]->Fill(et_ring_sums[1]*1e-3); 
	    h_truthTau_TCet_p1[cl_name][decayTag]->Fill(et_ring_sums[2]*1e-3); 
	    h_truthTau_TCet_p15[cl_name][decayTag]->Fill(et_ring_sums[3]*1e-3); 
	    h_truthTau_TCet_p2[cl_name][decayTag]->Fill(et_ring_sums[4]*1e-3); 
	    h_truthTau_TCet_p25[cl_name][decayTag]->Fill(et_ring_sums[5]*1e-3); 
	    for (int nPi0 = -1; nPi0 < 3; nPi0++){
	      if (nPi0==-1 || nPi0==nNeutralMeson || (nPi0==2 && nNeutralMeson>2)){
  	        h_truthTau_TCetFraction_C_ALL[cl_name][decayTag][nPi0]->Fill((et_ring_sums[0]+et_ring_sums[1])/(et_ring_sums[6]+1e-5)); 
	        h_truthTau_TCetFraction_R1_ALL[cl_name][decayTag][nPi0]->Fill((et_ring_sums[2]+et_ring_sums[3])/(et_ring_sums[6]+1e-5)); 
	        h_truthTau_TCetFraction_R2_ALL[cl_name][decayTag][nPi0]->Fill((et_ring_sums[4]+et_ring_sums[5])/(et_ring_sums[6]+1e-5)); 
	        h_truthTau_TCetFraction_R1_C[cl_name][decayTag][nPi0]->Fill((et_ring_sums[2]+et_ring_sums[3])/(et_ring_sums[0]+et_ring_sums[1]+1e-5)); 
	        h_truthTau_TCetFraction_R2_C[cl_name][decayTag][nPi0]->Fill((et_ring_sums[4]+et_ring_sums[5])/(et_ring_sums[2]+et_ring_sums[3]+1e-5)); 
	        h_truthTau_TCetFraction_R2_CR1[cl_name][decayTag][nPi0]->Fill((et_ring_sums[4]+et_ring_sums[5])/(et_ring_sums[0]+et_ring_sums[1]+et_ring_sums[2]+et_ring_sums[3]+1e-5)); 
	      }
	    }
	  }
	}

	// Fill after-the-fact hists
        for (string DRrange : DRrangeList) {
          for (string decayTag : decayTagList) {
    	    if (
    	        (decayTag=="_decayTagAll")
    	        || (decayTag=="_had" && isHadronic==1)
    	        || (decayTag=="_had1Prong" && isHadronic==1 && nProng==1)
    	        || (decayTag=="_had3Prong" && isHadronic==1 && nProng==3)
    	        ) {
	      int nMatched = nMatchedTC[cl_name][decayTag][DRrange]; 
              h_truthTau_nMatchedTC[cl_name][decayTag][DRrange]->Fill(nMatched); 
	      for (int nPi0 = -1; nPi0 < 3; nPi0++){
		if (nPi0==-1 || nPi0==nNeutralMeson || (nPi0==2 && nNeutralMeson>2)){
                  h_truthTau_aveEngFracEM[cl_name][decayTag][DRrange][nPi0]->Fill(sumEngFracEM[cl_name][decayTag][DRrange]/nMatched); 
		}
	      }
	      if (nMatched>0) {
	        h_truthTau_matched_tauPt[cl_name][decayTag][DRrange]->Fill(pt*1e-3); 
	        h_truthTau_seedTC_et[cl_name][decayTag][DRrange]->Fill(seedTC_et[cl_name][decayTag][DRrange]*1e-3); 
	        h_truthTau_seedTC_etFraction[cl_name][decayTag][DRrange]->Fill(seedTC_et[cl_name][decayTag][DRrange]/pt); 
	        h_truthTau_seedTC_dR[cl_name][decayTag][DRrange]->Fill(seedTC_dR[cl_name][decayTag][DRrange]); 
		for (int nPi0 = -1; nPi0 < 3; nPi0++){
		  if (nPi0==-1 || nPi0==nNeutralMeson || (nPi0==2 && nNeutralMeson>2)){
	            h_truthTau_seedTC_EngFracEM[cl_name][decayTag][DRrange][nPi0]->Fill(seedTC_EngFracEM[cl_name][decayTag][DRrange]); 
		  }
		}
	        h_truthTau_closestTC_et[cl_name][decayTag][DRrange]->Fill(closestTC_et[cl_name][decayTag][DRrange]*1e-3); 
	        h_truthTau_closestTC_dR[cl_name][decayTag][DRrange]->Fill(closestTC_dR[cl_name][decayTag][DRrange]); 
	      }
	      if (nMatched>1) {
	        h_truthTau_nextSeedTC_et[cl_name][decayTag][DRrange]->Fill(nextSeedTC_et[cl_name][decayTag][DRrange]*1e-3); 
	        h_truthTau_nextSeedTC_etFraction[cl_name][decayTag][DRrange]->Fill(nextSeedTC_et[cl_name][decayTag][DRrange]/pt); 
	        h_truthTau_nextSeedTC_dR[cl_name][decayTag][DRrange]->Fill(nextSeedTC_dR[cl_name][decayTag][DRrange]); 
	      } else if (nMatched==1) h_truthTau_matchedTo1_tauPt[cl_name][decayTag][DRrange]->Fill(pt*1e-3);
	    }
	  }
	  }
      }
    }
    
    if (truthTau_pt->size()==2 && nTaus==2){
      TLorentzVector recoZ_p4 = truthTau_p4[0] + truthTau_p4[1]; 
      TLorentzVector total_recoZ_p4 = truthVisibleTau_p4[0] + truthVisibleTau_p4[1]; 
      float recoZMass = recoZ_p4.M(); 
      float total_recoZMass = total_recoZ_p4.M(); 
      h_truthTau_recoZMass->Fill(recoZMass*1e-3); 
      h_truthTotalTau_recoZMass->Fill(total_recoZMass*1e-3); 
    }
  }
  // Hist dividing
  for (string cl_name : clustList) {
    for (string decayTag : decayTagList) {
      for (string DRrange : DRrangeList) {
	h_truthTau_matchedEfficiency_tauPt[cl_name][decayTag][DRrange]->Divide(h_truthTau_matched_tauPt[cl_name][decayTag][DRrange], h_truthTau_pt[decayTag]); 
	h_truthTau_matchedTo1Efficiency_tauPt[cl_name][decayTag][DRrange]->Divide(h_truthTau_matchedTo1_tauPt[cl_name][decayTag][DRrange], h_truthTau_pt[decayTag]); 
	for (string trigVar : trigVars){
	for (string trigCut : trigCuts[trigVar]){
	h_truthTau_pt_trigEffi[decayTag][trigVar][trigCut]->Divide(h_truthTau_pt_trig[decayTag][trigVar][trigCut], h_truthTau_pt[decayTag]); 
	}
	}
      }
    }
  }
  printf("\n"); // Finish progress printf

  // Write hist
  hist_file->Write(); 
  hist_file->Close(); 
}
