#pragma once

#include <iostream>
#include <vector>
#include "analysis.h"

#include "HepMC/GenEvent.h"
#include "fastjet/PseudoJet.hh"

// Helpful typedef
typedef enum {NTAG, BTAG, CTAG, LTAG} btagType;

// Analysis utility functions
double getDPhi(double phi1, double phi2);

// Substructure variables
std::vector< double > SplittingScales( std::vector<fastjet::PseudoJet> const& jetVec );
std::vector< double > NSubjettiness( std::vector<fastjet::PseudoJet> const& jetVec, double const& jet_rad );
std::vector< double > NSubjettiness( std::vector<fastjet::PseudoJet> const& jetVec, double const& jet_Rmax, double const& jet_Rmin, double const& jet_Rho );

double SplittingScales( fastjet::PseudoJet const& jet );
double NSubjettiness(   fastjet::PseudoJet const& jet, double const& jet_rad );
double LST_C2(double const& beta, fastjet::PseudoJet const& jet);
double LMN_D2(double const& beta, fastjet::PseudoJet const& jet);

// Ghost association for large-R double b-tagging
void get_assoc_trkjets( fastjet::PseudoJet calojet, std::vector<fastjet::PseudoJet> trkjets, std::vector<fastjet::PseudoJet> &matched_trkjets, bool debug);

// Btagging
double btag_eff( double jet_pt );
double mistag_eff( double jet_pt );
double charm_eff( double jet_pt );

