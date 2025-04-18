// Main plot function
auto plot_hists(vector<vector<Cluster>> *clusters, vector<vector<TruthTau>> *truthTaus, vector<vector<RecoTau>> *recoTaus, vector<vector<RecoTau>> *matchedRecoTaus, vector<vector<RecoTau>> *unmatchedRecoTaus){
	// Init maps of hists, easier to grab specific ones later for sophisticated plots
	DebugMap<string, Th1fHist> th1fHists = {}; // <name, Th1fHist>
	Th1fHist tmpTh1fHist; 
	DebugMap<string, Th2fHist> th2fHists = {}; // <name, Th2fHist>
	Th2fHist tmpTh2fHist; 

	// Add TH1F to map
	// Cluster
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_cluster_et", "cluster et [GeV]", "", 100, 0, 25); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_cluster_eta", "cluster eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_cluster_phi", "cluster phi", "", 70, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_cluster_EngFracEM", "cluster EngFracEM", "", 120, -.1, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_cluster_nClusters", "cluster nClusters", "", 120, 0, 1200); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	// Truth tau
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_pt", "truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_eta", "truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_phi", "truth tau phi", "", 70, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_seedCluster_et", "truth tau seedCluster et [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_seedCluster_eta", "truth tau seedCluster eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_seedCluster_phi", "truth tau seedCluster phi", "", 70, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_seedCluster_EngFracEM", "truth tau seedCluster EngFracEM", "", 120, -.1, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_noCut_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_noCut_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_seedEt2GeV_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_seedEt2GeV_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_seedEt5GeV_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_seedEt5GeV_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_seedEt8GeV_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_seedEt8GeV_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_et2GeV_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_et2GeV_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_et3GeV_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_et3GeV_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_et5GeV_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_et5GeV_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_CA0p2_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_CA0p2_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_CA0p5_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_CA0p5_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_CA0p8_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_CA0p8_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R1C0p2_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R1C0p2_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R1C0p5_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R1C0p5_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R1C0p8_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R1C0p8_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2C0p2_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2C0p2_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2C0p5_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2C0p5_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2C0p8_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2C0p8_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2R10p5_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2R10p5_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2R11p5_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2R11p5_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2R19p5_pt", "triggered truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_triggered_R2R19p5_eta", "triggered truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_nProng", "truth tau nProng", "", 8, 0, 8); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_nChargedMeson", "truth tau nChargedMeson", "", 8, 0, 8); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_nNeutralMeson", "truth tau nNeutralMeson", "", 8, 0, 8); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_isHadronic", "truth tau isHadronic", "", 2, 0, 2); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_isLeptonicEle", "truth tau isLeptonicEle", "", 2, 0, 2); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_nTruthTaus", "truth tau nTruthTaus", "", 5, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTau_nMatchedClusters", "truth tau nMatchedClusters", "", 15, 0, 15); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTauIsolation_CA", "truth tau core over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTauIsolation_R1A", "truth tau ring1 over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTauIsolation_R2A", "truth tau ring2 over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTauIsolation_R1C", "truth tau ring1 over core", "", 50, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTauIsolation_R2C", "truth tau ring2 over core", "", 50, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthTauIsolation_R2R1", "truth tau ring2 over ring1", "", 50, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	// Reco tau
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_pt", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_ptLeading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_ptSubleading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTT_ptLeading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTT_ptSubleading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigMM_ptLeading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigMM_ptSubleading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigLL_ptLeading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigLL_ptSubleading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTM_ptLeading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTM_ptSubleading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTL_ptLeading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTL_ptSubleading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigML_ptLeading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigML_ptSubleading", "reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_seedEtLeading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_seedEtSubleading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTT_seedEtLeading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTT_seedEtSubleading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigMM_seedEtLeading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigMM_seedEtSubleading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigLL_seedEtLeading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigLL_seedEtSubleading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTM_seedEtLeading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTM_seedEtSubleading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTL_seedEtLeading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTL_seedEtSubleading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigML_seedEtLeading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigML_seedEtSubleading", "reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_etaLeading", "reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTT_etaLeading", "reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigMM_etaLeading", "reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigLL_etaLeading", "reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTM_etaLeading", "reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTL_etaLeading", "reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigML_etaLeading", "reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauDeltaR", "reco tau di-tau deltaR", "", 314, 0, 6.28); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTT_diTauDeltaR", "reco tau di-tau deltaR", "", 314, 0, 6.28); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigMM_diTauDeltaR", "reco tau di-tau deltaR", "", 314, 0, 6.28); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigLL_diTauDeltaR", "reco tau di-tau deltaR", "", 314, 0, 6.28); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTM_diTauDeltaR", "reco tau di-tau deltaR", "", 314, 0, 6.28); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTL_diTauDeltaR", "reco tau di-tau deltaR", "", 314, 0, 6.28); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigML_diTauDeltaR", "reco tau di-tau deltaR", "", 314, 0, 6.28); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauMass", "reco tau di-tau mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTT_diTauMass", "reco tau di-tau mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigMM_diTauMass", "reco tau di-tau mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigLL_diTauMass", "reco tau di-tau mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTM_diTauMass", "reco tau di-tau mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigTL_diTauMass", "reco tau di-tau mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_diTauTrigML_diTauMass", "reco tau di-tau mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_eta", "reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_phi", "reco tau phi", "", 70, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_m", "reco tau mass [GeV]", "", 100, 0, 100); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_recoTau_nRecoTaus", "reco tau N", "", 50, 0, 50); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_nTracksIsolation", "tracks N", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist;
        tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_nTracksCharged", "tracks N", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist;
        tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_nAllTracks", "tracks N", "", 40, 0, 40); th1fHists[tmpTh1fHist.name] = tmpTh1fHist;


	// Event triggered
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_lowestPt_noCut", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_lowestPt_seedEt2GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_lowestPt_seedEt5GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_lowestPt_seedEt8GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_noCut", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_seedEt2GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_seedEt5GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_seedEt8GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_seedEt15GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_seedEt20GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_seedEt25GeV", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_CA0p2", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_CA0p5", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_CA0p8", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_R1C0p2", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_R1C0p5", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_R1C0p8", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_R2C0p2", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_R2C0p5", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_eventTriggered_recoTau_highestPt_R2C0p8", "reco tau pt [GeV]", "", 1500, 0, 150); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 

	// Truth-matched reco tau
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_nMatchedRecoTaus", "truth matched reco tau N", "", 5, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_nMatchedClusters", "truth matched reco tau nMatchedClusters", "", 15, 0, 15); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_eta", "truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_phi", "truth-matched reco tau phi", "", 70, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_seedET", "matched reco tau seed cluster et [GeV]", "", 500, 0, 50); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_seedToMatchedClustersEtFraction", "seed ET over matched clusters ET", "", 110, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_seedToRecoTauEtFraction", "seed ET over reco tau ET", "", 150, 0, 1.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_seedEtCore", "matched reco tau core over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_seedEtAll", "matched reco tau core over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_CA", "matched reco tau core over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_R1C", "matched reco tau ring1 over core", "", 50, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_R2C", "matched reco tau ring2 over core", "", 50, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_R2R1", "matched reco tau ring2 over ring1", "", 50, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_nCoreClusters", "matched reco tau nCoreClusters", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_nRing1Clusters", "matched reco tau nRing1Clusters", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTauIsolation_nRing2Clusters", "matched reco tau nRing2Clusters", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_etaLeading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_etaSubleading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_etaLeading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_etaSubleading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_etaLeading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_etaSubleading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_etaLeading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_etaSubleading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_etaLeading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_etaSubleading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_etaLeading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_etaSubleading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_etaLeading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_etaSubleading", "matched reco tau eta", "", 140, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_ptLeading", "truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_ptSubleading", "truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_ptLeading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_ptSubleading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_ptLeading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_ptSubleading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_ptLeading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_ptSubleading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_ptLeading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_ptSubleading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_ptLeading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_ptSubleading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_ptLeading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_ptSubleading", "matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_seedEtLeading", "truth-matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_seedEtSubleading", "truth-matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_seedEtLeading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_seedEtSubleading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_seedEtLeading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_seedEtSubleading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_seedEtLeading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_seedEtSubleading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_seedEtLeading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_seedEtSubleading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_seedEtLeading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_seedEtSubleading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_seedEtLeading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_seedEtSubleading", "matched reco tau seedEt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauDeltaR", "truth-matched reco tau di-tau delta R", "", 126, 0, 6.3); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_diTauDeltaR", "truth-matched reco tau di-tau delta R", "", 126, 0, 6.3); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_diTauDeltaR", "truth-matched reco tau di-tau delta R", "", 126, 0, 6.3); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_diTauDeltaR", "truth-matched reco tau di-tau delta R", "", 126, 0, 6.3); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_diTauDeltaR", "truth-matched reco tau di-tau delta R", "", 126, 0, 6.3); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_diTauDeltaR", "truth-matched reco tau di-tau delta R", "", 126, 0, 6.3); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_diTauDeltaR", "truth-matched reco tau di-tau delta R", "", 126, 0, 6.3); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauMass", "truth-matched reco tau di-tau Mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTT_diTauMass", "truth-matched reco tau di-tau Mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigMM_diTauMass", "truth-matched reco tau di-tau Mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigLL_diTauMass", "truth-matched reco tau di-tau Mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTM_diTauMass", "truth-matched reco tau di-tau Mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigTL_diTauMass", "truth-matched reco tau di-tau Mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_diTauTrigML_diTauMass", "truth-matched reco tau di-tau Mass [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_noCut_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_noCut_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt2GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt2GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt5GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt5GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt8GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt8GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt15GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt15GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt20GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt20GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt25GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_seedEt25GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_et2GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_et2GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_et3GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_et3GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_et5GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_et5GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_CA0p2_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_CA0p2_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_CA0p5_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_CA0p5_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_CA0p8_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_CA0p8_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R1C0p2_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R1C0p2_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R1C0p5_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R1C0p5_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R1C0p8_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R1C0p8_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2C0p2_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2C0p2_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2C0p5_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2C0p5_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2C0p8_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2C0p8_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2R10p5_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2R10p5_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2R11p5_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2R11p5_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2R19p5_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_triggered_R2R19p5_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	// Truth tau matched to a reco tau
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_eta", "reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_phi", "reco-matched truth tau phi", "", 70, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_seedCluster_EngFracEM", "matched reco tau seedCluster EngFracEM", "", 120, -.1, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_noCut_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_noCut_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt2GeV_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt2GeV_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt5GeV_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt5GeV_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt8GeV_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt8GeV_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt15GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt15GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt20GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt20GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt25GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_seedEt25GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_et2GeV_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_et2GeV_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_et3GeV_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_et3GeV_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_et5GeV_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_et5GeV_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_CA0p2_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_CA0p2_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_CA0p5_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_CA0p5_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_CA0p8_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_CA0p8_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R1C0p2_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R1C0p2_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R1C0p5_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R1C0p5_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R1C0p8_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R1C0p8_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2C0p2_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2C0p2_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2C0p5_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2C0p5_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2C0p8_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2C0p8_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2R10p5_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2R10p5_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2R11p5_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2R11p5_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2R19p5_pt", "triggered reco-matched truth tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_truthMatched2RecoTau_triggered_R2R19p5_eta", "triggered reco-matched truth tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	// Truth-unmatched reco tau
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_nUnmatchedRecoTaus", "not truth matched reco tau N", "", 50, 0, 50); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_nUnmatchedClusters", "truth-unmatched reco tau nMatchedClusters", "", 15, 0, 15); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_eta", "truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_phi", "truth-unmatched reco tau phi", "", 70, -3.5, 3.5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_seedET", "unmatched reco tau seed cluster et [GeV]", "", 500, 0, 50); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_seedEtCore", "matched reco tau core over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_seedEtAll", "matched reco tau core over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_CA", "unmatched reco tau core over all", "", 55, 0, 1.1); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_R1C", "unmatched reco tau ring1 over core", "", 50, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_R2C", "unmatched reco tau ring2 over core", "", 50, 0, 5); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_R2R1", "unmatched reco  tau ring2 over ring1", "", 50, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_nCoreClusters", "unmatched reco tau nCoreClusters", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_nRing1Clusters", "unmatched reco tau nRing1Clusters", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTauIsolation_nRing2Clusters", "unmatched reco tau nRing2Clusters", "", 10, 0, 10); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 

	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_noCut_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_noCut_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt2GeV_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt2GeV_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt5GeV_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt5GeV_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt8GeV_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt8GeV_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt15GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt15GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt20GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt20GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt25GeV_pt", "triggered truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_seedEt25GeV_eta", "triggered truth-matched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_et2GeV_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_et2GeV_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_et3GeV_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_et3GeV_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_et5GeV_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_et5GeV_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_CA0p2_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_CA0p2_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_CA0p5_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_CA0p5_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_CA0p8_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_CA0p8_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R1C0p2_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R1C0p2_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R1C0p5_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R1C0p5_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R1C0p8_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R1C0p8_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2C0p2_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2C0p2_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2C0p5_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2C0p5_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2C0p8_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2C0p8_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2R10p5_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2R10p5_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2R11p5_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2R11p5_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2R19p5_pt", "triggered truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_triggered_R2R19p5_eta", "triggered truth-unmatched reco tau eta", "", 80, -4, 4); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 

	// Trigger working points
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_trigBaseline_pt", "truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_trigLoose_pt", "truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_trigMedium_pt", "truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_matchedRecoTau_trigTight_pt", "truth-matched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_trigBaseline_pt", "truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_trigLoose_pt", "truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_trigMedium_pt", "truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 
	tmpTh1fHist = Th1fHist(); tmpTh1fHist.setParams("h_unmatchedRecoTau_trigTight_pt", "truth-unmatched reco tau pt [GeV]", "", 120, 0, 120); th1fHists[tmpTh1fHist.name] = tmpTh1fHist; 

	// Add TH2F to map
	// Truth tau
	tmpTh2fHist = Th2fHist(); tmpTh2fHist.setParams("h_truthTau_nChargedMeson_nNeutralMeson", "truth tau nChargedMeson", "truth tau nNeutralMeson", 8, 0, 8, 8, 0, 8); th2fHists[tmpTh2fHist.name] = tmpTh2fHist; 

	tmpTh2fHist = Th2fHist(); tmpTh2fHist.setParams("h_truthTau_nProng_nChargedMeson", "truth tau nProng", "truth tau nChargedMeson", 8, 0, 8, 8, 0, 8); th2fHists[tmpTh2fHist.name] = tmpTh2fHist; 
	tmpTh2fHist = Th2fHist(); tmpTh2fHist.setParams("h_matchedRecoTau_seedET_CA", "tau seedET [GeV]", "tau CA", 50, 0, 50, 55, 0, 1.1); th2fHists[tmpTh2fHist.name] = tmpTh2fHist; 

	/*tmpTh2fHist = Th2fHist(); tmpTh2fHist.setParams("h_matchedRecoTau_seedET_CA", "seedET [GeV]", "CA", 80, 0, 40, 100, 0, 1); th2fHists[tmpTh2fHist.name] = tmpTh2fHist; 
	tmpTh2fHist = Th2fHist(); tmpTh2fHist.setParams("h_unmatchedRecoTau_seedET_CA", "seedET [GeV]", "CA", 80, 0, 40, 100, 0, 1); th2fHists[tmpTh2fHist.name] = tmpTh2fHist; */

	// Event loop to push back vars
	int nEvent = clusters->size(); 
	int nEvent_withTwoMatchedRecoTaus = 0; 
	int nEvent_trigDiTau_sig_TT = 0; 
	int nEvent_trigDiTau_sig_MM = 0; 
	int nEvent_trigDiTau_sig_LL = 0; 
	int nEvent_trigDiTau_sig_TM = 0; 
	int nEvent_trigDiTau_sig_TL = 0; 
	int nEvent_trigDiTau_sig_ML = 0; 
	int nEvent_trigDiTau_bkg_TT = 0; 
	int nEvent_trigDiTau_bkg_MM = 0; 
	int nEvent_trigDiTau_bkg_LL = 0; 
	int nEvent_trigDiTau_bkg_TM = 0; 
	int nEvent_trigDiTau_bkg_TL = 0; 
	int nEvent_trigDiTau_bkg_ML = 0; 
	TriggerCuts tCuts; // Trigger cuts manager object 

        #pragma omp parallel
        {
	#pragma omp for
	for (int n=0; n<nEvent; n++){
		if (printProgress) printf("\rPushing back hist vars for event: %i/%i (%.1f%%)", n+1, nEvent, 100.*(n+1)/nEvent); 

		// Number of the thing in each event
		int nClusters = clusters->at(n).size(); 
		int nTruthTaus = truthTaus->at(n).size(); 
		int nRecoTaus = recoTaus->at(n).size(); 
		int nMatchedRecoTaus = matchedRecoTaus->at(n).size(); 
		int nUnmatchedRecoTaus = unmatchedRecoTaus->at(n).size(); 
		if (nMatchedRecoTaus >= 2) nEvent_withTwoMatchedRecoTaus++; 
		th1fHists.at("h_cluster_nClusters").vars.push_back(nClusters); 
		th1fHists.at("h_truthTau_nTruthTaus").vars.push_back(nTruthTaus); 
		th1fHists.at("h_recoTau_nRecoTaus").vars.push_back(nRecoTaus); 
		th1fHists.at("h_matchedRecoTau_nMatchedRecoTaus").vars.push_back(nMatchedRecoTaus); 
		th1fHists.at("h_unmatchedRecoTau_nUnmatchedRecoTaus").vars.push_back(nUnmatchedRecoTaus); 

		// Loop through clusters
		for (Cluster cluster : clusters->at(n)){
			th1fHists.at("h_cluster_et").vars.push_back(cluster.et*1e-3); // MeV -> GeV
			th1fHists.at("h_cluster_eta").vars.push_back(cluster.eta); 
			th1fHists.at("h_cluster_phi").vars.push_back(cluster.phi); 
			th1fHists.at("h_cluster_EngFracEM").vars.push_back(cluster.EngFracEM); 
		}

		// Loop through truth taus
		for (TruthTau truthTau : truthTaus->at(n)){
			th1fHists.at("h_truthTau_pt").vars.push_back(truthTau.pt*1e-3); 
			th1fHists.at("h_truthTau_eta").vars.push_back(truthTau.eta); 
			th1fHists.at("h_truthTau_phi").vars.push_back(truthTau.phi); 
			th1fHists.at("h_truthTau_nProng").vars.push_back(truthTau.nProng); 
			th1fHists.at("h_truthTau_nMatchedClusters").vars.push_back(truthTau.matchedClusters.size()); 
			th1fHists.at("h_truthTau_nChargedMeson").vars.push_back(truthTau.nChargedMeson); 
			th1fHists.at("h_truthTau_nNeutralMeson").vars.push_back(truthTau.nNeutralMeson); 
			th1fHists.at("h_truthTau_isHadronic").vars.push_back(truthTau.isHadronic); 
			th1fHists.at("h_truthTau_isLeptonicEle").vars.push_back(truthTau.isLeptonicEle); 

			// Tau trigger alg
			tCuts.setDefaults(); 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_seedCluster_et").vars.push_back(truthTau.seedCluster.et*1e-3); 
				th1fHists.at("h_truthTau_seedCluster_eta").vars.push_back(truthTau.seedCluster.eta); 
				th1fHists.at("h_truthTau_seedCluster_phi").vars.push_back(truthTau.seedCluster.phi); 
				th1fHists.at("h_truthTau_seedCluster_EngFracEM").vars.push_back(truthTau.seedCluster.EngFracEM); 
				th1fHists.at("h_truthTau_triggered_noCut_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_noCut_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 2000; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_seedEt2GeV_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_seedEt2GeV_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 5000; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_seedEt5GeV_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_seedEt5GeV_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 8000; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_seedEt8GeV_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_seedEt8GeV_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 2000; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_et2GeV_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_et2GeV_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 3000; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_et3GeV_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_et3GeV_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 5000; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_et5GeV_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_et5GeV_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.2; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_CA0p2_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_CA0p2_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.5; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_CA0p5_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_CA0p5_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.8; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_CA0p8_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_CA0p8_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.2; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R1C0p2_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R1C0p2_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.5; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R1C0p5_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R1C0p5_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.8; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R1C0p8_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R1C0p8_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.2; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R2C0p2_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R2C0p2_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.5; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R2C0p5_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R2C0p5_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.8; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R2C0p8_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R2C0p8_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 0.5; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R2R10p5_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R2R10p5_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 1.5; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R2R11p5_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R2R11p5_eta").vars.push_back(truthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 9.5; 
			if (tauTriggerAlg(truthTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_truthTau_triggered_R2R19p5_pt").vars.push_back(truthTau.pt*1e-3); 
				th1fHists.at("h_truthTau_triggered_R2R19p5_eta").vars.push_back(truthTau.eta); 
			}

			// Nearby et
			auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(truthTau, clusters->at(n)); 
			th1fHists.at("h_truthTauIsolation_CA").vars.push_back(core_et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_truthTauIsolation_R1A").vars.push_back(ring1_et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_truthTauIsolation_R2A").vars.push_back(ring2_et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_truthTauIsolation_R1C").vars.push_back(ring1_et/(core_et + 1e-5)); 
			th1fHists.at("h_truthTauIsolation_R2C").vars.push_back(ring2_et/(core_et + 1e-5)); 
			th1fHists.at("h_truthTauIsolation_R2R1").vars.push_back(ring2_et/(ring1_et + 1e-5)); 

			th2fHists["h_truthTau_nChargedMeson_nNeutralMeson"].xvars.push_back(truthTau.nChargedMeson); 
			th2fHists["h_truthTau_nChargedMeson_nNeutralMeson"].yvars.push_back(truthTau.nNeutralMeson); 
			th2fHists["h_truthTau_nProng_nChargedMeson"].xvars.push_back(truthTau.nProng); 
			th2fHists["h_truthTau_nProng_nChargedMeson"].yvars.push_back(truthTau.nChargedMeson); 
		}

		// Loop through reco taus
		float lowestTriggeredRecoPt_noCut = -99.; 
		float lowestTriggeredRecoPt_seedEt2GeV = -99.; 
		float lowestTriggeredRecoPt_seedEt5GeV = -99.; 
		float lowestTriggeredRecoPt_seedEt8GeV = -99.; 
		float highestTriggeredRecoPt_noCut = -99.; 
		float highestTriggeredRecoPt_seedEt2GeV = -99.; 
		float highestTriggeredRecoPt_seedEt5GeV = -99.; 
		float highestTriggeredRecoPt_seedEt8GeV = -99.; 
		float highestTriggeredRecoPt_seedEt15GeV = -99.; 
		float highestTriggeredRecoPt_seedEt20GeV = -99.; 
		float highestTriggeredRecoPt_seedEt25GeV = -99.; 
		float highestTriggeredRecoPt_CA0p2 = -99.; 
		float highestTriggeredRecoPt_CA0p5 = -99.; 
		float highestTriggeredRecoPt_CA0p8 = -99.; 
		float highestTriggeredRecoPt_R1C0p2 = -99.; 
		float highestTriggeredRecoPt_R1C0p5 = -99.; 
		float highestTriggeredRecoPt_R1C0p8 = -99.; 
		float highestTriggeredRecoPt_R2C0p2 = -99.; 
		float highestTriggeredRecoPt_R2C0p5 = -99.; 
		float highestTriggeredRecoPt_R2C0p8 = -99.; 
		int trigDiTau_bkg_TT = 0; 
		int trigDiTau_bkg_MM = 0; 
		int trigDiTau_bkg_LL = 0; 
		int trigDiTau_bkg_TM = 0; 
		int trigDiTau_bkg_TL = 0; 
		int trigDiTau_bkg_ML = 0; 

		RecoTau leadingTau; 
		RecoTau subleadingTau; 
		for (RecoTau recoTau : recoTaus->at(n)){
			th1fHists.at("h_recoTau_pt").vars.push_back(recoTau.pt*1e-3); 
			th1fHists.at("h_recoTau_eta").vars.push_back(recoTau.eta); 
			th1fHists.at("h_recoTau_phi").vars.push_back(recoTau.phi); 
			th1fHists.at("h_recoTau_m").vars.push_back(recoTau.m*1e-3); 
			
			if (recoTau.pt > leadingTau.pt) {
				subleadingTau = leadingTau; 
				leadingTau = recoTau; 
			} else if (recoTau.pt > subleadingTau.pt) {
				subleadingTau = recoTau; 
			}

			// Di-tau trigger
			if (trigDiTau_bkg_TT != 3) {
				if (tauTriggerTight(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_TT == 0) {
						trigDiTau_bkg_TT = 1; 
					} else if (trigDiTau_bkg_TT == 1) {
						trigDiTau_bkg_TT = 3; 
						nEvent_trigDiTau_bkg_TT++; 
					}
				}
			}
			if (trigDiTau_bkg_MM != 3) {
				if (tauTriggerMedium(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_MM == 0) {
						trigDiTau_bkg_MM = 1; 
					} else if (trigDiTau_bkg_MM == 1) {
						trigDiTau_bkg_MM = 3; 
						nEvent_trigDiTau_bkg_MM++; 
					}
				}
			}
			if (trigDiTau_bkg_LL != 3) {
				if (tauTriggerLoose(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_LL == 0) {
						trigDiTau_bkg_LL = 1; 
					} else if (trigDiTau_bkg_LL == 1) {
						trigDiTau_bkg_LL = 3; 
						nEvent_trigDiTau_bkg_LL++; 
					}
				}
			}
			if (trigDiTau_bkg_TM != 3) {
				if (tauTriggerTight(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_TM == 0) {
						trigDiTau_bkg_TM = 2; 
					} else if (trigDiTau_bkg_TM == 1 || trigDiTau_bkg_TM == 2) {
						trigDiTau_bkg_TM = 3; 
						nEvent_trigDiTau_bkg_TM++; 
					}
				} else if (tauTriggerMedium(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_TM == 0) {
						trigDiTau_bkg_TM = 1; 
					} else if (trigDiTau_bkg_TM == 2) {
						trigDiTau_bkg_TM = 3; 
					}
				}
			}
			if (trigDiTau_bkg_TL != 3) {
				if (tauTriggerTight(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_TL == 0) {
						trigDiTau_bkg_TL = 2; 
					} else if (trigDiTau_bkg_TL == 1 || trigDiTau_bkg_TL == 2) {
						trigDiTau_bkg_TL = 3; 
						nEvent_trigDiTau_bkg_TL++; 
					}
				} else if (tauTriggerLoose(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_TL == 0) {
						trigDiTau_bkg_TL = 1; 
					} else if (trigDiTau_bkg_TL == 2) {
						trigDiTau_bkg_TL = 3; 
					}
				}
			}
			if (trigDiTau_bkg_ML != 3) {
				if (tauTriggerMedium(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_ML == 0) {
						trigDiTau_bkg_ML = 2; 
					} else if (trigDiTau_bkg_ML == 1 || trigDiTau_bkg_ML == 2) {
						trigDiTau_bkg_ML = 3; 
						nEvent_trigDiTau_bkg_ML++; 
					}
				} else if (tauTriggerLoose(recoTau, clusters->at(n))) {
					if (trigDiTau_bkg_ML == 0) {
						trigDiTau_bkg_ML = 1; 
					} else if (trigDiTau_bkg_ML == 2) {
						trigDiTau_bkg_ML = 3; 
					}
				}
			}
			th1fHists.at("h_nTracksIsolation").vars.push_back(recoTau.nTracksIsolation);
                        th1fHists.at("h_nTracksCharged").vars.push_back(recoTau.nTracksCharged);
                        th1fHists.at("h_nAllTracks").vars.push_back(recoTau.nAllTracks);

			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5;  
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				lowestTriggeredRecoPt_noCut = (lowestTriggeredRecoPt_noCut==-99.) ? recoTau.pt : min(lowestTriggeredRecoPt_noCut, recoTau.pt); 
				highestTriggeredRecoPt_noCut = max(highestTriggeredRecoPt_noCut, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.seedET_min = 2000; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				lowestTriggeredRecoPt_seedEt2GeV = (lowestTriggeredRecoPt_seedEt2GeV==-99.) ? recoTau.pt : min(lowestTriggeredRecoPt_seedEt2GeV, recoTau.pt); 
				highestTriggeredRecoPt_seedEt2GeV = max(highestTriggeredRecoPt_seedEt2GeV, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.seedET_min = 5000; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				lowestTriggeredRecoPt_seedEt5GeV = (lowestTriggeredRecoPt_seedEt5GeV==-99.) ? recoTau.pt : min(lowestTriggeredRecoPt_seedEt5GeV, recoTau.pt); 
				highestTriggeredRecoPt_seedEt5GeV = max(highestTriggeredRecoPt_seedEt5GeV, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.seedET_min = 8000; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				lowestTriggeredRecoPt_seedEt8GeV = (lowestTriggeredRecoPt_seedEt8GeV==-99.) ? recoTau.pt : min(lowestTriggeredRecoPt_seedEt8GeV, recoTau.pt); 
				highestTriggeredRecoPt_seedEt8GeV = max(highestTriggeredRecoPt_seedEt8GeV, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.seedET_min = 15000; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_seedEt15GeV = max(highestTriggeredRecoPt_seedEt15GeV, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.seedET_min = 20000; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_seedEt20GeV = max(highestTriggeredRecoPt_seedEt20GeV, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.seedET_min = 25000; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_seedEt25GeV = max(highestTriggeredRecoPt_seedEt25GeV, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_CA_min = 0.2; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_CA0p2 = max(highestTriggeredRecoPt_CA0p2, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_CA_min = 0.5; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_CA0p5 = max(highestTriggeredRecoPt_CA0p5, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_CA_min = 0.8; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_CA0p8 = max(highestTriggeredRecoPt_CA0p8, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_R1C_max = 0.2; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_R1C0p2 = max(highestTriggeredRecoPt_R1C0p2, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_R1C_max = 0.5; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_R1C0p5 = max(highestTriggeredRecoPt_R1C0p5, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_R1C_max = 0.8; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_R1C0p8 = max(highestTriggeredRecoPt_R1C0p8, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_R2C_max = 0.2; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_R2C0p2 = max(highestTriggeredRecoPt_R2C0p2, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_R2C_max = 0.5; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_R2C0p5 = max(highestTriggeredRecoPt_R2C0p5, recoTau.pt); 
			}
			tCuts.setDefaults(); tCuts.tauAbsEta_max = 2.5; tCuts.iso_R2C_max = 0.8; 
			if (tauTriggerAlg(recoTau, clusters->at(n), tCuts)) {
				highestTriggeredRecoPt_R2C0p8 = max(highestTriggeredRecoPt_R2C0p8, recoTau.pt); 
			}
		}
		th1fHists.at("h_recoTau_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
		th1fHists.at("h_recoTau_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
		th1fHists.at("h_recoTau_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
		th1fHists.at("h_recoTau_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
		th1fHists.at("h_recoTau_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
		th1fHists.at("h_recoTau_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
		th1fHists.at("h_recoTau_etaLeading").vars.push_back(leadingTau.eta); 
		if (trigDiTau_bkg_TT == 3) {
			th1fHists.at("h_recoTau_diTauTrigTT_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTT_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTT_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTT_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTT_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
			th1fHists.at("h_recoTau_diTauTrigTT_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTT_etaLeading").vars.push_back(leadingTau.eta); 
		}
		if (trigDiTau_bkg_MM == 3) {
			th1fHists.at("h_recoTau_diTauTrigMM_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigMM_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigMM_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigMM_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigMM_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
			th1fHists.at("h_recoTau_diTauTrigMM_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigMM_etaLeading").vars.push_back(leadingTau.eta); 
		}
		if (trigDiTau_bkg_LL == 3) {
			th1fHists.at("h_recoTau_diTauTrigLL_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigLL_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigLL_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigLL_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigLL_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
			th1fHists.at("h_recoTau_diTauTrigLL_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigLL_etaLeading").vars.push_back(leadingTau.eta); 
		}
		if (trigDiTau_bkg_TM == 3) {
			th1fHists.at("h_recoTau_diTauTrigTM_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTM_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTM_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTM_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTM_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
			th1fHists.at("h_recoTau_diTauTrigTM_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTM_etaLeading").vars.push_back(leadingTau.eta); 
		}
		if (trigDiTau_bkg_TL == 3) {
			th1fHists.at("h_recoTau_diTauTrigTL_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTL_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTL_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTL_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTL_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
			th1fHists.at("h_recoTau_diTauTrigTL_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigTL_etaLeading").vars.push_back(leadingTau.eta); 
		}
		if (trigDiTau_bkg_ML == 3) {
			th1fHists.at("h_recoTau_diTauTrigML_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigML_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigML_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigML_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigML_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
			th1fHists.at("h_recoTau_diTauTrigML_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
			th1fHists.at("h_recoTau_diTauTrigML_etaLeading").vars.push_back(leadingTau.eta); 
		}

		if (lowestTriggeredRecoPt_noCut != -99.) th1fHists.at("h_eventTriggered_recoTau_lowestPt_noCut").vars.push_back(lowestTriggeredRecoPt_noCut*1e-3); 
		if (lowestTriggeredRecoPt_seedEt2GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_lowestPt_seedEt2GeV").vars.push_back(lowestTriggeredRecoPt_seedEt2GeV*1e-3); 
		if (lowestTriggeredRecoPt_seedEt5GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_lowestPt_seedEt5GeV").vars.push_back(lowestTriggeredRecoPt_seedEt5GeV*1e-3); 
		if (lowestTriggeredRecoPt_seedEt8GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_lowestPt_seedEt8GeV").vars.push_back(lowestTriggeredRecoPt_seedEt8GeV*1e-3); 
		if (highestTriggeredRecoPt_noCut != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_noCut").vars.push_back(highestTriggeredRecoPt_noCut*1e-3); 
		if (highestTriggeredRecoPt_seedEt2GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt2GeV").vars.push_back(highestTriggeredRecoPt_seedEt2GeV*1e-3); 
		if (highestTriggeredRecoPt_seedEt5GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt5GeV").vars.push_back(highestTriggeredRecoPt_seedEt5GeV*1e-3); 
		if (highestTriggeredRecoPt_seedEt8GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt8GeV").vars.push_back(highestTriggeredRecoPt_seedEt8GeV*1e-3); 
		if (highestTriggeredRecoPt_seedEt15GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt15GeV").vars.push_back(highestTriggeredRecoPt_seedEt15GeV*1e-3); 
		if (highestTriggeredRecoPt_seedEt20GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt20GeV").vars.push_back(highestTriggeredRecoPt_seedEt20GeV*1e-3); 
		if (highestTriggeredRecoPt_seedEt25GeV != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt25GeV").vars.push_back(highestTriggeredRecoPt_seedEt25GeV*1e-3); 
		if (highestTriggeredRecoPt_CA0p2 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_CA0p2").vars.push_back(highestTriggeredRecoPt_CA0p2*1e-3); 
		if (highestTriggeredRecoPt_CA0p5 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_CA0p5").vars.push_back(highestTriggeredRecoPt_CA0p5*1e-3); 
		if (highestTriggeredRecoPt_CA0p8 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_CA0p8").vars.push_back(highestTriggeredRecoPt_CA0p8*1e-3); 
		if (highestTriggeredRecoPt_R1C0p2 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_R1C0p2").vars.push_back(highestTriggeredRecoPt_R1C0p2*1e-3); 
		if (highestTriggeredRecoPt_R1C0p5 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_R1C0p5").vars.push_back(highestTriggeredRecoPt_R1C0p5*1e-3); 
		if (highestTriggeredRecoPt_R1C0p8 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_R1C0p8").vars.push_back(highestTriggeredRecoPt_R1C0p8*1e-3); 
		if (highestTriggeredRecoPt_R2C0p2 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_R2C0p2").vars.push_back(highestTriggeredRecoPt_R2C0p2*1e-3); 
		if (highestTriggeredRecoPt_R2C0p5 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_R2C0p5").vars.push_back(highestTriggeredRecoPt_R2C0p5*1e-3); 
		if (highestTriggeredRecoPt_R2C0p8 != -99.) th1fHists.at("h_eventTriggered_recoTau_highestPt_R2C0p8").vars.push_back(highestTriggeredRecoPt_R2C0p8*1e-3); 

		// Loop through truth-matched reco taus

		// Di-tau trigger status
		// 0: None found
		// 1: Sub-leading found
		// 2: Leading found
		// 3: Both found
		int trigDiTau_sig_TT = 0; 
		int trigDiTau_sig_MM = 0; 
		int trigDiTau_sig_LL = 0; 
		int trigDiTau_sig_TM = 0; 
		int trigDiTau_sig_TL = 0; 
		int trigDiTau_sig_ML = 0; 

		leadingTau.reset(); 
		subleadingTau.reset(); 
		for (RecoTau matchedRecoTau : matchedRecoTaus->at(n)){
			// Remove 1prong had taus with seed cluster EM ratio > 95%, which should be picked up by electron trigger
			//if (matchedRecoTau.matchedTruthTau.isHadronic && matchedRecoTau.matchedTruthTau.nProng==1 && matchedRecoTau.seedCluster.EngFracEM>.95) continue; 
			if (matchedRecoTau.pt > leadingTau.pt) {
				subleadingTau = leadingTau; 
				leadingTau = matchedRecoTau; 
			} else if (matchedRecoTau.pt > subleadingTau.pt) {
				subleadingTau = matchedRecoTau; 
			}
			th1fHists.at("h_matchedRecoTau_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
			th1fHists.at("h_matchedRecoTau_eta").vars.push_back(matchedRecoTau.eta); 
			th1fHists.at("h_matchedRecoTau_phi").vars.push_back(matchedRecoTau.phi); 
			th1fHists.at("h_truthMatched2RecoTau_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
			th1fHists.at("h_truthMatched2RecoTau_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			th1fHists.at("h_truthMatched2RecoTau_phi").vars.push_back(matchedRecoTau.matchedTruthTau.phi); 
			th1fHists.at("h_matchedRecoTau_nMatchedClusters").vars.push_back(matchedRecoTau.matchedClusters.size()); 
			th1fHists.at("h_matchedRecoTau_seedET").vars.push_back(matchedRecoTau.seedCluster.et*1e-3); 
			auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(matchedRecoTau, clusters->at(n)); 
			th1fHists.at("h_matchedRecoTauIsolation_seedEtCore").vars.push_back(matchedRecoTau.seedCluster.et/(core_et + 1e-5)); 
			th1fHists.at("h_matchedRecoTauIsolation_seedEtAll").vars.push_back(matchedRecoTau.seedCluster.et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_matchedRecoTauIsolation_CA").vars.push_back(core_et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_matchedRecoTauIsolation_R1C").vars.push_back(ring1_et/(core_et + 1e-5)); 
			th1fHists.at("h_matchedRecoTauIsolation_R2C").vars.push_back(ring2_et/(core_et + 1e-5)); 
			th1fHists.at("h_matchedRecoTauIsolation_R2R1").vars.push_back(ring2_et/(ring1_et + 1e-5)); 
			th1fHists.at("h_matchedRecoTau_seedToMatchedClustersEtFraction").vars.push_back(matchedRecoTau.seedCluster.et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_matchedRecoTau_seedToRecoTauEtFraction").vars.push_back(matchedRecoTau.seedCluster.et/matchedRecoTau.p4.Et()); 

			auto [nCoreClusters, nRing1Clusters, nRing2Clusters] = countNearbyClusters(matchedRecoTau.seedCluster, clusters->at(n)); 
			th1fHists.at("h_matchedRecoTauIsolation_nCoreClusters").vars.push_back(nCoreClusters); 
			th1fHists.at("h_matchedRecoTauIsolation_nRing1Clusters").vars.push_back(nRing1Clusters); 
			th1fHists.at("h_matchedRecoTauIsolation_nRing2Clusters").vars.push_back(nRing2Clusters); 
			th2fHists.at("h_matchedRecoTau_seedET_CA").xvars.push_back(matchedRecoTau.seedCluster.et*1e-3); 
			th2fHists.at("h_matchedRecoTau_seedET_CA").yvars.push_back(core_et/(core_et + ring1_et + ring2_et + 1e-5)); 

			/*th2fHists.at("h_matchedRecoTau_seedET_CA").xvars.push_back(matchedRecoTau.seedCluster.et*1e-3); 
			th2fHists.at("h_matchedRecoTau_seedET_CA").yvars.push_back(core_et/(core_et+ring1_et+ring2_et)); */

			// Trig working points
			if (tauTriggerBaseline(matchedRecoTau, clusters->at(n))) th1fHists.at("h_matchedRecoTau_trigBaseline_pt").vars.push_back(matchedRecoTau.pt*1e-3);
			if (tauTriggerLoose(matchedRecoTau, clusters->at(n))) th1fHists.at("h_matchedRecoTau_trigLoose_pt").vars.push_back(matchedRecoTau.pt*1e-3);
			if (tauTriggerMedium(matchedRecoTau, clusters->at(n))) th1fHists.at("h_matchedRecoTau_trigMedium_pt").vars.push_back(matchedRecoTau.pt*1e-3);
			if (tauTriggerTight(matchedRecoTau, clusters->at(n))) th1fHists.at("h_matchedRecoTau_trigTight_pt").vars.push_back(matchedRecoTau.pt*1e-3);

			// Di-tau trigger
			if (trigDiTau_sig_TT != 3) {
				if (tauTriggerTight(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_TT == 0) {
						trigDiTau_sig_TT = 1; 
					} else if (trigDiTau_sig_TT == 1) {
						trigDiTau_sig_TT = 3; 
						nEvent_trigDiTau_sig_TT++; 
					}
				}
			}
			if (trigDiTau_sig_MM != 3) {
				if (tauTriggerMedium(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_MM == 0) {
						trigDiTau_sig_MM = 1; 
					} else if (trigDiTau_sig_MM == 1) {
						trigDiTau_sig_MM = 3; 
						nEvent_trigDiTau_sig_MM++; 
					}
				}
			}
			if (trigDiTau_sig_LL != 3) {
				if (tauTriggerLoose(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_LL == 0) {
						trigDiTau_sig_LL = 1; 
					} else if (trigDiTau_sig_LL == 1) {
						trigDiTau_sig_LL = 3; 
						nEvent_trigDiTau_sig_LL++; 
					}
				}
			}
			if (trigDiTau_sig_TM != 3) {
				if (tauTriggerTight(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_TM == 0) {
						trigDiTau_sig_TM = 2; 
					} else if (trigDiTau_sig_TM == 1 || trigDiTau_sig_TM == 2) {
						trigDiTau_sig_TM = 3; 
						nEvent_trigDiTau_sig_TM++; 
					}
				} else if (tauTriggerMedium(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_TM == 0) {
						trigDiTau_sig_TM = 1; 
					} else if (trigDiTau_sig_TM == 2) {
						trigDiTau_sig_TM = 3; 
					}
				}
			}
			if (trigDiTau_sig_TL != 3) {
				if (tauTriggerTight(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_TL == 0) {
						trigDiTau_sig_TL = 2; 
					} else if (trigDiTau_sig_TL == 1 || trigDiTau_sig_TL == 2) {
						trigDiTau_sig_TL = 3; 
						nEvent_trigDiTau_sig_TL++; 
					}
				} else if (tauTriggerLoose(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_TL == 0) {
						trigDiTau_sig_TL = 1; 
					} else if (trigDiTau_sig_TL == 2) {
						trigDiTau_sig_TL = 3; 
					}
				}
			}
			if (trigDiTau_sig_ML != 3) {
				if (tauTriggerMedium(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_ML == 0) {
						trigDiTau_sig_ML = 2; 
					} else if (trigDiTau_sig_ML == 1 || trigDiTau_sig_ML == 2) {
						trigDiTau_sig_ML = 3; 
						nEvent_trigDiTau_sig_ML++; 
					}
				} else if (tauTriggerLoose(matchedRecoTau, clusters->at(n))) {
					if (trigDiTau_sig_ML == 0) {
						trigDiTau_sig_ML = 1; 
					} else if (trigDiTau_sig_ML == 2) {
						trigDiTau_sig_ML = 3; 
					}
				}
			}

			// Tau trig alg
			tCuts.setDefaults(); 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_noCut_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_noCut_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_seedCluster_EngFracEM").vars.push_back(matchedRecoTau.seedCluster.EngFracEM); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_noCut_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_noCut_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 2000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_seedEt2GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_seedEt2GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt2GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt2GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 5000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_seedEt5GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_seedEt5GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt5GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt5GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 8000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_seedEt8GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_seedEt8GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt8GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt8GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 15000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_seedEt15GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_seedEt15GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt15GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt15GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 20000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_seedEt20GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_seedEt20GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt20GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt20GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 25000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_seedEt25GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_seedEt25GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt25GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_seedEt25GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 2000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_et2GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_et2GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_et2GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_et2GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 3000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_et3GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_et3GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_et3GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_et3GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 5000; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_et5GeV_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_et5GeV_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_et5GeV_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_et5GeV_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.2; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_CA0p2_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_CA0p2_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_CA0p2_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_CA0p2_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.5; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_CA0p5_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_CA0p5_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_CA0p5_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_CA0p5_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.8; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_CA0p8_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_CA0p8_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_CA0p8_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_CA0p8_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.2; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R1C0p2_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R1C0p2_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R1C0p2_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R1C0p2_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.5; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R1C0p5_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R1C0p5_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R1C0p5_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R1C0p5_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.8; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R1C0p8_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R1C0p8_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R1C0p8_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R1C0p8_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.2; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R2C0p2_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R2C0p2_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2C0p2_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2C0p2_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.5; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R2C0p5_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R2C0p5_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2C0p5_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2C0p5_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.8; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R2C0p8_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R2C0p8_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2C0p8_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2C0p8_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 0.5; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R2R10p5_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R2R10p5_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2R10p5_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2R10p5_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 1.5; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R2R11p5_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R2R11p5_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2R11p5_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2R11p5_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 9.5; 
			if (tauTriggerAlg(matchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_matchedRecoTau_triggered_R2R19p5_pt").vars.push_back(matchedRecoTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_triggered_R2R19p5_eta").vars.push_back(matchedRecoTau.eta); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2R19p5_pt").vars.push_back(matchedRecoTau.matchedTruthTau.pt*1e-3); 
				th1fHists.at("h_truthMatched2RecoTau_triggered_R2R19p5_eta").vars.push_back(matchedRecoTau.matchedTruthTau.eta); 
			}

		}
		if (nMatchedRecoTaus == 2) {
			th1fHists.at("h_matchedRecoTau_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
			th1fHists.at("h_matchedRecoTau_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
			th1fHists.at("h_matchedRecoTau_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_matchedRecoTau_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
			th1fHists.at("h_matchedRecoTau_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
			th1fHists.at("h_matchedRecoTau_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
			th1fHists.at("h_matchedRecoTau_etaLeading").vars.push_back(leadingTau.eta); 
			th1fHists.at("h_matchedRecoTau_etaSubleading").vars.push_back(subleadingTau.eta); 
			if (trigDiTau_sig_TT == 3) {
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_etaLeading").vars.push_back(leadingTau.eta); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTT_etaSubleading").vars.push_back(subleadingTau.eta); 
			}
			if (trigDiTau_sig_MM == 3) {
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_etaLeading").vars.push_back(leadingTau.eta); 
				th1fHists.at("h_matchedRecoTau_diTauTrigMM_etaSubleading").vars.push_back(subleadingTau.eta); 
			}
			if (trigDiTau_sig_LL == 3) {
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_etaLeading").vars.push_back(leadingTau.eta); 
				th1fHists.at("h_matchedRecoTau_diTauTrigLL_etaSubleading").vars.push_back(subleadingTau.eta); 
			}
			if (trigDiTau_sig_TM == 3) {
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_etaLeading").vars.push_back(leadingTau.eta); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTM_etaSubleading").vars.push_back(subleadingTau.eta); 
			}
			if (trigDiTau_sig_TL == 3) {
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_etaLeading").vars.push_back(leadingTau.eta); 
				th1fHists.at("h_matchedRecoTau_diTauTrigTL_etaSubleading").vars.push_back(subleadingTau.eta); 
			}
			if (trigDiTau_sig_ML == 3) {
				th1fHists.at("h_matchedRecoTau_diTauTrigML_ptLeading").vars.push_back(leadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigML_ptSubleading").vars.push_back(subleadingTau.pt*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigML_seedEtLeading").vars.push_back(leadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigML_seedEtSubleading").vars.push_back(subleadingTau.seedCluster.et*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigML_diTauDeltaR").vars.push_back(leadingTau.p4.DeltaR(subleadingTau.p4)); 
				th1fHists.at("h_matchedRecoTau_diTauTrigML_diTauMass").vars.push_back((leadingTau.p4 + subleadingTau.p4).M()*1e-3); 
				th1fHists.at("h_matchedRecoTau_diTauTrigML_etaLeading").vars.push_back(leadingTau.eta); 
				th1fHists.at("h_matchedRecoTau_diTauTrigML_etaSubleading").vars.push_back(subleadingTau.eta); 
			}
		}
		// Loop through truth-unmatched reco taus
		for (RecoTau unmatchedRecoTau : unmatchedRecoTaus->at(n)){
			th1fHists.at("h_unmatchedRecoTau_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
			th1fHists.at("h_unmatchedRecoTau_eta").vars.push_back(unmatchedRecoTau.eta); 
			th1fHists.at("h_unmatchedRecoTau_phi").vars.push_back(unmatchedRecoTau.phi); 
			th1fHists.at("h_unmatchedRecoTau_nUnmatchedClusters").vars.push_back(unmatchedRecoTau.matchedClusters.size()); 
			th1fHists.at("h_unmatchedRecoTau_seedET").vars.push_back(unmatchedRecoTau.seedCluster.et*1e-3); 
			auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(unmatchedRecoTau, clusters->at(n)); 
			th1fHists.at("h_unmatchedRecoTauIsolation_seedEtCore").vars.push_back(unmatchedRecoTau.seedCluster.et/(core_et + 1e-5)); 
			th1fHists.at("h_unmatchedRecoTauIsolation_seedEtAll").vars.push_back(unmatchedRecoTau.seedCluster.et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_unmatchedRecoTauIsolation_CA").vars.push_back(core_et/(core_et+ring1_et+ring2_et)); 
			th1fHists.at("h_unmatchedRecoTauIsolation_R1C").vars.push_back(ring1_et/(core_et + 1e-5)); 
			th1fHists.at("h_unmatchedRecoTauIsolation_R2C").vars.push_back(ring2_et/(core_et + 1e-5)); 
			th1fHists.at("h_unmatchedRecoTauIsolation_R2R1").vars.push_back(ring2_et/(ring1_et + 1e-5)); 
			auto [nCoreClusters, nRing1Clusters, nRing2Clusters] = countNearbyClusters(unmatchedRecoTau.seedCluster, clusters->at(n)); 
			th1fHists.at("h_unmatchedRecoTauIsolation_nCoreClusters").vars.push_back(nCoreClusters); 
			th1fHists.at("h_unmatchedRecoTauIsolation_nRing1Clusters").vars.push_back(nRing1Clusters); 
			th1fHists.at("h_unmatchedRecoTauIsolation_nRing2Clusters").vars.push_back(nRing2Clusters); 
			
			/*th2fHists.at("h_unmatchedRecoTau_seedET_CA").xvars.push_back(unmatchedRecoTau.seedCluster.et*1e-3); 
			th2fHists.at("h_unmatchedRecoTau_seedET_CA").yvars.push_back(core_et/(core_et+ring1_et+ring2_et)); */

			// Trig working points
			if (tauTriggerBaseline(unmatchedRecoTau, clusters->at(n))) th1fHists.at("h_unmatchedRecoTau_trigBaseline_pt").vars.push_back(unmatchedRecoTau.pt*1e-3);
			if (tauTriggerLoose(unmatchedRecoTau, clusters->at(n))) th1fHists.at("h_unmatchedRecoTau_trigLoose_pt").vars.push_back(unmatchedRecoTau.pt*1e-3);
			if (tauTriggerMedium(unmatchedRecoTau, clusters->at(n))) th1fHists.at("h_unmatchedRecoTau_trigMedium_pt").vars.push_back(unmatchedRecoTau.pt*1e-3);
			if (tauTriggerTight(unmatchedRecoTau, clusters->at(n))) th1fHists.at("h_unmatchedRecoTau_trigTight_pt").vars.push_back(unmatchedRecoTau.pt*1e-3);
			
			// Tau trig alg
			tCuts.setDefaults(); 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_noCut_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_noCut_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 2000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt2GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt2GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 5000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt5GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt5GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 8000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt8GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt8GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 15000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt15GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt15GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 20000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt20GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt20GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.seedET_min = 25000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt25GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_seedEt25GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 2000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_et2GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_et2GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 3000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_et3GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_et3GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.et_min = 5000; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_et5GeV_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_et5GeV_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.2; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_CA0p2_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_CA0p2_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.5; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_CA0p5_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_CA0p5_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_CA_min = 0.8; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_CA0p8_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_CA0p8_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.2; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R1C0p2_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R1C0p2_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.5; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R1C0p5_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R1C0p5_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R1C_max = 0.8; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R1C0p8_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R1C0p8_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.2; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R2C0p2_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R2C0p2_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.5; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R2C0p5_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R2C0p5_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2C_max = 0.8; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R2C0p8_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R2C0p8_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 0.5; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R2R10p5_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R2R10p5_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 1.5; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R2R11p5_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R2R11p5_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
			tCuts.setDefaults(); tCuts.iso_R2R1_max = 9.5; 
			if (tauTriggerAlg(unmatchedRecoTau, clusters->at(n), tCuts)) {
				th1fHists.at("h_unmatchedRecoTau_triggered_R2R19p5_pt").vars.push_back(unmatchedRecoTau.pt*1e-3); 
				th1fHists.at("h_unmatchedRecoTau_triggered_R2R19p5_eta").vars.push_back(unmatchedRecoTau.eta); 
			}
		}
	}
        }
	if (printProgress) printf("\n"); // Finish progress printf

	// Plot all hists in map
	int nTh1fs = th1fHists.size(); 
	int ind1 = 0; 
	for (auto& iter : th1fHists){
		ind1++; 
		if (printProgress) printf("\rPlotting TH1F: %i/%i (%.1f%%)", ind1, nTh1fs, 100.*ind1/nTh1fs); 
		iter.second.plot_hist(); 
	}
	if (printProgress) printf("\n"); 

	int nTh2fs = th2fHists.size(); 
	int ind2 = 0; 
	for (auto& iter : th2fHists){
		ind2++; 
		if (printProgress) printf("\rPlotting TH2F: %i/%i (%.1f%%)", ind2, nTh2fs, 100.*ind2/nTh2fs); 
		iter.second.plot_hist(); 
	}
	if (printProgress) printf("\n"); 

	printf("trigEfficiencyDiTau_sig_TT = %.1f%%\n", 100.*nEvent_trigDiTau_sig_TT/nEvent_withTwoMatchedRecoTaus); 
	printf("trigEfficiencyDiTau_sig_MM = %.1f%%\n", 100.*nEvent_trigDiTau_sig_MM/nEvent_withTwoMatchedRecoTaus); 
	printf("trigEfficiencyDiTau_sig_LL = %.1f%%\n", 100.*nEvent_trigDiTau_sig_LL/nEvent_withTwoMatchedRecoTaus); 
	printf("trigEfficiencyDiTau_sig_TM = %.1f%%\n", 100.*nEvent_trigDiTau_sig_TM/nEvent_withTwoMatchedRecoTaus); 
	printf("trigEfficiencyDiTau_sig_TL = %.1f%%\n", 100.*nEvent_trigDiTau_sig_TL/nEvent_withTwoMatchedRecoTaus); 
	printf("trigEfficiencyDiTau_sig_ML = %.1f%%\n", 100.*nEvent_trigDiTau_sig_ML/nEvent_withTwoMatchedRecoTaus); 
	printf("trigRate_TT = %.1f kHz\n", 40000.*nEvent_trigDiTau_bkg_TT/nEvent); 
	printf("trigRate_MM = %.1f kHz\n", 40000.*nEvent_trigDiTau_bkg_MM/nEvent); 
	printf("trigRate_LL = %.1f kHz\n", 40000.*nEvent_trigDiTau_bkg_LL/nEvent); 
	printf("trigRate_TM = %.1f kHz\n", 40000.*nEvent_trigDiTau_bkg_TM/nEvent); 
	printf("trigRate_TL = %.1f kHz\n", 40000.*nEvent_trigDiTau_bkg_TL/nEvent); 
	printf("trigRate_ML = %.1f kHz\n", 40000.*nEvent_trigDiTau_bkg_ML/nEvent); 

	struct result {DebugMap<string, Th1fHist> th1fHists; DebugMap<string, Th2fHist> th2fHists;}; 
	return result {th1fHists, th2fHists}; // Return TH1F for secondary plots
}
