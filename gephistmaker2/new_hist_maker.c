#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TLine.h>
#include <TGraph.h>
#include <TMultiGraph.h>

using namespace std; 

// Includes separate pieces of this script
#include "classes.h"
#include "read_ntuple.c"
#include "matching.c"
#include "RetrieveRecoEff.c"
#include "tauTriggerAlg.c"
#include "plot_hists.c"
#include "more_plots.c"

void new_hist_maker(){
	bool checkRuntime = true; 
	string tree_file_name, hist_file_name; 
	switch(1){
		case 0:
			tree_file_name = "/mnt/home/cianci13/CMSE401Project/gephistmaker/inputTree.root"; 
			hist_file_name = "/mnt/home/cianci13/CMSE401Project/gephistmaker/outputHistsMiniSerial.root"; 
			break;
		case 1:
			tree_file_name = "/mnt/home/cianci13/CMSE401Project/gephistmaker/inputTreeLarge.root";   
                        hist_file_name = "/mnt/home/cianci13/CMSE401Project/gephistmaker/outputHistsParallel.root";
			break; 
	}
	
	// Vectors of obj
	vector<vector<Cluster>> clusters; 
	vector<vector<TruthTau>> truthTaus; 
	vector<vector<RecoTau>> recoTaus; 

	// Read ntuple into vectors of obj
	auto checkpoint0 = chrono::high_resolution_clock::now(); // Checkpoint for run time check

	read_ntuple(tree_file_name, &clusters, &truthTaus, &recoTaus); 
	int nEvent = clusters.size(); 

	auto checkpoint1 = chrono::high_resolution_clock::now(); // Checkpoint for run time check

	// Do matchings such as cluster to truth tau, reco tau to truth tau, cluster to reco tau
	auto [matchedRecoTaus, unmatchedRecoTaus] = RetrieveRecoEff(&truthTaus, &recoTaus); 
	
	auto checkpoint2 = chrono::high_resolution_clock::now(); // Checkpoint for run time check

	matching(&clusters, &truthTaus, &recoTaus, &matchedRecoTaus, &unmatchedRecoTaus); 

	auto checkpoint3 = chrono::high_resolution_clock::now(); // Checkpoint for run time check

	// TFile to receive plots
	printf("\033[2m    Hist save destination: %s\n\033[0m", hist_file_name.c_str()); 
	TFile *hist_file = new TFile(hist_file_name.c_str(), "recreate", "Output of hist maker"); 

	// Plot simple TH1 and TH2, returning a map of TH1 for further use
	auto [th1fHists, th2fHists] = plot_hists(&clusters, &truthTaus, &recoTaus, &matchedRecoTaus, &unmatchedRecoTaus); 

	auto checkpoint4 = chrono::high_resolution_clock::now(); // Checkpoint for run time check

	// Plot more plots such as efficency and overlay from the simple TH1
	more_plots(th1fHists, th2fHists, nEvent); 

	auto checkpoint5 = chrono::high_resolution_clock::now(); // Checkpoint for run time check

	// Write and close the TFile
	hist_file->Write(); 
	hist_file->Close(); 

	float duration_read_ntuple = chrono::duration_cast<chrono::microseconds>(checkpoint1 - checkpoint0).count(); 
	if (checkRuntime) printf("DEBUG: Runtime for read_ntuple: %.2f min\n", duration_read_ntuple*1e-6/60); 
	float duration_RetrieveRecoEff = chrono::duration_cast<chrono::microseconds>(checkpoint2 - checkpoint1).count(); 
	if (checkRuntime) printf("DEBUG: Runtime for RetrieveRecoEff: %.2f min\n", duration_RetrieveRecoEff*1e-6/60); 
	float duration_matching = chrono::duration_cast<chrono::microseconds>(checkpoint3 - checkpoint2).count(); 
	if (checkRuntime) printf("DEBUG: Runtime for matching: %.2f min\n", duration_matching*1e-6/60); 
	float duration_plot_hists = chrono::duration_cast<chrono::microseconds>(checkpoint4 - checkpoint3).count(); 
	if (checkRuntime) printf("DEBUG: Runtime for plot_hists: %.2f min\n", duration_plot_hists*1e-6/60); 
	float duration_more_plots = chrono::duration_cast<chrono::microseconds>(checkpoint5 - checkpoint4).count(); 
	if (checkRuntime) printf("DEBUG: Runtime for more_plots: %.2f min\n", duration_more_plots*1e-6/60); 
}
