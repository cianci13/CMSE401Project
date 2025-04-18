//Script input/output customization is at the bottom. To change the histogram itself, alter the first two functions

TCanvas* make_canvas(string name, int w, int h, float t, float b, float l, float r) {
 
    gStyle->SetOptTitle(0);

    TCanvas* canvas = new TCanvas(name.c_str(), name.c_str(), 50, 50, w, h);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetFrameFillStyle(0);
    canvas->SetFrameBorderMode(0);
    canvas->SetLeftMargin(l/w);
    canvas->SetRightMargin(r/w);
    canvas->SetTopMargin(t/h);
    canvas->SetBottomMargin(b/h);
    canvas->SetTickx(0);
    canvas->SetTicky(0);

    return canvas;
}

TCanvas* superimpose_hists(std::vector<string> filePaths, std::vector<string> histNames, std::string iteration, std::string suffix = "tautau") {
    bool drawErrors = false;
    std::cout << histNames.at(0) << std::endl;
    gStyle->SetOptStat(0);
    std::vector<TH1*> hists;

    int colorList[] = {1, 2, 4, 6, 7, 9};
    int colorNum = 0;
    double max = 0;

    TCanvas* canvas = make_canvas((histNames.at(1) + suffix + iteration).c_str(), 800, 600, 48, 72, 96, 32);

    auto legend = new TLegend(0.76, 0.77, 0.96, 0.92);	
	legend->SetTextSize(0.015);

    for(int i = 0; i < filePaths.size(); i++) {
        TFile* file = TFile::Open(filePaths.at(i).c_str(), "read");
        if(!file) {
            throw runtime_error("No file for " + filePaths.at(i));
        }

	    TH1* histogram = dynamic_cast<TH1*>((file->Get(histNames.at(i).c_str()))->Clone());
        histogram->SetLineColor(colorList[colorNum]);    
        histogram->SetStats(0);    
        colorNum++;
        histogram->Scale(1/histogram->Integral());

        if(!histogram) {
	        throw runtime_error("No hist for " + histNames.at(i) + " in file " + filePaths.at(i));
	    }
        if(i == 0) {
            histogram->Draw("HIST");
            max = histogram->GetMaximum();
        }
        else {
            histogram->Draw("HIST SAME");
            if (histogram->GetMaximum() > max) {
                max = histogram->GetMaximum();
            }
        }

        std::vector<std::string> filePathSplit;
        std::stringstream ss(filePaths.at(i));
        std::string part;
        while(!ss.eof()) {
            getline(ss, part, '/');
            filePathSplit.push_back(part);
        }

        std::string legendName = filePathSplit[filePathSplit.size() - 1] + "/" + histNames.at(i);
        legend->AddEntry(histogram, legendName.c_str(), "L");
        legend->Draw();
        canvas->Update();

    }

    TH1 *tempHist = (TH1*)canvas->FindObject(histNames.at(0).c_str());
    tempHist->GetYaxis()->SetRangeUser(0,1.1*max);

    canvas->Update();
    return(canvas);
}

void superimpose() {

    //Change variables here
    TFile* outFile = TFile::Open("../gep/run/superimposedHists.root", "RECREATE");

    std::vector<string> hists1 = {"h_recoTau_ptLeading_rate", "h_recoTau_ptLeading_rate", "h_recoTau_ptLeading_rate"};
    std::vector<string> files1 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root" };

   std::vector<string> hists2 = {"h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_noCut_pt", "h_truthTau_triggerEfficiency_noCut_pt"};
std::vector<string> files2 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists3 = {"h_truthTauIsolation_CA", "h_truthTauIsolation_CA", "h_truthTauIsolation_CA"};
std::vector<string> files3 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists4 = {"h_matchedRecoTauIsolation_CA", "h_matchedRecoTauIsolation_CA", "h_matchedRecoTauIsolation_CA"};
std::vector<string> files4 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists5 = {"h_recoTau_phi", "h_recoTau_phi", "h_recoTau_phi"};
std::vector<string> files5 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists6 = {"h_recoTau_eta", "h_recoTau_eta", "h_recoTau_eta"};
std::vector<string> files6 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists7 = {"h_recoTau_pt", "h_recoTau_pt", "h_recoTau_pt"};
std::vector<string> files7 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists8 = {"h_truthTau_phi", "h_truthTau_phi", "h_truthTau_phi"};
std::vector<string> files8 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists9 = {"h_truthTau_eta", "h_truthTau_eta", "h_truthTau_eta"};
std::vector<string> files9 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};

std::vector<string> hists10 = {"h_truthTau_pt", "h_truthTau_pt", "h_truthTau_pt"};
std::vector<string> files10 = {"../gep/run/outputHists28.root", "../gep/run/outputHists29.root", "../gep/run/outputHists30.root"};
/*
    std::vector<string> hists2 = {"h_recoTau_eta", "h_recoTau_eta", "h_recoTau_eta", "h_recoTau_eta"};
    std::vector<string> files2 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists3 = {"h_recoTau_phi", "h_recoTau_phi", "h_recoTau_phi", "h_recoTau_phi"};
    std::vector<string> files3 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists4 = {"h_ptFinalCalib", "h_ptFinalCalib", "h_ptFinalCalib", "h_ptFinalCalib"};
    std::vector<string> files4 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists5 = {"h_recoTau_nAllTracks", "h_recoTau_nAllTracks", "h_recoTau_nAllTracks", "h_recoTau_nAllTracks"};
    std::vector<string> files5 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists6 = {"h_nTracksCharged", "h_nTracksCharged", "h_nTracksCharged", "h_nTracksCharged"};
    std::vector<string> files6 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists7 = {"h_nTracksIsolation", "h_nTracksIsolation","h_nTracksIsolation", "h_nTracksIsolation"};
    std::vector<string> files7 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists8 = {"h_truthTau_pt", "h_truthTau_pt", "h_truthTau_pt", "h_truthTau_pt"};
    std::vector<string> files8 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists9 = {"h_truthTau_eta", "h_truthTau_eta", "h_truthTau_eta", "h_truthTau_eta"};
    std::vector<string> files9 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists10 = {"h_truthTau_phi", "h_truthTau_phi", "h_truthTau_phi", "h_truthTau_phi"};
    std::vector<string> files10 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists11 = {"h_recoTau_nTaus", "h_recoTau_nTaus", "h_recoTau_nTaus", "h_recoTau_nTaus"};
    std::vector<string> files11 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };

    std::vector<string> hists12 = {"h_truthTau_nTaus", "h_truthTau_nTaus", "h_truthTau_nTaus", "h_truthTau_nTaus"};
    std::vector<string> files12 = {"../gep/run/outputHists28.root", "../gep/run/outputHists30.root" };
*/
    /*std::vector<string> hists1 = {"h_recoTau_pt", "h_recoTau_pt"};
    std::vector<string> files1 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists2 = {"h_recoTau_pt", "h_recoTau_unmatchedpt"};
    std::vector<string> files2 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists3 = {"h_recoTau_eta", "h_recoTau_eta"};
    std::vector<string> files3 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists4 = {"h_recoTau_phi", "h_recoTau_phi"};
    std::vector<string> files4 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists5 = {"h_recoTau_pt", "h_recoTau_matchedpt"};
    std::vector<string> files5 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists6 = {"h_recoTau_nearestDr", "h_recoTau_nearestDr"};
    std::vector<string> files6 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};*/

    /*std::vector<string> hists7 = {"h_recoTau_pt_0-2eta", "h_recoTau_pt_0-2eta"};
    std::vector<string> files7 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists8 = {"h_recoTau_pt_0-2eta", "h_recoTau_unmatchedpt_0-2eta"};
    std::vector<string> files8 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists9 = {"h_recoTau_pt_2-25eta", "h_recoTau_pt_2-25eta"};
    std::vector<string> files9 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists10 = {"h_recoTau_pt_2-25eta", "h_recoTau_unmatchedpt_2-25eta"};
    std::vector<string> files10 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists11 = {"h_recoTau_pt_25-infeta", "h_recoTau_pt_25-infeta"};
    std::vector<string> files11 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists12 = {"h_recoTau_pt_25-infeta", "h_recoTau_unmatchedpt_25-infeta"};
    std::vector<string> files12 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists13 = {"h_recoTau_et", "h_recoTau_et"};
    std::vector<string> files13 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists14 = {"h_recoTau_et", "h_recoTau_unmatchedet"};
    std::vector<string> files14 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists15 = {"h_recoTau_et_0-2eta", "h_recoTau_et_0-2eta"};
    std::vector<string> files15 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists16 = {"h_recoTau_et_0-2eta", "h_recoTau_unmatchedet_0-2eta"};
    std::vector<string> files16 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists17 = {"h_recoTau_et_2-25eta", "h_recoTau_et_2-25eta"};
    std::vector<string> files17 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists18 = {"h_recoTau_et_2-25eta", "h_recoTau_unmatchedet_2-25eta"};
    std::vector<string> files18 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists19 = {"h_recoTau_et_25-infeta", "h_recoTau_et_25-infeta"};
    std::vector<string> files19 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists20 = {"h_recoTau_et_25-infeta", "h_recoTau_unmatchedet_25-infeta"};
    std::vector<string> files20 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};*/

    /*std::vector<string> hists17 = {"h_ptFinalCalib", "h_ptFinalCalib"};
    std::vector<string> files17 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists18 = {"h_nTracksIsolation", "h_nTracksIsolation"};
    std::vector<string> files18 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists19 = {"h_nTracksCharged", "h_nTracksCharged"};
    std::vector<string> files19 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};

    std::vector<string> hists20 = {"h_nPi0s", "h_nPi0s"};
    std::vector<string> files20 = {"../gep/run/tautaugridOutput.root", "../gep/run/zTauTaugridOutput.root"};*/

    std::vector<TCanvas*> canvasVec = {superimpose_hists(files1, hists1, "1"), superimpose_hists(files2, hists2, "2"), superimpose_hists(files3, hists3, "3"), superimpose_hists(files4, hists4, "4")
    , superimpose_hists(files5, hists5, "5"), superimpose_hists(files6, hists6, "6"), superimpose_hists(files7, hists7, "7"), superimpose_hists(files8, hists8, "8"), superimpose_hists(files9, hists9, "9"), 
    superimpose_hists(files10, hists10, "10"), /*superimpose_hists(files11, hists11, "11"), superimpose_hists(files12, hists12, "12"), superimpose_hists(files13, hists13, "13"), superimpose_hists(files14, hists14, "14"), 
    superimpose_hists(files15, hists15, "15"), superimpose_hists(files16, hists16, "16")*//*, superimpose_hists(files17, hists17, "17"), superimpose_hists(files18, hists18, "18"), 
    superimpose_hists(files19, hists19, "19"), superimpose_hists(files20, hists20, "20")*/};

    for(TCanvas* canvas : canvasVec) {
        outFile->WriteObject(canvas, canvas->GetName());
    }

    outFile->Close();
}
