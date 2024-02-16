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

    // Try02
    float Calib_3D_C     = 0.0000679020;
    float Calib_3D_mid_C = 0.0000877270;
    float Calib_3D_W1_C  = 0.0000066562;
    float Calib_3D_W2_C  = 0.0000195006;
    float Calib_3D_W3_C  = 0.0000155819;
    float Calib_HW_C   = 0.0000683731;
    float Calib_H1_C   = 0.0000581156;
    float Calib_H2_C   = 0.0000567910;
    float Calib_H3_C   = 0.0000621084;
    float Calib_L1_C    = 0.0000688122;
    float Calib_L2_C    = 0.0003758166;
    float Calib_L3_C    = 0.0000731954;
    float Calib_L4_C    = 0.0001290469;

    float Calib_3D_S     = 0.0000321260;
    float Calib_3D_mid_S = 0.0000422702;
    float Calib_3D_W1_S  = 0.0000042383;
    float Calib_3D_W2_S  = 0.0000045148;
    float Calib_3D_W3_S  = 0.0000049629;
    float Calib_HW_S   = 0.0000398390;
    float Calib_H1_S   = 0.0000348551;
    float Calib_H2_S   = 0.0000369434;
    float Calib_H3_S   = 0.0000356663;
    float Calib_L1_S    = 0.0000423230;
    float Calib_L2_S    = 0.0000255801;
    float Calib_L3_S    = 0.0000455753;
    float Calib_L4_S    = 0.0000705785;

    // Hist for Pedestal distribution (Evt-by-evt)
    TH2F* Hist_C_counter_1_Wave = new TH2F("C_counter_1_Wave", "C_counter_1_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_C_counter_2_Wave = new TH2F("C_counter_2_Wave", "C_counter_2_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

    TH2F* Hist_Trigger_1_Wave = new TH2F("Trigger_1_Wave", "Trigger_1_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_Trigger_2_Wave = new TH2F("Trigger_2_Wave", "Trigger_2_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

    TH2F* Hist_3D_mid_C_Wave = new TH2F("3D_mid_C_Wave", "3D_mid_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_3D_W1_C_Wave  = new TH2F("3D_W1_C_Wave", "3D_W1_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_3D_W2_C_Wave  = new TH2F("3D_W2_C_Wave", "3D_W2_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_3D_W3_C_Wave  = new TH2F("3D_W3_C_Wave", "3D_W3_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

    TH2F* Hist_3D_mid_S_Wave = new TH2F("3D_mid_S_Wave", "3D_mid_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_3D_W1_S_Wave  = new TH2F("3D_W1_S_Wave", "3D_W1_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_3D_W2_S_Wave  = new TH2F("3D_W2_S_Wave", "3D_W2_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_3D_W3_S_Wave  = new TH2F("3D_W3_S_Wave", "3D_W3_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

    TH2F* Hist_HW_C_Wave = new TH2F("HS_W_C_Wave", "HS_W_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_H1_C_Wave = new TH2F("HS_1_C_Wave", "HS_1_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_H2_C_Wave = new TH2F("HS_2_C_Wave", "HS_2_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_H3_C_Wave = new TH2F("HS_3_C_Wave", "HS_3_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

    TH2F* Hist_HW_S_Wave = new TH2F("HS_W_S_Wave", "HS_W_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_H1_S_Wave = new TH2F("HS_1_S_Wave", "HS_1_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_H2_S_Wave = new TH2F("HS_2_S_Wave", "HS_2_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_H3_S_Wave = new TH2F("HS_3_S_Wave", "HS_3_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

    TH2F* Hist_L1_C_Wave = new TH2F("L1_C_Wave", "L1_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_L2_C_Wave = new TH2F("L2_C_Wave", "L2_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_L3_C_Wave = new TH2F("L3_C_Wave", "L3_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_L4_C_Wave = new TH2F("L4_C_Wave", "L4_C_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

    TH2F* Hist_L1_S_Wave = new TH2F("L1_S_Wave", "L1_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_L2_S_Wave = new TH2F("L2_S_Wave", "L2_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_L3_S_Wave = new TH2F("L3_S_Wave", "L3_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);
    TH2F* Hist_L4_S_Wave = new TH2F("L4_S_Wave", "L4_S_Wave;bin;ADC", 1000, 0, 1000, 4096, 0, 4096);

        // Load mapping, pedestal info is not available for now, will be updated
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

        for(int bin = 1; bin < 1001; bin++) {
            Hist_C_counter_1_Wave->Fill(bin, Wave_C_counter.at(0)[bin]);
            Hist_C_counter_2_Wave->Fill(bin, Wave_C_counter.at(1)[bin]);

            Hist_Trigger_1_Wave->Fill(bin, Wave_Trigger.at(0)[bin]);
            Hist_Trigger_2_Wave->Fill(bin, Wave_Trigger.at(1)[bin]);

            Hist_3D_mid_C_Wave->Fill(bin, Wave_3D_C.at(0)[bin]);
            Hist_3D_W1_C_Wave ->Fill(bin, Wave_3D_C.at(1)[bin]);
            Hist_3D_W2_C_Wave ->Fill(bin, Wave_3D_C.at(2)[bin]);
            Hist_3D_W3_C_Wave ->Fill(bin, Wave_3D_C.at(3)[bin]);

            Hist_3D_mid_S_Wave->Fill(bin, Wave_3D_S.at(0)[bin]);
            Hist_3D_W1_S_Wave ->Fill(bin, Wave_3D_S.at(1)[bin]);
            Hist_3D_W2_S_Wave ->Fill(bin, Wave_3D_S.at(2)[bin]);
            Hist_3D_W3_S_Wave ->Fill(bin, Wave_3D_S.at(3)[bin]);

            Hist_HW_C_Wave->Fill(bin, Wave_HeatSink_C.at(0)[bin]);
            Hist_H1_C_Wave->Fill(bin, Wave_HeatSink_C.at(1)[bin]);
            Hist_H2_C_Wave->Fill(bin, Wave_HeatSink_C.at(2)[bin]);
            Hist_H3_C_Wave->Fill(bin, Wave_HeatSink_C.at(3)[bin]);

            Hist_HW_S_Wave->Fill(bin, Wave_HeatSink_S.at(0)[bin]);
            Hist_H1_S_Wave->Fill(bin, Wave_HeatSink_S.at(1)[bin]);
            Hist_H2_S_Wave->Fill(bin, Wave_HeatSink_S.at(2)[bin]);
            Hist_H3_S_Wave->Fill(bin, Wave_HeatSink_S.at(3)[bin]);

            Hist_L1_C_Wave->Fill(bin, Wave_Lego_C.at(0)[bin]);
            Hist_L2_C_Wave->Fill(bin, Wave_Lego_C.at(1)[bin]);
            Hist_L3_C_Wave->Fill(bin, Wave_Lego_C.at(2)[bin]);
            Hist_L4_C_Wave->Fill(bin, Wave_Lego_C.at(3)[bin]);

            Hist_L1_S_Wave->Fill(bin, Wave_Lego_S.at(0)[bin]);
            Hist_L2_S_Wave->Fill(bin, Wave_Lego_S.at(1)[bin]);
            Hist_L3_S_Wave->Fill(bin, Wave_Lego_S.at(2)[bin]);
            Hist_L4_S_Wave->Fill(bin, Wave_Lego_S.at(3)[bin]);

        }
    }

    // Save the outputs
    std::string outFile = "./WaveformOverlap/WaveformOverlap_Run_" + std::to_string(runNum) + ".root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    Hist_C_counter_1_Wave->Write();
    Hist_C_counter_2_Wave->Write();

    Hist_Trigger_1_Wave->Write();
    Hist_Trigger_2_Wave->Write();

    Hist_3D_mid_C_Wave->Write();
    Hist_3D_W1_C_Wave ->Write();
    Hist_3D_W2_C_Wave ->Write();
    Hist_3D_W3_C_Wave ->Write();

    Hist_3D_mid_S_Wave->Write();
    Hist_3D_W1_S_Wave ->Write();
    Hist_3D_W2_S_Wave ->Write();
    Hist_3D_W3_S_Wave ->Write();

    Hist_HW_C_Wave->Write();
    Hist_H1_C_Wave->Write();
    Hist_H2_C_Wave->Write();
    Hist_H3_C_Wave->Write();

    Hist_HW_S_Wave->Write();
    Hist_H1_S_Wave->Write();
    Hist_H2_S_Wave->Write();
    Hist_H3_S_Wave->Write();

    Hist_L1_C_Wave->Write();
    Hist_L2_C_Wave->Write();
    Hist_L3_C_Wave->Write();
    Hist_L4_C_Wave->Write();

    Hist_L1_S_Wave->Write();
    Hist_L2_S_Wave->Write();
    Hist_L3_S_Wave->Write();
    Hist_L4_S_Wave->Write();

    outputRoot->WriteObject(&runPed, "runPedMap");

    outputRoot->Close();
}