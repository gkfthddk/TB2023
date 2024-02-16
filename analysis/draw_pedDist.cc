#include "TH1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TString.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TLatex.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    int runNum = std::stoi(argv[1]);

    TFile* f = TFile::Open(("./PedDistribution/PedDistribution_Run_"+std::to_string(runNum)+".root").c_str(), "READ");
    f->cd();
    gSystem->Exec( ("mkdir ./PedDistribution/Run_" + std::to_string(runNum)).c_str());

    TH1F* Hist_C_counter_1_Ped = (TH1F*) f->Get("C_counter_1_Ped");
    TH1F* Hist_C_counter_2_Ped = (TH1F*) f->Get("C_counter_2_Ped");
    TH1F* Hist_Trigger_1_Ped = (TH1F*) f->Get("Trigger_1_Ped");
    TH1F* Hist_Trigger_2_Ped = (TH1F*) f->Get("Trigger_2_Ped");
    
    TH1F* Hist_3D_mid_C_Ped = (TH1F*) f->Get("3D_mid_C_Ped");
    TH1F* Hist_3D_W1_C_Ped  = (TH1F*) f->Get("3D_W1_C_Ped");
    TH1F* Hist_3D_W2_C_Ped  = (TH1F*) f->Get("3D_W2_C_Ped");
    TH1F* Hist_3D_W3_C_Ped  = (TH1F*) f->Get("3D_W3_C_Ped");

    TH1F* Hist_3D_mid_S_Ped = (TH1F*) f->Get("3D_mid_S_Ped");
    TH1F* Hist_3D_W1_S_Ped  = (TH1F*) f->Get("3D_W1_S_Ped");
    TH1F* Hist_3D_W2_S_Ped  = (TH1F*) f->Get("3D_W2_S_Ped");
    TH1F* Hist_3D_W3_S_Ped  = (TH1F*) f->Get("3D_W3_S_Ped");

    TH1F* Hist_HW_C_Ped = (TH1F*) f->Get("HS_W_C_Ped");
    TH1F* Hist_H1_C_Ped = (TH1F*) f->Get("HS_1_C_Ped");
    TH1F* Hist_H2_C_Ped = (TH1F*) f->Get("HS_2_C_Ped");
    TH1F* Hist_H3_C_Ped = (TH1F*) f->Get("HS_3_C_Ped");

    TH1F* Hist_HW_S_Ped = (TH1F*) f->Get("HS_W_S_Ped");
    TH1F* Hist_H1_S_Ped = (TH1F*) f->Get("HS_1_S_Ped");
    TH1F* Hist_H2_S_Ped = (TH1F*) f->Get("HS_2_S_Ped");
    TH1F* Hist_H3_S_Ped = (TH1F*) f->Get("HS_3_S_Ped");

    TH1F* Hist_L1_C_Ped = (TH1F*) f->Get("L_1_C_Ped");
    TH1F* Hist_L2_C_Ped = (TH1F*) f->Get("L_2_C_Ped");
    TH1F* Hist_L3_C_Ped = (TH1F*) f->Get("L_3_C_Ped");
    TH1F* Hist_L4_C_Ped = (TH1F*) f->Get("L_4_C_Ped");

    TH1F* Hist_L1_S_Ped = (TH1F*) f->Get("L_1_S_Ped");
    TH1F* Hist_L2_S_Ped = (TH1F*) f->Get("L_2_S_Ped");
    TH1F* Hist_L3_S_Ped = (TH1F*) f->Get("L_3_S_Ped");
    TH1F* Hist_L4_S_Ped = (TH1F*) f->Get("L_4_S_Ped");

    std::map<std::string, float>* pMap;
    f->GetObject("runPedMap", pMap);
    std::map<std::string, float> runPedMap = *pMap;

    float RunPed_C_counter_1 = runPedMap.at("C_counter_1");
    float RunPed_C_counter_2 = runPedMap.at("C_counter_2");
    float RunPed_Trigger_1   = runPedMap.at("Trigger_1");
    float RunPed_Trigger_2   = runPedMap.at("Trigger_2");

    float RunPed_3D_mid_C = runPedMap.at("3D_mid_C");
    float RunPed_3D_W1_C  = runPedMap.at("3D_W_1_C");
    float RunPed_3D_W2_C  = runPedMap.at("3D_W_2_C");
    float RunPed_3D_W3_C  = runPedMap.at("3D_W_3_C");
    float RunPed_H_W_C    = runPedMap.at("HS_W_C");
    float RunPed_H_1_C    = runPedMap.at("HS_1_C");
    float RunPed_H_2_C    = runPedMap.at("HS_2_C");
    float RunPed_H_3_C    = runPedMap.at("HS_3_C");
    float RunPed_L_1_C    = runPedMap.at("L_1_C");
    float RunPed_L_2_C    = runPedMap.at("L_2_C");
    float RunPed_L_3_C    = runPedMap.at("L_3_C");
    float RunPed_L_4_C    = runPedMap.at("L_4_C");

    float RunPed_3D_mid_S = runPedMap.at("3D_mid_S");
    float RunPed_3D_W1_S  = runPedMap.at("3D_W_1_S");
    float RunPed_3D_W2_S  = runPedMap.at("3D_W_2_S");
    float RunPed_3D_W3_S  = runPedMap.at("3D_W_3_S");
    float RunPed_H_W_S    = runPedMap.at("HS_W_S");
    float RunPed_H_1_S    = runPedMap.at("HS_1_S");
    float RunPed_H_2_S    = runPedMap.at("HS_2_S");
    float RunPed_H_3_S    = runPedMap.at("HS_3_S");
    float RunPed_L_1_S    = runPedMap.at("L_1_S");
    float RunPed_L_2_S    = runPedMap.at("L_2_S");
    float RunPed_L_3_S    = runPedMap.at("L_3_S");
    float RunPed_L_4_S    = runPedMap.at("L_4_S");

    // float RunPed_C_counter_1 = Hist_C_counter_1_Ped->GetMean();
    // float RunPed_C_counter_2 = Hist_C_counter_2_Ped->GetMean();
    // float RunPed_Trigger_1   = Hist_Trigger_1_Ped->GetMean();
    // float RunPed_Trigger_2   = Hist_Trigger_2_Ped->GetMean();

    // float RunPed_3D_mid_C = Hist_3D_mid_C_Ped->GetMean();
    // float RunPed_3D_W1_C  = Hist_3D_W1_C_Ped->GetMean();
    // float RunPed_3D_W2_C  = Hist_3D_W2_C_Ped->GetMean();
    // float RunPed_3D_W3_C  = Hist_3D_W3_C_Ped->GetMean();
    // float RunPed_H_W_C    = Hist_HW_C_Ped->GetMean();
    // float RunPed_H_1_C    = Hist_H1_C_Ped->GetMean();
    // float RunPed_H_2_C    = Hist_H2_C_Ped->GetMean();
    // float RunPed_H_3_C    = Hist_H3_C_Ped->GetMean();
    // float RunPed_L_1_C    = Hist_L1_C_Ped->GetMean();
    // float RunPed_L_2_C    = Hist_L2_C_Ped->GetMean();
    // float RunPed_L_3_C    = Hist_L3_C_Ped->GetMean();
    // float RunPed_L_4_C    = Hist_L4_C_Ped->GetMean();

    // float RunPed_3D_mid_S = Hist_3D_mid_S_Ped->GetMean();
    // float RunPed_3D_W1_S  = Hist_3D_W1_S_Ped->GetMean();
    // float RunPed_3D_W2_S  = Hist_3D_W2_S_Ped->GetMean();
    // float RunPed_3D_W3_S  = Hist_3D_W3_S_Ped->GetMean();
    // float RunPed_H_W_S    = Hist_HW_S_Ped->GetMean();
    // float RunPed_H_1_S    = Hist_H1_S_Ped->GetMean();
    // float RunPed_H_2_S    = Hist_H2_S_Ped->GetMean();
    // float RunPed_H_3_S    = Hist_H3_S_Ped->GetMean();
    // float RunPed_L_1_S    = Hist_L1_S_Ped->GetMean();
    // float RunPed_L_2_S    = Hist_L2_S_Ped->GetMean();
    // float RunPed_L_3_S    = Hist_L3_S_Ped->GetMean();
    // float RunPed_L_4_S    = Hist_L4_S_Ped->GetMean();

    TCanvas* c = new TCanvas("c", "c", 1000, 1000);
    TLine* l = new TLine(0., 0., 0., 0.);
    l->SetLineColor(kRed);
    TLatex* t = new TLatex();
    t->SetTextSize(0.03);
    
    c->cd();
    Hist_C_counter_1_Ped->SetStats(0);
    Hist_C_counter_1_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_C_counter_1_Ped->Draw();
    l->SetX1(RunPed_C_counter_1);
    l->SetX2(RunPed_C_counter_1);
    l->SetY2(Hist_C_counter_1_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_C_counter_1_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_C_counter_1_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_C_counter_1_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );
    
    c->cd();
    Hist_C_counter_2_Ped->SetStats(0);
    Hist_C_counter_2_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_C_counter_2_Ped->Draw();
    l->SetX1(RunPed_C_counter_2);
    l->SetX2(RunPed_C_counter_2);
    l->SetY2(Hist_C_counter_2_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_C_counter_2_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_C_counter_2_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_C_counter_2_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );
    
    c->cd();
    Hist_Trigger_1_Ped->SetStats(0);
    Hist_Trigger_1_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_Trigger_1_Ped->Draw();
    l->SetX1(RunPed_Trigger_1);
    l->SetX2(RunPed_Trigger_1);
    l->SetY2(Hist_Trigger_1_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_Trigger_1_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_Trigger_1_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_Trigger_1_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );
    
    c->cd();
    Hist_Trigger_2_Ped->SetStats(0);
    Hist_Trigger_2_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_Trigger_2_Ped->Draw();
    l->SetX1(RunPed_Trigger_2);
    l->SetX2(RunPed_Trigger_2);
    l->SetY2(Hist_Trigger_2_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_Trigger_2_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_Trigger_2_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_Trigger_2_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );
    
    c->cd();
    Hist_3D_mid_C_Ped->SetStats(0);
    Hist_3D_mid_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_mid_C_Ped->Draw();
    l->SetX1(RunPed_3D_mid_C);
    l->SetX2(RunPed_3D_mid_C);
    l->SetY2(Hist_3D_mid_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_mid_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_mid_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_mid_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_3D_W1_C_Ped->SetStats(0);
    Hist_3D_W1_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_W1_C_Ped->Draw();
    l->SetX1(RunPed_3D_W1_C);
    l->SetX2(RunPed_3D_W1_C);
    l->SetY2(Hist_3D_W1_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_W1_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_W1_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_W1_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_3D_W2_C_Ped->SetStats(0);
    Hist_3D_W2_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_W2_C_Ped->Draw();
    l->SetX1(RunPed_3D_W2_C);
    l->SetX2(RunPed_3D_W2_C);
    l->SetY2(Hist_3D_W2_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_W2_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_W2_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_W2_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_3D_W3_C_Ped->SetStats(0);
    Hist_3D_W3_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_W3_C_Ped->Draw();
    l->SetX1(RunPed_3D_W3_C);
    l->SetX2(RunPed_3D_W3_C);
    l->SetY2(Hist_3D_W3_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_W3_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_W3_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_W3_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );


    c->cd();
    Hist_HW_C_Ped->SetStats(0);
    Hist_HW_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_HW_C_Ped->Draw();
    l->SetX1(RunPed_H_W_C);
    l->SetX2(RunPed_H_W_C);
    l->SetY2(Hist_HW_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_HW_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_HW_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_HW_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_H1_C_Ped->SetStats(0);
    Hist_H1_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_H1_C_Ped->Draw();
    l->SetX1(RunPed_H_1_C);
    l->SetX2(RunPed_H_1_C);
    l->SetY2(Hist_H1_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_H1_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_H1_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_H1_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_H2_C_Ped->SetStats(0);
    Hist_H2_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_H2_C_Ped->Draw();
    l->SetX1(RunPed_H_2_C);
    l->SetX2(RunPed_H_2_C);
    l->SetY2(Hist_H2_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_H2_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_H2_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_H2_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_H3_C_Ped->SetStats(0);
    Hist_H3_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_H3_C_Ped->Draw();
    l->SetX1(RunPed_H_3_C);
    l->SetX2(RunPed_H_3_C);
    l->SetY2(Hist_H3_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_H3_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_H3_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_H3_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L1_C_Ped->SetStats(0);
    Hist_L1_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L1_C_Ped->Draw();
    l->SetX1(RunPed_L_1_C);
    l->SetX2(RunPed_L_1_C);
    l->SetY2(Hist_L1_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L1_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L1_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L1_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L2_C_Ped->SetStats(0);
    Hist_L2_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L2_C_Ped->Draw();
    l->SetX1(RunPed_L_2_C);
    l->SetX2(RunPed_L_2_C);
    l->SetY2(Hist_L2_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L2_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L2_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L2_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L3_C_Ped->SetStats(0);
    Hist_L3_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L3_C_Ped->Draw();
    l->SetX1(RunPed_L_3_C);
    l->SetX2(RunPed_L_3_C);
    l->SetY2(Hist_L3_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L3_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L3_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L3_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L4_C_Ped->SetStats(0);
    Hist_L4_C_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L4_C_Ped->Draw();
    l->SetX1(RunPed_L_4_C);
    l->SetX2(RunPed_L_4_C);
    l->SetY2(Hist_L4_C_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L4_C_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L4_C_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L4_C_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_3D_mid_S_Ped->SetStats(0);
    Hist_3D_mid_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_mid_S_Ped->Draw();
    l->SetX1(RunPed_3D_mid_S);
    l->SetX2(RunPed_3D_mid_S);
    l->SetY2(Hist_3D_mid_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_mid_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_mid_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_mid_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_3D_W1_S_Ped->SetStats(0);
    Hist_3D_W1_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_W1_S_Ped->Draw();
    l->SetX1(RunPed_3D_W1_S);
    l->SetX2(RunPed_3D_W1_S);
    l->SetY2(Hist_3D_W1_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_W1_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_W1_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_W1_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_3D_W2_S_Ped->SetStats(0);
    Hist_3D_W2_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_W2_S_Ped->Draw();
    l->SetX1(RunPed_3D_W2_S);
    l->SetX2(RunPed_3D_W2_S);
    l->SetY2(Hist_3D_W2_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_W2_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_W2_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_W2_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_3D_W3_S_Ped->SetStats(0);
    Hist_3D_W3_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_3D_W3_S_Ped->Draw();
    l->SetX1(RunPed_3D_W3_S);
    l->SetX2(RunPed_3D_W3_S);
    l->SetY2(Hist_3D_W3_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_3D_W3_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_3D_W3_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_3D_W3_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );


    c->cd();
    Hist_HW_S_Ped->SetStats(0);
    Hist_HW_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_HW_S_Ped->Draw();
    l->SetX1(RunPed_H_W_S);
    l->SetX2(RunPed_H_W_S);
    l->SetY2(Hist_HW_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_HW_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_HW_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_HW_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_H1_S_Ped->SetStats(0);
    Hist_H1_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_H1_S_Ped->Draw();
    l->SetX1(RunPed_H_1_S);
    l->SetX2(RunPed_H_1_S);
    l->SetY2(Hist_H1_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_H1_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_H1_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_H1_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_H2_S_Ped->SetStats(0);
    Hist_H2_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_H2_S_Ped->Draw();
    l->SetX1(RunPed_H_2_S);
    l->SetX2(RunPed_H_2_S);
    l->SetY2(Hist_H2_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_H2_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_H2_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_H2_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_H3_S_Ped->SetStats(0);
    Hist_H3_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_H3_S_Ped->Draw();
    l->SetX1(RunPed_H_3_S);
    l->SetX2(RunPed_H_3_S);
    l->SetY2(Hist_H3_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_H3_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_H3_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_H3_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L1_S_Ped->SetStats(0);
    Hist_L1_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L1_S_Ped->Draw();
    l->SetX1(RunPed_L_1_S);
    l->SetX2(RunPed_L_1_S);
    l->SetY2(Hist_L1_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L1_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L1_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L1_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L2_S_Ped->SetStats(0);
    Hist_L2_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L2_S_Ped->Draw();
    l->SetX1(RunPed_L_2_S);
    l->SetX2(RunPed_L_2_S);
    l->SetY2(Hist_L2_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L2_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L2_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L2_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L3_S_Ped->SetStats(0);
    Hist_L3_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L3_S_Ped->Draw();
    l->SetX1(RunPed_L_3_S);
    l->SetX2(RunPed_L_3_S);
    l->SetY2(Hist_L3_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L3_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L3_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L3_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );

    c->cd();
    Hist_L4_S_Ped->SetStats(0);
    Hist_L4_S_Ped->GetXaxis()->SetRangeUser(3000, 4000);
    Hist_L4_S_Ped->Draw();
    l->SetX1(RunPed_L_4_S);
    l->SetX2(RunPed_L_4_S);
    l->SetY2(Hist_L4_S_Ped->GetMaximum());
    l->Draw();
    t->DrawLatexNDC(0.15, 0.8, ("Mean : " + std::to_string(Hist_L4_S_Ped->GetMean())).c_str() );
    t->DrawLatexNDC(0.15, 0.75, ("Std : " + std::to_string(Hist_L4_S_Ped->GetStdDev())).c_str() );
    c->SaveAs( ("./PedDistribution/Run_" + std::to_string(runNum) + "/Hist_L4_S_Ped_Run_" + std::to_string(runNum) + ".png").c_str() );
    }