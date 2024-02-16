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

namespace fs = std::filesystem;

// This script is for drawing average time structure (average of waveform for all events in each run)
//
// 1. Compile this script by
// ./compile.sh avgTime
//
// 2. Run the compiled script by
// ./avgTime <run number> <max entry>
// Ex) ./avgTime 4234 -1
//
// <max entry> == -1 means run over all the entries

int main(int argc, char** argv) {
    gStyle->SetOptStat(0);

    int runNum = std::stoi(argv[1]);
    int maxEntry = std::stoi(argv[2]);

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

    // Preparing histograms
    TH1F* Hist_C_counter_1_AvgTimeStruc = new TH1F("C_counter_1_AvgTimeStruc", "C_counter_1_AvgTimeStruc;bin;ADC", 1000, 0, 1000);
    TH1F* Hist_C_counter_2_AvgTimeStruc = new TH1F("C_counter_2_AvgTimeStruc", "C_counter_2_AvgTimeStruc;bin;ADC", 1000, 0, 1000);

    TH1F* Hist_3D_mid_C_AvgTimeStruc = new TH1F("MCP_sum_C_AvgTimeStruc", "MCP_sum_C_AvgTimeStruc;bin;ADC", 1000, 0, 1000);
    TH1F* Hist_3D_W1_C_AvgTimeStruc  = new TH1F("3D_W1_C_AvgTimeStruc",   "3D_W1_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_3D_W2_C_AvgTimeStruc  = new TH1F("3D_W2_C_AvgTimeStruc",   "3D_W2_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_3D_W3_C_AvgTimeStruc  = new TH1F("3D_W3_C_AvgTimeStruc",   "3D_W3_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);

    TH1F* Hist_3D_mid_S_AvgTimeStruc = new TH1F("MCP_sum_S_AvgTimeStruc", "MCP_sum_S_AvgTimeStruc;bin;ADC", 1000, 0, 1000);
    TH1F* Hist_3D_W1_S_AvgTimeStruc  = new TH1F("3D_W1_S_AvgTimeStruc",   "3D_W1_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_3D_W2_S_AvgTimeStruc  = new TH1F("3D_W2_S_AvgTimeStruc",   "3D_W2_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_3D_W3_S_AvgTimeStruc  = new TH1F("3D_W3_S_AvgTimeStruc",   "3D_W3_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);

    TH1F* Hist_HS_W_C_AvgTimeStruc  = new TH1F("HS_W_C_AvgTimeStruc",   "HS_W_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_HS_1_C_AvgTimeStruc  = new TH1F("HS_1_C_AvgTimeStruc",   "HS_1_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_HS_2_C_AvgTimeStruc  = new TH1F("HS_2_C_AvgTimeStruc",   "HS_2_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_HS_3_C_AvgTimeStruc  = new TH1F("HS_3_C_AvgTimeStruc",   "HS_3_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);

    TH1F* Hist_HS_W_S_AvgTimeStruc  = new TH1F("HS_W_S_AvgTimeStruc",   "HS_W_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_HS_1_S_AvgTimeStruc  = new TH1F("HS_1_S_AvgTimeStruc",   "HS_1_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_HS_2_S_AvgTimeStruc  = new TH1F("HS_2_S_AvgTimeStruc",   "HS_2_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_HS_3_S_AvgTimeStruc  = new TH1F("HS_3_S_AvgTimeStruc",   "HS_3_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);

    TH1F* Hist_L_1_C_AvgTimeStruc  = new TH1F("L_1_C_AvgTimeStruc",   "L_1_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_L_2_C_AvgTimeStruc  = new TH1F("L_2_C_AvgTimeStruc",   "L_2_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_L_3_C_AvgTimeStruc  = new TH1F("L_3_C_AvgTimeStruc",   "L_3_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_L_4_C_AvgTimeStruc  = new TH1F("L_4_C_AvgTimeStruc",   "L_4_C_AvgTimeStruc;bin;ADC",   1000, 0, 1000);

    TH1F* Hist_L_1_S_AvgTimeStruc  = new TH1F("L_1_S_AvgTimeStruc",   "L_1_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_L_2_S_AvgTimeStruc  = new TH1F("L_2_S_AvgTimeStruc",   "L_2_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_L_3_S_AvgTimeStruc  = new TH1F("L_3_S_AvgTimeStruc",   "L_3_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);
    TH1F* Hist_L_4_S_AvgTimeStruc  = new TH1F("L_4_S_AvgTimeStruc",   "L_4_S_AvgTimeStruc;bin;ADC",   1000, 0, 1000);

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

    // Event Loop start
    for (int iEvt = 0; iEvt < totalEntry; iEvt++) {
        printProgress(iEvt + 1, totalEntry); // Print progress bar
        evtChain->GetEntry(iEvt); // Get event

        // Get TBwaveform data and store it
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

        // Get waveform vector from TBwaveform
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
        
        // Fill histogram with waveform
        // The waveforms of each event is all summed up in this step
        // After looping over all events, it will be divided with <number of events>
        // to give the "average" waveform
        for (int bin = 1; bin < 1001; bin++) {
            Hist_C_counter_1_AvgTimeStruc->Fill(bin, Wave_C_counter.at(0)[bin]);
            Hist_C_counter_2_AvgTimeStruc->Fill(bin, Wave_C_counter.at(1)[bin]);

            Hist_3D_mid_C_AvgTimeStruc->Fill(bin, Wave_3D_C.at(0)[bin]);
            Hist_3D_W1_C_AvgTimeStruc ->Fill(bin, Wave_3D_C.at(1)[bin]);
            Hist_3D_W2_C_AvgTimeStruc ->Fill(bin, Wave_3D_C.at(2)[bin]);
            Hist_3D_W3_C_AvgTimeStruc ->Fill(bin, Wave_3D_C.at(3)[bin]);

            Hist_3D_mid_S_AvgTimeStruc->Fill(bin, Wave_3D_S.at(0)[bin]);
            Hist_3D_W1_S_AvgTimeStruc ->Fill(bin, Wave_3D_S.at(1)[bin]);
            Hist_3D_W2_S_AvgTimeStruc ->Fill(bin, Wave_3D_S.at(2)[bin]);
            Hist_3D_W3_S_AvgTimeStruc ->Fill(bin, Wave_3D_S.at(3)[bin]);

            Hist_HS_W_C_AvgTimeStruc->Fill(bin, Wave_HeatSink_C.at(0)[bin]);
            Hist_HS_1_C_AvgTimeStruc->Fill(bin, Wave_HeatSink_C.at(1)[bin]);
            Hist_HS_2_C_AvgTimeStruc->Fill(bin, Wave_HeatSink_C.at(2)[bin]);
            Hist_HS_3_C_AvgTimeStruc->Fill(bin, Wave_HeatSink_C.at(3)[bin]);

            Hist_HS_W_S_AvgTimeStruc->Fill(bin, Wave_HeatSink_S.at(0)[bin]);
            Hist_HS_1_S_AvgTimeStruc->Fill(bin, Wave_HeatSink_S.at(1)[bin]);
            Hist_HS_2_S_AvgTimeStruc->Fill(bin, Wave_HeatSink_S.at(2)[bin]);
            Hist_HS_3_S_AvgTimeStruc->Fill(bin, Wave_HeatSink_S.at(3)[bin]);

            Hist_L_1_C_AvgTimeStruc->Fill(bin, Wave_Lego_C.at(0)[bin]);
            Hist_L_2_C_AvgTimeStruc->Fill(bin, Wave_Lego_C.at(1)[bin]);
            Hist_L_3_C_AvgTimeStruc->Fill(bin, Wave_Lego_C.at(2)[bin]);
            Hist_L_4_C_AvgTimeStruc->Fill(bin, Wave_Lego_C.at(3)[bin]);

            Hist_L_1_S_AvgTimeStruc->Fill(bin, Wave_Lego_S.at(0)[bin]);
            Hist_L_2_S_AvgTimeStruc->Fill(bin, Wave_Lego_S.at(1)[bin]);
            Hist_L_3_S_AvgTimeStruc->Fill(bin, Wave_Lego_S.at(2)[bin]);
            Hist_L_4_S_AvgTimeStruc->Fill(bin, Wave_Lego_S.at(3)[bin]);
        }
    }

    // Prepare output directory
    fs::path dir("./AvgTimeStruc");
    if ( !(fs::exists(dir)) ) fs::create_directory(dir);
    // Create output root file
    std::string outFile = "./AvgTimeStruc/AvgTimeStruc_Run_" + std::to_string(runNum) + ".root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    // Save histograms
    Hist_C_counter_1_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry)); // Divide with <number of events>
    Hist_C_counter_1_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_C_counter_1_AvgTimeStruc->Write();
    Hist_C_counter_2_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_C_counter_2_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_C_counter_2_AvgTimeStruc->Write();

    Hist_3D_mid_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_mid_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_mid_C_AvgTimeStruc->Write();
    Hist_3D_W1_C_AvgTimeStruc ->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_W1_C_AvgTimeStruc ->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_W1_C_AvgTimeStruc ->Write();
    Hist_3D_W2_C_AvgTimeStruc ->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_W2_C_AvgTimeStruc ->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_W2_C_AvgTimeStruc ->Write();
    Hist_3D_W3_C_AvgTimeStruc ->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_W3_C_AvgTimeStruc ->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_W3_C_AvgTimeStruc ->Write();

    Hist_3D_mid_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_mid_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_mid_S_AvgTimeStruc->Write();
    Hist_3D_W1_S_AvgTimeStruc ->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_W1_S_AvgTimeStruc ->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_W1_S_AvgTimeStruc ->Write();
    Hist_3D_W2_S_AvgTimeStruc ->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_W2_S_AvgTimeStruc ->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_W2_S_AvgTimeStruc ->Write();
    Hist_3D_W3_S_AvgTimeStruc ->Scale( (float)(1. / (float) totalEntry));
    Hist_3D_W3_S_AvgTimeStruc ->GetYaxis()->SetRangeUser(0, 4095);
    Hist_3D_W3_S_AvgTimeStruc ->Write();

    Hist_HS_W_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_W_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_W_C_AvgTimeStruc->Write();
    Hist_HS_1_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_1_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_1_C_AvgTimeStruc->Write();
    Hist_HS_2_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_2_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_2_C_AvgTimeStruc->Write();
    Hist_HS_3_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_3_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_3_C_AvgTimeStruc->Write();

    Hist_HS_W_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_W_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_W_S_AvgTimeStruc->Write();
    Hist_HS_1_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_1_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_1_S_AvgTimeStruc->Write();
    Hist_HS_2_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_2_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_2_S_AvgTimeStruc->Write();
    Hist_HS_3_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_HS_3_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_HS_3_S_AvgTimeStruc->Write();

    Hist_L_1_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_1_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_1_C_AvgTimeStruc->Write();
    Hist_L_2_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_2_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_2_C_AvgTimeStruc->Write();
    Hist_L_3_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_3_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_3_C_AvgTimeStruc->Write();
    Hist_L_4_C_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_4_C_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_4_C_AvgTimeStruc->Write();

    Hist_L_1_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_1_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_1_S_AvgTimeStruc->Write();
    Hist_L_2_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_2_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_2_S_AvgTimeStruc->Write();
    Hist_L_3_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_3_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_3_S_AvgTimeStruc->Write();
    Hist_L_4_S_AvgTimeStruc->Scale( (float)(1. / (float) totalEntry));
    Hist_L_4_S_AvgTimeStruc->GetYaxis()->SetRangeUser(0, 4095);
    Hist_L_4_S_AvgTimeStruc->Write();

    outputRoot->Close();
}
