// Read ntuple into vectors of obj, pushing back to the vector pointers in the argument
void read_ntuple(string tree_file_name, vector<vector<Cluster>> *clusters, vector<vector<TruthTau>> *truthTaus, vector<vector<RecoTau>> *recoTaus){
	// Ntuple path
	//string dir = "/msu/data/t3work13/xinfei/tmp/atlas/gep/"; 
	//string tree_file_name = dir + "myfile_tree.root"; 
	//string tree_file_name = dir + "user.xinfei.GepOutputReader_mc15_14TeV.800281.Py8EG_AZ_Ztautau.recon.AOD.e8379_s3735_s3738_r13046_v10_agg.root"; 
	const string cl_name = "CaloTopoClusters422";	
	// Read TTree
	printf("\033[2m    Parsing ntuple: %s\n\033[0m", tree_file_name.c_str()); 
	TFile *tree_file = new TFile(tree_file_name.c_str()); 
	TTree *tree = (TTree*) tree_file->Get("ntuple"); 
	// Setup vectors to get values from TTree
	vector<float>* cluster_et = 0; 
	vector<float>* cluster_eta = 0; 
	vector<float>* cluster_phi = 0; 
	//<vector<float>>* cluster_EngFracEM = 0; 
	tree->SetBranchAddress((cl_name+"_et").c_str(), &(cluster_et)); 
	tree->SetBranchAddress((cl_name+"_eta").c_str(), &(cluster_eta)); 
	tree->SetBranchAddress((cl_name+"_phi").c_str(), &(cluster_phi)); 
	//tree->SetBranchAddress((cl_name+"_EngFracEM").c_str(), &(cluster_EngFracEM)); 
   
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
	tree->SetBranchAddress("truthTau_isHadronic", &truthTau_isHadronic); 
	tree->SetBranchAddress("truthTau_isLeptonicEle", &truthTau_isLeptonicEle); 

	vector<float> *recoTau_pt = 0;
	vector<float> *recoTau_eta = 0;
	vector<float> *recoTau_phi = 0;
	vector<float> *recoTau_m = 0;
	vector<float> *recoTau_nTaus = 0;
	//tree->SetBranchAddress("recoTau_pt", &recoTau_pt);
	tree->SetBranchAddress("recoTau_ptFinalCalib", &recoTau_pt); // Using final calib pt
	tree->SetBranchAddress("recoTau_eta", &recoTau_eta);
	tree->SetBranchAddress("recoTau_phi", &recoTau_phi); 
	tree->SetBranchAddress("recoTau_m", &recoTau_m); 
	tree->SetBranchAddress("recoTau_nTaus", &recoTau_nTaus);


	vector<float> *nTracksCharged = 0;
  	vector<float> *nTracksIsolation = 0;
  	vector<float> *nAllTracks = 0;
	tree->SetBranchAddress("nTracksCharged", &nTracksCharged);
  	tree->SetBranchAddress("nTracksIsolation", &nTracksIsolation);
  	tree->SetBranchAddress("nAllTracks", &nAllTracks);

	// Event loop for parsing ntuple
	int nEvent = tree->GetEntries(); 
	for (int n=0; n<nEvent; n++) {
		if (printProgress) printf("\rParsing ntuple event: %i/%i (%.1f%%)", n+1, nEvent, 100.*(n+1)/nEvent); 
		tree->GetEntry(n);

		// Clusters
		vector<Cluster> vec_clusters = {}; // Temp vector for clusters in this event
		// Loop over each cluster
		for (int i=0; i < static_cast<int>(cluster_et->size()); i++){
			Cluster cluster; 
			cluster.et = cluster_et->at(i); 
			cluster.eta = cluster_eta->at(i); 
			cluster.phi = cluster_phi->at(i); 
			//cluster.EngFracEM = cluster_EngFracEM->at(0).at(i); 

			if (cluster.et < 1000) continue; // Cluster et cut
			vec_clusters.push_back(cluster); 
		}
		clusters->push_back(vec_clusters); 

		// Truth Taus
		vector<TruthTau> vec_truthTaus = {}; // Temp vector for truth taus in this event
		// Loop over each truth tau
		for (int j=0; j < static_cast<int>(truthTau_pt->size()); j++) {
			TruthTau truthTau; 
			truthTau.pt = truthTau_pt->at(j); 
			truthTau.eta = truthTau_eta->at(j); 
			truthTau.phi = truthTau_phi->at(j); 
			truthTau.totalpt = truthTau_totalpt->at(j); 
			truthTau.neutrinopt = truthTau_neutrinopt->at(j); 
			truthTau.neutrinoeta = truthTau_neutrinoeta->at(j); 
			truthTau.neutrinophi = truthTau_neutrinophi->at(j); 
			truthTau.set_p4(); 
			truthTau.isHadronic = truthTau_isHadronic->at(j); 
			truthTau.isLeptonicEle = truthTau_isLeptonicEle->at(j); 
			truthTau.nProng = truthTau_nProng->at(j); 
			truthTau.nChargedMeson = truthTau_nChargedMeson->at(j); 
			truthTau.nNeutralMeson = truthTau_nNeutralMeson->at(j); 
			truthTau.set_p4(); 

			if (abs(truthTau.eta)>2.5) continue; // Truth tau eta cut
			vec_truthTaus.push_back(truthTau); 
		}
		truthTaus->push_back(vec_truthTaus); 

		// Reco taus
		vector<RecoTau> vec_recoTaus; // Temp vector for reco taus in this event
		// Loop over each reco tau
		for (int k=0; k < static_cast<int>(recoTau_pt->size()); k++) {
			RecoTau recoTau; 
			recoTau.pt = recoTau_pt->at(k); 
			recoTau.eta = recoTau_eta->at(k); 
			recoTau.phi = recoTau_phi->at(k); 
			recoTau.m = recoTau_m->at(k); 
			recoTau.nTracksCharged = nTracksCharged->at(k);
			recoTau.nAllTracks = nAllTracks->at(k);
			recoTau.nTracksIsolation = nTracksIsolation->at(k);
			recoTau.set_p4(); 
			vec_recoTaus.push_back(recoTau); 
		}
		recoTaus->push_back(vec_recoTaus); 
	}
	if (printProgress) printf("\n"); // Finish progress printf
}
