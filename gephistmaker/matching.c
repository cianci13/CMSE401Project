// Do matching and edit the obj in vector

// Get dR between two particles
template <class Part1, class Part2> float getDR(Part1 part1, Part2 part2){
	return TMath::Sqrt( (part1.eta-part2.eta)*(part1.eta-part2.eta) + (part1.phi-part2.phi)*(part1.phi-part2.phi) );
}

// For each truth/reco tau get a vector of matched clusters and return the updated tau
template <typename Tau> Tau matchClusters2Tau(Tau tau, vector<Cluster> vec_clusters, float max_dR, float min_et = 0){
	for (Cluster cluster : vec_clusters){
		if (cluster.et < min_et) continue; // Cluster et cut
		float dR = getDR(tau, cluster); 
		if (dR > max_dR) continue; // Delta R cut
		cluster.matchedDR = dR; 
		tau.matchedClusters.push_back(cluster); 
	}
	return tau; 
}

// Main matching function
void matching(vector<vector<Cluster>> *clusters, vector<vector<TruthTau>> *truthTaus, vector<vector<RecoTau>> *recoTaus, vector<vector<RecoTau>> *matchedRecoTaus, vector<vector<RecoTau>> *unmatchedRecoTaus){
	// Event loop for matching
	int nEvent = clusters->size(); 
	for (int n=0; n<nEvent; n++) {
		if (printProgress) printf("\rCluster matching for event: %i/%i (%.1f%%)", n+1, nEvent, 100.*(n+1)/nEvent); 
		int nTruthTaus = truthTaus->at(n).size(); 
		for (int j=0; j<nTruthTaus; j++){
			// Matching cluster to truth tau
			float max_dR = 0.3; 
			float min_et = 1000; // MeV
			truthTaus->at(n).at(j) = matchClusters2Tau(truthTaus->at(n).at(j), clusters->at(n), max_dR, min_et); 
			truthTaus->at(n).at(j).set_seedCluster(0.1); 
		}

		int nRecoTaus = recoTaus->at(n).size(); 
		for (int j=0; j<nRecoTaus; j++){
			// Matching cluster to reco tau
			float max_dR = 0.3; 
			float min_et = 1000; // MeV
			recoTaus->at(n).at(j) = matchClusters2Tau(recoTaus->at(n).at(j), clusters->at(n), max_dR, min_et); 
			recoTaus->at(n).at(j).set_seedCluster(0.1);
		}

		int nMatchedRecoTaus = matchedRecoTaus->at(n).size(); 
		for (int k=0; k<nMatchedRecoTaus; k++){
			// Matching cluster to truth-matched reco tau
			float max_dR = 0.3; 
			float min_et = 1000; // MeV
			matchedRecoTaus->at(n).at(k) = matchClusters2Tau(matchedRecoTaus->at(n).at(k), clusters->at(n), max_dR, min_et); 
			matchedRecoTaus->at(n).at(k).set_seedCluster(0.1);
		}

		int nUnmatchedRecoTaus = unmatchedRecoTaus->at(n).size(); 
		for (int l=0; l<nUnmatchedRecoTaus; l++){
			// Matching cluster to truth-unmatched reco tau
			float max_dR = 0.3; 
			float min_et = 1000; // MeV
			unmatchedRecoTaus->at(n).at(l) = matchClusters2Tau(unmatchedRecoTaus->at(n).at(l), clusters->at(n), max_dR, min_et); 
			unmatchedRecoTaus->at(n).at(l).set_seedCluster(0.1);
		}
	}
	if (printProgress) printf("\n"); // Finish progress printf
}
