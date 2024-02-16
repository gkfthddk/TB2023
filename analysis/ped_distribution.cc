#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "TBevt.h"
#include "TButility.h"

#include "functions.cc"

#include "TStyle.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

int main(int argc, char** argv) {
    int runNum   = std::stoi(argv[1]);
    int maxEntry = std::stoi(argv[2]);

    // Hist for Pedestal distribution (Evt-by-evt)
    TH1F* Hist_C_counter_1_Ped = new TH1F("C_counter_1_Ped", "C_counter_1_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_C_counter_2_Ped = new TH1F("C_counter_2_Ped", "C_counter_2_Ped;ADC;Evt", 4096, 0, 4096);

    TH1F* Hist_Trigger_1_Ped = new TH1F("Trigger_1_Ped", "Trigger_1_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_Trigger_2_Ped = new TH1F("Trigger_2_Ped", "Trigger_2_Ped;ADC;Evt", 4096, 0, 4096);

    TH1F* Hist_3D_mid_C_Ped = new TH1F("3D_mid_C_Ped", "3D_mid_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_3D_mid_S_Ped = new TH1F("3D_mid_S_Ped", "3D_mid_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_3D_W1_C_Ped  = new TH1F("3D_W1_C_Ped", "3D_W1_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_3D_W1_S_Ped  = new TH1F("3D_W1_S_Ped", "3D_W1_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_3D_W2_C_Ped  = new TH1F("3D_W2_C_Ped", "3D_W2_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_3D_W2_S_Ped  = new TH1F("3D_W2_S_Ped", "3D_W2_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_3D_W3_C_Ped  = new TH1F("3D_W3_C_Ped", "3D_W3_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_3D_W3_S_Ped  = new TH1F("3D_W3_S_Ped", "3D_W3_S_Ped;ADC;Evt", 4096, 0, 4096);

    TH1F* Hist_HW_C_Ped = new TH1F("HS_W_C_Ped", "HS_W_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_HW_S_Ped = new TH1F("HS_W_S_Ped", "HS_W_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_H1_C_Ped = new TH1F("HS_1_C_Ped", "HS_1_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_H1_S_Ped = new TH1F("HS_1_S_Ped", "HS_1_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_H2_C_Ped = new TH1F("HS_2_C_Ped", "HS_2_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_H2_S_Ped = new TH1F("HS_2_S_Ped", "HS_2_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_H3_C_Ped = new TH1F("HS_3_C_Ped", "HS_3_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_H3_S_Ped = new TH1F("HS_3_S_Ped", "HS_3_S_Ped;ADC;Evt", 4096, 0, 4096);

    TH1F* Hist_L1_C_Ped = new TH1F("L_1_C_Ped", "L_1_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_L1_S_Ped = new TH1F("L_1_S_Ped", "L_1_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_L2_C_Ped = new TH1F("L_2_C_Ped", "L_2_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_L2_S_Ped = new TH1F("L_2_S_Ped", "L_2_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_L3_C_Ped = new TH1F("L_3_C_Ped", "L_3_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_L3_S_Ped = new TH1F("L_3_S_Ped", "L_3_S_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_L4_C_Ped = new TH1F("L_4_C_Ped", "L_4_C_Ped;ADC;Evt", 4096, 0, 4096);
    TH1F* Hist_L4_S_Ped = new TH1F("L_4_S_Ped", "L_4_S_Ped;ADC;Evt", 4096, 0, 4096);

    // Load mapping
    auto map = getModuleConfigMap();

    std::vector<TBcid> CID_C_counter = {TBcid( map.at("C1").at(0), map.at("C1").at(1)),
                                        TBcid( map.at("C1").at(0), map.at("C2").at(1))};

    std::vector<TBcid> CID_Trigger = {  TBcid( map.at("T1").at(0), map.at("T1").at(1)),
                                        TBcid( map.at("T2").at(0), map.at("T2").at(1))};

    std::vector<TBcid> CID_3D_C = { TBcid( map.at("mid-Ceren").at(0),  map.at("mid-Ceren").at(1) ),
                                    TBcid( map.at("W1-Ceren").at(0),   map.at("W1-Ceren").at(1)  ),
                                    TBcid( map.at("W2-Ceren").at(0),   map.at("W2-Ceren").at(1)  ),
                                    TBcid( map.at("W3-Ceren").at(0),   map.at("W3-Ceren").at(1)  )};

    std::vector<TBcid> CID_3D_S = { TBcid( map.at("mid-Scint").at(0),  map.at("mid-Scint").at(1) ),
                                    TBcid( map.at("W1-Scint").at(0),   map.at("W1-Scint").at(1)  ),
                                    TBcid( map.at("W2-Scint").at(0),   map.at("W2-Scint").at(1)  ),
                                    TBcid( map.at("W3-Scint").at(0),   map.at("W3-Scint").at(1)  )};

    std::vector<TBcid> CID_HeatSink_C= {TBcid( map.at("HW-Ceren").at(0),  map.at("HW-Ceren").at(1) ),
                                        TBcid( map.at("H1-Ceren").at(0),  map.at("H1-Ceren").at(1) ),
                                        TBcid( map.at("H2-Ceren").at(0),  map.at("H2-Ceren").at(1) ),
                                        TBcid( map.at("H3-Ceren").at(0),  map.at("H3-Ceren").at(1) )};

    std::vector<TBcid> CID_HeatSink_S= {TBcid( map.at("HW-Scint").at(0),  map.at("HW-Scint").at(1) ),
                                        TBcid( map.at("H1-Scint").at(0),  map.at("H1-Scint").at(1) ),
                                        TBcid( map.at("H2-Scint").at(0),  map.at("H2-Scint").at(1) ),
                                        TBcid( map.at("H3-Scint").at(0),  map.at("H3-Scint").at(1) )};

    std::vector<TBcid> CID_Lego_C= {TBcid( map.at("L1-Ceren").at(0),  map.at("L1-Ceren").at(1) ),
                                    TBcid( map.at("L2-Ceren").at(0),  map.at("L2-Ceren").at(1) ),
                                    TBcid( map.at("L3-Ceren").at(0),  map.at("L3-Ceren").at(1) ),
                                    TBcid( map.at("L4-Ceren").at(0),  map.at("L4-Ceren").at(1) )};

    std::vector<TBcid> CID_Lego_S= {TBcid( map.at("L1-Scint").at(0),  map.at("L1-Scint").at(1) ),
                                    TBcid( map.at("L2-Scint").at(0),  map.at("L2-Scint").at(1) ),
                                    TBcid( map.at("L3-Scint").at(0),  map.at("L3-Scint").at(1) ),
                                    TBcid( map.at("L4-Scint").at(0),  map.at("L4-Scint").at(1) )};

    // Load pedestal
    TH2F* pedMap = (TH2F*) (TFile::Open(("/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2023_DRC_TB_analysis/ped/Run_" + std::to_string(runNum) +"_pedestal.root").c_str()) )->Get("pedestal"); // By using pedestal map directly
    
    std::map<std::string, float> runPed;
    float RunPed_C_counter_1 = pedMap->GetBinContent( CID_C_counter.at(0).mid(), CID_C_counter.at(0).channel() ); runPed.insert( std::make_pair("C_counter_1", RunPed_C_counter_1) );
    float RunPed_C_counter_2 = pedMap->GetBinContent( CID_C_counter.at(1).mid(), CID_C_counter.at(1).channel() ); runPed.insert( std::make_pair("C_counter_2", RunPed_C_counter_2) );
    float RunPed_Trigger_1   = pedMap->GetBinContent( CID_Trigger.at(0).mid(), CID_Trigger.at(0).channel() ); runPed.insert( std::make_pair("Trigger_1", RunPed_Trigger_1) );
    float RunPed_Trigger_2   = pedMap->GetBinContent( CID_Trigger.at(1).mid(), CID_Trigger.at(1).channel() ); runPed.insert( std::make_pair("Trigger_2", RunPed_Trigger_2) );

    float RunPed_3D_mid_C = pedMap->GetBinContent( CID_3D_C.at(0).mid(), CID_3D_C.at(0).channel() ); runPed.insert( std::make_pair("3D_mid_C", RunPed_3D_mid_C) );
    float RunPed_3D_W1_C  = pedMap->GetBinContent( CID_3D_C.at(1).mid(), CID_3D_C.at(1).channel() ); runPed.insert( std::make_pair("3D_W_1_C", RunPed_3D_W1_C) );
    float RunPed_3D_W2_C  = pedMap->GetBinContent( CID_3D_C.at(2).mid(), CID_3D_C.at(2).channel() ); runPed.insert( std::make_pair("3D_W_2_C", RunPed_3D_W2_C) );
    float RunPed_3D_W3_C  = pedMap->GetBinContent( CID_3D_C.at(3).mid(), CID_3D_C.at(3).channel() ); runPed.insert( std::make_pair("3D_W_3_C", RunPed_3D_W3_C) );
    float RunPed_H_W_C    = pedMap->GetBinContent( CID_HeatSink_C.at(0).mid(), CID_HeatSink_C.at(0).channel() ); runPed.insert( std::make_pair("HS_W_C", RunPed_H_W_C) );
    float RunPed_H_1_C    = pedMap->GetBinContent( CID_HeatSink_C.at(1).mid(), CID_HeatSink_C.at(1).channel() ); runPed.insert( std::make_pair("HS_1_C", RunPed_H_1_C) );
    float RunPed_H_2_C    = pedMap->GetBinContent( CID_HeatSink_C.at(2).mid(), CID_HeatSink_C.at(2).channel() ); runPed.insert( std::make_pair("HS_2_C", RunPed_H_2_C) );
    float RunPed_H_3_C    = pedMap->GetBinContent( CID_HeatSink_C.at(3).mid(), CID_HeatSink_C.at(3).channel() ); runPed.insert( std::make_pair("HS_3_C", RunPed_H_3_C) );
    float RunPed_L_1_C    = pedMap->GetBinContent( CID_Lego_C.at(0).mid(), CID_Lego_C.at(0).channel() ); runPed.insert( std::make_pair("L_1_C", RunPed_L_1_C) );
    float RunPed_L_2_C    = pedMap->GetBinContent( CID_Lego_C.at(1).mid(), CID_Lego_C.at(1).channel() ); runPed.insert( std::make_pair("L_2_C", RunPed_L_2_C) );
    float RunPed_L_3_C    = pedMap->GetBinContent( CID_Lego_C.at(2).mid(), CID_Lego_C.at(2).channel() ); runPed.insert( std::make_pair("L_3_C", RunPed_L_3_C) );
    float RunPed_L_4_C    = pedMap->GetBinContent( CID_Lego_C.at(3).mid(), CID_Lego_C.at(3).channel() ); runPed.insert( std::make_pair("L_4_C", RunPed_L_4_C) );

    float RunPed_3D_mid_S = pedMap->GetBinContent( CID_3D_S.at(0).mid(), CID_3D_S.at(0).channel() ); runPed.insert( std::make_pair("3D_mid_S", RunPed_3D_mid_S) );
    float RunPed_3D_W1_S  = pedMap->GetBinContent( CID_3D_S.at(1).mid(), CID_3D_S.at(1).channel() ); runPed.insert( std::make_pair("3D_W_1_S", RunPed_3D_W1_S) );
    float RunPed_3D_W2_S  = pedMap->GetBinContent( CID_3D_S.at(2).mid(), CID_3D_S.at(2).channel() ); runPed.insert( std::make_pair("3D_W_2_S", RunPed_3D_W2_S) );
    float RunPed_3D_W3_S  = pedMap->GetBinContent( CID_3D_S.at(3).mid(), CID_3D_S.at(3).channel() ); runPed.insert( std::make_pair("3D_W_3_S", RunPed_3D_W3_S) );
    float RunPed_H_W_S    = pedMap->GetBinContent( CID_HeatSink_S.at(0).mid(), CID_HeatSink_S.at(0).channel() ); runPed.insert( std::make_pair("HS_W_S", RunPed_H_W_S) );
    float RunPed_H_1_S    = pedMap->GetBinContent( CID_HeatSink_S.at(1).mid(), CID_HeatSink_S.at(1).channel() ); runPed.insert( std::make_pair("HS_1_S", RunPed_H_1_S) );
    float RunPed_H_2_S    = pedMap->GetBinContent( CID_HeatSink_S.at(2).mid(), CID_HeatSink_S.at(2).channel() ); runPed.insert( std::make_pair("HS_2_S", RunPed_H_2_S) );
    float RunPed_H_3_S    = pedMap->GetBinContent( CID_HeatSink_S.at(3).mid(), CID_HeatSink_S.at(3).channel() ); runPed.insert( std::make_pair("HS_3_S", RunPed_H_3_S) );
    float RunPed_L_1_S    = pedMap->GetBinContent( CID_Lego_S.at(0).mid(), CID_Lego_S.at(0).channel() ); runPed.insert( std::make_pair("L_1_S", RunPed_L_1_S) );
    float RunPed_L_2_S    = pedMap->GetBinContent( CID_Lego_S.at(1).mid(), CID_Lego_S.at(1).channel() ); runPed.insert( std::make_pair("L_2_S", RunPed_L_2_S) );
    float RunPed_L_3_S    = pedMap->GetBinContent( CID_Lego_S.at(2).mid(), CID_Lego_S.at(2).channel() ); runPed.insert( std::make_pair("L_3_S", RunPed_L_3_S) );
    float RunPed_L_4_S    = pedMap->GetBinContent( CID_Lego_S.at(3).mid(), CID_Lego_S.at(3).channel() ); runPed.insert( std::make_pair("L_4_S", RunPed_L_4_S) );

    // Load Ntuple using TChain
    TChain* evtChain = new TChain("event");
    for (int fn = 0; fn < 50; fn++) {
        std::string fileName = "ntuple_Run_" + std::to_string(runNum) + "_Wave_" + std::to_string(fn) + ".root";
        std::string filePath = "/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2023_DRC_TB_ntuple/Run_"  + std::to_string(runNum) + "/Run_" + std::to_string(runNum) + "_Wave/"+ fileName;
        if ( !access(filePath.c_str(), F_OK) ){
            std::cout << fn << " Ntuple file added to TChain : " << filePath << std::endl;
            evtChain->Add(filePath.c_str());
        }
    }
    TBevt<TBwaveform>* anEvt = new TBevt<TBwaveform>(); // Will use waveform data
    evtChain->SetBranchAddress("TBevt", &anEvt);

    // Check total # of events, limit # of events to process if maxEntry is specified
    int totalEntry = evtChain->GetEntries();
    std::cout << "Total entries : " << totalEntry << std::endl;
    if ( (maxEntry > 0) && (maxEntry < totalEntry) ) {
        totalEntry = maxEntry;
        std::cout << "Will process maximum " << std::to_string(totalEntry) << " events" << std::endl;
    }

    for (int iEvt = 0; iEvt < totalEntry; iEvt++) {
        printProgress(iEvt + 1, totalEntry);
        evtChain->GetEntry(iEvt);

        // TBwaveform
        std::vector<TBwaveform> Data_C_counter;
        for(TBcid cid : CID_C_counter) {
            Data_C_counter.push_back(anEvt->GetData(cid));
        }

        std::vector<TBwaveform> Data_Trigger;
        for(TBcid cid : CID_Trigger) {
            Data_Trigger.push_back(anEvt->GetData(cid));
        }

        std::vector<TBwaveform> Data_3D_C;
        for(TBcid cid : CID_3D_C) {
            Data_3D_C.push_back(anEvt->GetData(cid));
        }
        std::vector<TBwaveform> Data_3D_S;
        for(TBcid cid : CID_3D_S) {
            Data_3D_S.push_back(anEvt->GetData(cid));
        }

        std::vector<TBwaveform> Data_HeatSink_C;
        for(TBcid cid : CID_HeatSink_C) {
            Data_HeatSink_C.push_back(anEvt->GetData(cid));
        }
        std::vector<TBwaveform> Data_HeatSink_S;
        for(TBcid cid : CID_HeatSink_S) {
            Data_HeatSink_S.push_back(anEvt->GetData(cid));
        }

        std::vector<TBwaveform> Data_Lego_C;
        for(TBcid cid : CID_Lego_C) {
            Data_Lego_C.push_back(anEvt->GetData(cid));
        }
        std::vector<TBwaveform> Data_Lego_S;
        for(TBcid cid : CID_Lego_S) {
            Data_Lego_S.push_back(anEvt->GetData(cid));
        }

        // Waveform vector
        std::vector< std::vector<short> > Wave_C_counter;
        for(TBwaveform data : Data_C_counter) {
            Wave_C_counter.push_back(data.waveform());
        }

        std::vector< std::vector<short> > Wave_Trigger;
        for(TBwaveform data : Data_Trigger) {
            Wave_Trigger.push_back(data.waveform());
        }
        
        std::vector< std::vector<short> > Wave_3D_C;
        for(TBwaveform data : Data_3D_C) {
            Wave_3D_C.push_back(data.waveform());
        }
        std::vector< std::vector<short> > Wave_3D_S;
        for(TBwaveform data : Data_3D_S) {
            Wave_3D_S.push_back(data.waveform());
        }

        std::vector< std::vector<short> > Wave_HeatSink_C;
        for(TBwaveform data : Data_HeatSink_C) {
            Wave_HeatSink_C.push_back(data.waveform());
        }
        std::vector< std::vector<short> > Wave_HeatSink_S;
        for(TBwaveform data : Data_HeatSink_S) {
            Wave_HeatSink_S.push_back(data.waveform());
        }

        std::vector< std::vector<short> > Wave_Lego_C;
        for(TBwaveform data : Data_Lego_C) {
            Wave_Lego_C.push_back(data.waveform());
        }
        std::vector< std::vector<short> > Wave_Lego_S;
        for(TBwaveform data : Data_Lego_S) {
            Wave_Lego_S.push_back(data.waveform());
        }

        // Evt-by-evt pedestal
        float EvtPed_C_counter_1 = 0.f;
        float EvtPed_C_counter_2 = 0.f;
        float EvtPed_Trigger_1   = 0.f;
        float EvtPed_Trigger_2   = 0.f;
        float EvtPed_3D_mid_C = 0.f;
        float EvtPed_3D_W1_C  = 0.f;
        float EvtPed_3D_W2_C  = 0.f;
        float EvtPed_3D_W3_C  = 0.f;
        float EvtPed_HW_C     = 0.f;
        float EvtPed_H1_C     = 0.f;
        float EvtPed_H2_C     = 0.f;
        float EvtPed_H3_C     = 0.f;
        float EvtPed_L1_C     = 0.f;
        float EvtPed_L2_C     = 0.f;
        float EvtPed_L3_C     = 0.f;
        float EvtPed_L4_C     = 0.f;
        float EvtPed_3D_mid_S = 0.f;
        float EvtPed_3D_W1_S  = 0.f;
        float EvtPed_3D_W2_S  = 0.f;
        float EvtPed_3D_W3_S  = 0.f;
        float EvtPed_HW_S     = 0.f;
        float EvtPed_H1_S     = 0.f;
        float EvtPed_H2_S     = 0.f;
        float EvtPed_H3_S     = 0.f;
        float EvtPed_L1_S     = 0.f;
        float EvtPed_L2_S     = 0.f;
        float EvtPed_L3_S     = 0.f;
        float EvtPed_L4_S     = 0.f;
        for(int bin = 1; bin < 101; bin++) {
            EvtPed_C_counter_1 += (float) (Wave_C_counter.at(0)[bin] / 100.);
            EvtPed_C_counter_2 += (float) (Wave_C_counter.at(1)[bin] / 100.);
            EvtPed_Trigger_1   += (float) (Wave_Trigger.at(0)[bin] / 100.);
            EvtPed_Trigger_2   += (float) (Wave_Trigger.at(1)[bin] / 100.);
            EvtPed_3D_mid_C += (float) (Wave_3D_C.at(0)[bin] / 100.);      
            EvtPed_3D_W1_C  += (float) (Wave_3D_C.at(1)[bin] / 100.);
            EvtPed_3D_W2_C  += (float) (Wave_3D_C.at(2)[bin] / 100.);
            EvtPed_3D_W3_C  += (float) (Wave_3D_C.at(3)[bin] / 100.);
            EvtPed_HW_C     += (float) (Wave_HeatSink_C.at(0)[bin] / 100.);
            EvtPed_H1_C     += (float) (Wave_HeatSink_C.at(1)[bin] / 100.);
            EvtPed_H2_C     += (float) (Wave_HeatSink_C.at(2)[bin] / 100.);
            EvtPed_H3_C     += (float) (Wave_HeatSink_C.at(3)[bin] / 100.);
            EvtPed_L1_C     += (float) (Wave_Lego_C.at(0)[bin] / 100.);
            EvtPed_L2_C     += (float) (Wave_Lego_C.at(1)[bin] / 100.);
            EvtPed_L3_C     += (float) (Wave_Lego_C.at(2)[bin] / 100.);
            EvtPed_L4_C     += (float) (Wave_Lego_C.at(3)[bin] / 100.);
            EvtPed_3D_mid_S += (float) (Wave_3D_S.at(0)[bin] / 100.);      
            EvtPed_3D_W1_S  += (float) (Wave_3D_S.at(1)[bin] / 100.);
            EvtPed_3D_W2_S  += (float) (Wave_3D_S.at(2)[bin] / 100.);
            EvtPed_3D_W3_S  += (float) (Wave_3D_S.at(3)[bin] / 100.);
            EvtPed_HW_S     += (float) (Wave_HeatSink_S.at(0)[bin] / 100.);
            EvtPed_H1_S     += (float) (Wave_HeatSink_S.at(1)[bin] / 100.);
            EvtPed_H2_S     += (float) (Wave_HeatSink_S.at(2)[bin] / 100.);
            EvtPed_H3_S     += (float) (Wave_HeatSink_S.at(3)[bin] / 100.);
            EvtPed_L1_S     += (float) (Wave_Lego_S.at(0)[bin] / 100.);
            EvtPed_L2_S     += (float) (Wave_Lego_S.at(1)[bin] / 100.);
            EvtPed_L3_S     += (float) (Wave_Lego_S.at(2)[bin] / 100.);
            EvtPed_L4_S     += (float) (Wave_Lego_S.at(3)[bin] / 100.);
        }

        // Fill evt ped
        Hist_C_counter_1_Ped->Fill(EvtPed_C_counter_1);
        Hist_C_counter_2_Ped->Fill(EvtPed_C_counter_2);

        Hist_Trigger_1_Ped->Fill(EvtPed_Trigger_1);
        Hist_Trigger_2_Ped->Fill(EvtPed_Trigger_2);

        Hist_3D_mid_C_Ped->Fill(EvtPed_3D_mid_C);
        Hist_3D_W1_C_Ped->Fill(EvtPed_3D_W1_C);
        Hist_3D_W2_C_Ped->Fill(EvtPed_3D_W2_C);
        Hist_3D_W3_C_Ped->Fill(EvtPed_3D_W3_C);

        Hist_HW_C_Ped->Fill(EvtPed_HW_C);
        Hist_H1_C_Ped->Fill(EvtPed_H1_C);
        Hist_H2_C_Ped->Fill(EvtPed_H2_C);
        Hist_H3_C_Ped->Fill(EvtPed_H3_C);

        Hist_L1_C_Ped->Fill(EvtPed_L1_C);
        Hist_L2_C_Ped->Fill(EvtPed_L2_C);
        Hist_L3_C_Ped->Fill(EvtPed_L3_C);
        Hist_L4_C_Ped->Fill(EvtPed_L4_C);

        Hist_3D_mid_S_Ped->Fill(EvtPed_3D_mid_S);
        Hist_3D_W1_S_Ped->Fill(EvtPed_3D_W1_S);
        Hist_3D_W2_S_Ped->Fill(EvtPed_3D_W2_S);
        Hist_3D_W3_S_Ped->Fill(EvtPed_3D_W3_S);
        
        Hist_HW_S_Ped->Fill(EvtPed_HW_S);
        Hist_H1_S_Ped->Fill(EvtPed_H1_S);
        Hist_H2_S_Ped->Fill(EvtPed_H2_S);
        Hist_H3_S_Ped->Fill(EvtPed_H3_S);

        Hist_L1_S_Ped->Fill(EvtPed_L1_S);
        Hist_L2_S_Ped->Fill(EvtPed_L2_S);
        Hist_L3_S_Ped->Fill(EvtPed_L3_S);
        Hist_L4_S_Ped->Fill(EvtPed_L4_S);        
    }

    // Save the outputs
    std::string outFile = "./PedDistribution/PedDistribution_Run_" + std::to_string(runNum) + ".root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    Hist_C_counter_1_Ped->Write();
    Hist_C_counter_2_Ped->Write();

    Hist_Trigger_1_Ped->Write();
    Hist_Trigger_2_Ped->Write();

    Hist_3D_mid_C_Ped->Write();
    Hist_3D_W1_C_Ped->Write();
    Hist_3D_W2_C_Ped->Write();
    Hist_3D_W3_C_Ped->Write();

    Hist_HW_C_Ped->Write();
    Hist_H1_C_Ped->Write();
    Hist_H2_C_Ped->Write();
    Hist_H3_C_Ped->Write();

    Hist_L1_C_Ped->Write();
    Hist_L2_C_Ped->Write();
    Hist_L3_C_Ped->Write();
    Hist_L4_C_Ped->Write();

    Hist_3D_mid_S_Ped->Write();
    Hist_3D_W1_S_Ped->Write();
    Hist_3D_W2_S_Ped->Write();
    Hist_3D_W3_S_Ped->Write();
    
    Hist_HW_S_Ped->Write();
    Hist_H1_S_Ped->Write();
    Hist_H2_S_Ped->Write();
    Hist_H3_S_Ped->Write();

    Hist_L1_S_Ped->Write();
    Hist_L2_S_Ped->Write();
    Hist_L3_S_Ped->Write();
    Hist_L4_S_Ped->Write();

    outputRoot->WriteObject(&runPed, "runPedMap");

    outputRoot->Close();
}