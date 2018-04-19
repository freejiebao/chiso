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

char cleg[7];
Int_t bin=50;

void sysstyle();
void histstyle(TH1D *h1,int i,TLegend *leg);
void compare_med(TTree* t0);
void compare_los(TTree* t1);
void compare_los5(TTree* t2);
void compare(TTree* t0,TTree* t1,TTree* t3);
int paint(){
  sysstyle();

  TFile *ipt = new TFile("wjet.root");
  TTree *medtree =(TTree*)ipt->Get("medtree");
  TTree *los5tree =(TTree*)ipt->Get("los5tree");
  TTree *lostree =(TTree*)ipt->Get("lostree");

  compare_med(medtree);
  compare_los(lostree);
  compare_los5(los5tree);
  compare(medtree,lostree,los5tree);
  /*Long64_t n=tree->GetEntries();
  for(Long64_t i=0;i<n;i++){
    tree->GetEntry(i);
    if (pho_chiso<0.441){
      hm[0]->Fill(pho_sieie);
    }
    for(int i=1;i<7;i++){
      if (pho_chiso>(Double_t)2.*i ){
        hm[i]->Fill(pho_sieie);
      }
    }
  }
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetLogy();
  TLegend *l1 = new TLegend(0.5,0.60,0.8,0.8);
  l1->SetBorderSize(2);
  l1->SetFillColor(0);
  for(int i=0;i<6;i++){
    c1->cd();
    histstyle(hm[i], i, l1);
  }*/
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
  h1->SetLineWidth(3);
  h1->DrawNormalized("HIST e,SAME");
  if(i==0)
  leg->AddEntry(h1,"photon_chiso[0]<0.441","l");
  else{
    sprintf(cleg,"photon_chiso[0]>%d",2*i);
    leg->AddEntry(h1,cleg,"l");
  }
}
void compare_med(TTree* t0){
  Double_t sieie_med;
  Double_t chiso_med;

  t0->SetBranchAddress("sieie_med",&sieie_med);
  t0->SetBranchAddress("chiso_med",&chiso_med);
  TH1D *hmed[7];
  char cmed[7];
  for (int i=0;i<7;i++){
    //h[i]=new TH1D(ch,"photon_chiso[0]<0.441;photon_sieie[0];count",bin1,-0.01,0.09);
    sprintf(cmed,"hmed%d",i);
    //hm[i]=new TH1D(Form("hm%d",i);photon_sieie[0];count",bin3,-0.005,0.020);
    hmed[i]=new TH1D(cmed,";photon_sieie[0];count",bin,-0.005,0.018);
  }
  Long64_t n=t0->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t0->GetEntry(i);
    if (chiso_med<0.441){
      hmed[0]->Fill(sieie_med);
    }
    for(int i=1;i<7;i++){
      if (chiso_med>(Double_t)2.*i ){
        hmed[i]->Fill(sieie_med);
      }
    }
  }
  TCanvas *c0 = new TCanvas("c0","c0");
  c0->SetLogy();
  TLegend *l0 = new TLegend(0.5,0.60,0.8,0.8);
  l0->SetBorderSize(2);
  l0->SetFillColor(0);
  for(int i=0;i<6;i++){
    c0->cd();
    histstyle(hmed[i], i, l0);
  }
  l0->Draw();
  c0->SaveAs("c0.eps");
}

void compare_los(TTree* t1){
  Double_t sieie_los;
  Double_t chiso_los;

  t1->SetBranchAddress("sieie_los",&sieie_los);
  t1->SetBranchAddress("chiso_los",&chiso_los);
  TH1D *hlos[7];
  char clos[7];
  for (int i=0;i<7;i++){
    //h[i]=new TH1D(ch,"photon_chiso[0]<0.441;photon_sieie[0];count",bin1,-0.01,0.09);
    sprintf(clos,"hlos%d",i);
    //hm[i]=new TH1D(Form("hm%d",i);photon_sieie[0];count",bin3,-0.005,0.020);
    hlos[i]=new TH1D(clos,";photon_sieie[0];count",bin,-0.005,0.018);
  }
  Long64_t n=t1->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t1->GetEntry(i);
    if (chiso_los<1.295){
      hlos[0]->Fill(sieie_los);
    }
    for(int i=1;i<7;i++){
      if (chiso_los>(Double_t)2.*i ){
        hlos[i]->Fill(sieie_los);
      }
    }
  }
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetLogy();
  TLegend *l1 = new TLegend(0.5,0.60,0.8,0.8);
  l1->SetBorderSize(2);
  l1->SetFillColor(0);
  for(int i=0;i<6;i++){
    c1->cd();
    histstyle(hlos[i], i, l1);
  }
  l1->Draw();
  c1->SaveAs("c1.eps");
}
void compare_los5(TTree* t2){
  Double_t sieie_los5;
  Double_t chiso_los5;

  t2->SetBranchAddress("sieie_los5",&sieie_los5);
  t2->SetBranchAddress("chiso_los5",&chiso_los5);
  TH1D *hlos5[7];
  char clos5[7];
  for (int i=0;i<7;i++){
    //h[i]=new TH1D(ch,"photon_chiso[0]<0.441;photon_sieie[0];count",bin1,-0.01,0.09);
    sprintf(clos5,"hlos5%d",i);
    //hm[i]=new TH1D(Form("hm%d",i);photon_sieie[0];count",bin3,-0.005,0.020);
    hlos5[i]=new TH1D(clos5,";photon_sieie[0];count",bin,-0.005,0.018);
  }
  Long64_t n=t2->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t2->GetEntry(i);
    if (chiso_los5<5*1.295){
      hlos5[0]->Fill(sieie_los5);
    }
    for(int i=1;i<7;i++){
      if (chiso_los5>(Double_t)2.*i ){
        hlos5[i]->Fill(sieie_los5);
      }
    }
  }
  TCanvas *c2 = new TCanvas("c2","c2");
  c2->SetLogy();
  TLegend *l2 = new TLegend(0.5,0.60,0.8,0.8);
  l2->SetBorderSize(2);
  l2->SetFillColor(0);
  for(int i=0;i<6;i++){
    c2->cd();
    histstyle(hlos5[i], i, l2);
  }
  l2->Draw();
  c2->SaveAs("c2.eps");
}

void compare(TTree* t0,TTree* t1,TTree* t2){
  Double_t sieie_med,sieie_los,sieie_los5;
  Double_t chiso_med,chiso_los,chiso_los5;

  t0->SetBranchAddress("sieie_med",&sieie_med);
  t0->SetBranchAddress("chiso_med",&chiso_med);

  t1->SetBranchAddress("sieie_los",&sieie_los);
  t1->SetBranchAddress("chiso_los",&chiso_los);

  t2->SetBranchAddress("sieie_los5",&sieie_los5);
  t2->SetBranchAddress("chiso_los5",&chiso_los5);
  /*TH1D *hmed[7];
  char cmed[7];
  for (int i=0;i<7;i++){
    //h[i]=new TH1D(ch,"photon_chiso[0]<0.441;photon_sieie[0];count",bin1,-0.01,0.09);
    sprintf(cmed,"hmed%d",i);
    //hm[i]=new TH1D(Form("hm%d",i);photon_sieie[0];count",bin3,-0.005,0.020);
    hmed[i]=new TH1D(cmed,";photon_sieie[0];count",bin,-0.005,0.018);
  }*/
  Long64_t n=t0->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t0->GetEntry(i);
    if (chiso_med<0.441){
      hmed0->Fill(sieie_med);
    }
    if (chiso_med>4 && chiso_med<10 ){
      hmed1->Fill(sieie_med);
    }
  }
  n=t1->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t1->GetEntry(i);
    if (chiso_los<1.295){
      hlos0->Fill(sieie_los);
    }
    if (chiso_los>4 && chiso_los<10 ){
      hlos1->Fill(sieie_los);
    }
  }
  n=t2->GetEntries();
  for(Long64_t i=0;i<n;i++){
    t2->GetEntry(i);
    if (chiso_los5<5*1.295){
      hlos50->Fill(sieie_los5);
    }
    if (chiso_los5>4 && chiso_los5<10 ){
      hlos51->Fill(sieie_los5);
    }
  }
  TCanvas *c0 = new TCanvas("c0","c0");
  c0->SetLogy();
  TLegend *l0 = new TLegend(0.5,0.60,0.8,0.8);
  l0->SetBorderSize(2);
  l0->SetFillColor(0);
  for(int i=0;i<6;i++){
    c0->cd();
    histstyle(hmed[i], i, l0);
  }
  l0->Draw();
  c0->SaveAs("c0.eps");
}
