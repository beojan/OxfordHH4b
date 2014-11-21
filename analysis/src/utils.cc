#include "utils.h"

// General settings for analysis and jet reconstruction
#include "settings.h"

#include "Pythia8/Pythia.h"


/*
This routine initializes Pythia8
with all the settings for the shower and underlying event
 */
void InitPythia(Pythia8::Pythia & pythiaRun, string eventfile){

  // Initialize random seed
  srand (time(NULL));
  std::cout<<"time = "<<time(NULL)<<std::endl;
  double random = double(rand())/RAND_MAX;
  std::cout<<"\n\n Random number I = "<<random<<"\n\n"<<std::endl;
  random = double(rand())/RAND_MAX;
  std::cout<<"\n\n Random number II = "<<random<<"\n\n"<<std::endl;
  
  // Random seed
  pythiaRun.readString("Random:setSeed = on");
  double random_seed_pythia = 100000 * double(rand())/RAND_MAX;
  ostringstream o;
  o<<"Random:seed = "<<int(random_seed_pythia);
  cout<<o.str()<<endl;
  pythiaRun.readString(o.str());

  // Initialize Les Houches Event File run. List initialization information.
  pythiaRun.readString("Beams:frameType = 4"); 
  
  // Shower settings
 
  // The shower is QCD only, no QED or weak effects included
  pythiaRun.readString("SpaceShower:QEDshowerByQ  = off"); // QED shower off
  pythiaRun.readString("SpaceShower:QEDshowerByL  = off"); // QED shower off
  pythiaRun.readString("TimeShower:QEDshowerByQ = off");  // QED off on ISR / quarks irradiate photons
  pythiaRun.readString("TimeShower:QEDshowerByL = off");  // QED off on ISR / leptons irradiate photons  
  pythiaRun.readString("TimeShower:QEDshowerByGamma = off");  // Allow photons to branch into lepton or quark pairs 
  // Initial and final state radiation activated
  pythiaRun.readString("PartonLevel:ISR = on");  // Shower on
  pythiaRun.readString("PartonLevel:FSR = on");  // Shower on
  
  // No hadronization
  pythiaRun.readString("HadronLevel:all = off"); // Of hadronization
 
  // For the time being no  UE or PU included
  pythiaRun.readString("PartonLevel:MPI = off"); // Off multiple interactions (UE) 
 
  // Higgs decays always into 4b
  // Need to correct by hand the xsecs for the BR(HH->4b) branching fraction
  pythiaRun.readString("25:onMode = off");
  pythiaRun.readString("25:onIfAll = 5 -5");

  // b quarks and do not decay
  // They are treated as stable particles in the detector
  pythiaRun.readString("5:mayDecay = no");
  pythiaRun.readString("-5:mayDecay = no");

  // Read the Les Houches Event File
  string ofile;
  ofile="Beams:LHEF = "+eventfile;
  pythiaRun.readString(ofile.c_str());

   // Main initialization
  pythiaRun.init();

  std::cout<<"\n Pythia8 Initialized \n "<<std::endl;
  
}


/*
This routine initializes Pythia8
with all the settings for the shower and underlying event
 */
void InitPythia_PartonLevel(Pythia8::Pythia & pythiaRun, string eventfile){

  // Initialize random seed
  srand (time(NULL));
  std::cout<<"time = "<<time(NULL)<<std::endl;
  double random = double(rand())/RAND_MAX;
  std::cout<<"\n\n Random number I = "<<random<<"\n\n"<<std::endl;
  random = double(rand())/RAND_MAX;
  std::cout<<"\n\n Random number II = "<<random<<"\n\n"<<std::endl;
  
  // Random seed
  pythiaRun.readString("Random:setSeed = on");
  double random_seed_pythia = 100000 * double(rand())/RAND_MAX;
  ostringstream o;
  o<<"Random:seed = "<<int(random_seed_pythia);
  cout<<o.str()<<endl;
  pythiaRun.readString(o.str());

  // Initialize Les Houches Event File run. List initialization information.
  pythiaRun.readString("Beams:frameType = 4"); 
  
  // Shower settings
 
  // No shower
  pythiaRun.readString("SpaceShower:QEDshowerByQ  = off"); // QED shower off
  pythiaRun.readString("SpaceShower:QEDshowerByL  = off"); // QED shower off
  pythiaRun.readString("TimeShower:QEDshowerByQ = off");  // QED off on ISR / quarks irradiate photons
  pythiaRun.readString("TimeShower:QEDshowerByL = off");  // QED off on ISR / leptons irradiate photons  
  pythiaRun.readString("TimeShower:QEDshowerByGamma = off");  // Allow photons to branch into lepton or quark pairs 

  
  // Initial and final state radiation deactivated
  pythiaRun.readString("PartonLevel:ISR = off");  // Shower on
  pythiaRun.readString("PartonLevel:FSR = off");  // Shower on
  
  // No hadronization
  pythiaRun.readString("HadronLevel:all = off"); // Of hadronization
 
  // For the time being no  UE or PU included
  pythiaRun.readString("PartonLevel:MI = off"); // Off multiple interactions (UE) 
 
  // Higgs decays always into 4b
  // Need to correct by hand the xsecs for the BR(HH->4b) branching fraction
  pythiaRun.readString("25:onMode = off");
  pythiaRun.readString("25:onIfAll = 5 -5");

  // b quarks and do not decay
  // They are treated as stable particles in the detector
  pythiaRun.readString("5:mayDecay = no");
  pythiaRun.readString("-5:mayDecay = no");

  // Read the Les Houches Event File
  string ofile;
  ofile="Beams:LHEF = "+eventfile;
  pythiaRun.readString(ofile.c_str());

   // Main initialization
  pythiaRun.init();

  std::cout<<"\n Pythia8 Initialized \n "<<std::endl;
  
}


/*
  Get the information on all final state particles
 */
void get_final_state_particles(Pythia8::Pythia & pythiaRun, finalState& particles){

  for (int i = 0; i < pythiaRun.event.size(); i++){
    
    // Initialization
    double px = 0;
    double py = 0;
    double pz =0;
    double E = 0;
    
    // Get PDG ID
    int particle_id = pythiaRun.event[i].id();
    
    // Get PDG chargeID (three times the real charge)
    int particle_charge = pythiaRun.event[i].chargeType();
    
    // Get particle status: in pythia8, status > 0 means final state particles
    int particle_status = pythiaRun.event[i].status();
    
    // Consider only final state particles
    if( particle_status <= 0 ) continue;
    
    // Get the particle kinematics
    px= pythiaRun.event[i].px();
    py= pythiaRun.event[i].py();
    pz= pythiaRun.event[i].pz();
    E= pythiaRun.event[i].e();
    
    // quarks and gluons
    // including b-quarks
    if(abs(particle_id)<6 || particle_id==21 ){
      // Set kinematics
      particles.push_back( fastjet::PseudoJet(px,py,pz,E) );
      // Set PDG ID
      particles.at(particles.size()-1).set_user_index(particle_id);
    }
    // beam remnants
    else if(particle_id > 2000 ){
      particles.push_back( fastjet::PseudoJet(px,py,pz,E) );
      particles.at(particles.size()-1).set_user_index(particle_id);
    }
    else{
      std::cout<<"Invalid particle ID = "<<particle_id<<std::endl;
      exit(-10);
    }
    
  } // End loop over particles in event
  
  // Verify final state four momenta
  Analysis::VerifyFourMomentum(particles);
}


// ----------------------------------------------------------------------------------
// Recluster with kt algorithm to obtain splitting scales
std::vector< double > SplittingScales( std::vector<fastjet::PseudoJet> const& jetVec )
{
   
   //vectors that contain the respective splitting scales for all jets
   std::vector<double> split12_vec;
   
   for( int i = 0; i < (int) jetVec.size(); i++){
   
      // For now: Calculate substructure information only for the two leading jets
      if( i > 1 ) continue;
   
      double split12 = -1.;

      if (!jetVec.at(i).has_constituents()){
         std::cout << "ERROR! Splittings (d12, d23, ...) can only be calculated on jets for which the constituents are known."<< std::endl;
         split12_vec.push_back(-1);
         continue;
      }
   
      vector<fastjet::PseudoJet> constits = jetVec.at(i).constituents();
      
//       std::cout << "Jet " <<  i << " has " << constits.size() << " constituents." << std::endl;
      
      fastjet::JetDefinition ekt_jd = fastjet::JetDefinition( fastjet::kt_algorithm, 1.5, fastjet::E_scheme, fastjet::Best);
      const fastjet::ClusterSequence kt_seq_excl = fastjet::ClusterSequence( constits, ekt_jd);
      fastjet::PseudoJet kt_jet = sorted_by_pt( kt_seq_excl.inclusive_jets())[0];
      
      split12 = 1.5*sqrt( kt_seq_excl.exclusive_subdmerge( kt_jet, 1));
      
      split12_vec.push_back(split12);
   }
   
   return split12_vec;
}


// ----------------------------------------------------------------------------------
// Recluster with kt algorithm to obtain nsubjettiness - fixed-R version
std::vector< double > NSubjettiness( std::vector<fastjet::PseudoJet> const& jetVec, double const& jet_rad )
{

   // Reclustering with VR kt algorithm to obtain nsubjettiness
   
   //vector that contain the respective nsubjettiness variables for all jets
   std::vector<double> tau1_vec;
   std::vector<double> tau2_vec;
   std::vector<double> tau3_vec;
   
   std::vector<double> tau21_vec;
   
   double alpha=1;
   
   for( int i = 0; i < (int) jetVec.size(); i++)
   {
   
      // For now: Calculate substructure information only for the two leading jets
      if( i > 1 ) continue;
   
      double tau1 = -1.;
      double tau2 = -1.;
      double tau3 = -1.;

      if (!jetVec.at(i).has_constituents())
      {
        std::cout << "ERROR! NSubjettiness (tau1, tau2, ...) can only be calculated on jets for which the constituents are known."<< std::endl;
         
        tau1_vec.push_back(-1);
        tau2_vec.push_back(-1);
        tau3_vec.push_back(-1);
  
        double tau21 = tau2/tau1;
        tau21_vec.push_back(-1);
        continue;
      }
      
      //Code snippet taken from https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/JetSubstructureVariables#N_subjettiness
      vector<fastjet::PseudoJet> constits = jetVec.at(i).constituents();
      if(constits.size()>0){
      
   double R_kt = 1.5; // ******************************************  SHOULD THIS BE jet_rad? ********************************
   fastjet::JetDefinition jet_def = fastjet::JetDefinition(fastjet::kt_algorithm,R_kt,fastjet::E_scheme,fastjet::Best);
   fastjet::ClusterSequence kt_clust_seq(constits, jet_def);
   vector<fastjet::PseudoJet> kt1axes = kt_clust_seq.exclusive_jets(1);
   double tauNum = 0.0;
   double tauDen = 0.0;
   for (int i = 0; i < (int)constits.size(); i++) {
      // find minimum distance
      double minR = 10000.0; // large number
      for (int j = 0; j < (int)kt1axes.size(); j++) {
         double tempR = sqrt(constits[i].squared_distance(kt1axes[j])); // delta R distance
         if (tempR < minR) minR = tempR;
      }
      tauNum += constits[i].perp() * pow(minR,alpha);
      tauDen += constits[i].perp() * pow(jet_rad,alpha);
   }
   tau1 = tauNum/tauDen;

   if(constits.size()>1){
      vector<fastjet::PseudoJet> kt2axes = kt_clust_seq.exclusive_jets(2);
      tauNum = 0.0;
      tauDen = 0.0;
      for (int i = 0; i < (int)constits.size(); i++) {
      // find minimum distance
      double minR = 10000.0; // large number
      for (int j = 0; j < (int)kt2axes.size(); j++) {
         double tempR = sqrt(constits[i].squared_distance(kt2axes[j]));
         if (tempR < minR) minR = tempR;
      }
      tauNum += constits[i].perp() * pow(minR,alpha);
      tauDen += constits[i].perp() * pow(jet_rad,alpha);
      }
      tau2 = tauNum/tauDen;
      
      if(constits.size() > 2){
      
         vector<fastjet::PseudoJet> kt3axes = kt_clust_seq.exclusive_jets(3);
         tauNum = 0.0;
         tauDen = 0.0;
         for (int i = 0; i < (int)constits.size(); i++) {
         // find minimum distance
         double minR = 10000.0; // large number
         for (int j = 0; j < (int)kt3axes.size(); j++) {
      double tempR = sqrt(constits[i].squared_distance(kt3axes[j]));
      if (tempR < minR) minR = tempR;
         }
         tauNum += constits[i].perp() * pow(minR,alpha);
         tauDen += constits[i].perp() * pow(jet_rad,alpha);
         }
         tau3 = tauNum/tauDen;
      }

   }
      }
      
      tau1_vec.push_back(tau1);
      tau2_vec.push_back(tau2);
      tau3_vec.push_back(tau3);
      
      double tau21 = tau2/tau1;
      tau21_vec.push_back(tau21);
   }
   
   return tau21_vec;
}




// ----------------------------------------------------------------------------------
// Recluster with kt algorithm to obtain nsubjettiness
std::vector< double > NSubjettiness( std::vector<fastjet::PseudoJet> const& jetVec, double const& jet_Rmax, double const& jet_Rmin, double const& jet_Rho )
{

   // Reclustering with VR kt algorithm to obtain nsubjettiness
   
   //vector that contain the respective nsubjettiness variables for all jets
   std::vector<double> tau1_vec;
   std::vector<double> tau2_vec;
   std::vector<double> tau3_vec;
   
   std::vector<double> tau21_vec;
   
   double alpha=1;
   
   for( int i = 0; i < (int) jetVec.size(); i++){
   
      // For now: Calculate substructure information only for the two leading jets
      if( i > 1 ) continue;
   
      double tau1 = -1.;
      double tau2 = -1.;
      double tau3 = -1.;
      
      // Calculate effective jet radius
      double jet_Pt = jetVec[i].pt();
      
      double jet_rad;
      if( jet_Pt > jet_Rmax ) jet_rad = jet_Rmax;
      else if( jet_Pt < jet_Rmin ) jet_rad = jet_Rmin;
      else jet_rad = jet_Rho / jet_Pt;

      if (!jetVec.at(i).has_constituents()){
         std::cout << "ERROR! NSubjettiness (tau1, tau2, ...) can only be calculated on jets for which the constituents are known."<< std::endl;
         
         tau1_vec.push_back(-1);
   tau2_vec.push_back(-1);
   tau3_vec.push_back(-1);
  
   double tau21 = tau2/tau1;
   tau21_vec.push_back(-1);
         continue;
      }
      
      //Code snippet taken from https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/JetSubstructureVariables#N_subjettiness
      vector<fastjet::PseudoJet> constits = jetVec.at(i).constituents();
      if(constits.size()>0){
      
   double R_kt = 1.5; // ******************************************  SHOULD THIS BE jet_rad? ********************************
   fastjet::JetDefinition jet_def = fastjet::JetDefinition(fastjet::kt_algorithm,R_kt,fastjet::E_scheme,fastjet::Best);
   fastjet::ClusterSequence kt_clust_seq(constits, jet_def);
   vector<fastjet::PseudoJet> kt1axes = kt_clust_seq.exclusive_jets(1);
   double tauNum = 0.0;
   double tauDen = 0.0;
   for (int i = 0; i < (int)constits.size(); i++) {
      // find minimum distance
      double minR = 10000.0; // large number
      for (int j = 0; j < (int)kt1axes.size(); j++) {
         double tempR = sqrt(constits[i].squared_distance(kt1axes[j])); // delta R distance
         if (tempR < minR) minR = tempR;
      }
      tauNum += constits[i].perp() * pow(minR,alpha);
      tauDen += constits[i].perp() * pow(jet_rad,alpha);
   }
   tau1 = tauNum/tauDen;

   if(constits.size()>1){
      vector<fastjet::PseudoJet> kt2axes = kt_clust_seq.exclusive_jets(2);
      tauNum = 0.0;
      tauDen = 0.0;
      for (int i = 0; i < (int)constits.size(); i++) {
      // find minimum distance
      double minR = 10000.0; // large number
      for (int j = 0; j < (int)kt2axes.size(); j++) {
         double tempR = sqrt(constits[i].squared_distance(kt2axes[j]));
         if (tempR < minR) minR = tempR;
      }
      tauNum += constits[i].perp() * pow(minR,alpha);
      tauDen += constits[i].perp() * pow(jet_rad,alpha);
      }
      tau2 = tauNum/tauDen;
      
      if(constits.size() > 2){
      
         vector<fastjet::PseudoJet> kt3axes = kt_clust_seq.exclusive_jets(3);
         tauNum = 0.0;
         tauDen = 0.0;
         for (int i = 0; i < (int)constits.size(); i++) {
         // find minimum distance
         double minR = 10000.0; // large number
         for (int j = 0; j < (int)kt3axes.size(); j++) {
      double tempR = sqrt(constits[i].squared_distance(kt3axes[j]));
      if (tempR < minR) minR = tempR;
         }
         tauNum += constits[i].perp() * pow(minR,alpha);
         tauDen += constits[i].perp() * pow(jet_rad,alpha);
         }
         tau3 = tauNum/tauDen;
      }

   }
      }
      
      tau1_vec.push_back(tau1);
      tau2_vec.push_back(tau2);
      tau3_vec.push_back(tau3);
      
      double tau21 = tau2/tau1;
      tau21_vec.push_back(tau21);
   }
   
   return tau21_vec;
}

// ---------------------------------------------------------------------------------------
// Associate charged small-R ("track") jets to large-R ("calo") jet
void get_assoc_trkjets( fastjet::PseudoJet calojet, std::vector<fastjet::PseudoJet> trkjets, std::vector<fastjet::PseudoJet> &matched_trkjets, bool debug=false){

    // vector to hold input clusters and ghosts
    std::vector<fastjet::PseudoJet> input_particles;
    input_particles.clear();

    // jet clusters from large-R jet
    vector<fastjet::PseudoJet> constituents = calojet.constituents();

    if( debug ) std::cout << "calo constituents size = " << constituents.size() << std::endl;

    for(unsigned int constItr = 0; constItr < constituents.size(); ++constItr) {
    
      fastjet::PseudoJet noghost = constituents.at(constItr);
      
      noghost.reset_PtYPhiM (noghost.pt(), noghost.rapidity(), noghost.phi(), 0.0);
      if(noghost.E()<0.) continue;

      // set user index for calo clusters to -1 to differentiate them from "track" constituents later
      noghost.set_user_index(-1);
      input_particles.push_back(noghost);
    }

    if( debug ) std::cout << "calo only input particles size = " << input_particles.size() << std::endl;

    // make ghost PseudoJets out of track jet direction
    for(unsigned int trackJetItr = 0; trackJetItr < trkjets.size(); ++trackJetItr){
    
      fastjet::PseudoJet myghost = trkjets.at(trackJetItr);
      
      myghost.reset_PtYPhiM (1e-12, myghost.rapidity(), myghost.phi(), 0.0);
      if(myghost.E()<0.) continue;

      myghost.set_user_index(trackJetItr);
      input_particles.push_back(myghost);
    }

    if( debug ) std::cout << "calo+track jets input particles size = " << input_particles.size() << std::endl;

    // do ghost association and get list of pseudojet track jets that are associated
    double Rparam = 1.0;
    fastjet::Strategy strategy = fastjet::Best;  // according to atlas reco
    fastjet::RecombinationScheme recomb_scheme = fastjet::E_scheme;  // according to atlas reco
    fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, Rparam, recomb_scheme, strategy);

    // run the jet clustering with the above jet definition
    fastjet::ClusterSequence clust_seq(input_particles, jet_def);
    vector<fastjet::PseudoJet> sorted_jets = fastjet::sorted_by_pt( clust_seq.inclusive_jets() );

    if( debug ) std::cout << "number of sorted jets = " << sorted_jets.size() << std::endl;

    fastjet::PseudoJet newJet = sorted_jets.at(0); //there are more jets in the vector, but they all have pT ~0
    if( debug ) std::cout << "new jet constituent size = " << newJet.constituents().size() << std::endl;
    vector<fastjet::PseudoJet> newJet_constituents = newJet.constituents();
    for(unsigned int i=0; i<newJet_constituents.size(); ++i){
      fastjet::PseudoJet constit = newJet_constituents.at(i);
      if( debug ) std::cout << " user index = " << constit.user_index() << ", pt of constit = " << constit.pt() << std::endl;
      if(constit.user_index()>=0){
	  int iter = constit.user_index();
	  if(trkjets.at(iter).pt() > 20. && fabs(trkjets.at(iter).eta()) < 2.5 ) matched_trkjets.push_back(trkjets.at(iter));
      }
    }

    return;
}

// ---------------------------------------------------------------------------------------
// B-tagging based on ATLAS PubNotes 
// (ATL-PHYS-PUB-2014-013, ATL-PHYS-PUB-2014-014)

double btag_eff( double jet_pt ){

  if( jet_pt <= 20. ) return 0.05;
  else if( jet_pt > 20. && jet_pt <= 50. ) return 0.35;
  else if( jet_pt > 50. && jet_pt <= 70. ) return 0.65;
  else if( jet_pt > 70. && jet_pt <= 100. ) return 0.70;
  else if( jet_pt > 100. && jet_pt <= 200. ) return 0.65;
  else if( jet_pt > 200. && jet_pt <= 350. ) return 0.60;
  else if( jet_pt > 350. && jet_pt <= 500. ) return 0.55;
  else return 0.50;
}

double mistag_eff( double jet_pt ){

  if( jet_pt <= 70. ) return 1./150.;
  else if( jet_pt > 70. && jet_pt <= 180. ) return 1./170.;
  else if( jet_pt > 180. && jet_pt <= 250. ) return 1./130.;
  else return 1./100.;
}

double charm_eff( double jet_pt ){

  if( jet_pt <= 70. ) return 1./6.;
  else if( jet_pt > 70. && jet_pt <= 180. ) return 1./4.;
  else if( jet_pt > 180. && jet_pt <= 250. ) return 1./4.5;
  else return 1./5.;
}