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

void reco_hist_maker(){
  // Params
  string dir = "/msu/data/t3work13/dcianciolo/gepOutput2/gep/run/"; 
  const string tree_file_name = dir + "outputGEPNtuple130Hbb.root";
  //const string tree_file_name = dir + "user.xinfei.GepOutputReader_mc15_14TeV.800281.Py8EG_AZ_Ztautau.recon.AOD.e8379_s3735_s3738_r13046_v4_agg.root"; 
  const string hist_file_name = dir + "130histsHbb.root";  
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
  vector<float> *recoTau_nTaus = 0;
  tree->SetBranchAddress("recoTau_pt", &recoTau_pt);
  tree->SetBranchAddress("recoTau_eta", &recoTau_eta);
  tree->SetBranchAddress("recoTau_phi", &recoTau_phi); 
  tree->SetBranchAddress("recoTau_nTaus", &recoTau_nTaus);
 
  vector<float> *ptFinalCalib = 0;
  vector<float> *nTracksCharged = 0;
  vector<float> *nTracksIsolation = 0;
  vector<float> *nAllTracks = 0;
  tree->SetBranchAddress("recoTau_ptFinalCalib", &ptFinalCalib);
  tree->SetBranchAddress("nTracksCharged", &nTracksCharged);
  tree->SetBranchAddress("nTracksIsolation", &nTracksIsolation);
  tree->SetBranchAddress("nAllTracks", &nAllTracks);
 
  vector<float> *truthTau_pt = 0;
  vector<float> *truthTau_eta = 0;
  vector<float> *truthTau_phi = 0;
  vector<float> *truthTau_nTaus = 0;
  tree->SetBranchAddress("truthTau_pt", &truthTau_pt);
  tree->SetBranchAddress("truthTau_eta", &truthTau_eta);
  tree->SetBranchAddress("truthTau_phi", &truthTau_phi);
  tree->SetBranchAddress("truthTau_nTaus", &truthTau_nTaus); 

  gInterpreter->GenerateDictionary("vector<vector<float> >", "vector"); // Generate dict for vector<vector<float>>

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
  TH1F* h_ptFinalCalib = new TH1F("h_ptFinalCalib", "", 100, 0, 50);
  TH1F* h_nTracksCharged = new TH1F("h_nTracksCharged", "", 16, 0, 16);
  TH1F* h_nTracksIsolation = new TH1F("h_nTracksIsolation", "", 16, 0, 16);
  TH1F* h_recoTau_pt = new TH1F("h_recoTau_pt", "", 60, 2, 120);
  TH1F* h_recoTau_eta = new TH1F("h_recoTau_eta", "", 100, -4, 4);
  TH1F* h_recoTau_phi = new TH1F("h_recoTau_phi", "", 100, -3.5, 3.5);
  TH1F* h_recoTau_nTaus = new TH1F("h_recoTau_nTaus", "", 50, 0, 50);
  TH1F* h_nAllTracks = new TH1F("h_recoTau_nAllTracks", "", 50, 0, 50);
 
  TH1F* h_truthTau_pt = new TH1F("h_truthTau_pt", "", 60, 2, 120);
  TH1F* h_truthTau_eta = new TH1F("h_truthTau_eta", "", 100, -4, 4);
  TH1F* h_truthTau_phi = new TH1F("h_truthTau_phi", "", 100, -3.5, 3.5); 
  TH1F* h_truthTau_nTaus = new TH1F("h_truthTau_nTaus", "", 7, 0, 7);

  const string trigTags[] = {
    "trigTagAll", 
    "trig", 
    "nontrig", 
  };

  // Event loop
  int nEvent = tree->GetEntries(); 
  for (int i=0; i<nEvent; i++) {
    printf("\rProcessing event: %i/%i (%.2f%%)", i+1, nEvent, 100.*(i+1)/nEvent); 
    tree->GetEntry(i);
    h_recoTau_nTaus->Fill(recoTau_nTaus->at(0));
    h_truthTau_nTaus->Fill(truthTau_nTaus->at(0));
    for (int j=0; j<recoTau_pt->size(); j++) {
	if (ptFinalCalib->at(j) >= 6500) {
	h_recoTau_pt->Fill(recoTau_pt->at(j)*1e-3);
        h_recoTau_eta->Fill(recoTau_eta->at(j));
        h_recoTau_phi->Fill(recoTau_phi->at(j));
        h_ptFinalCalib->Fill(ptFinalCalib->at(j)*1e-3);
        h_nTracksIsolation->Fill(nTracksIsolation->at(j));
        h_nTracksCharged->Fill(nTracksCharged->at(j));
        h_nAllTracks->Fill(nAllTracks->at(j));
    	}
    }
    for (int k=0; k<truthTau_pt->size(); k++) {
	h_truthTau_pt->Fill(truthTau_pt->at(k)*1e-3);
        h_truthTau_eta->Fill(truthTau_eta->at(k));
        h_truthTau_phi->Fill(truthTau_phi->at(k));
    }
  }

  printf("\n"); // Finish progress printf

  // Write hist
  hist_file->Write(); 
  hist_file->Close(); 
}
