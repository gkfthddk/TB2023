#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "TBevt.h"
#include "TButility.h"

#include "functions.cc"

#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"

int main(int argc, char** argv) {
    int runNum = std::stoi(argv[1]);
    int maxEntry = std::stoi(argv[2]);

    TH2F* pedHist = new TH2F("pedestal", "pedestal;MID;CH", 15, 0, 15, 32, 0, 32);

    // std::vector<int> MIDvec = {1, 2, 3, 4, 8, 9, 12};
    std::vector<int> MIDvec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15};
    std::vector<TBcid> CIDvec;
    for(int MID : MIDvec) {
        for(int CH = 1; CH < 33; CH++){
            CIDvec.push_back(TBcid(MID, CH));
        }
    }
    std::vector<float> PEDvec(CIDvec.size(), 0.);

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

    // Evt Loop start
    for (int iEvt = 0; iEvt < totalEntry; iEvt++) {
        printProgress(iEvt + 1, totalEntry); // Print progress bar
        evtChain->GetEntry(iEvt); // Get event

        for(int idx = 0; idx < CIDvec.size(); idx++) {
            TBcid CID = CIDvec.at(idx);
            TBwaveform data = anEvt->GetData(CID);            
            std::vector<short> wave = data.waveform();
            if(!(wave.size() == 1024)) continue;
            float single_ped = std::accumulate( wave.begin() + 1, wave.begin() + 101, 0.) / 100.;
            PEDvec.at(idx) += single_ped;
        }
    }

    for(int idx = 0; idx < CIDvec.size(); idx++) {
        float tmp_ped = PEDvec.at(idx) / (float) totalEntry;
        int MID = (CIDvec.at(idx)).mid();
        int CH  = (CIDvec.at(idx)).channel();
        pedHist->Fill(MID-1, CH-1, tmp_ped);
    }

    TFile* output = new TFile( (TString)("./ped/Run_" + std::to_string(runNum) + "_pedestal.root"), "RECREATE");
    output->cd();
    pedHist->Write();
    output->Close();
}
