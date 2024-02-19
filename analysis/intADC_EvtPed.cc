#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <filesystem>

#include "TBevt.h"
#include "TButility.h"

#include "functions.cc"

#include "TStyle.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

namespace fs = std::filesystem;

// This script is for calculating "integrated ADC count"
//
// 1. Compile the script
// ./compile intADC_EvtPed
//
// 2. Run the compiled script
// ./intADC_EvtPed <run number> <max entry>
// Ex) ./intADC_EvtPed 4234 -1
// <max entry> == -1 means run all the entries
//
// This example uses event pedestal

int main(int argc, char** argv) {
    int runNum = std::stoi(argv[1]);
    int maxEntry = std::stoi(argv[2]);

    // PID selection criteria
    float Cut_C_counter_1 = 100.;
    float Cut_C_counter_2 = 80.;

    int c_counter1_range[2] = {390,660};
    int c_counter2_range[2] = {230,420};

    int c_3d_mid_range[2] = {130,410};
    int c_3d_w1_range[2] = {130,354};
    int c_3d_w2_range[2] = {130,358};
    int c_3d_w3_range[2] = {140,354};
    int s_3d_mid_range[2] = {130,427};
    int s_3d_w1_range[2] = {130,354};
    int s_3d_w2_range[2] = {130,358};
    int s_3d_w3_range[2] = {140,354};

    int c_hs_w_range[2] = {126,322};
    int c_hs_1_range[2] = {139,371};
    int c_hs_2_range[2] = {145,327};
    int c_hs_3_range[2] = {141,338};
    int s_hs_w_range[2] = {139,356};
    int s_hs_1_range[2] = {152,366};
    int s_hs_2_range[2] = {155,345};
    int s_hs_3_range[2] = {151,365};

    int c_l_1_range[2] = {150,353};
    int c_l_2_range[2] = {214,350};
    int c_l_3_range[2] = {140,335};
    int c_l_4_range[2] = {148,319};
    int s_l_1_range[2] = {160,377};
    int s_l_2_range[2] = {214,428};
    int s_l_3_range[2] = {156,370};
    int s_l_4_range[2] = {155,339};

    // Load mapping
    auto map = getModuleConfigMap();

    std::vector<TBcid> CID_C_counter = {TBcid( map.at("C1").at(0), map.at("C1").at(1)),
                                        TBcid( map.at("C1").at(0), map.at("C2").at(1))};

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

    // Preparing histograms for ADC
    TH1F* Hist_C_counter_1_PeakADC = new TH1F("C_counter_1_PeakADC", "C_counter_1_PeakADC;PeakADC;Evt", 4096, 0, 4096);
    TH1F* Hist_C_counter_2_PeakADC = new TH1F("C_counter_2_PeakADC", "C_counter_2_PeakADC;PeakADC;Evt", 4096, 0, 4096);

    TH1F* Hist_3D_mid_C_IntADC = new TH1F("MCP_sum_C_IntADC", "MCP_sum_C_IntADC;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_C_IntADC  = new TH1F("3D_W1_C_IntADC",   "3D_W1_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_C_IntADC  = new TH1F("3D_W2_C_IntADC",   "3D_W2_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_C_IntADC  = new TH1F("3D_W3_C_IntADC",   "3D_W3_C_IntADC;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_3D_mid_S_IntADC = new TH1F("MCP_sum_S_IntADC", "MCP_sum_S_IntADC;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_S_IntADC  = new TH1F("3D_W1_S_IntADC",   "3D_W1_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_S_IntADC  = new TH1F("3D_W2_S_IntADC",   "3D_W2_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_S_IntADC  = new TH1F("3D_W3_S_IntADC",   "3D_W3_S_IntADC;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_HS_W_C_IntADC  = new TH1F("HS_W_C_IntADC",   "HS_W_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_1_C_IntADC  = new TH1F("HS_1_C_IntADC",   "HS_1_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_2_C_IntADC  = new TH1F("HS_2_C_IntADC",   "HS_2_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_3_C_IntADC  = new TH1F("HS_3_C_IntADC",   "HS_3_C_IntADC;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_HS_W_S_IntADC  = new TH1F("HS_W_S_IntADC",   "HS_W_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_1_S_IntADC  = new TH1F("HS_1_S_IntADC",   "HS_1_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_2_S_IntADC  = new TH1F("HS_2_S_IntADC",   "HS_2_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_3_S_IntADC  = new TH1F("HS_3_S_IntADC",   "HS_3_S_IntADC;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_L_1_C_IntADC  = new TH1F("L_1_C_IntADC",   "L_1_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_2_C_IntADC  = new TH1F("L_2_C_IntADC",   "L_2_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_3_C_IntADC  = new TH1F("L_3_C_IntADC",   "L_3_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_4_C_IntADC  = new TH1F("L_4_C_IntADC",   "L_4_C_IntADC;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_L_1_S_IntADC  = new TH1F("L_1_S_IntADC",   "L_1_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_2_S_IntADC  = new TH1F("L_2_S_IntADC",   "L_2_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_3_S_IntADC  = new TH1F("L_3_S_IntADC",   "L_3_S_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_4_S_IntADC  = new TH1F("L_4_S_IntADC",   "L_4_S_IntADC;IntADC;Evt",   1000, -5000, 200000);

    // After PID selection
    TH1F* Hist_C_counter_1_PeakADC_cut = new TH1F("C_counter_1_PeakADC_cut", "C_counter_1_PeakADC_cut;PeakADC;Evt", 4096, 0, 4096);
    TH1F* Hist_C_counter_2_PeakADC_cut = new TH1F("C_counter_2_PeakADC_cut", "C_counter_2_PeakADC_cut;PeakADC;Evt", 4096, 0, 4096);

    TH1F* Hist_3D_mid_C_IntADC_cut = new TH1F("MCP_sum_C_IntADC_cut", "MCP_sum_C_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_C_IntADC_cut  = new TH1F("3D_W1_C_IntADC_cut",   "3D_W1_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_C_IntADC_cut  = new TH1F("3D_W2_C_IntADC_cut",   "3D_W2_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_C_IntADC_cut  = new TH1F("3D_W3_C_IntADC_cut",   "3D_W3_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_3D_mid_S_IntADC_cut = new TH1F("MCP_sum_S_IntADC_cut", "MCP_sum_S_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_S_IntADC_cut  = new TH1F("3D_W1_S_IntADC_cut",   "3D_W1_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_S_IntADC_cut  = new TH1F("3D_W2_S_IntADC_cut",   "3D_W2_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_S_IntADC_cut  = new TH1F("3D_W3_S_IntADC_cut",   "3D_W3_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_HS_W_C_IntADC_cut  = new TH1F("HS_W_C_IntADC_cut",   "HS_W_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_1_C_IntADC_cut  = new TH1F("HS_1_C_IntADC_cut",   "HS_1_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_2_C_IntADC_cut  = new TH1F("HS_2_C_IntADC_cut",   "HS_2_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_3_C_IntADC_cut  = new TH1F("HS_3_C_IntADC_cut",   "HS_3_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_HS_W_S_IntADC_cut  = new TH1F("HS_W_S_IntADC_cut",   "HS_W_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_1_S_IntADC_cut  = new TH1F("HS_1_S_IntADC_cut",   "HS_1_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_2_S_IntADC_cut  = new TH1F("HS_2_S_IntADC_cut",   "HS_2_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_HS_3_S_IntADC_cut  = new TH1F("HS_3_S_IntADC_cut",   "HS_3_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_L_1_C_IntADC_cut  = new TH1F("L_1_C_IntADC_cut",   "L_1_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_2_C_IntADC_cut  = new TH1F("L_2_C_IntADC_cut",   "L_2_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_3_C_IntADC_cut  = new TH1F("L_3_C_IntADC_cut",   "L_3_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_4_C_IntADC_cut  = new TH1F("L_4_C_IntADC_cut",   "L_4_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_L_1_S_IntADC_cut  = new TH1F("L_1_S_IntADC_cut",   "L_1_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_2_S_IntADC_cut  = new TH1F("L_2_S_IntADC_cut",   "L_2_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_3_S_IntADC_cut  = new TH1F("L_3_S_IntADC_cut",   "L_3_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_L_4_S_IntADC_cut  = new TH1F("L_4_S_IntADC_cut",   "L_4_S_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    // Load Ntuple using TChain
    TChain* evtChain = loadNtuple(runNum);
    TBevt<TBwaveform>* anEvt = new TBevt<TBwaveform>(); // Will use waveform data
    evtChain->SetBranchAddress("TBevt", &anEvt);

    // Check total # of events, limit # of events to process if maxEntry is specified
    int totalEntry = evtChain->GetEntries();
    std::cout << "Total entries : " << totalEntry << std::endl;
    if ( (maxEntry > 0) && (maxEntry < totalEntry) ) {
        totalEntry = maxEntry;
        std::cout << "Will process maximum " << std::to_string(totalEntry) << " events" << std::endl;
    }

    // Evt Loop start
    for (int iEvt = 0; iEvt < totalEntry; iEvt++) {
        printProgress(iEvt + 1, totalEntry); // Print progress bar
        evtChain->GetEntry(iEvt); // Get event

        // Get TBwaveform
        std::vector<TBwaveform> Data_C_counter;
        for(TBcid cid : CID_C_counter) {
            Data_C_counter.push_back(anEvt->GetData(cid));
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

        // Get Waveform vector
        std::vector< std::vector<short> > Wave_C_counter;
        for(TBwaveform data : Data_C_counter) {
            Wave_C_counter.push_back(data.waveform());
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
        
        // This script uses pedestal measured event-by-event (EvtPed)
        // EvtPed = sum(waveform from bin 1 ~ bin 100) / 100
        // Calculate EvtPed here
        float Ped_C_counter_1 = 0.f;
        float Ped_C_counter_2 = 0.f;
        float Ped_3D_mid_C = 0.f;
        float Ped_3D_W1_C  = 0.f;
        float Ped_3D_W2_C  = 0.f;
        float Ped_3D_W3_C  = 0.f;
        float Ped_HW_C     = 0.f;
        float Ped_H1_C     = 0.f;
        float Ped_H2_C     = 0.f;
        float Ped_H3_C     = 0.f;
        float Ped_L1_C     = 0.f;
        float Ped_L2_C     = 0.f;
        float Ped_L3_C     = 0.f;
        float Ped_L4_C     = 0.f;
        float Ped_3D_mid_S = 0.f;
        float Ped_3D_W1_S  = 0.f;
        float Ped_3D_W2_S  = 0.f;
        float Ped_3D_W3_S  = 0.f;
        float Ped_HW_S     = 0.f;
        float Ped_H1_S     = 0.f;
        float Ped_H2_S     = 0.f;
        float Ped_H3_S     = 0.f;
        float Ped_L1_S     = 0.f;
        float Ped_L2_S     = 0.f;
        float Ped_L3_S     = 0.f;
        float Ped_L4_S     = 0.f;
        float ped_width=112.;
        for(int bin = 1; bin < ped_width+1; bin++) {
            Ped_C_counter_1 += (float) (Wave_C_counter.at(0)[bin] / ped_width);
            Ped_C_counter_2 += (float) (Wave_C_counter.at(1)[bin] / ped_width);
            Ped_3D_mid_C += (float) (Wave_3D_C.at(0)[bin] / ped_width);      
            Ped_3D_W1_C  += (float) (Wave_3D_C.at(1)[bin] / ped_width);
            Ped_3D_W2_C  += (float) (Wave_3D_C.at(2)[bin] / ped_width);
            Ped_3D_W3_C  += (float) (Wave_3D_C.at(3)[bin] / ped_width);
            Ped_HW_C     += (float) (Wave_HeatSink_C.at(0)[bin] / ped_width);
            Ped_H1_C     += (float) (Wave_HeatSink_C.at(1)[bin] / ped_width);
            Ped_H2_C     += (float) (Wave_HeatSink_C.at(2)[bin] / ped_width);
            Ped_H3_C     += (float) (Wave_HeatSink_C.at(3)[bin] / ped_width);
            Ped_L1_C     += (float) (Wave_Lego_C.at(0)[bin] / ped_width);
            Ped_L2_C     += (float) (Wave_Lego_C.at(1)[bin] / ped_width);
            Ped_L3_C     += (float) (Wave_Lego_C.at(2)[bin] / ped_width);
            Ped_L4_C     += (float) (Wave_Lego_C.at(3)[bin] / ped_width);
            Ped_3D_mid_S += (float) (Wave_3D_S.at(0)[bin] / ped_width);      
            Ped_3D_W1_S  += (float) (Wave_3D_S.at(1)[bin] / ped_width);
            Ped_3D_W2_S  += (float) (Wave_3D_S.at(2)[bin] / ped_width);
            Ped_3D_W3_S  += (float) (Wave_3D_S.at(3)[bin] / ped_width);
            Ped_HW_S     += (float) (Wave_HeatSink_S.at(0)[bin] / ped_width);
            Ped_H1_S     += (float) (Wave_HeatSink_S.at(1)[bin] / ped_width);
            Ped_H2_S     += (float) (Wave_HeatSink_S.at(2)[bin] / ped_width);
            Ped_H3_S     += (float) (Wave_HeatSink_S.at(3)[bin] / ped_width);
            Ped_L1_S     += (float) (Wave_Lego_S.at(0)[bin] / ped_width);
            Ped_L2_S     += (float) (Wave_Lego_S.at(1)[bin] / ped_width);
            Ped_L3_S     += (float) (Wave_Lego_S.at(2)[bin] / ped_width);
            Ped_L4_S     += (float) (Wave_Lego_S.at(3)[bin] / ped_width);
        }
        // PID uses "Peak ADC count"!!
        // GetPeakWithPed(waveform, peak range start, peak range end, pedestal value)
        // this function returns PeakADC count of provided waveform
        // searched within provided peak range and pedestal
        // Here we use EvtPed to calculate PeakADC

        float PeakADC_C_counter_1 = GetPeakWithPed(Wave_C_counter.at(0), c_counter1_range[0], c_counter1_range[1], Ped_C_counter_1);
        float PeakADC_C_counter_2 = GetPeakWithPed(Wave_C_counter.at(1), c_counter2_range[0], c_counter2_range[1], Ped_C_counter_2);
        
        // Get "Integrated ADC count"
        // GetIntWithPed(waveform, integral range start, integral range end, pedestal value)
        // this function retuns IntADC count of provided waveform
        // integrated within [start, end), with provided pedestal value
        
        
        float IntADC_3D_mid_C = GetIntWithPed(Wave_3D_C.at(0), c_3d_mid_range[0], c_3d_mid_range[1], Ped_3D_mid_C);
        float IntADC_3D_W1_C  = GetIntWithPed(Wave_3D_C.at(1), c_3d_w1_range[0], c_3d_w1_range[1], Ped_3D_W1_C );
        float IntADC_3D_W2_C  = GetIntWithPed(Wave_3D_C.at(2), c_3d_w2_range[0], c_3d_w2_range[1], Ped_3D_W2_C );
        float IntADC_3D_W3_C  = GetIntWithPed(Wave_3D_C.at(3), c_3d_w3_range[0], c_3d_w3_range[1], Ped_3D_W3_C );

        float IntADC_3D_mid_S = GetIntWithPed(Wave_3D_S.at(0), s_3d_mid_range[0], s_3d_mid_range[1], Ped_3D_mid_S);
        float IntADC_3D_W1_S  = GetIntWithPed(Wave_3D_S.at(1), s_3d_w1_range[0], s_3d_w1_range[1], Ped_3D_W1_S );
        float IntADC_3D_W2_S  = GetIntWithPed(Wave_3D_S.at(2), s_3d_w2_range[0], s_3d_w2_range[1], Ped_3D_W2_S );
        float IntADC_3D_W3_S  = GetIntWithPed(Wave_3D_S.at(3), s_3d_w3_range[0], s_3d_w3_range[1], Ped_3D_W3_S );

        float IntADC_HS_W_C  = GetIntWithPed(Wave_HeatSink_C.at(0), c_hs_w_range[0], c_hs_w_range[1], Ped_HW_C);
        float IntADC_HS_1_C  = GetIntWithPed(Wave_HeatSink_C.at(1), c_hs_1_range[0], c_hs_1_range[1], Ped_H1_C);
        float IntADC_HS_2_C  = GetIntWithPed(Wave_HeatSink_C.at(2), c_hs_2_range[0], c_hs_2_range[1], Ped_H2_C);
        float IntADC_HS_3_C  = GetIntWithPed(Wave_HeatSink_C.at(3), c_hs_3_range[0], c_hs_3_range[1], Ped_H3_C);

        float IntADC_HS_W_S  = GetIntWithPed(Wave_HeatSink_S.at(0), s_hs_w_range[0], s_hs_w_range[1], Ped_HW_S);
        float IntADC_HS_1_S  = GetIntWithPed(Wave_HeatSink_S.at(1), s_hs_1_range[0], s_hs_1_range[1], Ped_H1_S);
        float IntADC_HS_2_S  = GetIntWithPed(Wave_HeatSink_S.at(2), s_hs_2_range[0], s_hs_2_range[1], Ped_H2_S);
        float IntADC_HS_3_S  = GetIntWithPed(Wave_HeatSink_S.at(3), s_hs_3_range[0], s_hs_3_range[1], Ped_H3_S);

        float IntADC_L_1_C  = GetIntWithPed(Wave_Lego_C.at(0), c_l_1_range[0], c_l_1_range[1], Ped_L1_C);
        float IntADC_L_2_C  = GetIntWithPed(Wave_Lego_C.at(1), c_l_2_range[0], c_l_2_range[1], Ped_L2_C);
        float IntADC_L_3_C  = GetIntWithPed(Wave_Lego_C.at(2), c_l_3_range[0], c_l_3_range[1], Ped_L3_C);
        float IntADC_L_4_C  = GetIntWithPed(Wave_Lego_C.at(3), c_l_4_range[0], c_l_4_range[1], Ped_L4_C);

        float IntADC_L_1_S  = GetIntWithPed(Wave_Lego_S.at(0), s_l_1_range[0], s_l_1_range[1], Ped_L1_S);
        float IntADC_L_2_S  = GetIntWithPed(Wave_Lego_S.at(1), s_l_2_range[0], s_l_2_range[1], Ped_L2_S);
        float IntADC_L_3_S  = GetIntWithPed(Wave_Lego_S.at(2), s_l_3_range[0], s_l_3_range[1], Ped_L3_S);
        float IntADC_L_4_S  = GetIntWithPed(Wave_Lego_S.at(3), s_l_4_range[0], s_l_4_range[1], Ped_L4_S);

        // Here we fill IntADC histograms before PID selection        
        Hist_C_counter_1_PeakADC->Fill(PeakADC_C_counter_1);
        Hist_C_counter_2_PeakADC->Fill(PeakADC_C_counter_2);

        Hist_3D_mid_C_IntADC->Fill(IntADC_3D_mid_C);
        Hist_3D_W1_C_IntADC ->Fill(IntADC_3D_W1_C);
        Hist_3D_W2_C_IntADC ->Fill(IntADC_3D_W2_C);
        Hist_3D_W3_C_IntADC ->Fill(IntADC_3D_W3_C);

        Hist_3D_mid_S_IntADC->Fill(IntADC_3D_mid_S);
        Hist_3D_W1_S_IntADC ->Fill(IntADC_3D_W1_S);
        Hist_3D_W2_S_IntADC ->Fill(IntADC_3D_W2_S);
        Hist_3D_W3_S_IntADC ->Fill(IntADC_3D_W3_S);

        Hist_HS_W_C_IntADC->Fill(IntADC_HS_W_C);
        Hist_HS_1_C_IntADC->Fill(IntADC_HS_1_C);
        Hist_HS_2_C_IntADC->Fill(IntADC_HS_2_C);
        Hist_HS_3_C_IntADC->Fill(IntADC_HS_3_C);

        Hist_HS_W_S_IntADC->Fill(IntADC_HS_W_S);
        Hist_HS_1_S_IntADC->Fill(IntADC_HS_1_S);
        Hist_HS_2_S_IntADC->Fill(IntADC_HS_2_S);
        Hist_HS_3_S_IntADC->Fill(IntADC_HS_3_S);
    
        Hist_L_1_C_IntADC->Fill(IntADC_L_1_C);
        Hist_L_2_C_IntADC->Fill(IntADC_L_2_C);
        Hist_L_3_C_IntADC->Fill(IntADC_L_3_C);
        Hist_L_4_C_IntADC->Fill(IntADC_L_4_C);

        Hist_L_1_S_IntADC->Fill(IntADC_L_1_S);
        Hist_L_2_S_IntADC->Fill(IntADC_L_2_S);
        Hist_L_3_S_IntADC->Fill(IntADC_L_3_S);
        Hist_L_4_S_IntADC->Fill(IntADC_L_4_S);

        // PID selection here
        // To find e+ : reject the events which doesn't make Cherenkov lights in Cherenkov counters
        // (heavier particles such as proton, pion etc... will not make Cherenkov light)
        // That is, veto the events with low PeakADC counts
        if( (PeakADC_C_counter_1 < Cut_C_counter_1) || (PeakADC_C_counter_2 < Cut_C_counter_2) ) continue;

        Hist_C_counter_1_PeakADC_cut->Fill(PeakADC_C_counter_1);
        Hist_C_counter_2_PeakADC_cut->Fill(PeakADC_C_counter_2);

        Hist_3D_mid_C_IntADC_cut->Fill(IntADC_3D_mid_C);
        Hist_3D_W1_C_IntADC_cut ->Fill(IntADC_3D_W1_C);
        Hist_3D_W2_C_IntADC_cut ->Fill(IntADC_3D_W2_C);
        Hist_3D_W3_C_IntADC_cut ->Fill(IntADC_3D_W3_C);

        Hist_3D_mid_S_IntADC_cut->Fill(IntADC_3D_mid_S);
        Hist_3D_W1_S_IntADC_cut ->Fill(IntADC_3D_W1_S);
        Hist_3D_W2_S_IntADC_cut ->Fill(IntADC_3D_W2_S);
        Hist_3D_W3_S_IntADC_cut ->Fill(IntADC_3D_W3_S);

        Hist_HS_W_C_IntADC_cut->Fill(IntADC_HS_W_C);
        Hist_HS_1_C_IntADC_cut->Fill(IntADC_HS_1_C);
        Hist_HS_2_C_IntADC_cut->Fill(IntADC_HS_2_C);
        Hist_HS_3_C_IntADC_cut->Fill(IntADC_HS_3_C);

        Hist_HS_W_S_IntADC_cut->Fill(IntADC_HS_W_S);
        Hist_HS_1_S_IntADC_cut->Fill(IntADC_HS_1_S);
        Hist_HS_2_S_IntADC_cut->Fill(IntADC_HS_2_S);
        Hist_HS_3_S_IntADC_cut->Fill(IntADC_HS_3_S);
    
        Hist_L_1_C_IntADC_cut->Fill(IntADC_L_1_C);
        Hist_L_2_C_IntADC_cut->Fill(IntADC_L_2_C);
        Hist_L_3_C_IntADC_cut->Fill(IntADC_L_3_C);
        Hist_L_4_C_IntADC_cut->Fill(IntADC_L_4_C);

        Hist_L_1_S_IntADC_cut->Fill(IntADC_L_1_S);
        Hist_L_2_S_IntADC_cut->Fill(IntADC_L_2_S);
        Hist_L_3_S_IntADC_cut->Fill(IntADC_L_3_S);
        Hist_L_4_S_IntADC_cut->Fill(IntADC_L_4_S);
    }

    // Prepare output directory
    fs::path dir("./IntADC");
    if ( !(fs::exists(dir)) ) fs::create_directory(dir);
    // Create output root file
    std::string outFile = "./IntADC/IntADC_EvtPed_Run_" + std::to_string(runNum) + ".root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    // Write histogram before cut
    Hist_C_counter_1_PeakADC->Write();
    Hist_C_counter_2_PeakADC->Write();

    Hist_3D_mid_C_IntADC->Write();
    Hist_3D_W1_C_IntADC ->Write();
    Hist_3D_W2_C_IntADC ->Write();
    Hist_3D_W3_C_IntADC ->Write();

    Hist_3D_mid_S_IntADC->Write();
    Hist_3D_W1_S_IntADC ->Write();
    Hist_3D_W2_S_IntADC ->Write();
    Hist_3D_W3_S_IntADC ->Write();

    Hist_HS_W_C_IntADC->Write();
    Hist_HS_1_C_IntADC->Write();
    Hist_HS_2_C_IntADC->Write();
    Hist_HS_3_C_IntADC->Write();

    Hist_HS_W_S_IntADC->Write();
    Hist_HS_1_S_IntADC->Write();
    Hist_HS_2_S_IntADC->Write();
    Hist_HS_3_S_IntADC->Write();

    Hist_L_1_C_IntADC->Write();
    Hist_L_2_C_IntADC->Write();
    Hist_L_3_C_IntADC->Write();
    Hist_L_4_C_IntADC->Write();

    Hist_L_1_S_IntADC->Write();
    Hist_L_2_S_IntADC->Write();
    Hist_L_3_S_IntADC->Write();
    Hist_L_4_S_IntADC->Write();

    // Write histogram after cut
    Hist_C_counter_1_PeakADC_cut->Write();
    Hist_C_counter_2_PeakADC_cut->Write();

    Hist_3D_mid_C_IntADC_cut->Write();
    Hist_3D_W1_C_IntADC_cut->Write();
    Hist_3D_W2_C_IntADC_cut->Write();
    Hist_3D_W3_C_IntADC_cut->Write();

    Hist_3D_mid_S_IntADC_cut->Write();
    Hist_3D_W1_S_IntADC_cut->Write();
    Hist_3D_W2_S_IntADC_cut->Write();
    Hist_3D_W3_S_IntADC_cut->Write();

    Hist_HS_W_C_IntADC_cut->Write();
    Hist_HS_1_C_IntADC_cut->Write();
    Hist_HS_2_C_IntADC_cut->Write();
    Hist_HS_3_C_IntADC_cut->Write();

    Hist_HS_W_S_IntADC_cut->Write();
    Hist_HS_1_S_IntADC_cut->Write();
    Hist_HS_2_S_IntADC_cut->Write();
    Hist_HS_3_S_IntADC_cut->Write();

    Hist_L_1_C_IntADC_cut->Write();
    Hist_L_2_C_IntADC_cut->Write();
    Hist_L_3_C_IntADC_cut->Write();
    Hist_L_4_C_IntADC_cut->Write();

    Hist_L_1_S_IntADC_cut->Write();
    Hist_L_2_S_IntADC_cut->Write();
    Hist_L_3_S_IntADC_cut->Write();
    Hist_L_4_S_IntADC_cut->Write();

    outputRoot->Close();
}
