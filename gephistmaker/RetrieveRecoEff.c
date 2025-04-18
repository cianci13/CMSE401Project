auto RetrieveRecoEff(vector<vector<TruthTau>> *truthTaus, vector<vector<RecoTau>> *recoTaus) {
  //Clear vectors and set vars
  vector<float> m_truthTau_indivPt = {};
  vector<float> m_recoTau_indivPt = {};
  vector<float> m_truthTau_twoMatchedPt = {};
  vector<float> m_recoTau_twoMatchedPt = {};
  vector<float> m_recoTau_twoMatchedUnchangedPt = {};
  vector<float> m_truthTau_twoMatchedEta = {};
  vector<float> m_recoTau_twoMatchedEta = {};
  vector<float> m_truthTau_twoMatchedE = {};
  vector<float> m_recoTau_twoMatchedE = {};
  vector<float> m_recoTau_indivInvMass = {};
  vector<float> m_truthTau_indivInvMass = {};
  vector<float> m_recoTau_unmatchedpt = {};
  vector<float> m_recoTau_unmatchedeta = {};
  vector<float> m_recoTau_unmatchedphi = {};
  vector<float> m_recoTau_unmatchedE = {};
  vector<float> m_recoTau_unmatchedM = {};
  vector<float> m_truthTau_unmatchedpt = {};
  vector<float> m_truthTau_unmatchedeta = {};
  vector<float> m_truthTau_unmatchedphi = {};
  vector<float> m_truthTau_unmatchedE = {};
  vector<float> m_truthTau_unmatchedM = {};
  vector<float> m_recoTau_matchedpt = {};
  vector<float> m_truthTau_ptWithCut = {};
  vector<float> m_truthTau_matchedpt = {};
  vector<float> m_truthTau_matchedInvMass = {};
  vector<float> m_recoTau_matchedInvMass = {};
  vector<float> m_invMassRatio = {};
  vector<float> m_ptRatio = {};
  vector<float> m_eRatio = {};
  vector<float> m_nMatchedTaus = {};
  vector<float> m_minDR = {};
  vector<float> m_nextClosestDR = {};

  vector<RecoTau> eventSpecificMatchedTaus; 
  vector<double> tempDR = {};
  vector<TruthTau> matchedTruth = {};
  vector<TruthTau> tempmatchedTruth = {};
  vector<RecoTau> matchedReco = {};
  vector<RecoTau> tempmatchedReco = {};
  vector<vector<RecoTau>> m_recoTau_matchedTaus = {}; 
  vector<vector<RecoTau>> m_recoTau_unmatchedTaus = {}; 
  
  //Event loop - over truths
  int nEvent = truthTaus->size(); 
  #pragma omp parallel
  {
  #pragma omp for
  for (int n = 0; n < nEvent; n++) {
  if (printProgress) printf("\rMatching reco to truth tau: %i/%i (%.1f%%)", n+1, nEvent, 100.*(n+1)/nEvent); 
  vector<RecoTau> matchedRecoTaus = {}; 
  vector<RecoTau> unmatchedRecoTaus = {}; 
  int nTaus = 0;
  bool eventStarted = false;
  m_truthTau_indivPt.clear();
  m_recoTau_indivPt.clear();
  m_truthTau_twoMatchedPt.clear();
  m_recoTau_twoMatchedPt.clear();
  m_recoTau_twoMatchedUnchangedPt.clear();
  m_truthTau_twoMatchedEta.clear();
  m_recoTau_twoMatchedEta.clear();
  m_truthTau_twoMatchedE.clear();
  m_recoTau_twoMatchedE.clear();
  m_recoTau_indivInvMass.clear();
  m_truthTau_indivInvMass.clear();
  m_recoTau_unmatchedpt.clear();
  m_recoTau_unmatchedeta.clear();
  m_recoTau_unmatchedphi.clear();
  m_recoTau_unmatchedE.clear();
  m_recoTau_unmatchedM.clear();
  m_truthTau_unmatchedpt.clear();
  m_truthTau_unmatchedeta.clear();
  m_truthTau_unmatchedphi.clear();
  m_truthTau_unmatchedE.clear();
  m_truthTau_unmatchedM.clear();
  m_recoTau_matchedpt.clear();
  m_truthTau_ptWithCut.clear();
  m_truthTau_matchedpt.clear();
  m_truthTau_matchedInvMass.clear();
  m_recoTau_matchedInvMass.clear();
  m_invMassRatio.clear();
  m_ptRatio.clear();
  m_eRatio.clear();
  m_nMatchedTaus.clear();
  m_minDR.clear();
  m_nextClosestDR.clear();

  tempDR.clear();
  matchedTruth.clear();
  tempmatchedTruth.clear();
  matchedReco.clear();
  tempmatchedReco.clear();
  eventSpecificMatchedTaus.clear(); 

  int nTruthTau = truthTaus->at(n).size(); 
  for (int j = 0; j < nTruthTau; j++) {
	TruthTau tau = truthTaus->at(n).at(j); 
    tempmatchedTruth.clear();
    tempmatchedReco.clear();
    //Checks for valid truth Taus
    if (abs(tau.eta) < 2.5) {
	if(tau.isHadronic) {
          eventStarted = true;
          m_truthTau_ptWithCut.push_back(tau.pt);
	  tempDR.clear();
	  //Reco Tau Loop
	  int nRecoTau = recoTaus->at(n).size(); 
	  for (int k = 0; k < nRecoTau; k++) {
		RecoTau recoTau = recoTaus->at(n).at(k); 
	    TLorentzVector* recoTauVec = new TLorentzVector();
	    recoTauVec->SetPtEtaPhiM(recoTau.pt, recoTau.eta, recoTau.phi, recoTau.m);
	    TLorentzVector recoTauVec1 = *recoTauVec;
            /*if(recoTauVec->Pt() < 10000) {
          	recoTauVec1 *= 1 / 0.3776;
       	    }
            else if(recoTauVec->Pt() < 20000) {
          	recoTauVec1 *= 1 / 0.7462;
            }
            else if(recoTauVec->Pt() < 30000) {
          	recoTauVec1 *= 1 / 0.8843;
            }
            else if(recoTauVec->Pt() < 40000) {
          	recoTauVec1 *= 1 / 0.9848;
       	    }
            else if(recoTauVec->Pt() < 50000) {
          	recoTauVec1 *= 1 / 1.075;
      	    }
       	    else {
          	recoTauVec1 *= 1 / 1.107;
            }*/
	    bool alreadyMatched = false;
            //Check if truth has already been matched
	    for(TruthTau part : matchedTruth) {
                    if(abs(part.pt -  tau.pt) < 1e-6) {
                        alreadyMatched = true;
                    }
            } 
	    if(!alreadyMatched) {   
	    tempDR.push_back(tau.p4.DeltaR(recoTauVec1));
	    //If within dR, keep, and remove any corresponding unmatched entry 
	    if(tau.p4.DeltaR(recoTauVec1) <= 0.2) {
		if(!alreadyMatched) {
		    tempmatchedTruth.push_back(tau);
		    tempmatchedReco.push_back(recoTau);
		    /*for(unsigned int j=0; j < m_recoTau_unmatchedpt.size(); j++) {
			if(abs(m_recoTau_unmatchedpt.at(j) - recoTauVec1.Pt()) < 1e-6) {
			m_recoTau_unmatchedpt.erase(m_recoTau_unmatchedpt.begin() + j);
                   	m_recoTau_unmatchedeta.erase(m_recoTau_unmatchedeta.begin() + j);
                   	m_recoTau_unmatchedphi.erase(m_recoTau_unmatchedphi.begin() + j);
                   	m_recoTau_unmatchedM.erase(m_recoTau_unmatchedM.begin() + j);
                   	m_recoTau_unmatchedE.erase(m_recoTau_unmatchedE.begin() + j);    
			auto it = std::find(unmatchedRecoTaus.begin(), unmatchedRecoTaus.end(), recoTau);
			if(it != unmatchedRecoTaus.end()) {
			    unmatchedRecoTaus.erase(it);
			}
 			}
		    }*/
			float minDistance = 50.0;
			for(int k2 = 0; k2 < nRecoTau; k2++) {
			RecoTau recoTau2 = recoTaus->at(n).at(k2); 
			TLorentzVector* recoTauVecTempNew = new TLorentzVector();
            		recoTauVecTempNew->SetPtEtaPhiM(recoTau2.pt, recoTau2.eta, recoTau2.phi, recoTau2.m);
            		TLorentzVector recoTauVecNew = *recoTauVecTempNew;
  			/*if(recoTauVecTempNew->Pt() < 10000) {
                	recoTauVecNew *= 1 / 0.3776;
            		}
            		else if(recoTauVecTempNew->Pt() < 20000) {
                	recoTauVecNew *= 1 / 0.7462;
            		}
            		else if(recoTauVecTempNew->Pt() < 30000) {
                	recoTauVecNew *= 1 / 0.8843;
            		}
            		else if(recoTauVecTempNew->Pt() < 40000) {
                	recoTauVecNew *= 1 / 0.9848;
           		}
           		else if(recoTauVecTempNew->Pt() < 50000) {
                	recoTauVecNew *= 1 / 1.075;
           		}
            		else {
                	recoTauVecNew *= 1 / 1.107;
           		}*/
			if(!(abs(recoTauVecNew.Pt() - recoTauVec1.Pt()) < 1e-6)) {
			    if(tau.p4.DeltaR(recoTauVecNew) < minDistance) {
				minDistance = tau.p4.DeltaR(recoTauVecNew);
			    }
			}
			}
			m_nextClosestDR.push_back(minDistance);
	        }
            }
	    /*else {
	       //Else, unmatched Reco tau 
	       bool found = false;
	       for(float pt : m_recoTau_unmatchedpt) {
		   if(abs(pt - recoTauVec1.Pt())< 1e-6) {
			found = true;
		   }
	       }
	       if(!found) {
                   unmatchedRecoTaus.push_back(recoTau);
		   m_recoTau_unmatchedpt.push_back(recoTauVec1.Pt());
		   m_recoTau_unmatchedeta.push_back(recoTauVec1.Eta());
		   m_recoTau_unmatchedphi.push_back(recoTauVec1.Phi());
	       	   m_recoTau_unmatchedM.push_back(recoTauVec1.M());
		   m_recoTau_unmatchedE.push_back(recoTauVec1.E());
		}
	    }*/
	    }
	    delete recoTauVec;
	    
	  }
	   //Adding minDR
	   if(tempDR.size() > 0) {
                std::sort(tempDR.begin(), tempDR.end());
                m_minDR.push_back(tempDR.at(0));
            }
          //Getting the "correct" recoTau of possible candidates
	  if(tempmatchedTruth.size() > 0) {
    	    float maxPt = 0.0;
    	    TruthTau toKeep = tempmatchedTruth.at(0);
	    RecoTau toKeep2;
	    int count = 0;
    	    for(RecoTau tauPart : tempmatchedReco) {
	      double tempPt = tauPart.pt;
              //Correcting (again). This cannot be done to a const xAOD::TruthTau_v3.
	      /*if(tauPart.pt < 10000) {
                tempPt *= 1 / 0.3776;
              }
              else if(tauPart.pt < 20000) {
                tempPt  *= 1 / 0.7462;
              }
              else if(tauPart.pt < 30000) {
                tempPt *= 1 / 0.8843;
              }
              else if(tauPart.pt < 40000) {
                tempPt *= 1 / 0.9848;
              }
              else if(tauPart.pt < 50000) {
                tempPt *= 1 / 1.075;
              }
              else {
                tempPt *= 1 / 1.107;
              }*/
	      if(abs(tempPt - tempmatchedTruth.at(count).pt) < maxPt) {
	        maxPt = abs(tempPt - tempmatchedTruth.at(count).pt);
	        toKeep = tempmatchedTruth.at(count);
	        toKeep2 = tauPart;
	      }
	      count++;
            }
	    if (maxPt == 0.0) {
                toKeep = tempmatchedTruth.at(0);
                toKeep2 = tempmatchedReco.at(0);
            }
            //Adds unmatched recos from the candidates
	    /*for(RecoTau part : tempmatchedReco) {
		if(!(abs(toKeep2.pt - part.pt) < 1e-6)) {
		    m_recoTau_unmatchedpt.push_back(part.pt);
		    m_recoTau_unmatchedeta.push_back(part.eta);
		    m_recoTau_unmatchedphi.push_back(part.phi);
		    m_recoTau_unmatchedE.push_back(part.p4.E());
		    m_recoTau_unmatchedM.push_back(part.m);
		}
	    }*/
		toKeep2.matchedTruthTau = toKeep; 
        matchedTruth.push_back(toKeep);
		eventSpecificMatchedTaus.push_back(toKeep2);
	    matchedRecoTaus.push_back(toKeep2);
	    matchedReco.push_back(toKeep2);
            m_truthTau_matchedpt.push_back(toKeep.pt);
	    m_recoTau_matchedpt.push_back(toKeep2.pt);
	    nTaus++;
          }
          //unmatched truth setters
	  else {
	    m_truthTau_unmatchedpt.push_back(tau.pt);
 	    m_truthTau_unmatchedeta.push_back(tau.eta);
	    m_truthTau_unmatchedphi.push_back(tau.phi);
	    m_truthTau_unmatchedE.push_back(tau.p4.E());
	    m_truthTau_unmatchedM.push_back(tau.p4.M());	    
	  }
	}
     }
  }  
  for(auto recoTau : recoTaus->at(n)) {
    bool matched = false;
    for(const auto recoTau2 : eventSpecificMatchedTaus) {
      if(recoTau == recoTau2) {
        matched = true;
        //std::cout << "cut 1 tau" << std::endl;
      }
    }
    if(!matched) {
        float pt = recoTau.pt;
        float phi = recoTau.phi;
        float eta = recoTau.eta;
		    float m = recoTau.m;
        /*
        if(pt < 10000) {
          	pt *= 1 / 0.3776;
            phi *= 1 / 0.3776;
            eta *= 1 / 0.3776;
            m *= 1 / 0.3776;
            e *= 1 / 0.3776;
       	    }
            else if(pt < 20000) {
          	pt *= 1 / 0.7462;
            phi *= 1 / 0.7462;
            eta *= 1 / 0.7462;
            m *= 1 / 0.7462;
            e *= 1 / 0.7462;
            }
            else if(pt < 30000) {
          	pt *= 1 / 0.8843;
            phi *= 1 / 0.8843;
            eta *= 1 / 0.8843;
            m *= 1 / 0.8843;
            e *= 1 / 0.8843;
            }
            else if(pt < 40000) {
          	pt *= 1 / 0.9848;
            phi *= 1 / 0.9848;
            eta *= 1 / 0.9848;
            m *= 1 / 0.9848;
            e *= 1 / 0.9848;
       	    }
            else if(pt < 50000) {
          	pt *= 1 / 1.075;
            phi *= 1 / 1.075;
            eta *= 1 / 1.075;
            m *= 1 / 1.075;
            e *= 1 / 1.075;
      	    }
       	    else {
          	pt *= 1 / 1.107;
            phi *= 1 / 1.107;
            eta *= 1 / 1.107;
            m *= 1 / 1.107;
            e *= 1 / 1.107;
            }*/
      unmatchedRecoTaus.push_back(recoTau);
      m_recoTau_unmatchedpt.push_back(pt);
		  m_recoTau_unmatchedeta.push_back(eta);
		  m_recoTau_unmatchedphi.push_back(phi);
  	  m_recoTau_unmatchedM.push_back(m);
    }
  }
  /*if(m_recoTau_unmatchedpt.size() != recoTaus.size() - eventSpecificMatchedTaus.size()) {
    std::cout << "values do not match, expected " << recoTaus.size() - eventSpecificMatchedTaus.size() << " got " << m_recoTau_unmatchedpt.size() << std::endl;
  }*/
  m_recoTau_matchedTaus.push_back(matchedRecoTaus); 
  m_recoTau_unmatchedTaus.push_back(unmatchedRecoTaus); 
  }
  }
  if (printProgress) printf("\n"); 
  struct result {vector<vector<RecoTau>> v0; vector<vector<RecoTau>> v1;}; 
  return result {m_recoTau_matchedTaus, m_recoTau_unmatchedTaus}; 
}
