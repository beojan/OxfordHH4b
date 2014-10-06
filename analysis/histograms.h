/*
Here we collect the routines that are used to plot the various distributions
(before the corresponding kinematical cuts) using Root
All plots are normalized
*/

// --------------------------------------------------------------------------------

// pt of the HH system
TCanvas* c_pthh = new TCanvas();
vector<TH1D*> histo_pthh;
double const pthh_min=0;
double const pthh_max=500;
int nbin_pthh=20;
double histo_pthh_binwidth = (  pthh_max -  pthh_min ) / nbin_pthh;

// pt of the H candidates
TCanvas* c_pth = new TCanvas();
vector<TH1D*> histo_pth;
double const pth_min=0;
double const pth_max=600;
int nbin_pth=20;
double histo_pth_binwidth = (  pthh_max -  pthh_min ) / nbin_pthh;

// pt of the b jets
// To be used in the resolved strategy
TCanvas* c_ptb1 = new TCanvas();
vector<TH1D*> histo_ptb1;
double const ptb_min=0;
double const ptb_max=600;
int nbin_ptb=20;
double histo_ptb_binwidth = (  ptb_max -  ptb_min ) / nbin_ptb;

TCanvas* c_ptb2 = new TCanvas();
vector<TH1D*> histo_ptb2;
TCanvas* c_ptb3 = new TCanvas();
vector<TH1D*> histo_ptb3;
TCanvas* c_ptb4 = new TCanvas();
vector<TH1D*> histo_ptb4;

// Plot legend
TLegend *leg = new TLegend(0.70,0.68,0.89,0.89,NULL,"brNDC");

// --------------------------------------------------------------------------------

// Histogram initialization
void histo_init(){

  // Select here linear or log scales of y axis
  bool ylog=true;
  if(ylog){
        
    // pt of the HH system
    c_pthh -> SetLogy();

    // pt of the higgs candidates
    c_pth -> SetLogy();

    // pt of the b jets in the resolved analysis
    c_ptb1 -> SetLogy();
    c_ptb2 -> SetLogy();
    c_ptb3 -> SetLogy();
    c_ptb4 -> SetLogy();
    
  }

}

// --------------------------------------------------------------------------------

// Create the histograms
// There is one histogram for each of the signal and background samples
void histo_create(){

  // pt of the HH system
  histo_pthh.push_back(new TH1D("histo_pthh","histo_pthh",nbin_pthh,  pthh_min,  pthh_max)) ;
  // pt of the h system
  histo_pth.push_back(new TH1D("histo_pth","histo_pth",nbin_pth,  pth_min,  pth_max)) ;
  // pt of the b jets in the resolved analysis
  histo_ptb1.push_back(new TH1D("histo_ptb1","histo_ptb1",nbin_ptb,  ptb_min,  ptb_max)) ;
  histo_ptb2.push_back(new TH1D("histo_ptb1","histo_ptb2",nbin_ptb,  ptb_min,  ptb_max)) ;
  histo_ptb3.push_back(new TH1D("histo_ptb1","histo_ptb3",nbin_ptb,  ptb_min,  ptb_max)) ;
  histo_ptb4.push_back(new TH1D("histo_ptb1","histo_ptb4",nbin_ptb,  ptb_min,  ptb_max)) ;

}

// ----------------------------------------------------------------------

// Plot the histogram
// All histograms are normalized
void histo_plot(){

  double total_xsec=0.0;
  bool draw=true;

  std::cout<<"\n Drawing pthh histogram \n "<<std::endl;
  
  c_pthh->cd();
  histo_pthh.back()->GetXaxis()->SetTitle("p_{T}^{hh} (GeV) ");
  histo_pthh.back()->GetXaxis()->CenterTitle(true);
  histo_pthh.back()->GetYaxis()->CenterTitle(true);
  histo_pthh.back()->GetYaxis()->SetTitle("d #sigma / d p_{T}^{hh} ( AU ) ");
  histo_pthh.back()->SetTitle("Gluon Fusion HH, LHC 14 TeV");
  histo_pthh.back()->SetLineWidth(3);
  histo_pthh.back()->SetLineColor(histo_pthh.size());
  histo_pthh.back()->SetLineStyle(histo_pthh.size());
  histo_pthh.back()->GetYaxis()->SetRangeUser(1e-4,1.0);
  histo_pthh.back()->GetYaxis()->SetLimits(1e-4,1.0);
  total_xsec=0;
  for(int j=1; j<=histo_pthh.back()->GetNbinsX(); j++   ){
    total_xsec+= histo_pthh.back()->GetBinContent(j) * histo_pthh_binwidth ;
  }
  draw=true;
  if(total_xsec<1e-30){
    std::cout<<"Too small xsec = "<<total_xsec<<std::endl;
    std::cout<<"Not drawing histograms for this sample"<<std::endl;
    draw=false;
  }
  if(draw){
    histo_pthh.back()->Scale(1.0/total_xsec);
    if( histo_pthh.size()==1)histo_pthh.back()->Draw();
    if( histo_pthh.size()>1)histo_pthh.back()->Draw("same");
  }
  
  std::cout<<"\n Drawing pth histogram \n "<<std::endl;
  
  c_pth->cd();
  histo_pth.back()->GetXaxis()->SetTitle("p_{T}^{hh} (GeV) ");
  histo_pth.back()->GetXaxis()->CenterTitle(true);
  histo_pth.back()->GetYaxis()->CenterTitle(true);
  histo_pth.back()->GetYaxis()->SetTitle("d #sigma / d p_{T}^{h} ( AU ) ");
  histo_pth.back()->SetTitle("Gluon Fusion HH, LHC 14 TeV");
  histo_pth.back()->SetLineWidth(3);
  histo_pth.back()->SetLineColor(histo_pth.size());
  histo_pth.back()->SetLineStyle(histo_pth.size());
  histo_pth.back()->GetYaxis()->SetRangeUser(1e-4,1.0);
  histo_pth.back()->GetYaxis()->SetLimits(1e-4,1.0);
  total_xsec=0;
  for(int j=1; j<=histo_pth.back()->GetNbinsX(); j++   ){
    total_xsec+= histo_pth.back()->GetBinContent(j) * histo_pth_binwidth ;
  }
  draw=true;
  if(total_xsec<1e-30){
    std::cout<<"Too small xsec = "<<total_xsec<<std::endl;
    std::cout<<"Not drawing histograms for this sample"<<std::endl;
    draw=false;
  }
  if(draw){
    histo_pth.back()->Scale(1.0/total_xsec);
    if( histo_pth.size()==1)histo_pth.back()->Draw();
    if( histo_pth.size()>1)histo_pth.back()->Draw("same");
  }



  std::cout<<"\n Drawing ptb histogram \n "<<std::endl;
  
  c_ptb1->cd();
  histo_ptb1.back()->GetXaxis()->SetTitle("p_{T}^{b} Leading (GeV) ");
  histo_ptb1.back()->GetXaxis()->CenterTitle(true);
  histo_ptb1.back()->GetYaxis()->CenterTitle(true);
  histo_ptb1.back()->GetYaxis()->SetTitle("d #sigma / d p_{T}^{b} ( AU ) ");
  histo_ptb1.back()->SetTitle("Gluon Fusion HH, LHC 14 TeV");
  histo_ptb1.back()->SetLineWidth(3);
  histo_ptb1.back()->SetLineColor(histo_ptb1.size());
  histo_ptb1.back()->SetLineStyle(histo_ptb1.size());
  histo_ptb1.back()->GetYaxis()->SetRangeUser(1e-4,1.0);
  histo_ptb1.back()->GetYaxis()->SetLimits(1e-4,1.0);
  total_xsec=0;
  for(int j=1; j<=histo_ptb1.back()->GetNbinsX(); j++   ){
    total_xsec+= histo_ptb1.back()->GetBinContent(j) * histo_ptb_binwidth ;
  }
  draw=true;
  if(total_xsec<1e-30){
    std::cout<<"Too small xsec = "<<total_xsec<<std::endl;
    std::cout<<"Not drawing histograms for this sample"<<std::endl;
    draw=false;
  }
  if(draw){
    histo_ptb1.back()->Scale(1.0/total_xsec);
    if( histo_ptb1.size()==1)histo_ptb1.back()->Draw();
    if( histo_ptb1.size()>1)histo_ptb1.back()->Draw("same");
  }

  c_ptb2->cd();
  histo_ptb2.back()->GetXaxis()->SetTitle("p_{T}^{b} Sub-Leading (GeV) ");
  histo_ptb2.back()->GetXaxis()->CenterTitle(true);
  histo_ptb2.back()->GetYaxis()->CenterTitle(true);
  histo_ptb2.back()->GetYaxis()->SetTitle("d #sigma / d p_{T}^{b} ( AU ) ");
  histo_ptb2.back()->SetTitle("Gluon Fusion HH, LHC 14 TeV");
  histo_ptb2.back()->SetLineWidth(3);
  histo_ptb2.back()->SetLineColor(histo_ptb2.size());
  histo_ptb2.back()->SetLineStyle(histo_ptb2.size());
  histo_ptb2.back()->GetYaxis()->SetRangeUser(1e-4,1.0);
  histo_ptb2.back()->GetYaxis()->SetLimits(1e-4,1.0);
  total_xsec=0;
  for(int j=1; j<=histo_ptb2.back()->GetNbinsX(); j++   ){
    total_xsec+= histo_ptb2.back()->GetBinContent(j) * histo_ptb_binwidth ;
  }
  draw=true;
  if(total_xsec<1e-30){
    std::cout<<"Too small xsec = "<<total_xsec<<std::endl;
    std::cout<<"Not drawing histograms for this sample"<<std::endl;
    draw=false;
  }
  if(draw){
    histo_ptb2.back()->Scale(1.0/total_xsec);
    if( histo_ptb2.size()==1)histo_ptb2.back()->Draw();
    if( histo_ptb2.size()>1)histo_ptb2.back()->Draw("same");
  }

   c_ptb3->cd();
  histo_ptb3.back()->GetXaxis()->SetTitle("p_{T}^{b} Third Jet (GeV) ");
  histo_ptb3.back()->GetXaxis()->CenterTitle(true);
  histo_ptb3.back()->GetYaxis()->CenterTitle(true);
  histo_ptb3.back()->GetYaxis()->SetTitle("d #sigma / d p_{T}^{b} ( AU ) ");
  histo_ptb3.back()->SetTitle("Gluon Fusion HH, LHC 14 TeV");
  histo_ptb3.back()->SetLineWidth(3);
  histo_ptb3.back()->SetLineColor(histo_ptb3.size());
  histo_ptb3.back()->SetLineStyle(histo_ptb3.size());
  histo_ptb3.back()->GetYaxis()->SetRangeUser(1e-4,1.0);
  histo_ptb3.back()->GetYaxis()->SetLimits(1e-4,1.0);
  total_xsec=0;
  for(int j=1; j<=histo_ptb3.back()->GetNbinsX(); j++   ){
    total_xsec+= histo_ptb3.back()->GetBinContent(j) * histo_ptb_binwidth ;
  }
  draw=true;
  if(total_xsec<1e-30){
    std::cout<<"Too small xsec = "<<total_xsec<<std::endl;
    std::cout<<"Not drawing histograms for this sample"<<std::endl;
    draw=false;
  }
  if(draw){
    histo_ptb3.back()->Scale(1.0/total_xsec);
    if( histo_ptb3.size()==1)histo_ptb3.back()->Draw();
    if( histo_ptb3.size()>1)histo_ptb3.back()->Draw("same");
  }

  c_ptb4->cd();
  histo_ptb4.back()->GetXaxis()->SetTitle("p_{T}^{b} Fourth Jet (GeV) ");
  histo_ptb4.back()->GetXaxis()->CenterTitle(true);
  histo_ptb4.back()->GetYaxis()->CenterTitle(true);
  histo_ptb4.back()->GetYaxis()->SetTitle("d #sigma / d p_{T}^{b} ( AU ) ");
  histo_ptb4.back()->SetTitle("Gluon Fusion HH, LHC 14 TeV");
  histo_ptb4.back()->SetLineWidth(3);
  histo_ptb4.back()->SetLineColor(histo_ptb4.size());
  histo_ptb4.back()->SetLineStyle(histo_ptb4.size());
  histo_ptb4.back()->GetYaxis()->SetRangeUser(1e-4,1.0);
  histo_ptb4.back()->GetYaxis()->SetLimits(1e-4,1.0);
  total_xsec=0;
  for(int j=1; j<=histo_ptb4.back()->GetNbinsX(); j++   ){
    total_xsec+= histo_ptb4.back()->GetBinContent(j) * histo_ptb_binwidth ;
  }
  draw=true;
  if(total_xsec<1e-30){
    std::cout<<"Too small xsec = "<<total_xsec<<std::endl;
    std::cout<<"Not drawing histograms for this sample"<<std::endl;
    draw=false;
  }
  if(draw){
    histo_ptb4.back()->Scale(1.0/total_xsec);
    if( histo_ptb4.size()==1)histo_ptb4.back()->Draw();
    if( histo_ptb4.size()>1)histo_ptb4.back()->Draw("same");
  }

}

// -----------------------------------------------------------------------

/*
  Print histograms into files
*/

void histo_plot_final(){

  // Legend
  leg->SetLineStyle(1);
  leg->SetBorderSize(1);
  leg->SetFillColor(0);
  TLegendEntry *entry;

  entry=leg->AddEntry("Graph1","hh SM","L");
  entry->SetLineStyle(1);
  entry->SetLineColor(1);
  entry->SetLineWidth(3);
  entry=leg->AddEntry("Graph1","hh BSM, #lambda = 10*#lambda_{SM} ","L");
  entry->SetLineStyle(2);
  entry->SetLineColor(2);
  entry->SetLineWidth(3);
  entry=leg->AddEntry("Graph1","QCD 4b","L");
  entry->SetLineStyle(3);
  entry->SetLineColor(3);
  entry->SetLineWidth(3);
  entry=leg->AddEntry("Graph1","QCD 2b2j","L");
  entry->SetLineStyle(4);
  entry->SetLineColor(4);
  entry->SetLineWidth(3);
  entry=leg->AddEntry("Graph1","QCD 4j","L");
  entry->SetLineStyle(5);
  entry->SetLineColor(5);
  entry->SetLineWidth(3);
   entry=leg->AddEntry("Graph1","tt Hadronic","L");
  entry->SetLineStyle(6);
  entry->SetLineColor(6);
  entry->SetLineWidth(3);

  // Set the corresponding final state label
  string label="14tev_bbbb";

  c_pthh->cd();
  gStyle->SetOptStat(0);
  leg->Draw();
  string file1="histo_pthh_"+label+".eps";
  string file2="histo_pthh_"+label+".C";
  c_pthh->SaveAs(file1.c_str());
  c_pthh->SaveAs(file2.c_str());

  c_pth->cd();
  gStyle->SetOptStat(0);
  leg->Draw();
  file1="histo_pth_"+label+".eps";
  file2="histo_pth_"+label+".C";
  c_pth->SaveAs(file1.c_str());
  c_pth->SaveAs(file2.c_str());

  c_ptb1->cd();
  gStyle->SetOptStat(0);
  leg->Draw();
  file1="histo_ptb1_"+label+".eps";
  file2="histo_ptb1_"+label+".C";
  c_ptb1->SaveAs(file1.c_str());
  c_ptb1->SaveAs(file2.c_str());

   c_ptb2->cd();
  gStyle->SetOptStat(0);
  leg->Draw();
  file1="histo_ptb2_"+label+".eps";
  file2="histo_ptb2_"+label+".C";
  c_ptb2->SaveAs(file1.c_str());
  c_ptb2->SaveAs(file2.c_str());

  c_ptb3->cd();
  gStyle->SetOptStat(0);
  leg->Draw();
  file1="histo_ptb3_"+label+".eps";
  file2="histo_ptb3_"+label+".C";
  c_ptb3->SaveAs(file1.c_str());
  c_ptb3->SaveAs(file2.c_str());

  c_ptb4->cd();
  gStyle->SetOptStat(0);
  leg->Draw();
  file1="histo_ptb4_"+label+".eps";
  file2="histo_ptb4_"+label+".C";
  c_ptb4->SaveAs(file1.c_str());
  c_ptb4->SaveAs(file2.c_str());


}

// --------------------------------------------------------------------------------------------

/*
 Here we fill the histograms
 With the corresponding event weight
 */

void histo_fill(string histofill, double event_weight, double entry){

  // Check that the event weight is non zero
  if(event_weight < 1e-10 ){
    std::cout<<"Stopping, using zero weight in filling histograms"<<std::endl;
    std::cout<<"event_weight = "<<event_weight<<std::endl;
    std::cout<<"histofill = "<<histofill<<std::endl;
    exit(-10);
   }

   // Check that you are not filling the histogram with zero entries
   if(fabs(entry) < 1e-20 ){
     std::cout<<"Stopping,  filling histograms with zeros, not allowed"<<std::endl;
     std::cout<<"entry_fill = "<<entry<<std::endl;
     std::cout<<"histofill = "<<histofill<<std::endl;
     exit(-10);
   }
   
   // Fill the corresponding histograms
   if(histofill=="pthh"){
     histo_pthh.back()->Fill(entry,event_weight);
   }
   else if(histofill=="pth"){
     histo_pth.back()->Fill(entry,event_weight);
   }
   else if(histofill=="ptb1"){
     histo_ptb1.back()->Fill(entry,event_weight);
   }
   else if(histofill=="ptb2"){
     histo_ptb2.back()->Fill(entry,event_weight);
   }
   else if(histofill=="ptb3"){
     histo_ptb3.back()->Fill(entry,event_weight);
   }
   else if(histofill=="ptb4"){
     histo_ptb4.back()->Fill(entry,event_weight);
   }

   else{
     std::cout<<"Invalid option for histogram plotting, histofill = "<<histofill<<std::endl;
     exit(-10);
   }
   
   // End of the routine
   return;

}

// --------------------------------------------------------------------------------------------
