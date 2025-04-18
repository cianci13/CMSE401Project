#include <map>
#include <stdexcept>
#include <sstream>

// The cpp standard map does not show the faulty key when map::at throws out_of_range, which is very very inconsiderate. This fixes that. 
template <typename K, typename V>
class DebugMap : public std::map<K, V> {
public:
    V& at(const K& key) {
        try {
            return std::map<K, V>::at(key);
        } catch (const std::out_of_range&) {
            std::ostringstream oss;
            oss << "Key not found in map: " << key;
            throw std::out_of_range(oss.str());
        }
    }

    const V& at(const K& key) const {
        try {
            return std::map<K, V>::at(key);
        } catch (const std::out_of_range&) {
            std::ostringstream oss;
            oss << "Key not found in map: " << key;
            throw std::out_of_range(oss.str());
        }
    }
};

bool printProgress = true; 

// Classes for physics objects and histogram handling
class Cluster {
	public:
		float et = -99; 
		float eta = -99; 
		float phi = -99; 
		float EngFracEM = -99; // EM Calo energy fraction
		float matchedDR = -99; // Keeping a record of the dR after matching

		void reset(){
			et = -99; 
			eta = -99; 
			phi = -99; 
			EngFracEM = -99; // EM Calo energy fraction
			matchedDR = -99; // Keeping a record of the dR after matching
		}
		 
		Cluster(){
		}
};

class Tau {
	public:
		float pt = -99; 
		float eta = -99; 
		float phi = -99; 
		float m = -99; 
		TLorentzVector p4 = {0, 0, 0, 0}; 

		std::vector<Cluster> matchedClusters = {}; // Vector for matched cluster to this tau
		Cluster seedCluster; // Cluster matched within a dR with highest et

		// Set 4 momentum using the stored attributes
		void set_p4(){
			p4.SetPtEtaPhiM(pt, eta, phi, m); 
		}

		// Select seed cluster for this tau from the matchedClusters vector
		void set_seedCluster(float dR){
			float top_et = -99; 
			for (Cluster cluster : matchedClusters){
				if (cluster.matchedDR > dR) continue; 
				if (cluster.et < top_et) continue; 
				top_et = cluster.et; 
				seedCluster = cluster; 
			}
		}

		// Function for equating two Tau, needed in reco to truth matching
		bool operator==(const Tau& other) const {
			if (pt != other.pt) return false; 
			if (eta != other.eta) return false; 
			if (phi != other.phi) return false; 
			if (m != other.m) return false; 
			return true; 
		}

		void reset(){
			pt = -99; 
			eta = -99; 
			phi = -99; 
			m = -99; 
			p4 = {0, 0, 0, 0}; 

			matchedClusters = {}; // Vector for matched cluster to this tau
			seedCluster.reset(); // Cluster matched within a dR with highest et
		}

		Tau(){
		}
};

class TruthTau : public Tau {
	public:
		float totalpt = -99; 
		float neutrinopt = -99; 
		float neutrinoeta = -99; 
		float neutrinophi = -99; 
		int nProng = -99; // Number of charged decay product
		int nChargedMeson = -99; // Pion and occasionally Kaon
		int nNeutralMeson = -99; // Pion and occasionally Kaon
		int isHadronic = 0; // Whether there is at least one charged meson in the decay
		int isLeptonicEle = 0; // Whether there is at least one electron in the decay

		TruthTau(){
			m = 1776; 
		}
};

class RecoTau : public Tau {
	public:
		bool matchedToTruth = 0; // Flag for whether this reco tau is matched to a truth tau
		int nTracksCharged = 0;
		int nTracksIsolation = 0;
		int nAllTracks = 0;

		TruthTau matchedTruthTau = TruthTau(); // Keep track of matched truth tau

		RecoTau(){
		}
};

// Classes for handling histogram's values, labels, binning, and TH1F creation
class Th1fHist{
	public: 
		string name; 
		string xlabel; 
		string ylabel; 
		vector<float> vars; // Variables to be filled into this hist
		float nbin; 
		float bin_min; 
		float bin_max; 
		TH1F* hist; 

		void plot_hist(){
			delete hist; 
			hist = new TH1F(name.c_str(), (name+";"+xlabel+";"+ylabel).c_str(), nbin, bin_min, bin_max); 
			for (float var : vars){
				hist->Fill(var); 
			}
			hist->SetMinimum(0); // Making sure the verticle axis starts at 0
		}

		void setParams(string _name, string _xlabel, string _ylabel, float _nbin, float _bin_min, float _bin_max){
			name = _name; 
			xlabel = _xlabel; 
			ylabel = _ylabel; 
			nbin = _nbin; 
			bin_min = _bin_min; 
			bin_max = _bin_max; 
		}

		Th1fHist(){
			name = "dummyName"; 
			xlabel = "dummyXLabel"; 
			ylabel = "dummyYLabel"; 
			vars = {}; 
			nbin = 99; 
			bin_min = -99; 
			bin_max = 99; 
			hist = 0; 
		}
}; 

class Th2fHist{
	public: 
		string name; 
		string xlabel; 
		string ylabel; 
		vector<float> xvars; // Variables to be filled into this hist
		vector<float> yvars; // Should have same dimensions
		float xnbin; 
		float xbin_min; 
		float xbin_max; 
		float ynbin; 
		float ybin_min; 
		float ybin_max; 
		TH2F* hist; 

		void plot_hist(){
			delete hist; 
			hist = new TH2F(name.c_str(), (name+";"+xlabel+";"+ylabel).c_str(), xnbin, xbin_min, xbin_max, ynbin, ybin_min, ybin_max); 
			for (int i=0; i < static_cast<int>(xvars.size()); i++){
				hist->Fill(xvars.at(i), yvars.at(i)); 
			}
		}

		void setParams(string _name, string _xlabel, string _ylabel, float _xnbin, float _xbin_min, float _xbin_max, float _ynbin, float _ybin_min, float _ybin_max){
			name = _name; 
			xlabel = _xlabel; 
			ylabel = _ylabel; 
			xnbin = _xnbin; 
			xbin_min = _xbin_min; 
			xbin_max = _xbin_max; 
			ynbin = _ynbin; 
			ybin_min = _ybin_min; 
			ybin_max = _ybin_max; 
		}

		Th2fHist(){
			name = "dummyName"; 
			xlabel = "dummyXLabel"; 
			ylabel = "dummyYLabel"; 
			xvars = {}; 
			yvars = {}; 
			xnbin = 99; 
			xbin_min = -99; 
			xbin_max = 99; 
			ynbin = 99; 
			ybin_min = -99; 
			ybin_max = 99; 
			hist = 0; 
		}
}; 

