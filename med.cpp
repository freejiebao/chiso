#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include <string>
#include <stdio.h>
#include "TFile.h"

using namespace std;

void sysstyle();
void histstyle(TH1D *h1,int i,TLegend *leg);
int med(){
  TChain *chain = new TChain("treeDumper/PKUCandidates");
  chain->Add("../treePKU*.root");
  Int_t bin1=50;
  Int_t bin2=50;
  Int_t bin3=50;
  Int_t lep;
  Int_t nlooseeles;
  Int_t nloosemus;
  Double_t mtVlepJECnew;
  Double_t ptlep1;
  Double_t etalep1;
  Double_t MET_et;
  Int_t photon_isprompt[6];
  Double_t photon_drla[6];
  Double_t photon_hoe[6];
  Double_t photon_nhiso[6];
  Double_t photon_phoiso[6];
  Double_t photon_chiso[6];
  Double_t photon_sieie[6];
  Double_t photon_pt[6];
  Double_t photon_eta[6];
  Double_t scalef;

  chain->SetBranchAddress("lep",&lep);
  chain->SetBranchAddress("nlooseeles",&nlooseeles);
  chain->SetBranchAddress("nloosemus",&nloosemus);
  chain->SetBranchAddress("mtVlepJECnew",&mtVlepJECnew);
  chain->SetBranchAddress("ptlep1",&ptlep1);
  chain->SetBranchAddress("etalep1",&etalep1);
  chain->SetBranchAddress("MET_et",&MET_et);
  chain->SetBranchAddress("photon_isprompt",photon_isprompt);
  chain->SetBranchAddress("photon_drla",photon_drla);
  chain->SetBranchAddress("photon_hoe",photon_hoe);
  chain->SetBranchAddress("photon_nhiso",photon_nhiso);
  chain->SetBranchAddress("photon_phoiso",photon_phoiso);
  chain->SetBranchAddress("photon_chiso",photon_chiso);
  chain->SetBranchAddress("photon_sieie",photon_sieie);
  chain->SetBranchAddress("photon_pt",photon_pt);
  chain->SetBranchAddress("photon_eta",photon_eta);
  Double_t sieie_med,sieie_los,sieie_los5;
  Double_t chiso_med,chiso_los,chiso_los5;
  TFile *opt=new TFile("wjet.root","recreate");
  TTree *medtree=new TTree("medtree","medium_id");
  medtree->Branch("sieie_med",&sieie_med,"sieie_med/D");
  medtree->Branch("chiso_med",&chiso_med,"chiso_med/D");
  TTree *lostree=new TTree("lostree","loose_id");
  lostree->Branch("sieie_los",&sieie_los,"sieie_los/D");
  lostree->Branch("chiso_los",&chiso_los,"chiso_los/D");
  TTree *los5tree=new TTree("los5tree","loose_id5");
  los5tree->Branch("sieie_los5",&sieie_los5,"sieie_los5/D");
  los5tree->Branch("chiso_los5",&chiso_los5,"chiso_los5/D");
  bool wjet;
  bool photon_cut;
  bool loose;
  bool loose5;
  bool medium;
  Long64_t nentries = chain->GetEntries();
  TH1D *h[7];
  TH1D *hm[7];
  Double_t pho_pt[3];
  Int_t flag[3];
  Int_t total[3]={0};
  for (Long64_t jentry=0; jentry<nentries/*jentry<2000*/;jentry++){
    chain->GetEntry(jentry);
    pho_pt[0]=0.;pho_pt[1]=0.;pho_pt[2]=0.;
    flag[0]=100;flag[1]=100;flag[2]=100;
    for (int j=0;j<6;j++) {
       wjet = (lep==13 && nlooseeles==0 && nloosemus<2 && mtVlepJECnew>30 && ptlep1>30 && fabs(etalep1)<2.5 && MET_et>35);
       photon_cut = photon_isprompt[j] != 1  &&  photon_drla[j]>0.5 && fabs(photon_eta[j])<1.442;
       loose5 = photon_hoe[j]<5*0.0597 && photon_nhiso[j]<5*(10.910+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j]) && photon_phoiso[j]<5*(3.630+0.0047*photon_pt[j]);
       loose = photon_hoe[j]<0.0597 && photon_nhiso[j]<10.910+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<3.630+0.0047*photon_pt[j];
       medium = photon_hoe[j]<0.0396 && photon_nhiso[j]<2.725+0.0148*photon_pt[j]+0.000017*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.571+0.0047*photon_pt[j];
        if ( wjet && photon_cut ) {
          if (loose5) {
            total[0]++;
            if (pho_pt[0]<photon_pt[j]){
              pho_pt[0]=photon_pt[j];
              flag[0]=j;
            }
          }
          if (loose) {
            total[1]++;
            if (pho_pt[1]<photon_pt[j]){
              pho_pt[1]=photon_pt[j];
              flag[1]=j;
            }
          }
          if (medium) {
            total[2]++;
            if (pho_pt[2]<photon_pt[j]){
              pho_pt[2]=photon_pt[j];
              flag[2]=j;
            }
          }
        }
      if ( j==5 && flag[0]!=100) {
        sieie_los5=photon_sieie[flag[0]];
        chiso_los5=photon_chiso[flag[0]];
        los5tree->Fill();
      }
      if ( j==5 && flag[1]!=100) {
        sieie_los=photon_sieie[flag[1]];
        chiso_los=photon_chiso[flag[1]];
        lostree->Fill();
      }
      if ( j==5 && flag[2]!=100) {
        sieie_med=photon_sieie[flag[2]];
        chiso_med=photon_chiso[flag[2]];
        medtree->Fill();
        //cout<<sieie_los5<<"\t"<<sieie_los<<"\t"<<sieie_med<<endl;
      }
    }
  }
  opt->Write();
  cout<<"loose5_total:"<<total[0]<<endl;
  cout<<"loose_total:"<<total[1]<<endl;
  cout<<"medium_total:"<<total[2]<<endl;
  return 0;
}
