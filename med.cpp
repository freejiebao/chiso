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
using namespace std;

char cleg[6];

void sysstyle();
void histstyle(TH1D *h1,int i,TLegend *leg);
int med(){
  TChain *chain = new TChain("treeDumper/PKUCandidates");
  chain->Add("../treePKU*.root");
  Int_t bin1=50;
  Int_t bin2=50;
  Int_t bin3=50;

  //TLatex *ltx;
  //ltx->SetTextAlign(13);
  //ltx->SetTextSize(0.08);
  /*TFile *f = new TFile("treePKU213.root");
  TDirectoryFile *file=(TDirectoryFile *)f->Get("treeDumper");
  TTree *chain=(TTree *)file->Get("PKUCandidates");*/
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
  //string loose="photon_hoe[0]<0.105 && photon_nhiso[0]<9.188+0.0126*photon_pt[0]+0.000026*photon_pt[0]*photon_pt[0] && photon_phoiso[0]<2.956+0.0035*photon_pt[0]";
  //string medium="photon_hoe[0]<0.035 && photon_nhiso[0]<2.491+0.0126*photon_pt[0]+0.000026*photon_pt[0]*photon_pt[0] && photon_phoiso[0]<2.952+0.0040*photon_pt[0]";
  bool wjet;
  bool photon_cut;
  bool loose;
  bool medium;
  Long64_t nentries = chain->GetEntries();
  TH1D *h[7];
  TH1D *hm[7];
  Double_t pt_cut;
  Int_t flag;
  char ch[7];
  for (int i=0;i<7;i++){
    //h[i]=new TH1D(ch,"photon_chiso[0]<0.441;photon_sieie[0];count",bin1,-0.01,0.09);
    sprintf(ch,"h%d",i);
    hm[i]=new TH1D(ch,";photon_sieie[0];count",bin3,-0.005,0.020);
  }
  /*TH2D *h3=new TH2D("h3","photon_chiso[0]<0.441 && photon_sieie[0]<0.09;photon_sieie[0];photon_chiso[0]",bin2,-0.001,0.09,bin3,-0.5,1.);
  TH2D *h4=new TH2D("h4","photon_chiso[0]>1.2 && photon_sieie[0]<0.09;photon_sieie[0];photon_chiso[0]",bin2,-0.001,0.09,225,-5,220);
  TH2D *h5=new TH2D("h5","photon_chiso[0]<0.441 && photon_sieie[0]<0.018;photon_sieie[0];photon_chiso[0]",bin3,-0.001,0.018,bin3,-0.5,1.);
  TH2D *h6=new TH2D("h6","photon_chiso[0]>1.2 && photon_sieie[0]<0.018;photon_sieie[0];photon_chiso[0]",bin3,-0.001,0.018,225,-5,220);*/
  for (Long64_t jentry=0; jentry<nentries/*jentry<2000*/;jentry++){
    chain->GetEntry(jentry);
    pt_cut=0.;
    flag=0;
    //cout<<flag<<"aaa"<<photon_pt[0]<<"aaa"<<photon_pt[1]<<"aaa"<<photon_pt[2]<<"aaa"<<photon_pt[3]<<"aaa"<<photon_pt[4]<<"aaa"<<photon_pt[5]<<endl;
    wjet = lep==13 && nlooseeles==0 && nloosemus<2 && mtVlepJECnew>30 && ptlep1>25 && fabs(etalep1)<2.1 && MET_et>35;
    for (int j=0;j<6;j++) {
       photon_cut = photon_isprompt[j] != 1  &&  photon_drla[j]>0.3 && photon_eta[j]<1.442 && photon_sieie[j]<0.018; //limit photon in the barrel, and restrict photon_sieie<0.018
       loose = photon_hoe[j]<0.105 && photon_nhiso[j]<9.188+0.0126*photon_pt[j]+0.000026*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.956+0.0035*photon_pt[j];
       medium = photon_hoe[j]<0.035 && photon_nhiso[j]<2.491+0.0126*photon_pt[j]+0.000026*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.952+0.0040*photon_pt[j];
        if ( wjet && photon_cut && medium) {
         if (pt_cut<photon_pt[j]){
           pt_cut=photon_pt[j];
           flag=j;
           cout<<pt_cut<<"\t"<<flag<<"\t"<<photon_pt[0]<<"\t"<<photon_pt[1]<<"\t"<<photon_pt[2]<<"\t"<<photon_pt[3]<<"\t"<<photon_pt[4]<<"\t"<<photon_pt[5]<<endl;
         }
         if ( j==5 ) {
           if (photon_chiso[flag]<1.416){
             hm[0]->Fill(photon_sieie[flag]);
           }
           for(int i=1;i<7;i++){
             if (photon_chiso[flag]>(Double_t)2.*i ){
               hm[i]->Fill(photon_sieie[flag]);
             }
           }
         }

       }
       // if (Cut(ientry) < 0) continue;
    }
  }
  sysstyle();
  TCanvas *c1 = new TCanvas("c1","c1");
  TLegend *l1 = new TLegend(0.5,0.60,0.8,0.8);
  l1->SetBorderSize(2);
  l1->SetFillColor(0);
  for(int i=0;i<6;i++){
    c1->cd();
    histstyle(hm[i], i, l1);
    //delete h[i];
    //delete hm[i];
  }
  l1->Draw();
  c1->SaveAs("med-50bin.eps");
  return 0;
}
void sysstyle(){
  gStyle->SetPadBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
}
void histstyle(TH1D *h1,int i,TLegend *leg){

  h1->SetStats(kFALSE);
  h1->SetLineColor(i+1);
  h1->GetXaxis()->SetTitleSize(0.043);
  h1->GetYaxis()->SetTitleSize(0.043);
  h1->SetLineWidth(1);
  h1->DrawNormalized("HIST e,SAME");
  if(i==0)
  leg->AddEntry(h1,"photon_chiso[0]<1.416","l");
  else{
    sprintf(cleg,"photon_chiso[0]>%d",2*i);
    leg->AddEntry(h1,cleg,"l");
  }
}
