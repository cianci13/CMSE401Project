void convert_hist() {
   string dir = "/msu/data/t3work13/xinfei/tmp/atlas/gep/"; 
   string hist_file_name = dir + "myhists_test.root"; 
   string outname = dir + "myhists.pdf"; 

   TFile *f1 = TFile::Open(hist_file_name.c_str()); 
   TIter keyList(f1->GetListOfKeys());
   TKey *key;
   TCanvas c1;

   c1.Print((outname + string("[")).c_str());
   while ((key = (TKey*)keyList())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TH1")) continue;
      TH1F *h = (TH1F*)key->ReadObj();
      gStyle->SetOptStat(0);
      TString hname = key->GetName(); 
      h->SetTitle(hname); 
      if (hname.Contains("Efficiency")){
	      h->Draw("pl"); 
	      h->SetMarkerColor(kBlue); 
	      h->SetMarkerStyle(20);
      } else if (cl->InheritsFrom("TH2")){
	 h->Draw("hist"); 
      } else {
         h->Scale(1./(h->Integral()+1e-5)); 
	 h->SetMinimum(0); 
         h->Draw("hist");
      }
         c1.Print(outname.c_str()); 
   }
   c1.Print((outname + string("]")).c_str());
}
