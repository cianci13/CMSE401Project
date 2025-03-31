#include <AsgTools/MessageCheck.h>
#include "TrigL0GepPerf/GepTauAlg.h"
#include "CaloInterface/ICalorimeterNoiseTool.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertex.h"
#include "CaloDetDescr/CaloDetDescrManager.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterAuxContainer.h"
#include "xAODCaloEvent/CaloCluster.h"
#include "xAODJet/JetContainer.h"

//adapted from eFEX tau trigger https://gitlab.cern.ch/atlas/athena/-/blob/master/Trigger/TrigT1/TrigT1CaloFexPerf/src/EFexTauAlgorithm.cxx

GepTauAlg::GepTauAlg( const std::string& name, ISvcLocator* pSvcLocator ) : 
  AthAnalysisAlgorithm( name, pSvcLocator ),
  m_tauAlg ("TauAlg"),
  m_noiseTool("CalorimeterNoiseTool/noiseTool", this)
{
	declareProperty("TauAlg",m_tauAlg,"tau label");
   declareProperty("CaloNoiseTool", m_noiseTool, "Tool Handle for noise tool");
   declareProperty("GetEventInfo", m_getEventInfo);
   declareProperty("TowerEtCut", m_towerEtCut=1000, "Minimum tower Et (in MeV)" );
   declareProperty("SeedEtCut", m_seedEtCut=4000, "Minimum seed Et (in MeV)" );
}

GepTauAlg::~GepTauAlg() {
  
   delete cellEta;
	delete cellPhi;
	delete cellEt;
	delete cellLayer;
	delete truthTauEt;
   delete truthTauEta;
   delete truthTauPhi;
   delete towerEt;
   delete towerEta_index;
   delete towerPhi_index;
   delete seedet;
   delete seedEta;
   delete seedPhi;
   delete recon_tau_ET;
	delete fCoreInner;
	delete fCoreOuter;
	delete fCore;
	delete clusteret;
	delete clusterEta;
	delete clusterPhi;
	delete clusterLayer;
	delete clusterSigma;
	
}

//check if the cell ID exists in the caloCellMap
StatusCode GepTauAlg::IDCheck(const std::map<unsigned int, Gep::CustomCaloCell> caloCellsMap, unsigned int cellID, int layer){
		
	if (cellID==0) ATH_MSG_INFO("cell ID is zero !" );
	if (cellID > 1000000000) ATH_MSG_INFO("10 digit cell id muber !");
	std::map<unsigned int, Gep::CustomCaloCell>::const_iterator itr;
	itr = caloCellsMap.find(cellID);
	if (itr == caloCellsMap.end()) {
		ATH_MSG_INFO("We failed---in-----with "<<cellID <<" in layer "<< layer);
	} else ATH_MSG_INFO("We succeeded");

	return StatusCode::SUCCESS;
}

//look at a small window around the seed cell and find a better seed cell (that has the largest Et)
StatusCode GepTauAlg::Recentering(const std::map<unsigned int, Gep::CustomCaloCell> caloCellsMap, Gep::CustomCaloCell &Original_seedCell, TH2D *cellMapEM, int offsetL, int offsetR, int sdx, int sdy ){
	//could get a zero cellID after the recentering process
	unsigned int tpsdLID;
	Gep::CustomCaloCell tpseedCell;
	int tmpEta;
	int tmpPhi;
	int tmpet = Original_seedCell.et;
	//readjusting the seed cell location by looking at the surrounding cells
	for (int a=-offsetL; a<offsetR+1; ++a){
		for (int b=-offsetL; b<offsetR+1; ++b){
			tmpEta = sdx+a;
			tmpPhi = sdy+b;
			tpsdLID = cellMapEM ->GetBinContent(tmpEta, tmpPhi);
			if((tpsdLID!=0)&&(tpsdLID<1000000000)) {
				
				tpseedCell = caloCellsMap.at(tpsdLID);
				if ((tpseedCell.et > 0) &&( tpseedCell.et> tmpet)) {
					
					tmpet = tpseedCell.et;
					Original_seedCell = tpseedCell;
				}
				
			}
		}
	}
	return StatusCode::SUCCESS;

}

//given a seed cell, Calculate the cluster Et in a window with the size of window_w*2 and window_h*2, at a certain layer 
StatusCode GepTauAlg::Clustering(const std::map<unsigned int, Gep::CustomCaloCell> caloCellsMap, Gep::CustomCaloCell seedCell, double &emtauET, float window_w, float window_h, unsigned int layer){
	float deltaE=0;
	float deltaP=0;
	std::vector<unsigned int> all_added_cells;
	Gep::CustomCaloCell center;// = caloCellsMap.at(centerID);
	std::vector<unsigned int> neighbour; 
	std::vector<unsigned int> tmp_id_list;
	std::vector<unsigned int> tmp_list;
	bool Stop_Sign = false;
	tmp_id_list.push_back(seedCell.id);
	all_added_cells.push_back(seedCell.id);
	
	if (seedCell.et>0) {emtauET+= seedCell.et;}
	int ct=0;
	
		while (1){
			tmp_list.clear();
		
			for (const auto & tl: tmp_id_list){
				Gep::CustomCaloCell shell = caloCellsMap.at(tl);
				deltaE = abs(shell.eta - seedCell.eta);
				deltaP = abs(abs(abs(shell.phi - seedCell.phi)-M_PI)-M_PI);
				if((abs(deltaE) >= window_w) && (abs(deltaP) >= window_h)) {Stop_Sign=true;
					break; 
				}
			}
		
			if(Stop_Sign) break;
			for (const auto & nb_id: tmp_id_list) {
				center = caloCellsMap.at(nb_id);
			
				neighbour = center.neighbours;
				for (const auto & cn: neighbour ){
					Gep::CustomCaloCell nb = caloCellsMap.at(cn);
					if (nb.sampling != layer) continue;
				
					if (std::find(all_added_cells.begin(), all_added_cells.end(), nb.id) != all_added_cells.end()) continue;
					else {
						all_added_cells.push_back(nb.id);
						tmp_list.push_back(nb.id);
						
						if((abs(nb.eta - seedCell.eta) < window_w) && (abs(abs(abs(nb.phi - seedCell.phi)-M_PI)-M_PI) < window_h)) {
						  	
							clusteret->push_back(nb.et);
							clusterEta->push_back(nb.eta);
							clusterPhi->push_back(nb.phi);
							clusterLayer->push_back(nb.sampling);
							clusterSigma->push_back(nb.sigma);
							if (nb.et <= 0) continue;
							if (nb.sigma <2) continue;
							emtauET+=nb.et;
							
							}
					}
				}
			}//end of center list loop
			tmp_id_list=tmp_list;
			ct++;
		}
	
		
	return StatusCode::SUCCESS;
}

// $$$$$$$$$$$$$$$$$$
// Initialize
// $$$$$$$$$$$$$$$$$$

StatusCode GepTauAlg::initialize() {
	
	ATH_MSG_INFO ("Initializing " << name() << "...");
  
   // Noise tool
   if(m_noiseTool.retrieve().isFailure()){
   	ATH_MSG_ERROR("Unable to find noise tool");
      return StatusCode::FAILURE;
   }
   else {
      ATH_MSG_INFO("Noise tool retrieved");
   }
   // pass noise tool to CaloCellsHandler 
   m_cch.passNoiseTool(m_noiseTool);
  
   // CaloIndentifier
   CHECK( detStore()->retrieve (m_ccIdHelper, "CaloCell_ID") );
   // pass caloIndentifier to CaloCellsHandler
   m_cch.passCaloCellIDTool(m_ccIdHelper);

   ANA_MSG_INFO("tau algo name is " <<  m_tauAlg);
   ANA_MSG_INFO("The tower Et cut is "<< m_towerEtCut);
   ANA_MSG_INFO("The seed Et cut is "<< m_seedEtCut);
   
	// em0: 0.025 * 0.1
	// em1: 0.003125 * 0.1  //0.0032 * 0.1
	// em2: 0.025 * 0.025
	// em3: 0.05 * 0.025
	// em4: 0.025 * 0.1
	// em7: 0.050 * 0.025
	cellMapEM0 = new TH2D("SupercellMapEM0", "map of EM0", 112, -1.4, 1.4, 64,  -M_PI, M_PI);
	cellMapEM1 = new TH2D("SupercellMapEM1", "map of EM1", 896, -1.4, 1.4, 64, -M_PI, M_PI);
	cellMapEM2 = new TH2D("SupercellMapEM2", "map of EM2", 112, -1.4, 1.4, 256, -M_PI, M_PI);
	cellMapEM3 = new TH2D("SupercellMapEM3", "map of EM3", 56, -1.4, 1.4, 256, -M_PI, M_PI);
	cellMapEM4 = new TH2D("SupercellMapEM4", "map of EM4", 112, -1.4, 1.4, 64,  -M_PI, M_PI);
	cellMapEM7 = new TH2D("SupercellMapEM7", "map of EM7", 56, -1.4, 1.4, 256, -M_PI, M_PI);
   mytree = new TTree ("tautuple","tautuple");
   	  
	mytree->Branch ("truthTauEt", &truthTauEt);
	mytree->Branch ("truthTauEta", &truthTauEta);
	mytree->Branch ("truthTauPhi", &truthTauPhi);
	mytree->Branch ("towerEt", &towerEt); //self constructed towers
	mytree->Branch ("towerEta_index", &towerEta_index);
	mytree->Branch ("towerPhi_index", &towerPhi_index);
	mytree->Branch ("seedet", &seedet);
	mytree->Branch ("seedEta", &seedEta);
	mytree->Branch ("seedPhi", &seedPhi);
	mytree->Branch ("recon_tau_ET", &recon_tau_ET);
	mytree->Branch ("fCoreInner", &fCoreInner);
	mytree->Branch ("fCoreOuter", &fCoreOuter);
	mytree->Branch ("fCore", &fCore);
	mytree->Branch ("eventNumber", &eventNumber);
	mytree->Branch ("clusteret", &clusteret);
	mytree->Branch ("clusterEta", &clusterEta);
	mytree->Branch ("clusterPhi", &clusterPhi);
	mytree->Branch ("clusterLayer", &clusterLayer);
	mytree->Branch ("clusterSigma", &clusterSigma);
	mytree->Branch ("cellEta", &cellEta);
	mytree->Branch ("cellPhi", &cellPhi);
	mytree->Branch ("cellEt", &cellEt);
	mytree->Branch ("cellLayer", &cellLayer);
	
	mytree->Branch ("bkg_leadJet", &bkg_leadJet);
	
	
   CHECK( histSvc()->regTree("/STREAM_TREE/tautuple",mytree) );
	   
   
  return StatusCode::SUCCESS;
}

// $$$$$$$$$$$$$$$$$$
// Execute
// $$$$$$$$$$$$$$$$$$

StatusCode GepTauAlg::execute() {  
   	
	// get event info
	if(m_getEventInfo){
		const xAOD::EventInfo* eventInfo = 0;
		CHECK( evtStore()->retrieve( eventInfo, "EventInfo" ) );
		eventNumber = eventInfo->eventNumber();
		runNumber = eventInfo->runNumber();
	}
	
	truthTauEt->clear();
	truthTauEta->clear();
	truthTauPhi->clear();
   towerEt->clear();
   towerEta_index->clear();
   towerPhi_index->clear();
   seedet->clear();
   seedEta->clear();
   seedPhi->clear();
   recon_tau_ET->clear();
	fCoreInner->clear();
	fCoreOuter->clear();
	fCore->clear();
	clusteret->clear();
	clusterEta->clear();
	clusterPhi->clear();
	clusterLayer->clear();
	clusterSigma->clear();
	cellEta->clear();
	cellPhi->clear();
	cellEt->clear();
	cellLayer->clear();
	
	TH2F CellMapTower("SupercellMapTWR", "Supercell map of TWR", 98, -4.9, 4.9, 64, -M_PI, M_PI);
   
   	
//******* retriving truth particles
	//TruthParticles (xAOD::TruthParticleAuxContainer_v1) [Truth]
	const xAOD::TruthParticleContainer *truth_particles = nullptr;
	CHECK (evtStore()->retrieve(truth_particles, "TruthParticles"));
		
	for (auto truth_particle : *truth_particles) {
		//picking out the taus
		if (abs(truth_particle->pdgId()) != 15) continue;
		//note not all truth particles have decay vertices, this statement "truth_particle->decayVtx()" can't
		//be called on all truth particles
		if (truth_particle->hasDecayVtx()){
			 const xAOD::TruthVertex *decayVtx = truth_particle->decayVtx();
			 double finalTauet=0, finalTaueta=0, finalTauphi=0;
			 bool Outgoing_tau = false;
			 
			 float TruthtauPt = truth_particle->pt();
			 //ATH_MSG_INFO("+----truth tau pt" << truth_particle->pt());
			 float TruthtauEta = truth_particle->eta();
			 float TruthtauPhi = truth_particle->phi();
			 TLorentzVector truthTau;
		    truthTau.SetPtEtaPhiM(TruthtauPt, TruthtauEta, TruthtauPhi, 1776);
			 //std::cout <<"The number of outgoing particles: "<<decayVtx->nOutgoingParticles()<<std::endl;  	
			 
			 	TLorentzVector neutrino;
				const xAOD::TruthParticle *Outparticle;
				//looping over outgoing particles
				for (unsigned int v = 0;  v < decayVtx->nOutgoingParticles(); ++v ) {
					Outparticle = decayVtx->outgoingParticle(v);
					//ATH_MSG_INFO("--OutPar id"<< Outparticle->pdgId() << ", and pt "<<Outparticle->pt() <<", status "<< Outparticle->status());
					if (abs(Outparticle->pdgId()) == 15) {
						Outgoing_tau = true;
						finalTauet=Outparticle->pt();
						finalTaueta=Outparticle->eta();
						finalTauphi=Outparticle->phi();
						ATH_MSG_INFO ("outgoing particle has taus !");
					//note, don't use outgoing particles with status =3, they don't add up for pt conservation
					} else if ((Outparticle->isNeutrino()) && (Outparticle->status()!=3) ){
						
						//std::cout  <<" "<< Outparticle->pt()<<" "<<Outparticle->eta()<< std::endl;
						neutrino.SetPtEtaPhiM(Outparticle->pt(),Outparticle->eta(), Outparticle->phi(), 0);
						//std::cout <<"neutrino " <<neutrino.Et() <<", "<<neutrino.Pt()<<", "<<neutrino.Eta()  <<std::endl;
					}
			}//end of outgoing particle loop
		
				
			//ATH_MSG_INFO ("whether have outgoing taus"<<Outgoing_tau);
			if (Outgoing_tau) continue;
			if (truth_particle->status()==3) continue;
			//std::cout <<"-------truth particle(d) is " <<truth_particle->pdgId()<< "pt "<< truth_particle->pt() <<std::endl;
			//std::cout <<"whether the truth particle has decay vertex: "<<truth_particle->hasDecayVtx() <<", status "<< truth_particle->status() <<std::endl;
			truthTauEt->push_back((truthTau-neutrino).Et());
			truthTauEta->push_back((truthTau-neutrino).Eta());	
			truthTauPhi->push_back((truthTau-neutrino).Phi());
			
			Outgoing_tau = false;
		}//if truth  has vertex
	}//end of truth particle loop

//**********Get jet information
//loop over the jets in the container
  const xAOD::JetContainer* jets = nullptr;
  ANA_CHECK (evtStore()->retrieve (jets, "AntiKt4EMPFlowJets"));
  
  int jetn=0;
  //bkg_leadJet=0;
  for (const xAOD::Jet* jet : *jets) {
  	if (jetn>0) break;
  	//std::cout<< jet->pt() * 0.001 <<std::endl; // GeV
  	bkg_leadJet = jet->pt() * 0.001;
  	jetn++;
  } // end for loop over jets
  
//************** end of jet information
	
//******** Get cell information
	const CaloCellContainer* cells = 0;
	CHECK( evtStore()->retrieve( cells, "AllCalo") );
	
	if(!m_cellsFilledOnce){ 

		m_cch.fillCellsInformation(cells);

		m_cellsFilledOnce = true;
	} else {
		m_cch.updateCellsInformation(cells);
	}
	
// ******** read cells and build cell ID maps
	const std::map<unsigned int, Gep::CustomCaloCell> caloCellsMap = m_cch.getCaloCellsMap();
    
   for (auto const& cell_itr : caloCellsMap) {
		
		Gep::CustomCaloCell celldata =  cell_itr.second;
		
		//build the map only against the first event
		if (globalCounter == 0) {
			if (celldata.sampling == 0){
				cellMapEM0->Fill (celldata.eta, celldata.phi, celldata.id);
				
			} else if ((celldata.sampling == 1) && (abs(celldata.eta)<1.4)) {
				cellMapEM1->Fill (celldata.eta, celldata.phi, celldata.id);
			} else if ((celldata.sampling == 2) && (abs(celldata.eta)<1.4)) {
				cellMapEM2->Fill (celldata.eta, celldata.phi, celldata.id);
			} else if (celldata.sampling == 3) {
				cellMapEM3->Fill (celldata.eta, celldata.phi, celldata.id);
			} else if (celldata.sampling == 4) {
				cellMapEM4->Fill (celldata.eta, celldata.phi, celldata.id);
			} else if (celldata.sampling == 7) {
				cellMapEM7->Fill (celldata.eta, celldata.phi, celldata.id);
			}
		
		}
		
		//filter out the bad cells and the cells with negative Et's
		if (celldata.isBadCell()==true) continue;
		if (celldata.sigma>2){
			cellEta->push_back(celldata.eta);
			cellPhi->push_back(celldata.phi);
			cellEt->push_back(celldata.et);
			cellLayer->push_back(celldata.sampling);
		}
		if (celldata.et<=0) continue;
		CellMapTower.Fill (celldata.eta, celldata.phi, celldata.et);
		
	
	}
	
// ********** Find local maxima
	std::vector<TLorentzVector> localMaxima;
	localMaxima.reserve(200);

	// X is eta, Y is phi
	for (int i = 0; i < CellMapTower.GetNbinsX(); i++) {
 	  for (int j = 0; j < CellMapTower.GetNbinsY(); j++) {
 	   	  	
 	  	double towerET = CellMapTower.GetBinContent(i + 1, j + 1);
 	  	//std::cout << "i: "<<i+1 <<" j: "<<j+1<< " tower Et" << towerET <<std::endl;
 	  	
 	  	towerEt->push_back(towerET);
		towerEta_index->push_back(i);
		towerPhi_index->push_back(j);
		
 	  	if (towerET < m_towerEtCut) continue;
 	  
 	   // Check if the current tower has the largest ET in this 3x3 window
		// Need to be careful with wrap-around in phi, unfortunately.
 		std::vector<double> binsAbove;
 		binsAbove.reserve(4);
 		std::vector<double> binsBelow;
 		binsBelow.reserve(4);
 		
 		// Handle wrap-around in phi
		 int aboveInPhi = j + 1;
		 if (j == CellMapTower.GetNbinsY() - 1)
			aboveInPhi = 0;
		 int belowInPhi = j - 1;
		 if (j == 0)
			belowInPhi = CellMapTower.GetNbinsY() - 1;

 		 // The convention here is arbitrary, but needs to be mirrored
		 // Take the cells in the next row in phi, and the one cell above in eta
		 binsAbove.push_back(CellMapTower.GetBinContent(i, aboveInPhi + 1));
		 binsAbove.push_back(CellMapTower.GetBinContent(i + 1, aboveInPhi + 1));
		 binsAbove.push_back(CellMapTower.GetBinContent(i + 2, aboveInPhi + 1));
		 binsAbove.push_back(CellMapTower.GetBinContent(i + 2, j + 1));

		 // Inversely so for the bins below
		 binsBelow.push_back(CellMapTower.GetBinContent(i, belowInPhi + 1));
		 binsBelow.push_back(CellMapTower.GetBinContent(i + 1, belowInPhi + 1));
		 binsBelow.push_back(CellMapTower.GetBinContent(i + 2, belowInPhi + 1));
		 binsBelow.push_back(CellMapTower.GetBinContent(i, j + 1));

		 bool isMax = true;

		 // Check if it is a local maximum
		 for (unsigned int k = 0; k < binsAbove.size(); k++)
		 {
			if ((towerET < binsAbove[k]) || (towerET <=0))
			   isMax = false;
		 }
		 for (unsigned int k = 0; k < binsBelow.size(); k++)
		 {
			if ((towerET <= binsBelow[k]) || (towerET <=0))
			   isMax = false;
		 }

		 if (isMax)
		 {
			TLorentzVector myMaximum;
			myMaximum.SetPtEtaPhiM(towerET, CellMapTower.GetXaxis()->GetBinCenter(i + 1), CellMapTower.GetYaxis()->GetBinCenter(j + 1), 0);
			localMaxima.push_back(myMaximum);
		 }
 	  }
 	}
 	
 // Loop over the local max's and build clusters around each one
	for (const auto &localMax: localMaxima ) {
		
		double SeedET = localMax.Et();
		double SeedEta = localMax.Eta();
		double SeedPhi = localMax.Phi();
	
		// no cells have eta larger than 2.5, check the sampling vs eta graph 
		if (std::abs(localMax.Eta()) > 1.3) continue;
		if (SeedET < m_seedEtCut) continue;
      
		seedet->push_back(SeedET);
		seedEta->push_back(SeedEta);
		seedPhi->push_back(SeedPhi);
	
		double em0tauET=0;
    	double em1tauET=0;
 		double em2tauET=0;
		double em3tauET=0;
 		double IsoInnerET=0;
 		double IsoOuterET=0;
 		double Oregon_tauET=0;
 		double tauIsolation;
 		
 		//****************
 		//building layer 2 clusters and calculate the FCore(isolation) variable
		int sd_x2 = cellMapEM2->GetXaxis()->FindFixBin(SeedEta);
		int sd_y2 = cellMapEM2->GetYaxis()->FindFixBin(SeedPhi);
		unsigned int sdL2ID = cellMapEM2 ->GetBinContent(sd_x2,sd_y2);
		//ATH_CHECK(IDCheck(caloCellsMap, sdL2ID, 2));
		if (sdL2ID!=0){
			Gep::CustomCaloCell seedCell2 = caloCellsMap.at(sdL2ID);
			ATH_CHECK(Recentering(caloCellsMap, seedCell2, cellMapEM2, 2, 2, sd_x2, sd_y2));
			
			SeedEta = seedCell2.eta;
			SeedPhi = seedCell2.phi;
			
			ATH_CHECK(Clustering(caloCellsMap, seedCell2 , em2tauET, 0.0625, 0.1, 2));
			//build inner sum for FCore on layer 2
			ATH_CHECK(Clustering(caloCellsMap, seedCell2 , IsoInnerET, 0.0375, 0.0625, 2));
			//build outer sum for FCore on layer 2 
			ATH_CHECK(Clustering(caloCellsMap, seedCell2 , IsoOuterET, 0.1375, 0.2125, 2));
			fCoreInner->push_back(IsoInnerET);
			fCoreOuter->push_back(IsoOuterET);
			tauIsolation = IsoInnerET/IsoOuterET;
			fCore->push_back(tauIsolation);
		}
 		
 		//****************
 		//building layer 0 clusters
		int sd_x = cellMapEM0->GetXaxis()->FindFixBin(SeedEta);
		int sd_y = cellMapEM0->GetYaxis()->FindFixBin(SeedPhi);
		unsigned int sdL0ID = cellMapEM0 ->GetBinContent(sd_x,sd_y);
		//ATH_CHECK(IDCheck(caloCellsMap, sdL0ID, 0));
		if (sdL0ID!=0){
 			Gep::CustomCaloCell seedCell0 = caloCellsMap.at(sdL0ID);
 			//ATH_CHECK(Recentering(caloCellsMap, seedCell0, cellMapEM0, 1, 1, sd_x, sd_y));			
 			ATH_CHECK(Clustering(caloCellsMap, seedCell0, em0tauET, 0.15, 0.1, 0));
		}
		
		//****************
		//building layer 1 clusters
		int sd_x1 = cellMapEM1->GetXaxis()->FindFixBin(SeedEta);
		int sd_y1 = cellMapEM1->GetYaxis()->FindFixBin(SeedPhi);
		unsigned int sdL1ID = cellMapEM1 ->GetBinContent(sd_x1,sd_y1);
		//ATH_CHECK(IDCheck(caloCellsMap, sdL1ID, 1));
		
		if ((sdL1ID!=0) && (sdL1ID<1000000000)){
 			Gep::CustomCaloCell seedCell1 = caloCellsMap.at(sdL1ID);
 
 			//ATH_CHECK(Recentering(caloCellsMap, seedCell1, cellMapEM1, 1, 1, sd_x1, sd_y1));
			ATH_CHECK(Clustering(caloCellsMap, seedCell1, em1tauET, 0.0625, 0.1, 1));	
 
		}
		//****************
		//building layer 3 clusters
		int sd_x3 = cellMapEM3->GetXaxis()->FindFixBin(SeedEta);
		int sd_y3 = cellMapEM3->GetYaxis()->FindFixBin(SeedPhi);
		unsigned int sdL3ID = cellMapEM3 ->GetBinContent(sd_x3,sd_y3);
		//ATH_CHECK(IDCheck(caloCellsMap, sdL3ID, 3));
		
		if (sdL3ID!=0){
 			
 			Gep::CustomCaloCell seedCell3 = caloCellsMap.at(sdL3ID);
 			//ATH_CHECK(Recentering(caloCellsMap, seedCell3, cellMapEM3, 2, 2, sd_x3, sd_y3));
 			ATH_CHECK(Clustering(caloCellsMap, seedCell3, em3tauET, 0.15, 0.1, 3));
		}
		
		Oregon_tauET = em0tauET + em1tauET + em2tauET + em3tauET;
		recon_tau_ET->push_back(Oregon_tauET);
    	//ATH_MSG_INFO("em0: "<<em0tauET<< ", em1: "<<em1tauET <<", em2: "<<em2tauET<<", em3: "<<em3tauET);
    	//ATH_MSG_INFO("Reconstructed tau Et"<< Oregon_tauET);
		//ATH_MSG_INFO(" IsoInnerET "<< IsoInnerET << " IsoOuterET " << IsoOuterET);
		//ATH_MSG_INFO("Fcore: "<< tauIsolation );
		clusterCt++;
		
	// Make trigger decision with recoEt and FCore
	// int TrigEtThreshold = 5000;
   // float TrigFcoreThreshold = 0.6;
		
	}//end of localMax loop
	
	mytree->Fill ();
  	globalCounter++;
	return StatusCode::SUCCESS;
}//end of execute 


StatusCode GepTauAlg::finalize() {  
  ATH_MSG_INFO ("finalizing " << name() << "...");
  return StatusCode::SUCCESS;
}
