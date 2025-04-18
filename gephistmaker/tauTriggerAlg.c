// Nearby et integration, for isolation variable calculation
template <class Part> auto integrateNearbyEt(Part center, vector<Cluster> clusters, float clusterEt_min=0){
	float core_et = 0; // 0<dR<0.1
	float ring1_et = 0; // 0.1<dR<0.2
	float ring2_et = 0; // 0.2<dR<0.3
	// Uses only matched cluster to look through fewer clusters per tau
	for (Cluster cluster : clusters){
		if (cluster.et < clusterEt_min) continue; 
		float dR = getDR(center, cluster); 
		if (dR < 0.1){
			core_et += cluster.et; 
		} else if (dR < 0.2){
			ring1_et += cluster.et; 
		} else if (dR < 0.3){
			ring2_et += cluster.et; 
		}
	}
	struct result {float f0; float f1; float f2;}; 
	return result {core_et, ring1_et, ring2_et}; 
}

// Nearby cluster counting
template <class Part> auto countNearbyClusters(Part center, vector<Cluster> clusters, float clusterEt_min=0){
	int core_nClusters = 0; // 0<dR<0.1
	int ring1_nClusters = 0; // 0.1<dR<0.2
	int ring2_nClusters = 0; // 0.2<dR<0.3
	// Uses only matched cluster to look through fewer clusters per tau
	for (Cluster cluster : clusters){
		if (cluster.et < clusterEt_min) continue; 
		float dR = getDR(center, cluster); 
		if (dR < 0.1){
			core_nClusters++; 
		} else if (dR < 0.2){
			ring1_nClusters++; 
		} else if (dR < 0.3){
			ring2_nClusters++; 
		}
	}
	struct result {int i0; int i1; int i2;}; 
	return result {core_nClusters, ring1_nClusters, ring2_nClusters}; 
}

// Get seed cluster, aka the highest et cluster within a dR
Cluster getSeedCluster(Tau& tau, float seedDR_max, float seedET_min=0){
	Cluster seedCluster; 
	for (Cluster cluster : tau.matchedClusters){
		if (cluster.et < seedET_min) continue; 
		if (cluster.matchedDR > seedDR_max) continue; 
		if (cluster.et < seedCluster.et) continue; 
		seedCluster = cluster; 
	}
	return seedCluster; 
}

// Tau trigger algorithm
// Class for all possible cuts and their defaults
class TriggerCuts {
	public: 
		float tauAbsEta_max; 
		float seedDR_max; 
		float seedET_min; 
		float et_min; 
		float absEta_max; 
		float iso_CA_min; 
		float iso_R1C_max; 
		float iso_R2C_max; 
		float iso_R2R1_max; 
	
	void setDefaults(){
		tauAbsEta_max = 999; 
		seedDR_max = 0.1; 
		seedET_min = 0; 
		et_min = 0; 
		absEta_max = 999; 
		iso_CA_min = 0; 
		iso_R1C_max = 999; 
		iso_R2C_max = 999; 
		iso_R2R1_max = 999; 
	}

	TriggerCuts(){
		setDefaults(); 
	}
}; 
bool tauTriggerAlg(Tau& tau, vector<Cluster> clusters, TriggerCuts triggerCuts){
	// Get variables
	tau.seedCluster = getSeedCluster(tau, triggerCuts.seedDR_max, triggerCuts.seedET_min); 
	auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(tau.seedCluster, clusters); 

	// Cuts
	if (abs(tau.eta) > triggerCuts.tauAbsEta_max) return false; 
	if (tau.seedCluster.et < triggerCuts.et_min) return false; 
	if (abs(tau.seedCluster.eta) > triggerCuts.absEta_max) return false; 
	if (core_et/(core_et + ring1_et + ring2_et + 1e-5) < triggerCuts.iso_CA_min) return false; 
	if (ring1_et/(core_et + 1e-5) > triggerCuts.iso_R1C_max) return false; 
	if (ring2_et/(core_et + 1e-5) > triggerCuts.iso_R2C_max) return false; 
	if ((triggerCuts.iso_R2R1_max!=999) && (ring2_et/(ring1_et + 1e-5) > triggerCuts.iso_R2R1_max)) return false; 
	return true; 
}

bool tauTriggerBaseline(Tau& tau, vector<Cluster> clusters){
	// Get variables
	tau.seedCluster = getSeedCluster(tau, 0.1, 0); 
	auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(tau.seedCluster, clusters); 
	float CA = core_et/(core_et + ring1_et + ring2_et + 1e-5); 
	// Cuts
	if ((tau.seedCluster.et > 2000) || (CA > 0.2)) return true; 
	return false; 
}
bool tauTriggerLoose(Tau& tau, vector<Cluster> clusters){
	// Get variables
	tau.seedCluster = getSeedCluster(tau, 0.1, 0); 
	auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(tau.seedCluster, clusters); 
	float CA = core_et/(core_et + ring1_et + ring2_et + 1e-5); 
	// Cuts
	if ((tau.seedCluster.et > 6e3) && (CA > 0.85)) return true; 
	return false; 
}
bool tauTriggerMedium(Tau& tau, vector<Cluster> clusters){
	// Get variables
	tau.seedCluster = getSeedCluster(tau, 0.1, 0); 
	auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(tau.seedCluster, clusters); 
	float CA = core_et/(core_et + ring1_et + ring2_et + 1e-5); 
	// Cuts
	if ((tau.seedCluster.et > 9e3) && (CA > 0.9)) return true; 
	return false; 
}
bool tauTriggerTight(Tau& tau, vector<Cluster> clusters){
	// Get variables
	tau.seedCluster = getSeedCluster(tau, 0.1, 0); 
	auto [core_et, ring1_et, ring2_et] = integrateNearbyEt(tau.seedCluster, clusters); 
	float CA = core_et/(core_et + ring1_et + ring2_et + 1e-5); 
	// Cuts
	if ((tau.seedCluster.et > 12e3) && (CA > 0.9)) return true; 
	return false; 
}
