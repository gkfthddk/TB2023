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
    int MID      = std::stoi(argv[2]);
    int maxEntry = std::stoi(argv[3]);

    // Hist for Pedestal distribution (Evt-by-evt)
    TH1F* Hist_Ch_1 = new TH1F( "EvtPed_Ch_1", ("MID_" + std::to_string(MID) + "_Ch_1;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_2 = new TH1F( "EvtPed_Ch_2", ("MID_" + std::to_string(MID) + "_Ch_2;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_3 = new TH1F( "EvtPed_Ch_3", ("MID_" + std::to_string(MID) + "_Ch_3;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_4 = new TH1F( "EvtPed_Ch_4", ("MID_" + std::to_string(MID) + "_Ch_4;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_5 = new TH1F( "EvtPed_Ch_5", ("MID_" + std::to_string(MID) + "_Ch_5;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_6 = new TH1F( "EvtPed_Ch_6", ("MID_" + std::to_string(MID) + "_Ch_6;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_7 = new TH1F( "EvtPed_Ch_7", ("MID_" + std::to_string(MID) + "_Ch_7;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_8 = new TH1F( "EvtPed_Ch_8", ("MID_" + std::to_string(MID) + "_Ch_8;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_9 = new TH1F( "EvtPed_Ch_9", ("MID_" + std::to_string(MID) + "_Ch_9;ADC;Evt").c_str(), 4096, 0, 4096);

    TH1F* Hist_Ch_10 = new TH1F( "EvtPed_Ch_10", ("MID_" + std::to_string(MID) + "_Ch_10;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_11 = new TH1F( "EvtPed_Ch_11", ("MID_" + std::to_string(MID) + "_Ch_11;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_12 = new TH1F( "EvtPed_Ch_12", ("MID_" + std::to_string(MID) + "_Ch_12;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_13 = new TH1F( "EvtPed_Ch_13", ("MID_" + std::to_string(MID) + "_Ch_13;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_14 = new TH1F( "EvtPed_Ch_14", ("MID_" + std::to_string(MID) + "_Ch_14;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_15 = new TH1F( "EvtPed_Ch_15", ("MID_" + std::to_string(MID) + "_Ch_15;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_16 = new TH1F( "EvtPed_Ch_16", ("MID_" + std::to_string(MID) + "_Ch_16;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_17 = new TH1F( "EvtPed_Ch_17", ("MID_" + std::to_string(MID) + "_Ch_17;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_18 = new TH1F( "EvtPed_Ch_18", ("MID_" + std::to_string(MID) + "_Ch_18;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_19 = new TH1F( "EvtPed_Ch_19", ("MID_" + std::to_string(MID) + "_Ch_19;ADC;Evt").c_str(), 4096, 0, 4096);

    TH1F* Hist_Ch_20 = new TH1F( "EvtPed_Ch_20", ("MID_" + std::to_string(MID) + "_Ch_20;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_21 = new TH1F( "EvtPed_Ch_21", ("MID_" + std::to_string(MID) + "_Ch_21;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_22 = new TH1F( "EvtPed_Ch_22", ("MID_" + std::to_string(MID) + "_Ch_22;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_23 = new TH1F( "EvtPed_Ch_23", ("MID_" + std::to_string(MID) + "_Ch_23;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_24 = new TH1F( "EvtPed_Ch_24", ("MID_" + std::to_string(MID) + "_Ch_24;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_25 = new TH1F( "EvtPed_Ch_25", ("MID_" + std::to_string(MID) + "_Ch_25;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_26 = new TH1F( "EvtPed_Ch_26", ("MID_" + std::to_string(MID) + "_Ch_26;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_27 = new TH1F( "EvtPed_Ch_27", ("MID_" + std::to_string(MID) + "_Ch_27;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_28 = new TH1F( "EvtPed_Ch_28", ("MID_" + std::to_string(MID) + "_Ch_28;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_29 = new TH1F( "EvtPed_Ch_29", ("MID_" + std::to_string(MID) + "_Ch_29;ADC;Evt").c_str(), 4096, 0, 4096);

    TH1F* Hist_Ch_30 = new TH1F( "EvtPed_Ch_30", ("MID_" + std::to_string(MID) + "_Ch_30;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_31 = new TH1F( "EvtPed_Ch_31", ("MID_" + std::to_string(MID) + "_Ch_31;ADC;Evt").c_str(), 4096, 0, 4096);
    TH1F* Hist_Ch_32 = new TH1F( "EvtPed_Ch_32", ("MID_" + std::to_string(MID) + "_Ch_32;ADC;Evt").c_str(), 4096, 0, 4096);
    
    // Load pedestal
    TH2F* pedMap = (TH2F*) (TFile::Open(("/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2023_DRC_TB_analysis/ped/Run_" + std::to_string(runNum) +"_pedestal.root").c_str()) )->Get("pedestal"); // By using pedestal map directly
    
    std::vector<TBcid> CIDvec;
    for (int ch = 1; ch < 33; ch++) {
        CIDvec.push_back(TBcid(MID, ch));
    }
    std::map<std::string, float> runPed;
    float RunPed_Ch_1 = pedMap->GetBinContent( MID, 1 ); runPed.insert( std::make_pair("RunPed_Ch_1", RunPed_Ch_1) );
    float RunPed_Ch_2 = pedMap->GetBinContent( MID, 2 ); runPed.insert( std::make_pair("RunPed_Ch_2", RunPed_Ch_2) );
    float RunPed_Ch_3 = pedMap->GetBinContent( MID, 3 ); runPed.insert( std::make_pair("RunPed_Ch_3", RunPed_Ch_3) );
    float RunPed_Ch_4 = pedMap->GetBinContent( MID, 4 ); runPed.insert( std::make_pair("RunPed_Ch_4", RunPed_Ch_4) );
    float RunPed_Ch_5 = pedMap->GetBinContent( MID, 5 ); runPed.insert( std::make_pair("RunPed_Ch_5", RunPed_Ch_5) );
    float RunPed_Ch_6 = pedMap->GetBinContent( MID, 6 ); runPed.insert( std::make_pair("RunPed_Ch_6", RunPed_Ch_6) );
    float RunPed_Ch_7 = pedMap->GetBinContent( MID, 7 ); runPed.insert( std::make_pair("RunPed_Ch_7", RunPed_Ch_7) );
    float RunPed_Ch_8 = pedMap->GetBinContent( MID, 8 ); runPed.insert( std::make_pair("RunPed_Ch_8", RunPed_Ch_8) );
    float RunPed_Ch_9 = pedMap->GetBinContent( MID, 9 ); runPed.insert( std::make_pair("RunPed_Ch_9", RunPed_Ch_9) );

    float RunPed_Ch_10 = pedMap->GetBinContent( MID, 10 ); runPed.insert( std::make_pair("RunPed_Ch_10", RunPed_Ch_10) );
    float RunPed_Ch_11 = pedMap->GetBinContent( MID, 11 ); runPed.insert( std::make_pair("RunPed_Ch_11", RunPed_Ch_11) );
    float RunPed_Ch_12 = pedMap->GetBinContent( MID, 12 ); runPed.insert( std::make_pair("RunPed_Ch_12", RunPed_Ch_12) );
    float RunPed_Ch_13 = pedMap->GetBinContent( MID, 13 ); runPed.insert( std::make_pair("RunPed_Ch_13", RunPed_Ch_13) );
    float RunPed_Ch_14 = pedMap->GetBinContent( MID, 14 ); runPed.insert( std::make_pair("RunPed_Ch_14", RunPed_Ch_14) );
    float RunPed_Ch_15 = pedMap->GetBinContent( MID, 15 ); runPed.insert( std::make_pair("RunPed_Ch_15", RunPed_Ch_15) );
    float RunPed_Ch_16 = pedMap->GetBinContent( MID, 16 ); runPed.insert( std::make_pair("RunPed_Ch_16", RunPed_Ch_16) );
    float RunPed_Ch_17 = pedMap->GetBinContent( MID, 17 ); runPed.insert( std::make_pair("RunPed_Ch_17", RunPed_Ch_17) );
    float RunPed_Ch_18 = pedMap->GetBinContent( MID, 18 ); runPed.insert( std::make_pair("RunPed_Ch_18", RunPed_Ch_18) );
    float RunPed_Ch_19 = pedMap->GetBinContent( MID, 19 ); runPed.insert( std::make_pair("RunPed_Ch_19", RunPed_Ch_19) );

    float RunPed_Ch_20 = pedMap->GetBinContent( MID, 20 ); runPed.insert( std::make_pair("RunPed_Ch_20", RunPed_Ch_20) );
    float RunPed_Ch_21 = pedMap->GetBinContent( MID, 21 ); runPed.insert( std::make_pair("RunPed_Ch_21", RunPed_Ch_21) );
    float RunPed_Ch_22 = pedMap->GetBinContent( MID, 22 ); runPed.insert( std::make_pair("RunPed_Ch_22", RunPed_Ch_22) );
    float RunPed_Ch_23 = pedMap->GetBinContent( MID, 23 ); runPed.insert( std::make_pair("RunPed_Ch_23", RunPed_Ch_23) );
    float RunPed_Ch_24 = pedMap->GetBinContent( MID, 24 ); runPed.insert( std::make_pair("RunPed_Ch_24", RunPed_Ch_24) );
    float RunPed_Ch_25 = pedMap->GetBinContent( MID, 25 ); runPed.insert( std::make_pair("RunPed_Ch_25", RunPed_Ch_25) );
    float RunPed_Ch_26 = pedMap->GetBinContent( MID, 26 ); runPed.insert( std::make_pair("RunPed_Ch_26", RunPed_Ch_26) );
    float RunPed_Ch_27 = pedMap->GetBinContent( MID, 27 ); runPed.insert( std::make_pair("RunPed_Ch_27", RunPed_Ch_27) );
    float RunPed_Ch_28 = pedMap->GetBinContent( MID, 28 ); runPed.insert( std::make_pair("RunPed_Ch_28", RunPed_Ch_28) );
    float RunPed_Ch_29 = pedMap->GetBinContent( MID, 29 ); runPed.insert( std::make_pair("RunPed_Ch_29", RunPed_Ch_29) );

    float RunPed_Ch_30 = pedMap->GetBinContent( MID, 30 ); runPed.insert( std::make_pair("RunPed_Ch_30", RunPed_Ch_30) );
    float RunPed_Ch_31 = pedMap->GetBinContent( MID, 31 ); runPed.insert( std::make_pair("RunPed_Ch_31", RunPed_Ch_31) );
    float RunPed_Ch_32 = pedMap->GetBinContent( MID, 32 ); runPed.insert( std::make_pair("RunPed_Ch_32", RunPed_Ch_32) );

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
        std::vector<TBwaveform> data_vec;
        for (TBcid cid : CIDvec) {
            data_vec.push_back(anEvt->GetData(cid));
        }
        
        // Waveform vector
        std::vector<std::vector<short>> waveform_vec;
        for (TBwaveform wave : data_vec) {
            waveform_vec.push_back(wave.waveform());
        }

        // Evt-by-evt pedestal
        float EvtPed_Ch_1 = 0.f;
        float EvtPed_Ch_2 = 0.f;
        float EvtPed_Ch_3 = 0.f;
        float EvtPed_Ch_4 = 0.f;
        float EvtPed_Ch_5 = 0.f;
        float EvtPed_Ch_6 = 0.f;
        float EvtPed_Ch_7 = 0.f;
        float EvtPed_Ch_8 = 0.f;
        float EvtPed_Ch_9 = 0.f;

        float EvtPed_Ch_10 = 0.f;
        float EvtPed_Ch_11 = 0.f;
        float EvtPed_Ch_12 = 0.f;
        float EvtPed_Ch_13 = 0.f;
        float EvtPed_Ch_14 = 0.f;
        float EvtPed_Ch_15 = 0.f;
        float EvtPed_Ch_16 = 0.f;
        float EvtPed_Ch_17 = 0.f;
        float EvtPed_Ch_18 = 0.f;
        float EvtPed_Ch_19 = 0.f;

        float EvtPed_Ch_20 = 0.f;
        float EvtPed_Ch_21 = 0.f;
        float EvtPed_Ch_22 = 0.f;
        float EvtPed_Ch_23 = 0.f;
        float EvtPed_Ch_24 = 0.f;
        float EvtPed_Ch_25 = 0.f;
        float EvtPed_Ch_26 = 0.f;
        float EvtPed_Ch_27 = 0.f;
        float EvtPed_Ch_28 = 0.f;
        float EvtPed_Ch_29 = 0.f;

        float EvtPed_Ch_30 = 0.f;
        float EvtPed_Ch_31 = 0.f;
        float EvtPed_Ch_32 = 0.f;

        for(int bin = 1; bin < 101; bin++) {
            EvtPed_Ch_1 += (float) (waveform_vec.at(0)[bin] / 100.);
            EvtPed_Ch_2 += (float) (waveform_vec.at(1)[bin] / 100.);
            EvtPed_Ch_3 += (float) (waveform_vec.at(2)[bin] / 100.);
            EvtPed_Ch_4 += (float) (waveform_vec.at(3)[bin] / 100.);
            EvtPed_Ch_5 += (float) (waveform_vec.at(4)[bin] / 100.);
            EvtPed_Ch_6 += (float) (waveform_vec.at(5)[bin] / 100.);
            EvtPed_Ch_7 += (float) (waveform_vec.at(6)[bin] / 100.);
            EvtPed_Ch_8 += (float) (waveform_vec.at(7)[bin] / 100.);
            EvtPed_Ch_9 += (float) (waveform_vec.at(8)[bin] / 100.);

            EvtPed_Ch_10 += (float) (waveform_vec.at(9)[bin] / 100.);
            EvtPed_Ch_11 += (float) (waveform_vec.at(10)[bin] / 100.);
            EvtPed_Ch_12 += (float) (waveform_vec.at(11)[bin] / 100.);
            EvtPed_Ch_13 += (float) (waveform_vec.at(12)[bin] / 100.);
            EvtPed_Ch_14 += (float) (waveform_vec.at(13)[bin] / 100.);
            EvtPed_Ch_15 += (float) (waveform_vec.at(14)[bin] / 100.);
            EvtPed_Ch_16 += (float) (waveform_vec.at(15)[bin] / 100.);
            EvtPed_Ch_17 += (float) (waveform_vec.at(16)[bin] / 100.);
            EvtPed_Ch_18 += (float) (waveform_vec.at(17)[bin] / 100.);
            EvtPed_Ch_19 += (float) (waveform_vec.at(18)[bin] / 100.);

            EvtPed_Ch_20 += (float) (waveform_vec.at(19)[bin] / 100.);
            EvtPed_Ch_21 += (float) (waveform_vec.at(20)[bin] / 100.);
            EvtPed_Ch_22 += (float) (waveform_vec.at(21)[bin] / 100.);
            EvtPed_Ch_23 += (float) (waveform_vec.at(22)[bin] / 100.);
            EvtPed_Ch_24 += (float) (waveform_vec.at(23)[bin] / 100.);
            EvtPed_Ch_25 += (float) (waveform_vec.at(24)[bin] / 100.);
            EvtPed_Ch_26 += (float) (waveform_vec.at(25)[bin] / 100.);
            EvtPed_Ch_27 += (float) (waveform_vec.at(26)[bin] / 100.);
            EvtPed_Ch_28 += (float) (waveform_vec.at(27)[bin] / 100.);
            EvtPed_Ch_29 += (float) (waveform_vec.at(28)[bin] / 100.);

            EvtPed_Ch_30 += (float) (waveform_vec.at(29)[bin] / 100.);
            EvtPed_Ch_31 += (float) (waveform_vec.at(30)[bin] / 100.);
            EvtPed_Ch_32 += (float) (waveform_vec.at(31)[bin] / 100.);
        }

        // Fill evt ped
        Hist_Ch_1->Fill(EvtPed_Ch_1);        
        Hist_Ch_2->Fill(EvtPed_Ch_2);        
        Hist_Ch_3->Fill(EvtPed_Ch_3);        
        Hist_Ch_4->Fill(EvtPed_Ch_4);        
        Hist_Ch_5->Fill(EvtPed_Ch_5);        
        Hist_Ch_6->Fill(EvtPed_Ch_6);        
        Hist_Ch_7->Fill(EvtPed_Ch_7);        
        Hist_Ch_8->Fill(EvtPed_Ch_8);        
        Hist_Ch_9->Fill(EvtPed_Ch_9);     
        
        Hist_Ch_10->Fill(EvtPed_Ch_10);        
        Hist_Ch_11->Fill(EvtPed_Ch_11);        
        Hist_Ch_12->Fill(EvtPed_Ch_12);        
        Hist_Ch_13->Fill(EvtPed_Ch_13);        
        Hist_Ch_14->Fill(EvtPed_Ch_14);        
        Hist_Ch_15->Fill(EvtPed_Ch_15);        
        Hist_Ch_16->Fill(EvtPed_Ch_16);        
        Hist_Ch_17->Fill(EvtPed_Ch_17);        
        Hist_Ch_18->Fill(EvtPed_Ch_18);        
        Hist_Ch_19->Fill(EvtPed_Ch_19); 

        Hist_Ch_20->Fill(EvtPed_Ch_20);        
        Hist_Ch_21->Fill(EvtPed_Ch_21);        
        Hist_Ch_22->Fill(EvtPed_Ch_22);        
        Hist_Ch_23->Fill(EvtPed_Ch_23);        
        Hist_Ch_24->Fill(EvtPed_Ch_24);        
        Hist_Ch_25->Fill(EvtPed_Ch_25);        
        Hist_Ch_26->Fill(EvtPed_Ch_26);        
        Hist_Ch_27->Fill(EvtPed_Ch_27);        
        Hist_Ch_28->Fill(EvtPed_Ch_28);        
        Hist_Ch_29->Fill(EvtPed_Ch_29); 

        Hist_Ch_30->Fill(EvtPed_Ch_30);        
        Hist_Ch_31->Fill(EvtPed_Ch_31);        
        Hist_Ch_32->Fill(EvtPed_Ch_32); 
    }

    // Save the outputs
    std::string outFile = "./PedDistribution/PedDistribution_Run_" + std::to_string(runNum) + ".root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    Hist_Ch_1->Write();
    Hist_Ch_2->Write();
    Hist_Ch_3->Write();
    Hist_Ch_4->Write();
    Hist_Ch_5->Write();
    Hist_Ch_6->Write();
    Hist_Ch_7->Write();
    Hist_Ch_8->Write();
    Hist_Ch_9->Write();

    Hist_Ch_10->Write();
    Hist_Ch_11->Write();
    Hist_Ch_12->Write();
    Hist_Ch_13->Write();
    Hist_Ch_14->Write();
    Hist_Ch_15->Write();
    Hist_Ch_16->Write();
    Hist_Ch_17->Write();
    Hist_Ch_18->Write();
    Hist_Ch_19->Write();

    Hist_Ch_20->Write();
    Hist_Ch_21->Write();
    Hist_Ch_22->Write();
    Hist_Ch_23->Write();
    Hist_Ch_24->Write();
    Hist_Ch_25->Write();
    Hist_Ch_26->Write();
    Hist_Ch_27->Write();
    Hist_Ch_28->Write();
    Hist_Ch_29->Write();

    Hist_Ch_30->Write();
    Hist_Ch_31->Write();
    Hist_Ch_32->Write();

    outputRoot->WriteObject(&runPed, "runPedMap");

    outputRoot->Close();
}