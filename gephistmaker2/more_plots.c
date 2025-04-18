// Secondary plots using the existing TH1F, such as overlay and efficiency

// Plot efficiency
void plot_efficiency(string hName, string numeratorHandle, string denominatorHandle, string xlabel, string ylabel, int nbin, float bin_min, float bin_max, DebugMap<string, Th1fHist> th1fHists, DebugMap<string, TH1F*>& effiHists){
	if (printProgress) printf("\033[2m    %s\n\033[0m", hName.c_str()); 
	TH1F* h_efficiency = new TH1F(hName.c_str(), (hName+";"+xlabel+";"+ylabel).c_str(), nbin, bin_min, bin_max); 
	h_efficiency->Divide(th1fHists.at(numeratorHandle).hist, th1fHists.at(denominatorHandle).hist); 
	effiHists[hName] = h_efficiency; 
}
void plot_rejection(string hName, string numeratorHandle, string denominatorHandle, string xlabel, string ylabel, int nbin, float bin_min, float bin_max, DebugMap<string, TH1*> hists, DebugMap<string, TH1F*>& effiHists){
	if (printProgress) printf("\033[2m    %s\n\033[0m", hName.c_str()); 
	TH1F* h_efficiency = new TH1F(hName.c_str(), (hName+";"+xlabel+";"+ylabel).c_str(), nbin, bin_min, bin_max); 
	h_efficiency->Divide(hists.at(numeratorHandle), hists.at(denominatorHandle)); 
	
	for (int i=0; i < h_efficiency->GetNbinsX()+2; i++){
		h_efficiency->SetBinContent(i, 1 - h_efficiency->GetBinContent(i)); 
	}
	effiHists[hName] = h_efficiency; 
}

// Plot cumulative
void plot_cumulative(TH1F* sourceHist, bool forward, string suffix, float factor, string ylabel, DebugMap<string, TH1*>& rateHists, bool normalize = false){
	TH1* sourceHistClone = (TH1*) sourceHist->Clone(); 
	sourceHistClone->SetDirectory(nullptr); 
	sourceHistClone->SetStats(0); 
	if (normalize) sourceHistClone->Scale(1/(sourceHistClone->Integral()+1e-5)); 
	TH1* hc = sourceHistClone->GetCumulative(forward, suffix.c_str()); 
	hc->Scale(factor); 
	string name = sourceHistClone->GetTitle() + suffix; 
	hc->SetTitle(name.c_str()); 
	hc->GetYaxis()->SetTitle(ylabel.c_str()); 
	rateHists[name] = hc; 
	if (printProgress) printf("\033[2m    %s\n\033[0m", name.c_str()); 
}

// Plot ROC given sig and bkg normalized rate
void plot_ROC(string name, string xHandle, string yHandle, string xlabel, string ylabel, DebugMap<string, TH1*> rateHists, DebugMap<string, TGraph*>& ROCplots){
	if (printProgress) printf("\033[2m    %s\n\033[0m", name.c_str()); 
	TH1* xHist = (TH1*) rateHists.at(xHandle.c_str())->Clone(); 
	xHist->SetDirectory(nullptr); 
	xHist->SetStats(0); 
	TH1* yHist = (TH1*) rateHists.at(yHandle.c_str())->Clone(); 
	yHist->SetDirectory(nullptr); 
	yHist->SetStats(0); 

	int xNbins = xHist->GetNbinsX(); 
	int yNbins = yHist->GetNbinsX(); 
	if (xNbins != yNbins) throw runtime_error("plot_ROC(): Different number of bins plotting " + name); 

	float xs[xNbins+2], ys[xNbins+2]; 

	for (int i=0; i < xNbins+2; i++){
		xs[i] = xHist->GetBinContent(i); 
		ys[i] = 1-yHist->GetBinContent(i); 
	}

	TGraph* ROC = new TGraph(xNbins, xs, ys); 
	ROC->SetTitle(name.c_str()); 
	ROC->GetXaxis()->SetTitle(xlabel.c_str()); 
	ROC->GetYaxis()->SetTitle(ylabel.c_str()); 
	ROC->SetLineStyle(0); 
	ROC->SetMarkerStyle(1); 
	ROC->Write(name.c_str()); 
	ROCplots[name] = ROC; 
}

// Overlay plots
template <typename Th1Type> void overlay_plots(string name, string drawOption, bool yLog, vector<string> histnames, vector<string> labels, DebugMap<string, Th1Type*> histmap, string xlabel="", vector<int> customLineColor={}, vector<int> customLineStyle={}){
	if (printProgress) printf("\033[2m    %s\n\033[0m", name.c_str()); 
	if (histnames.size() != labels.size()) throw runtime_error("overlay_plots(): Sizes of hists and labels are different plotting " + name); 
	TCanvas* canvas = new TCanvas(name.c_str(), name.c_str(), 800, 600); 

	// Get the highestBinHeight
	float highestBinHeight = 0; 
	for (string histname : histnames){
		Th1Type* hist = (Th1Type*) histmap.at(histname.c_str())->Clone(); 
		hist->SetDirectory(nullptr); 
		hist->SetStats(0); 
		// Normalize when the name says norm
		if (name.find("_norm") != std::string::npos) hist->Scale(1/(hist->Integral()+1e-5));
		if (hist->GetMaximum() > highestBinHeight) highestBinHeight = hist->GetMaximum(); 
	}

	// Overlay
	auto legend = new TLegend(0.7, 0.7, 0.9, 0.9); 
	vector<int> colors = {1, 2, 3, 4, 6, 7, 9, 28}; 
	float xMin = 0; 
	float xMax = 0; 
	for (int i = 0; i < static_cast<int>(histnames.size()); i++){
		Th1Type* hist = (Th1Type*) histmap.at(histnames[i].c_str())->Clone(); 
		hist->SetDirectory(nullptr); 
		hist->SetStats(0); 
		if (name.find("_norm") != std::string::npos) hist->Scale(1/(hist->Integral()+1e-5));
		(customLineColor.size()==0) ? hist->SetLineColor(colors[i]) : hist->SetLineColor(customLineColor[i]); 
		(customLineStyle.size()==0) ? hist->SetLineStyle(1) : hist->SetLineStyle(customLineStyle[i]); 
		hist->SetLineWidth(2); 
		if (i==0) {
			xMin = hist->GetXaxis()->GetXmin();
			xMax = hist->GetXaxis()->GetXmax();
			if (xlabel != "") hist->GetXaxis()->SetTitle(xlabel.c_str()); 
			hist->SetMaximum(1.1 * highestBinHeight); 
			(yLog) ? hist->SetMinimum(.01) : hist->SetMinimum(0); 
			hist->SetTitle(name.c_str()); 
		}
		hist->Draw((drawOption + " SAME").c_str()); 
		legend->AddEntry(hist, labels[i].c_str(), "l"); 
	}
	if (yLog) canvas->SetLogy(); 

	// kHz line for rate plots
	if (name.find("h_eventTriggered_") != std::string::npos) {
		TLine* line = new TLine(xMin, 3, xMax, 3); 
		line->SetLineWidth(2); 
		line->SetLineColor(kGreen); 
		line->SetLineStyle(9);
		line->Draw("SAME");  
	} else if ((name.find("_diTauTrig_") != std::string::npos)&&(name.find("_rate") != std::string::npos)) {
		TLine* line = new TLine(xMin, 200, xMax, 200); 
		line->SetLineWidth(2); 
		line->SetLineColor(kGreen); 
		line->SetLineStyle(9);
		line->Draw("SAME");  
	}

	legend->Draw(); 
	canvas->Update(); 
	canvas->Write(); 
}

void overlay_graphs(string name, string drawOption, bool yLog, vector<string> graphnames, vector<string> labels, DebugMap<string, TGraph*> graphmap, vector<int> customMarkerColor={}, vector<int> customMarkerStyle={}){
	if (printProgress) printf("\033[2m    %s\n\033[0m", name.c_str()); 
	if (graphnames.size() != labels.size()) throw runtime_error("overlay_plots(): Sizes of graphs and labels are different plotting " + name); 
	
	TCanvas* canvas = new TCanvas(name.c_str(), name.c_str(), 800, 600); 
	TMultiGraph* mg = new TMultiGraph(); 
	auto legend = new TLegend(0.7, 0.7, 0.9, 0.9); 

	// Overlay
	vector<int> colors = {1, 2, 3, 4, 6, 7, 9, 28}; 
	for (int i = 0; i < static_cast<int>(graphnames.size()); i++){
		TGraph* graph = (TGraph*) graphmap.at(graphnames[i].c_str())->Clone(); 
		(customMarkerColor.size()==0) ? graph->SetMarkerColor(colors[i]) : graph->SetMarkerColor(customMarkerColor[i]); 
		(customMarkerStyle.size()==0) ? graph->SetMarkerStyle(47) : graph->SetMarkerStyle(customMarkerStyle[i]); 
		graph->SetMarkerSize(1); 
		graph->SetTitle(name.c_str()); 
		(i==0) ? graph->Draw((drawOption+"A").c_str()) : graph->Draw(drawOption.c_str()); 
		legend->AddEntry(graph, labels[i].c_str(), "p"); 
	}

	mg->Draw(drawOption.c_str()); 
	//canvas->BuildLegend(); 
	legend->Draw(); 
	canvas->Update(); 
	canvas->Write(); 
}

void scanPhaseSpace(string sigName, string bkgName, string sigEffiName, string bkgEffiName, string sigPurityName, bool xForward, bool yForward, DebugMap<string, Th2fHist> th2fHists){
	if (printProgress) printf("\033[2m    %s\n    %s\n    %s\n\033[0m", sigEffiName.c_str(), bkgEffiName.c_str(), sigPurityName.c_str()); 
	Th2fHist sigTh2fHist = th2fHists.at(sigName.c_str()); 
	TH2F* sigHist = (TH2F*) sigTh2fHist.hist->Clone(); 
	sigHist->SetDirectory(nullptr); 
	sigHist->SetStats(0); 
	Th2fHist bkgTh2fHist = th2fHists.at(bkgName.c_str()); 
	TH2F* bkgHist = (TH2F*) bkgTh2fHist.hist->Clone(); 
	bkgHist->SetDirectory(nullptr); 
	bkgHist->SetStats(0); 

	//float sigXStep = (sigTh2fHist.xbin_max - sigTh2fHist.xbin_min)/sigTh2fHist.xnbin; 
	//float sigYStep = (sigTh2fHist.ybin_max - sigTh2fHist.ybin_min)/sigTh2fHist.ynbin; 
	float sigSF = 1/sigHist->Integral(0, sigTh2fHist.xnbin+1, 0, sigTh2fHist.ynbin+1); 
	//float bkgXStep = (bkgTh2fHist.xbin_max - bkgTh2fHist.xbin_min)/bkgTh2fHist.xnbin; 
	//float bkgYStep = (bkgTh2fHist.ybin_max - bkgTh2fHist.ybin_min)/bkgTh2fHist.ynbin; 
	float bkgSF = 1/bkgHist->Integral(0, bkgTh2fHist.xnbin+1, 0, bkgTh2fHist.ynbin+1); 

	TH2F* sigEffiScan = new TH2F(sigEffiName.c_str(), (sigEffiName+";"+sigTh2fHist.xlabel+";"+sigTh2fHist.ylabel).c_str(), sigTh2fHist.xnbin, sigTh2fHist.xbin_min, sigTh2fHist.xbin_max, sigTh2fHist.ynbin, sigTh2fHist.ybin_min, sigTh2fHist.ybin_max); 
	TH2F* bkgEffiScan = new TH2F(bkgEffiName.c_str(), (bkgEffiName+";"+bkgTh2fHist.xlabel+";"+bkgTh2fHist.ylabel).c_str(), bkgTh2fHist.xnbin, bkgTh2fHist.xbin_min, bkgTh2fHist.xbin_max, bkgTh2fHist.ynbin, bkgTh2fHist.ybin_min, bkgTh2fHist.ybin_max); 
	TH2F* sigPurityScan = new TH2F(sigPurityName.c_str(), (sigPurityName+";"+sigTh2fHist.xlabel+";"+sigTh2fHist.ylabel).c_str(), sigTh2fHist.xnbin, sigTh2fHist.xbin_min, sigTh2fHist.xbin_max, sigTh2fHist.ynbin, sigTh2fHist.ybin_min, sigTh2fHist.ybin_max); 

	int imax = sigTh2fHist.xnbin+1; 
	int jmax = sigTh2fHist.ynbin+1; 
	for (int i=0; i<=imax; i++){
		for (int j=0; j<=jmax; j++){
			float sigIntegral = sigHist->Integral(
					xForward ? 0 : i, 
					xForward ? i : imax, 
					yForward ? 0 : j, 
					yForward ? j : jmax 
					);
			float bkgIntegral = bkgHist->Integral(
					xForward ? 0 : i, 
					xForward ? i : imax, 
					yForward ? 0 : j, 
					yForward ? j : jmax 
					);
			float sigEffi = sigIntegral*sigSF; 
			float bkgEffi = bkgIntegral*bkgSF; 
			sigEffiScan->SetBinContent(i, j, sigEffi); 
			bkgEffiScan->SetBinContent(i, j, bkgEffi); 
			sigPurityScan->SetBinContent(i, j, sigEffi/(sigEffi+bkgEffi)); 
		}
	}
}

// Main loop more plots
void more_plots(DebugMap<string, Th1fHist> th1fHists, DebugMap<string, Th2fHist> th2fHists, int nEvent){

	// Convert map of th1fHists
	DebugMap<string, TH1F*> th1fHists_onlyTH1F; 
	for (auto const& it : th1fHists) {
		th1fHists_onlyTH1F[it.first] = it.second.hist; 
	}
	
	// Disable TCanvas displaying
	gROOT->SetBatch(true); 
	
	if (printProgress) printf("Plotting secondary plots: \n");  
	// Store plots for later overlap
	DebugMap<string, TH1F*> effiHists = {}; 
	DebugMap<string, TH1*> rateHists = {}; 
	DebugMap<string, TGraph*> ROCplots = {}; 

	// Rates
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_lowestPt_noCut").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_lowestPt_seedEt2GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_lowestPt_seedEt5GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_lowestPt_seedEt8GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_noCut").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt2GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt5GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt8GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt15GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt20GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_seedEt25GeV").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_CA0p2").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_CA0p5").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_CA0p8").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_R1C0p2").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_R1C0p5").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_R1C0p8").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_R2C0p2").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_R2C0p5").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_eventTriggered_recoTau_highestPt_R2C0p8").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 

	// Normalized rate for cut variables
	plot_cumulative(th1fHists.at("h_matchedRecoTau_seedET").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_unmatchedRecoTau_seedET").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_matchedRecoTauIsolation_seedEtCore").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_unmatchedRecoTauIsolation_seedEtCore").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_matchedRecoTauIsolation_seedEtAll").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_unmatchedRecoTauIsolation_seedEtAll").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_matchedRecoTauIsolation_CA").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_unmatchedRecoTauIsolation_CA").hist, false, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_matchedRecoTauIsolation_R1C").hist, true, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_unmatchedRecoTauIsolation_R1C").hist, true, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_matchedRecoTauIsolation_R2C").hist, true, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_unmatchedRecoTauIsolation_R2C").hist, true, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_matchedRecoTauIsolation_R2R1").hist, true, "_normRate", 1, "Normalized Rate", rateHists, true); 
	plot_cumulative(th1fHists.at("h_unmatchedRecoTauIsolation_R2R1").hist, true, "_normRate", 1, "Normalized Rate", rateHists, true); 

	// ROC plots
	plot_ROC("h_ROC_seedET", "h_matchedRecoTau_seedET_normRate", "h_unmatchedRecoTau_seedET_normRate", "matchedRecoTau", "unmatchedRecoTau", rateHists, ROCplots); 
	plot_ROC("h_ROC_seedEtCore", "h_matchedRecoTauIsolation_seedEtCore_normRate", "h_unmatchedRecoTauIsolation_seedEtCore_normRate", "matchedRecoTau", "unmatchedRecoTau", rateHists, ROCplots); 
	plot_ROC("h_ROC_seedEtAll", "h_matchedRecoTauIsolation_seedEtAll_normRate", "h_unmatchedRecoTauIsolation_seedEtAll_normRate", "matchedRecoTau", "unmatchedRecoTau", rateHists, ROCplots); 
	plot_ROC("h_ROC_CA", "h_matchedRecoTauIsolation_CA_normRate", "h_unmatchedRecoTauIsolation_CA_normRate", "matchedRecoTau", "unmatchedRecoTau", rateHists, ROCplots); 
	plot_ROC("h_ROC_R1C", "h_matchedRecoTauIsolation_R1C_normRate", "h_unmatchedRecoTauIsolation_R1C_normRate", "matchedRecoTau", "unmatchedRecoTau", rateHists, ROCplots); 
	plot_ROC("h_ROC_R2C", "h_matchedRecoTauIsolation_R2C_normRate", "h_unmatchedRecoTauIsolation_R2C_normRate", "matchedRecoTau", "unmatchedRecoTau", rateHists, ROCplots); 
	plot_ROC("h_ROC_R2R1", "h_matchedRecoTauIsolation_R2R1_normRate", "h_unmatchedRecoTauIsolation_R2R1_normRate", "matchedRecoTau", "unmatchedRecoTau", rateHists, ROCplots); 

	// Phase space scan
	//scanPhaseSpace("h_matchedRecoTau_seedET_CA", "h_unmatchedRecoTau_seedET_CA", "h_scanSigEffi_seedET_CA", "h_scanBkgEffi_seedET_CA", "h_scanSigPurity_seedET_CA", false, false, th2fHists); 
	
	// Truth tau trigger effi
	// Null trigger
	plot_efficiency("h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggered_noCut_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV seedEt
	plot_efficiency("h_truthTau_triggerEfficiency_seedEt2GeV_pt", "h_truthTau_triggered_seedEt2GeV_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV seedEt
	plot_efficiency("h_truthTau_triggerEfficiency_seedEt5GeV_pt", "h_truthTau_triggered_seedEt5GeV_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 8 GeV seedEt
	plot_efficiency("h_truthTau_triggerEfficiency_seedEt8GeV_pt", "h_truthTau_triggered_seedEt8GeV_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV et
	plot_efficiency("h_truthTau_triggerEfficiency_et2GeV_pt", "h_truthTau_triggered_et2GeV_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3 GeV et
	plot_efficiency("h_truthTau_triggerEfficiency_et3GeV_pt", "h_truthTau_triggered_et3GeV_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV et
	plot_efficiency("h_truthTau_triggerEfficiency_et5GeV_pt", "h_truthTau_triggered_et5GeV_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.2 CA
	plot_efficiency("h_truthTau_triggerEfficiency_CA0p2_pt", "h_truthTau_triggered_CA0p2_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 CA
	plot_efficiency("h_truthTau_triggerEfficiency_CA0p5_pt", "h_truthTau_triggered_CA0p5_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 CA
	plot_efficiency("h_truthTau_triggerEfficiency_CA0p8_pt", "h_truthTau_triggered_CA0p8_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.2 R1C
	plot_efficiency("h_truthTau_triggerEfficiency_R1C0p2_pt", "h_truthTau_triggered_R1C0p2_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R1C
	plot_efficiency("h_truthTau_triggerEfficiency_R1C0p5_pt", "h_truthTau_triggered_R1C0p5_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R1C
	plot_efficiency("h_truthTau_triggerEfficiency_R1C0p8_pt", "h_truthTau_triggered_R1C0p8_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.2 R2C
	plot_efficiency("h_truthTau_triggerEfficiency_R2C0p2_pt", "h_truthTau_triggered_R2C0p2_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R2C
	plot_efficiency("h_truthTau_triggerEfficiency_R2C0p5_pt", "h_truthTau_triggered_R2C0p5_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R2C
	plot_efficiency("h_truthTau_triggerEfficiency_R2C0p8_pt", "h_truthTau_triggered_R2C0p8_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R2R1
	plot_efficiency("h_truthTau_triggerEfficiency_R2R10p5_pt", "h_truthTau_triggered_R2R10p5_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 1.5 R2R1
	plot_efficiency("h_truthTau_triggerEfficiency_R2R11p5_pt", "h_truthTau_triggered_R2R11p5_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3.5 R2R1
	plot_efficiency("h_truthTau_triggerEfficiency_R2R19p5_pt", "h_truthTau_triggered_R2R19p5_pt", "h_truthTau_pt", "truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// Truth-matched reco tau trigger effi
	// Null trigger
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_noCut_pt", "h_matchedRecoTau_triggered_noCut_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV seedEt
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_seedEt2GeV_pt", "h_matchedRecoTau_triggered_seedEt2GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV seedEt
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_seedEt5GeV_pt", "h_matchedRecoTau_triggered_seedEt5GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 8 GeV seedEt
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_seedEt8GeV_pt", "h_matchedRecoTau_triggered_seedEt8GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 15 GeV seedEt
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_seedEt15GeV_pt", "h_matchedRecoTau_triggered_seedEt15GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 20 GeV seedEt
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_seedEt20GeV_pt", "h_matchedRecoTau_triggered_seedEt20GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 25 GeV seedEt
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_seedEt25GeV_pt", "h_matchedRecoTau_triggered_seedEt25GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV et
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_et2GeV_pt", "h_matchedRecoTau_triggered_et2GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3 GeV et
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_et3GeV_pt", "h_matchedRecoTau_triggered_et3GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV et
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_et5GeV_pt", "h_matchedRecoTau_triggered_et5GeV_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.2 CA
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_CA0p2_pt", "h_matchedRecoTau_triggered_CA0p2_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 CA
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_CA0p5_pt", "h_matchedRecoTau_triggered_CA0p5_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 CA
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_CA0p8_pt", "h_matchedRecoTau_triggered_CA0p8_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.2 R1C
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R1C0p2_pt", "h_matchedRecoTau_triggered_R1C0p2_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R1C
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R1C0p5_pt", "h_matchedRecoTau_triggered_R1C0p5_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R1C
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R1C0p8_pt", "h_matchedRecoTau_triggered_R1C0p8_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.2 R2C
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R2C0p2_pt", "h_matchedRecoTau_triggered_R2C0p2_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R2C
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R2C0p5_pt", "h_matchedRecoTau_triggered_R2C0p5_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R2C
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R2C0p8_pt", "h_matchedRecoTau_triggered_R2C0p8_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.5 R2R1
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R2R10p5_pt", "h_matchedRecoTau_triggered_R2R10p5_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 1.5 R2R1
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R2R11p5_pt", "h_matchedRecoTau_triggered_R2R11p5_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3.5 R2R1
	plot_efficiency("h_matchedRecoTau_triggerEfficiency_R2R19p5_pt", "h_matchedRecoTau_triggered_R2R19p5_pt", "h_matchedRecoTau_pt", "truth-matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// Reco-matched truth tau trigger effi
	// Null trigger
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggered_noCut_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV seedEt
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_seedEt2GeV_pt", "h_truthMatched2RecoTau_triggered_seedEt2GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV seedEt
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_seedEt5GeV_pt", "h_truthMatched2RecoTau_triggered_seedEt5GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 8 GeV seedEt
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_seedEt8GeV_pt", "h_truthMatched2RecoTau_triggered_seedEt8GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 15 GeV seedEt
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_seedEt15GeV_pt", "h_truthMatched2RecoTau_triggered_seedEt15GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 20 GeV seedEt
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_seedEt20GeV_pt", "h_truthMatched2RecoTau_triggered_seedEt20GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 25 GeV seedEt
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_seedEt25GeV_pt", "h_truthMatched2RecoTau_triggered_seedEt25GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV et
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_et2GeV_pt", "h_truthMatched2RecoTau_triggered_et2GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3 GeV et
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_et3GeV_pt", "h_truthMatched2RecoTau_triggered_et3GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV et
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_et5GeV_pt", "h_truthMatched2RecoTau_triggered_et5GeV_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.2 CA
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_CA0p2_pt", "h_truthMatched2RecoTau_triggered_CA0p2_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 CA
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_CA0p5_pt", "h_truthMatched2RecoTau_triggered_CA0p5_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 CA
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_CA0p8_pt", "h_truthMatched2RecoTau_triggered_CA0p8_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.2 R1C
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R1C0p2_pt", "h_truthMatched2RecoTau_triggered_R1C0p2_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R1C
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R1C0p5_pt", "h_truthMatched2RecoTau_triggered_R1C0p5_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R1C
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R1C0p8_pt", "h_truthMatched2RecoTau_triggered_R1C0p8_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.2 R2C
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R2C0p2_pt", "h_truthMatched2RecoTau_triggered_R2C0p2_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R2C
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R2C0p5_pt", "h_truthMatched2RecoTau_triggered_R2C0p5_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R2C
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R2C0p8_pt", "h_truthMatched2RecoTau_triggered_R2C0p8_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.5 R2R1
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R2R10p5_pt", "h_truthMatched2RecoTau_triggered_R2R10p5_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 1.5 R2R1
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R2R11p5_pt", "h_truthMatched2RecoTau_triggered_R2R11p5_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3.5 R2R1
	plot_efficiency("h_truthMatched2RecoTau_triggerEfficiency_R2R19p5_pt", "h_truthMatched2RecoTau_triggered_R2R19p5_pt", "h_truthMatched2RecoTau_pt", "reco-matched truth tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// Truth-unmatched reco tau trigger effi
	// Null trigger
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggered_noCut_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV seedEt
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_seedEt2GeV_pt", "h_unmatchedRecoTau_triggered_seedEt2GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV seedEt
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_seedEt5GeV_pt", "h_unmatchedRecoTau_triggered_seedEt5GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 8 GeV seedEt
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_seedEt8GeV_pt", "h_unmatchedRecoTau_triggered_seedEt8GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 15 GeV seedEt
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_seedEt15GeV_pt", "h_unmatchedRecoTau_triggered_seedEt15GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 20 GeV seedEt
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_seedEt20GeV_pt", "h_unmatchedRecoTau_triggered_seedEt20GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 25 GeV seedEt
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_seedEt25GeV_pt", "h_unmatchedRecoTau_triggered_seedEt25GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 2 GeV et
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_et2GeV_pt", "h_unmatchedRecoTau_triggered_et2GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3 GeV et
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_et3GeV_pt", "h_unmatchedRecoTau_triggered_et3GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 5 GeV et
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_et5GeV_pt", "h_unmatchedRecoTau_triggered_et5GeV_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.2 CA
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_CA0p2_pt", "h_unmatchedRecoTau_triggered_CA0p2_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 CA
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_CA0p5_pt", "h_unmatchedRecoTau_triggered_CA0p5_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 CA
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_CA0p8_pt", "h_unmatchedRecoTau_triggered_CA0p8_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.2 R1C
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R1C0p2_pt", "h_unmatchedRecoTau_triggered_R1C0p2_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R1C
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R1C0p5_pt", "h_unmatchedRecoTau_triggered_R1C0p5_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R1C
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R1C0p8_pt", "h_unmatchedRecoTau_triggered_R1C0p8_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.2 R2C
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R2C0p2_pt", "h_unmatchedRecoTau_triggered_R2C0p2_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.5 R2C
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R2C0p5_pt", "h_unmatchedRecoTau_triggered_R2C0p5_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 0.8 R2C
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R2C0p8_pt", "h_unmatchedRecoTau_triggered_R2C0p8_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// 0.5 R2R1
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R2R10p5_pt", "h_unmatchedRecoTau_triggered_R2R10p5_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 1.5 R2R1
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R2R11p5_pt", "h_unmatchedRecoTau_triggered_R2R11p5_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	
	// 3.5 R2R1
	plot_efficiency("h_unmatchedRecoTau_triggerEfficiency_R2R19p5_pt", "h_unmatchedRecoTau_triggered_R2R19p5_pt", "h_unmatchedRecoTau_pt", "truth-unmatched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 

	// Overlay effi
	// Cut var spectra
	overlay_plots("h_seedET_norm", "HIST", false, {"h_matchedRecoTau_seedET", "h_unmatchedRecoTau_seedET"}, {"matched reco tau", "unmatched reco tau"}, th1fHists_onlyTH1F); 
	overlay_plots("h_isolation_CA_norm", "HIST", false, {"h_matchedRecoTauIsolation_CA", "h_unmatchedRecoTauIsolation_CA"}, {"matched reco tau", "unmatched reco tau"}, th1fHists_onlyTH1F); 
	overlay_plots("h_isolation_R1C_norm", "HIST", false, {"h_matchedRecoTauIsolation_R1C", "h_unmatchedRecoTauIsolation_R1C"}, {"matched reco tau", "unmatched reco tau"}, th1fHists_onlyTH1F); 
	overlay_plots("h_isolation_R2C_norm", "HIST", false, {"h_matchedRecoTauIsolation_R2C", "h_unmatchedRecoTauIsolation_R2C"}, {"matched reco tau", "unmatched reco tau"}, th1fHists_onlyTH1F); 
	overlay_plots("h_isolation_R2R1_norm", "HIST", false, {"h_matchedRecoTauIsolation_R2R1", "h_unmatchedRecoTauIsolation_R2R1"}, {"matched reco tau", "unmatched reco tau"}, th1fHists_onlyTH1F); 
	overlay_plots("h_matchedRecoTauIsolation_nNearbyClusters", "HIST", false, {"h_matchedRecoTauIsolation_nCoreClusters", "h_matchedRecoTauIsolation_nRing1Clusters", "h_matchedRecoTauIsolation_nRing2Clusters"}, {"nCoreClusters", "nRing1Clusters", "nRing2Clusters"}, th1fHists_onlyTH1F, "matched reco tau nNearbyClusters"); 
	overlay_plots("h_unmatchedRecoTauIsolation_nNearbyClusters", "HIST", false, {"h_unmatchedRecoTauIsolation_nCoreClusters", "h_unmatchedRecoTauIsolation_nRing1Clusters", "h_unmatchedRecoTauIsolation_nRing2Clusters"}, {"nCoreClusters", "nRing1Clusters", "nRing2Clusters"}, th1fHists_onlyTH1F, "unmatched reco tau nNearbyClusters"); 

	// Overlay ROC plots
	overlay_graphs("h_ROC_cutVars", "P", false, {"h_ROC_seedET", "h_ROC_CA", "h_ROC_R1C", "h_ROC_R2C", "h_ROC_R2R1", "h_ROC_seedEtCore", "h_ROC_seedEtAll"}, {"seedET", "CA", "R1C", "R2C", "R2R1", "seedEtCore", "seedEtAll"}, ROCplots); 

	// Rates
	overlay_plots("h_eventTriggered_recoTau_lowestPt_seedEtXGeV", "PL", true, {"h_eventTriggered_recoTau_lowestPt_noCut_rate", "h_eventTriggered_recoTau_lowestPt_seedEt2GeV_rate", "h_eventTriggered_recoTau_lowestPt_seedEt5GeV_rate", "h_eventTriggered_recoTau_lowestPt_seedEt8GeV_rate"}, {"noCut", "et2GeV", "et5GeV", "et8GeV"}, rateHists); 
	overlay_plots("h_eventTriggered_recoTau_highestPt_seedEtXGeV", "PL", true, {"h_eventTriggered_recoTau_highestPt_noCut_rate", "h_eventTriggered_recoTau_highestPt_seedEt2GeV_rate", "h_eventTriggered_recoTau_highestPt_seedEt5GeV_rate", "h_eventTriggered_recoTau_highestPt_seedEt8GeV_rate", "h_eventTriggered_recoTau_highestPt_seedEt15GeV_rate", "h_eventTriggered_recoTau_highestPt_seedEt20GeV_rate", "h_eventTriggered_recoTau_highestPt_seedEt25GeV_rate"}, {"noCut", "et2GeV", "et5GeV", "et8GeV", "et15GeV", "et20GeV", "et25GeV"}, rateHists); 
	overlay_plots("h_eventTriggered_recoTau_highestPt_CAX", "PL", true, {"h_eventTriggered_recoTau_highestPt_noCut_rate", "h_eventTriggered_recoTau_highestPt_CA0p2_rate", "h_eventTriggered_recoTau_highestPt_CA0p5_rate", "h_eventTriggered_recoTau_highestPt_CA0p8_rate"}, {"noCut", "CA0p2", "CA0p5", "CA0p8"}, rateHists); 
	overlay_plots("h_eventTriggered_recoTau_highestPt_R1CX", "PL", true, {"h_eventTriggered_recoTau_highestPt_noCut_rate", "h_eventTriggered_recoTau_highestPt_R1C0p2_rate", "h_eventTriggered_recoTau_highestPt_R1C0p5_rate", "h_eventTriggered_recoTau_highestPt_R1C0p8_rate"}, {"noCut", "R1C0p2", "R1C0p5", "R1C0p8"}, rateHists); 
	overlay_plots("h_eventTriggered_recoTau_highestPt_R2CX", "PL", true, {"h_eventTriggered_recoTau_highestPt_noCut_rate", "h_eventTriggered_recoTau_highestPt_R2C0p2_rate", "h_eventTriggered_recoTau_highestPt_R2C0p5_rate", "h_eventTriggered_recoTau_highestPt_R2C0p8_rate"}, {"noCut", "R2C0p2", "R2C0p5", "R2C0p8"}, rateHists); 

	// Truth Tau
	overlay_plots("h_truthTau_triggerEfficiency_seedEtXGeV_pt", "PL", false, {"h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_seedEt2GeV_pt", "h_truthTau_triggerEfficiency_seedEt5GeV_pt", "h_truthTau_triggerEfficiency_seedEt8GeV_pt"}, {"noCut", "et2GeV", "et5GeV", "et8GeV"}, effiHists); 
	overlay_plots("h_truthTau_triggerEfficiency_etXGeV_pt", "PL", false, {"h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_et2GeV_pt", "h_truthTau_triggerEfficiency_et3GeV_pt", "h_truthTau_triggerEfficiency_et5GeV_pt"}, {"noCut", "et2GeV", "et3GeV", "et5GeV"}, effiHists); 
	overlay_plots("h_truthTau_triggerEfficiency_CAX_pt", "PL", false, {"h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_CA0p2_pt", "h_truthTau_triggerEfficiency_CA0p5_pt", "h_truthTau_triggerEfficiency_CA0p8_pt"}, {"noCut", "CA0p2", "CA0p5", "CA0p8"}, effiHists); 
	overlay_plots("h_truthTau_triggerEfficiency_R1CX_pt", "PL", false, {"h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_R1C0p2_pt", "h_truthTau_triggerEfficiency_R1C0p5_pt", "h_truthTau_triggerEfficiency_R1C0p8_pt"}, {"noCut", "R1C0p2", "R1C0p5", "R1C0p8"}, effiHists); 
	overlay_plots("h_truthTau_triggerEfficiency_R2CX_pt", "PL", false, {"h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_R2C0p2_pt", "h_truthTau_triggerEfficiency_R2C0p5_pt", "h_truthTau_triggerEfficiency_R2C0p8_pt"}, {"noCut", "R2C0p2", "R2C0p5", "R2C0p8"}, effiHists); 
	overlay_plots("h_truthTau_triggerEfficiency_R2R1X_pt", "PL", false, {"h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_R2R10p5_pt", "h_truthTau_triggerEfficiency_R2R11p5_pt", "h_truthTau_triggerEfficiency_R2R19p5_pt"}, {"noCut", "R2R10p5", "R2R11p5", "R2R19p5"}, effiHists); 
	
	// Reco taus
	plot_cumulative(th1fHists.at("h_recoTau_ptLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTT_ptLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigMM_ptLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigLL_ptLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTM_ptLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTL_ptLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigML_ptLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_ptSubleading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTT_ptSubleading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigMM_ptSubleading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigLL_ptSubleading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTM_ptSubleading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTL_ptSubleading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigML_ptSubleading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	overlay_plots("h_recoTau_2leadingPt_norm", "HIST", false, {"h_recoTau_ptLeading", "h_recoTau_ptSubleading", "h_recoTau_diTauTrigTT_ptLeading", "h_recoTau_diTauTrigTT_ptSubleading", "h_recoTau_diTauTrigMM_ptLeading", "h_recoTau_diTauTrigMM_ptSubleading", "h_recoTau_diTauTrigLL_ptLeading", "h_recoTau_diTauTrigLL_ptSubleading"}, {"leading", "subleading", "TT leading", "TT subleading", "MM leading", "MM subleading", "LL leading", "LL subleading"}, th1fHists_onlyTH1F, "tau pt [GeV]", {kOrange+9, kOrange+9, kOrange+1, kOrange+1, kTeal+3, kTeal+3, kTeal+8, kTeal+8}, {1, 7, 1, 7, 1, 7, 1, 7}); 
	overlay_plots("h_recoTau_diTauTrig_TTMMLLTMTLML_ptLeading_rate", "PL", true, {"h_recoTau_ptLeading_rate", "h_recoTau_diTauTrigTT_ptLeading_rate", "h_recoTau_diTauTrigMM_ptLeading_rate", "h_recoTau_diTauTrigLL_ptLeading_rate", "h_recoTau_diTauTrigTM_ptLeading_rate", "h_recoTau_diTauTrigTL_ptLeading_rate", "h_recoTau_diTauTrigML_ptLeading_rate"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, rateHists); 
	overlay_plots("h_recoTau_diTauTrig_TTMMLLTMTLML_ptSubleading_rate", "PL", true, {"h_recoTau_ptSubleading_rate", "h_recoTau_diTauTrigTT_ptSubleading_rate", "h_recoTau_diTauTrigMM_ptSubleading_rate", "h_recoTau_diTauTrigLL_ptSubleading_rate", "h_recoTau_diTauTrigTM_ptSubleading_rate", "h_recoTau_diTauTrigTL_ptSubleading_rate", "h_recoTau_diTauTrigML_ptSubleading_rate"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, rateHists); 
	
	plot_rejection("h_recoTau_diTauTrigBkgRej_TT_ptLeading_cumulative", "h_recoTau_diTauTrigTT_ptLeading_rate", "h_recoTau_ptLeading_rate", "reco tau pt [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_MM_ptLeading_cumulative", "h_recoTau_diTauTrigMM_ptLeading_rate", "h_recoTau_ptLeading_rate", "reco tau pt [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_LL_ptLeading_cumulative", "h_recoTau_diTauTrigLL_ptLeading_rate", "h_recoTau_ptLeading_rate", "reco tau pt [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TM_ptLeading_cumulative", "h_recoTau_diTauTrigTM_ptLeading_rate", "h_recoTau_ptLeading_rate", "reco tau pt [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TL_ptLeading_cumulative", "h_recoTau_diTauTrigTL_ptLeading_rate", "h_recoTau_ptLeading_rate", "reco tau pt [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_ML_ptLeading_cumulative", "h_recoTau_diTauTrigML_ptLeading_rate", "h_recoTau_ptLeading_rate", "reco tau pt [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	overlay_plots("h_recoTau_diTauTrigBkgRej_TTMMLLTMTLML_ptLeading_cumulative", "PL", false, {"h_recoTau_diTauTrigBkgRej_TT_ptLeading_cumulative", "h_recoTau_diTauTrigBkgRej_MM_ptLeading_cumulative", "h_recoTau_diTauTrigBkgRej_LL_ptLeading_cumulative", "h_recoTau_diTauTrigBkgRej_TM_ptLeading_cumulative", "h_recoTau_diTauTrigBkgRej_TL_ptLeading_cumulative", "h_recoTau_diTauTrigBkgRej_ML_ptLeading_cumulative"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 

	plot_cumulative(th1fHists.at("h_recoTau_etaLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTT_etaLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigMM_etaLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigLL_etaLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTM_etaLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTL_etaLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigML_etaLeading").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TT_etaLeading_cumulative", "h_recoTau_diTauTrigTT_etaLeading_rate", "h_recoTau_etaLeading_rate", "reco tau eta", "Efficiency", 140, -3.5, 3.5, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_MM_etaLeading_cumulative", "h_recoTau_diTauTrigMM_etaLeading_rate", "h_recoTau_etaLeading_rate", "reco tau eta", "Efficiency", 140, -3.5, 3.5, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_LL_etaLeading_cumulative", "h_recoTau_diTauTrigLL_etaLeading_rate", "h_recoTau_etaLeading_rate", "reco tau eta", "Efficiency", 140, -3.5, 3.5, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TM_etaLeading_cumulative", "h_recoTau_diTauTrigTM_etaLeading_rate", "h_recoTau_etaLeading_rate", "reco tau eta", "Efficiency", 140, -3.5, 3.5, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TL_etaLeading_cumulative", "h_recoTau_diTauTrigTL_etaLeading_rate", "h_recoTau_etaLeading_rate", "reco tau eta", "Efficiency", 140, -3.5, 3.5, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_ML_etaLeading_cumulative", "h_recoTau_diTauTrigML_etaLeading_rate", "h_recoTau_etaLeading_rate", "reco tau eta", "Efficiency", 140, -3.5, 3.5, rateHists, effiHists); 
	overlay_plots("h_recoTau_diTauTrigBkgRej_TTMMLLTMTLML_etaLeading_cumulative", "PL", false, {"h_recoTau_diTauTrigBkgRej_TT_etaLeading_cumulative", "h_recoTau_diTauTrigBkgRej_MM_etaLeading_cumulative", "h_recoTau_diTauTrigBkgRej_LL_etaLeading_cumulative", "h_recoTau_diTauTrigBkgRej_TM_etaLeading_cumulative", "h_recoTau_diTauTrigBkgRej_TL_etaLeading_cumulative", "h_recoTau_diTauTrigBkgRej_ML_etaLeading_cumulative"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 

	plot_cumulative(th1fHists.at("h_recoTau_diTauDeltaR").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTT_diTauDeltaR").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigMM_diTauDeltaR").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigLL_diTauDeltaR").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTM_diTauDeltaR").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTL_diTauDeltaR").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigML_diTauDeltaR").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TT_diTauDeltaR_cumulative", "h_recoTau_diTauTrigTT_diTauDeltaR_rate", "h_recoTau_diTauDeltaR_rate", "reco tau di-tau deltaR", "Efficiency", 314, 0, 6.28, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_MM_diTauDeltaR_cumulative", "h_recoTau_diTauTrigMM_diTauDeltaR_rate", "h_recoTau_diTauDeltaR_rate", "reco tau di-tau deltaR", "Efficiency", 314, 0, 6.28, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_LL_diTauDeltaR_cumulative", "h_recoTau_diTauTrigLL_diTauDeltaR_rate", "h_recoTau_diTauDeltaR_rate", "reco tau di-tau deltaR", "Efficiency", 314, 0, 6.28, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TM_diTauDeltaR_cumulative", "h_recoTau_diTauTrigTM_diTauDeltaR_rate", "h_recoTau_diTauDeltaR_rate", "reco tau di-tau deltaR", "Efficiency", 314, 0, 6.28, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TL_diTauDeltaR_cumulative", "h_recoTau_diTauTrigTL_diTauDeltaR_rate", "h_recoTau_diTauDeltaR_rate", "reco tau di-tau deltaR", "Efficiency", 314, 0, 6.28, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_ML_diTauDeltaR_cumulative", "h_recoTau_diTauTrigML_diTauDeltaR_rate", "h_recoTau_diTauDeltaR_rate", "reco tau di-tau deltaR", "Efficiency", 314, 0, 6.28, rateHists, effiHists); 
	overlay_plots("h_recoTau_diTauTrigBkgRej_TTMMLLTMTLML_diTauDeltaR_cumulative", "PL", false, {"h_recoTau_diTauTrigBkgRej_TT_diTauDeltaR_cumulative", "h_recoTau_diTauTrigBkgRej_MM_diTauDeltaR_cumulative", "h_recoTau_diTauTrigBkgRej_LL_diTauDeltaR_cumulative", "h_recoTau_diTauTrigBkgRej_TM_diTauDeltaR_cumulative", "h_recoTau_diTauTrigBkgRej_TL_diTauDeltaR_cumulative", "h_recoTau_diTauTrigBkgRej_ML_diTauDeltaR_cumulative"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 

	plot_cumulative(th1fHists.at("h_recoTau_diTauMass").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTT_diTauMass").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigMM_diTauMass").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigLL_diTauMass").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTM_diTauMass").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigTL_diTauMass").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_cumulative(th1fHists.at("h_recoTau_diTauTrigML_diTauMass").hist, false, "_rate", 40e3/nEvent, "Rate [kHz]", rateHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TT_diTauMass_cumulative", "h_recoTau_diTauTrigTT_diTauMass_rate", "h_recoTau_diTauMass_rate", "reco tau di-tau mass [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_MM_diTauMass_cumulative", "h_recoTau_diTauTrigMM_diTauMass_rate", "h_recoTau_diTauMass_rate", "reco tau di-tau mass [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_LL_diTauMass_cumulative", "h_recoTau_diTauTrigLL_diTauMass_rate", "h_recoTau_diTauMass_rate", "reco tau di-tau mass [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TM_diTauMass_cumulative", "h_recoTau_diTauTrigTM_diTauMass_rate", "h_recoTau_diTauMass_rate", "reco tau di-tau mass [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_TL_diTauMass_cumulative", "h_recoTau_diTauTrigTL_diTauMass_rate", "h_recoTau_diTauMass_rate", "reco tau di-tau mass [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	plot_rejection("h_recoTau_diTauTrigBkgRej_ML_diTauMass_cumulative", "h_recoTau_diTauTrigML_diTauMass_rate", "h_recoTau_diTauMass_rate", "reco tau di-tau mass [GeV]", "Efficiency", 120, 0, 120, rateHists, effiHists); 
	overlay_plots("h_recoTau_diTauTrigBkgRej_TTMMLLTMTLML_diTauMass_cumulative", "PL", false, {"h_recoTau_diTauTrigBkgRej_TT_diTauMass_cumulative", "h_recoTau_diTauTrigBkgRej_MM_diTauMass_cumulative", "h_recoTau_diTauTrigBkgRej_LL_diTauMass_cumulative", "h_recoTau_diTauTrigBkgRej_TM_diTauMass_cumulative", "h_recoTau_diTauTrigBkgRej_TL_diTauMass_cumulative", "h_recoTau_diTauTrigBkgRej_ML_diTauMass_cumulative"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 

	// Truth-matched reco tau
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TT_ptLeading", "h_matchedRecoTau_diTauTrigTT_ptLeading", "h_matchedRecoTau_ptLeading", "matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_MM_ptLeading", "h_matchedRecoTau_diTauTrigMM_ptLeading", "h_matchedRecoTau_ptLeading", "matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_LL_ptLeading", "h_matchedRecoTau_diTauTrigLL_ptLeading", "h_matchedRecoTau_ptLeading", "matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TM_ptLeading", "h_matchedRecoTau_diTauTrigTM_ptLeading", "h_matchedRecoTau_ptLeading", "matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TL_ptLeading", "h_matchedRecoTau_diTauTrigTL_ptLeading", "h_matchedRecoTau_ptLeading", "matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_ML_ptLeading", "h_matchedRecoTau_diTauTrigML_ptLeading", "h_matchedRecoTau_ptLeading", "matched reco tau pt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrigEffi_TTMMLLTMTLML_ptLeading", "PL", false, {"h_matchedRecoTau_diTauTrigEffi_TT_ptLeading", "h_matchedRecoTau_diTauTrigEffi_MM_ptLeading", "h_matchedRecoTau_diTauTrigEffi_LL_ptLeading", "h_matchedRecoTau_diTauTrigEffi_TM_ptLeading", "h_matchedRecoTau_diTauTrigEffi_TL_ptLeading", "h_matchedRecoTau_diTauTrigEffi_ML_ptLeading"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_ptLeading_norm", "HIST", false, {"h_matchedRecoTau_ptLeading", "h_matchedRecoTau_diTauTrigTT_ptLeading", "h_matchedRecoTau_diTauTrigMM_ptLeading", "h_matchedRecoTau_diTauTrigLL_ptLeading", "h_matchedRecoTau_diTauTrigTM_ptLeading", "h_matchedRecoTau_diTauTrigTL_ptLeading", "h_matchedRecoTau_diTauTrigML_ptLeading"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau pt [GeV]"); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_ptSubleading_norm", "HIST", false, {"h_matchedRecoTau_ptSubleading", "h_matchedRecoTau_diTauTrigTT_ptSubleading", "h_matchedRecoTau_diTauTrigMM_ptSubleading", "h_matchedRecoTau_diTauTrigLL_ptSubleading", "h_matchedRecoTau_diTauTrigTM_ptSubleading", "h_matchedRecoTau_diTauTrigTL_ptSubleading", "h_matchedRecoTau_diTauTrigML_ptSubleading"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau pt [GeV]"); 
	
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TT_etaLeading", "h_matchedRecoTau_diTauTrigTT_etaLeading", "h_matchedRecoTau_etaLeading", "matched reco tau eta", "Efficiency", 140, -3.5, 3.5, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_MM_etaLeading", "h_matchedRecoTau_diTauTrigMM_etaLeading", "h_matchedRecoTau_etaLeading", "matched reco tau eta", "Efficiency", 140, -3.5, 3.5, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_LL_etaLeading", "h_matchedRecoTau_diTauTrigLL_etaLeading", "h_matchedRecoTau_etaLeading", "matched reco tau eta", "Efficiency", 140, -3.5, 3.5, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TM_etaLeading", "h_matchedRecoTau_diTauTrigTM_etaLeading", "h_matchedRecoTau_etaLeading", "matched reco tau eta", "Efficiency", 140, -3.5, 3.5, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TL_etaLeading", "h_matchedRecoTau_diTauTrigTL_etaLeading", "h_matchedRecoTau_etaLeading", "matched reco tau eta", "Efficiency", 140, -3.5, 3.5, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_ML_etaLeading", "h_matchedRecoTau_diTauTrigML_etaLeading", "h_matchedRecoTau_etaLeading", "matched reco tau eta", "Efficiency", 140, -3.5, 3.5, th1fHists, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrigEffi_TTMMLLTMTLML_etaLeading", "PL", false, {"h_matchedRecoTau_diTauTrigEffi_TT_etaLeading", "h_matchedRecoTau_diTauTrigEffi_MM_etaLeading", "h_matchedRecoTau_diTauTrigEffi_LL_etaLeading", "h_matchedRecoTau_diTauTrigEffi_TM_etaLeading", "h_matchedRecoTau_diTauTrigEffi_TL_etaLeading", "h_matchedRecoTau_diTauTrigEffi_ML_etaLeading"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_etaLeading_norm", "HIST", false, {"h_matchedRecoTau_etaLeading", "h_matchedRecoTau_diTauTrigTT_etaLeading", "h_matchedRecoTau_diTauTrigMM_etaLeading", "h_matchedRecoTau_diTauTrigLL_etaLeading", "h_matchedRecoTau_diTauTrigTM_etaLeading", "h_matchedRecoTau_diTauTrigTL_etaLeading", "h_matchedRecoTau_diTauTrigML_etaLeading"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau eta"); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_etaSubleading_norm", "HIST", false, {"h_matchedRecoTau_etaSubleading", "h_matchedRecoTau_diTauTrigTT_etaSubleading", "h_matchedRecoTau_diTauTrigMM_etaSubleading", "h_matchedRecoTau_diTauTrigLL_etaSubleading", "h_matchedRecoTau_diTauTrigTM_etaSubleading", "h_matchedRecoTau_diTauTrigTL_etaSubleading", "h_matchedRecoTau_diTauTrigML_etaSubleading"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau eta"); 
	
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TT_seedEtLeading", "h_matchedRecoTau_diTauTrigTT_seedEtLeading", "h_matchedRecoTau_seedEtLeading", "matched reco tau seedEt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_MM_seedEtLeading", "h_matchedRecoTau_diTauTrigMM_seedEtLeading", "h_matchedRecoTau_seedEtLeading", "matched reco tau seedEt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_LL_seedEtLeading", "h_matchedRecoTau_diTauTrigLL_seedEtLeading", "h_matchedRecoTau_seedEtLeading", "matched reco tau seedEt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TM_seedEtLeading", "h_matchedRecoTau_diTauTrigTM_seedEtLeading", "h_matchedRecoTau_seedEtLeading", "matched reco tau seedEt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TL_seedEtLeading", "h_matchedRecoTau_diTauTrigTL_seedEtLeading", "h_matchedRecoTau_seedEtLeading", "matched reco tau seedEt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_ML_seedEtLeading", "h_matchedRecoTau_diTauTrigML_seedEtLeading", "h_matchedRecoTau_seedEtLeading", "matched reco tau seedEt [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrigEffi_TTMMLLTMTLML_seedEtLeading", "PL", false, {"h_matchedRecoTau_diTauTrigEffi_TT_seedEtLeading", "h_matchedRecoTau_diTauTrigEffi_MM_seedEtLeading", "h_matchedRecoTau_diTauTrigEffi_LL_seedEtLeading", "h_matchedRecoTau_diTauTrigEffi_TM_seedEtLeading", "h_matchedRecoTau_diTauTrigEffi_TL_seedEtLeading", "h_matchedRecoTau_diTauTrigEffi_ML_seedEtLeading"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_seedEtLeading_norm", "HIST", false, {"h_matchedRecoTau_seedEtLeading", "h_matchedRecoTau_diTauTrigTT_seedEtLeading", "h_matchedRecoTau_diTauTrigMM_seedEtLeading", "h_matchedRecoTau_diTauTrigLL_seedEtLeading", "h_matchedRecoTau_diTauTrigTM_seedEtLeading", "h_matchedRecoTau_diTauTrigTL_seedEtLeading", "h_matchedRecoTau_diTauTrigML_seedEtLeading"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau seedEt [GeV]"); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_seedEtSubleading_norm", "HIST", false, {"h_matchedRecoTau_seedEtSubleading", "h_matchedRecoTau_diTauTrigTT_seedEtSubleading", "h_matchedRecoTau_diTauTrigMM_seedEtSubleading", "h_matchedRecoTau_diTauTrigLL_seedEtSubleading", "h_matchedRecoTau_diTauTrigTM_seedEtSubleading", "h_matchedRecoTau_diTauTrigTL_seedEtSubleading", "h_matchedRecoTau_diTauTrigML_seedEtSubleading"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau seedEt [GeV]"); 
	
	overlay_plots("h_matchedRecoTau_triggerEfficiency_seedEtXGeV_pt", "PL", false, {"h_matchedRecoTau_triggerEfficiency_noCut_pt", "h_matchedRecoTau_triggerEfficiency_seedEt2GeV_pt", "h_matchedRecoTau_triggerEfficiency_seedEt5GeV_pt", "h_matchedRecoTau_triggerEfficiency_seedEt8GeV_pt", "h_matchedRecoTau_triggerEfficiency_seedEt15GeV_pt", "h_matchedRecoTau_triggerEfficiency_seedEt20GeV_pt", "h_matchedRecoTau_triggerEfficiency_seedEt25GeV_pt"}, {"noCut", "et2GeV", "et5GeV", "et8GeV", "et15GeV", "et20GeV", "et25GeV"}, effiHists); 
	overlay_plots("h_matchedRecoTau_triggerEfficiency_etXGeV_pt", "PL", false, {"h_matchedRecoTau_triggerEfficiency_noCut_pt", "h_matchedRecoTau_triggerEfficiency_et2GeV_pt", "h_matchedRecoTau_triggerEfficiency_et3GeV_pt", "h_matchedRecoTau_triggerEfficiency_et5GeV_pt"}, {"noCut", "et2GeV", "et3GeV", "et5GeV"}, effiHists); 
	overlay_plots("h_matchedRecoTau_triggerEfficiency_CAX_pt", "PL", false, {"h_matchedRecoTau_triggerEfficiency_noCut_pt", "h_matchedRecoTau_triggerEfficiency_CA0p2_pt", "h_matchedRecoTau_triggerEfficiency_CA0p5_pt", "h_matchedRecoTau_triggerEfficiency_CA0p8_pt"}, {"noCut", "CA0p2", "CA0p5", "CA0p8"}, effiHists); 
	overlay_plots("h_matchedRecoTau_triggerEfficiency_R1CX_pt", "PL", false, {"h_matchedRecoTau_triggerEfficiency_noCut_pt", "h_matchedRecoTau_triggerEfficiency_R1C0p2_pt", "h_matchedRecoTau_triggerEfficiency_R1C0p5_pt", "h_matchedRecoTau_triggerEfficiency_R1C0p8_pt"}, {"noCut", "R1C0p2", "R1C0p5", "R1C0p8"}, effiHists); 
	overlay_plots("h_matchedRecoTau_triggerEfficiency_R2CX_pt", "PL", false, {"h_matchedRecoTau_triggerEfficiency_noCut_pt", "h_matchedRecoTau_triggerEfficiency_R2C0p2_pt", "h_matchedRecoTau_triggerEfficiency_R2C0p5_pt", "h_matchedRecoTau_triggerEfficiency_R2C0p8_pt"}, {"noCut", "R2C0p2", "R2C0p5", "R2C0p8"}, effiHists); 
	overlay_plots("h_matchedRecoTau_triggerEfficiency_R2R1X_pt", "PL", false, {"h_matchedRecoTau_triggerEfficiency_noCut_pt", "h_matchedRecoTau_triggerEfficiency_R2R10p5_pt", "h_matchedRecoTau_triggerEfficiency_R2R11p5_pt", "h_matchedRecoTau_triggerEfficiency_R2R19p5_pt"}, {"noCut", "R2R10p5", "R2R11p5", "R2R19p5"}, effiHists); 
	
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TT_diTauDeltaR", "h_matchedRecoTau_diTauTrigTT_diTauDeltaR", "h_matchedRecoTau_diTauDeltaR", "matched reco tau deltaR", "Efficiency", 126, 0, 6.3, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_MM_diTauDeltaR", "h_matchedRecoTau_diTauTrigMM_diTauDeltaR", "h_matchedRecoTau_diTauDeltaR", "matched reco tau deltaR", "Efficiency", 126, 0, 6.3, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_LL_diTauDeltaR", "h_matchedRecoTau_diTauTrigLL_diTauDeltaR", "h_matchedRecoTau_diTauDeltaR", "matched reco tau deltaR", "Efficiency", 126, 0, 6.3, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TM_diTauDeltaR", "h_matchedRecoTau_diTauTrigTM_diTauDeltaR", "h_matchedRecoTau_diTauDeltaR", "matched reco tau deltaR", "Efficiency", 126, 0, 6.3, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TL_diTauDeltaR", "h_matchedRecoTau_diTauTrigTL_diTauDeltaR", "h_matchedRecoTau_diTauDeltaR", "matched reco tau deltaR", "Efficiency", 126, 0, 6.3, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_ML_diTauDeltaR", "h_matchedRecoTau_diTauTrigML_diTauDeltaR", "h_matchedRecoTau_diTauDeltaR", "matched reco tau deltaR", "Efficiency", 126, 0, 6.3, th1fHists, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrigEffi_TTMMLLTMTLML_diTauDeltaR", "PL", false, {"h_matchedRecoTau_diTauTrigEffi_TT_diTauDeltaR", "h_matchedRecoTau_diTauTrigEffi_MM_diTauDeltaR", "h_matchedRecoTau_diTauTrigEffi_LL_diTauDeltaR", "h_matchedRecoTau_diTauTrigEffi_TM_diTauDeltaR", "h_matchedRecoTau_diTauTrigEffi_TL_diTauDeltaR", "h_matchedRecoTau_diTauTrigEffi_ML_diTauDeltaR"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_diTauDeltaR", "HIST", false, {"h_matchedRecoTau_diTauDeltaR", "h_matchedRecoTau_diTauTrigTT_diTauDeltaR", "h_matchedRecoTau_diTauTrigMM_diTauDeltaR", "h_matchedRecoTau_diTauTrigLL_diTauDeltaR", "h_matchedRecoTau_diTauTrigTM_diTauDeltaR", "h_matchedRecoTau_diTauTrigTL_diTauDeltaR", "h_matchedRecoTau_diTauTrigML_diTauDeltaR"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau seedEt [GeV]"); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_diTauDeltaR_norm", "HIST", false, {"h_matchedRecoTau_diTauDeltaR", "h_matchedRecoTau_diTauTrigTT_diTauDeltaR", "h_matchedRecoTau_diTauTrigMM_diTauDeltaR", "h_matchedRecoTau_diTauTrigLL_diTauDeltaR", "h_matchedRecoTau_diTauTrigTM_diTauDeltaR", "h_matchedRecoTau_diTauTrigTL_diTauDeltaR", "h_matchedRecoTau_diTauTrigML_diTauDeltaR"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau seedEt [GeV]"); 
	
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TT_diTauMass", "h_matchedRecoTau_diTauTrigTT_diTauMass", "h_matchedRecoTau_diTauMass", "matched reco tau di tau mass [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_MM_diTauMass", "h_matchedRecoTau_diTauTrigMM_diTauMass", "h_matchedRecoTau_diTauMass", "matched reco tau di tau mass [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_LL_diTauMass", "h_matchedRecoTau_diTauTrigLL_diTauMass", "h_matchedRecoTau_diTauMass", "matched reco tau di tau mass [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TM_diTauMass", "h_matchedRecoTau_diTauTrigTM_diTauMass", "h_matchedRecoTau_diTauMass", "matched reco tau di tau mass [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_TL_diTauMass", "h_matchedRecoTau_diTauTrigTL_diTauMass", "h_matchedRecoTau_diTauMass", "matched reco tau di tau mass [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	plot_efficiency("h_matchedRecoTau_diTauTrigEffi_ML_diTauMass", "h_matchedRecoTau_diTauTrigML_diTauMass", "h_matchedRecoTau_diTauMass", "matched reco tau di tau mass [GeV]", "Efficiency", 120, 0, 120, th1fHists, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrigEffi_TTMMLLTMTLML_diTauMass", "PL", false, {"h_matchedRecoTau_diTauTrigEffi_TT_diTauMass", "h_matchedRecoTau_diTauTrigEffi_MM_diTauMass", "h_matchedRecoTau_diTauTrigEffi_LL_diTauMass", "h_matchedRecoTau_diTauTrigEffi_TM_diTauMass", "h_matchedRecoTau_diTauTrigEffi_TL_diTauMass", "h_matchedRecoTau_diTauTrigEffi_ML_diTauMass"}, {"TT", "MM", "LL", "TM", "TL", "ML"}, effiHists); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_diTauMass", "HIST", false, {"h_matchedRecoTau_diTauMass", "h_matchedRecoTau_diTauTrigTT_diTauMass", "h_matchedRecoTau_diTauTrigMM_diTauMass", "h_matchedRecoTau_diTauTrigLL_diTauMass", "h_matchedRecoTau_diTauTrigTM_diTauMass", "h_matchedRecoTau_diTauTrigTL_diTauMass", "h_matchedRecoTau_diTauTrigML_diTauMass"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau seedEt [GeV]"); 
	overlay_plots("h_matchedRecoTau_diTauTrig_TTMMLLTMTLML_diTauMass_norm", "HIST", false, {"h_matchedRecoTau_diTauMass", "h_matchedRecoTau_diTauTrigTT_diTauMass", "h_matchedRecoTau_diTauTrigMM_diTauMass", "h_matchedRecoTau_diTauTrigLL_diTauMass", "h_matchedRecoTau_diTauTrigTM_diTauMass", "h_matchedRecoTau_diTauTrigTL_diTauMass", "h_matchedRecoTau_diTauTrigML_diTauMass"}, {"noCut", "TT", "MM", "LL", "TM", "TL", "ML"}, th1fHists_onlyTH1F, "tau seedEt [GeV]"); 
	
	// Reco-matched truth tau
	overlay_plots("h_truthMatched2RecoTau_triggerEfficiency_seedEtXGeV_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt2GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt5GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt8GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt15GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt20GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt25GeV_pt"}, {"noCut", "et2GeV", "et5GeV", "et8GeV", "et15GeV", "et20GeV", "et25GeV"}, effiHists); 
	overlay_plots("h_truthMatched2RecoTau_triggerEfficiency_etXGeV_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_et2GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_et3GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_et5GeV_pt"}, {"noCut", "et2GeV", "et3GeV", "et5GeV"}, effiHists); 
	overlay_plots("h_truthMatched2RecoTau_triggerEfficiency_CAX_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_CA0p2_pt", "h_truthMatched2RecoTau_triggerEfficiency_CA0p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_CA0p8_pt"}, {"noCut", "CA0p2", "CA0p5", "CA0p8"}, effiHists); 
	overlay_plots("h_truthMatched2RecoTau_triggerEfficiency_R1CX_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_R1C0p2_pt", "h_truthMatched2RecoTau_triggerEfficiency_R1C0p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_R1C0p8_pt"}, {"noCut", "R1C0p2", "R1C0p5", "R1C0p8"}, effiHists); 
	overlay_plots("h_truthMatched2RecoTau_triggerEfficiency_R2R1X_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2R10p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2R11p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2R19p5_pt"}, {"noCut", "R2R10p5", "R2R11p5", "R2R19p5"}, effiHists); 
	
	// Truth-unmatched reco tau
	overlay_plots("h_unmatchedRecoTau_triggerEfficiency_seedEtXGeV_pt", "PL", false, {"h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt2GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt5GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt8GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt15GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt20GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt25GeV_pt"}, {"noCut", "et2GeV", "et5GeV", "et8GeV", "et15GeV", "et20GeV", "et25GeV"}, effiHists); 
	overlay_plots("h_unmatchedRecoTau_triggerEfficiency_etXGeV_pt", "PL", false, {"h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_et2GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_et3GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_et5GeV_pt"}, {"noCut", "et2GeV", "et3GeV", "et5GeV"}, effiHists); 
	overlay_plots("h_unmatchedRecoTau_triggerEfficiency_CAX_pt", "PL", false, {"h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_CA0p2_pt", "h_unmatchedRecoTau_triggerEfficiency_CA0p5_pt", "h_unmatchedRecoTau_triggerEfficiency_CA0p8_pt"}, {"noCut", "CA0p2", "CA0p5", "CA0p8"}, effiHists); 
	overlay_plots("h_unmatchedRecoTau_triggerEfficiency_R1CX_pt", "PL", false, {"h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_R1C0p2_pt", "h_unmatchedRecoTau_triggerEfficiency_R1C0p5_pt", "h_unmatchedRecoTau_triggerEfficiency_R1C0p8_pt"}, {"noCut", "R1C0p2", "R1C0p5", "R1C0p8"}, effiHists); 
	overlay_plots("h_unmatchedRecoTau_triggerEfficiency_R2R1X_pt", "PL", false, {"h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_R2R10p5_pt", "h_unmatchedRecoTau_triggerEfficiency_R2R11p5_pt", "h_unmatchedRecoTau_triggerEfficiency_R2R19p5_pt"}, {"noCut", "R2R10p5", "R2R11p5", "R2R19p5"}, effiHists); 
	
	// S/B overlay

	// Trigger spectrum
	overlay_plots("h_SnB_triggered_CAX_pt_norm", "HIST", false, {"h_truthMatched2RecoTau_triggered_noCut_pt", "h_truthMatched2RecoTau_triggered_CA0p2_pt", "h_truthMatched2RecoTau_triggered_CA0p5_pt", "h_truthMatched2RecoTau_triggered_CA0p8_pt", "h_unmatchedRecoTau_triggered_noCut_pt", "h_unmatchedRecoTau_triggered_CA0p2_pt", "h_unmatchedRecoTau_triggered_CA0p5_pt", "h_unmatchedRecoTau_triggered_CA0p8_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_CA0p2", "truthMatched2RecoTau_CA0p5", "truthMatched2RecoTau_CA0p8", "unmatchedRecoTau_noCut", "unmatchedRecoTau_CA0p2", "unmatchedRecoTau_CA0p5", "unmatchedRecoTau_CA0p8"}, th1fHists_onlyTH1F, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggered_R1CX_pt_norm", "HIST", false, {"h_truthMatched2RecoTau_triggered_noCut_pt", "h_truthMatched2RecoTau_triggered_R1C0p2_pt", "h_truthMatched2RecoTau_triggered_R1C0p5_pt", "h_truthMatched2RecoTau_triggered_R1C0p8_pt", "h_unmatchedRecoTau_triggered_noCut_pt", "h_unmatchedRecoTau_triggered_R1C0p2_pt", "h_unmatchedRecoTau_triggered_R1C0p5_pt", "h_unmatchedRecoTau_triggered_R1C0p8_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_R1C0p2", "truthMatched2RecoTau_R1C0p5", "truthMatched2RecoTau_R1C0p8", "unmatchedRecoTau_noCut", "unmatchedRecoTau_R1C0p2", "unmatchedRecoTau_R1C0p5", "unmatchedRecoTau_R1C0p8"}, th1fHists_onlyTH1F, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggered_R2CX_pt_norm", "HIST", false, {"h_truthMatched2RecoTau_triggered_noCut_pt", "h_truthMatched2RecoTau_triggered_R2C0p2_pt", "h_truthMatched2RecoTau_triggered_R2C0p5_pt", "h_truthMatched2RecoTau_triggered_R2C0p8_pt", "h_unmatchedRecoTau_triggered_noCut_pt", "h_unmatchedRecoTau_triggered_R2C0p2_pt", "h_unmatchedRecoTau_triggered_R2C0p5_pt", "h_unmatchedRecoTau_triggered_R2C0p8_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_R2C0p2", "truthMatched2RecoTau_R2C0p5", "truthMatched2RecoTau_R2C0p8", "unmatchedRecoTau_noCut", "unmatchedRecoTau_R2C0p2", "unmatchedRecoTau_R2C0p5", "unmatchedRecoTau_R2C0p8"}, th1fHists_onlyTH1F, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggered_R2R1X_pt_norm", "HIST", false, {"h_truthMatched2RecoTau_triggered_noCut_pt", "h_truthMatched2RecoTau_triggered_R2R10p5_pt", "h_truthMatched2RecoTau_triggered_R2R11p5_pt", "h_truthMatched2RecoTau_triggered_R2R19p5_pt", "h_unmatchedRecoTau_triggered_noCut_pt", "h_unmatchedRecoTau_triggered_R2R10p5_pt", "h_unmatchedRecoTau_triggered_R2R11p5_pt", "h_unmatchedRecoTau_triggered_R2R19p5_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_R2R10p5", "truthMatched2RecoTau_R2R11p5", "truthMatched2RecoTau_R2R19p5", "unmatchedRecoTau_noCut", "unmatchedRecoTau_R2R10p5", "unmatchedRecoTau_R2R11p5", "unmatchedRecoTau_R2R19p5"}, th1fHists_onlyTH1F, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 

	// Trigger efficiency
	overlay_plots("h_SnB_triggerEfficiency_seedEtXGeV_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt2GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt5GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_seedEt8GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt2GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt5GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_seedEt8GeV_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_seedEt2GeV", "truthMatched2RecoTau_seedEt5GeV", "truthMatched2RecoTau_seedEt8GeV", "unmatchedRecoTau_noCut", "unmatchedRecoTau_et2GeV", "unmatchedRecoTau_et5GeV", "unmatchedRecoTau_et8GeV"}, effiHists, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggerEfficiency_etXGeV_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_et2GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_et3GeV_pt", "h_truthMatched2RecoTau_triggerEfficiency_et5GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_et2GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_et3GeV_pt", "h_unmatchedRecoTau_triggerEfficiency_et5GeV_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_et2GeV", "truthMatched2RecoTau_et3GeV", "truthMatched2RecoTau_et5GeV", "unmatchedRecoTau_noCut", "unmatchedRecoTau_et2GeV", "unmatchedRecoTau_et3GeV", "unmatchedRecoTau_et5GeV"}, effiHists, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggerEfficiency_CAX_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_CA0p2_pt", "h_truthMatched2RecoTau_triggerEfficiency_CA0p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_CA0p8_pt", "h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_CA0p2_pt", "h_unmatchedRecoTau_triggerEfficiency_CA0p5_pt", "h_unmatchedRecoTau_triggerEfficiency_CA0p8_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_CA0p2", "truthMatched2RecoTau_CA0p5", "truthMatched2RecoTau_CA0p8", "unmatchedRecoTau_noCut", "unmatchedRecoTau_CA0p2", "unmatchedRecoTau_CA0p5", "unmatchedRecoTau_CA0p8"}, effiHists, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggerEfficiency_R1CX_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_R1C0p2_pt", "h_truthMatched2RecoTau_triggerEfficiency_R1C0p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_R1C0p8_pt", "h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_R1C0p2_pt", "h_unmatchedRecoTau_triggerEfficiency_R1C0p5_pt", "h_unmatchedRecoTau_triggerEfficiency_R1C0p8_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_R1C0p2", "truthMatched2RecoTau_R1C0p5", "truthMatched2RecoTau_R1C0p8", "unmatchedRecoTau_noCut", "unmatchedRecoTau_R1C0p2", "unmatchedRecoTau_R1C0p5", "unmatchedRecoTau_R1C0p8"}, effiHists, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggerEfficiency_R2CX_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2C0p2_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2C0p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2C0p8_pt", "h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_R2C0p2_pt", "h_unmatchedRecoTau_triggerEfficiency_R2C0p5_pt", "h_unmatchedRecoTau_triggerEfficiency_R2C0p8_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_R2C0p2", "truthMatched2RecoTau_R2C0p5", "truthMatched2RecoTau_R2C0p8", "unmatchedRecoTau_noCut", "unmatchedRecoTau_R2C0p2", "unmatchedRecoTau_R2C0p5", "unmatchedRecoTau_R2C0p8"}, effiHists, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 
	overlay_plots("h_SnB_triggerEfficiency_R2R1X_pt", "PL", false, {"h_truthMatched2RecoTau_triggerEfficiency_noCut_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2R10p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2R11p5_pt", "h_truthMatched2RecoTau_triggerEfficiency_R2R19p5_pt", "h_unmatchedRecoTau_triggerEfficiency_noCut_pt", "h_unmatchedRecoTau_triggerEfficiency_R2R10p5_pt", "h_unmatchedRecoTau_triggerEfficiency_R2R11p5_pt", "h_unmatchedRecoTau_triggerEfficiency_R2R19p5_pt"}, {"truthMatched2RecoTau_noCut", "truthMatched2RecoTau_R2R10p5", "truthMatched2RecoTau_R2R11p5", "truthMatched2RecoTau_R2R19p5", "unmatchedRecoTau_noCut", "unmatchedRecoTau_R2R10p5", "unmatchedRecoTau_R2R11p5", "unmatchedRecoTau_R2R19p5"}, effiHists, "tau pt [GeV]", {kOrange+9, kOrange+7, kOrange+1, kOrange-2, kTeal+3, kTeal+5, kTeal+8, kTeal+1}, {1, 1, 1, 1, 7, 7, 7, 7}); 

	// Print other info
	float nSig = th1fHists.at("h_matchedRecoTau_pt").hist->Integral(); 
	float nSigBaseline = th1fHists.at("h_matchedRecoTau_trigBaseline_pt").hist->Integral(); 
	float nSigLoose = th1fHists.at("h_matchedRecoTau_trigLoose_pt").hist->Integral(); 
	float nSigMedium = th1fHists.at("h_matchedRecoTau_trigMedium_pt").hist->Integral(); 
	float nSigTight = th1fHists.at("h_matchedRecoTau_trigTight_pt").hist->Integral(); 
	float nBkg = th1fHists.at("h_unmatchedRecoTau_pt").hist->Integral(); 
	float nBkgBaseline = th1fHists.at("h_unmatchedRecoTau_trigBaseline_pt").hist->Integral(); 
	float nBkgLoose = th1fHists.at("h_unmatchedRecoTau_trigLoose_pt").hist->Integral(); 
	float nBkgMedium = th1fHists.at("h_unmatchedRecoTau_trigMedium_pt").hist->Integral(); 
	float nBkgTight = th1fHists.at("h_unmatchedRecoTau_trigTight_pt").hist->Integral(); 
	printf("Sig & bkg efficiencies: \n%-8s%7s%7s\n%-8s%6.1f%%%6.1f%%\n%-8s%6.1f%%%6.1f%%\n%-8s%6.1f%%%6.1f%%\n%-8s%6.1f%%%6.1f%%\n", "", "SigEff", "BkgRej", "Baseline", 100*nSigBaseline/nSig, 100-100*nBkgBaseline/nBkg, "Loose", 100*nSigLoose/nSig, 100-100*nBkgLoose/nBkg, "Medium", 100*nSigMedium/nSig, 100-100*nBkgMedium/nBkg, "Tight", 100*nSigTight/nSig, 100-100*nBkgTight/nBkg); 
}
