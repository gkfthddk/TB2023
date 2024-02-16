#include <iostream>
#include <string>

#include "TBevt.h"
#include "TButility.h"

#include "functions.cc"

#include "TChain.h"
#include "TFile.h"

// Run the script by
// ./TBanalysis_ex <run number> <max entry>
// For example, ./TBanalysis_ex 4234 -1
// <max entry> == -1 means run all the entries
// This example uses external pedestal

int main(int argc, char** argv) {
    int runNum = std::stoi(argv[1]);

    // Load Ntuple using TChain
    TChain* WaveEvtChain = new TChain("event");
    TChain* FastEvtChain = new TChain("event");
    for (int fn = 0; fn < 50; fn++) {
        std::string wave_fileName = "ntuple_Run_" + std::to_string(runNum) + "_Wave_" + std::to_string(fn) + ".root";
        std::string wave_filePath = "/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2023_DRC_TB_ntuple/Run_"  + std::to_string(runNum) + "/Run_" + std::to_string(runNum) + "_Wave/"+ wave_fileName;
        if ( !access(wave_filePath.c_str(), F_OK) ){
            // std::cout << fn << " Ntuple file added to TChain : " << wave_filePath << std::endl;
            WaveEvtChain->Add(wave_filePath.c_str());
        }

        std::string fast_fileName = "ntuple_Run_" + std::to_string(runNum) + "_Fast_" + std::to_string(fn) + ".root";
        std::string fast_filePath = "/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2023_DRC_TB_ntuple/Run_"  + std::to_string(runNum) + "/Run_" + std::to_string(runNum) + "_Fast/"+ fast_fileName;
        if ( !access(fast_filePath.c_str(), F_OK) ){
            // std::cout << fn << " Ntuple file added to TChain : " << fast_filePath << std::endl;
            FastEvtChain->Add(fast_filePath.c_str());
        }
    }
    TBevt<TBwaveform>* WaveformEvt = new TBevt<TBwaveform>(); 
    WaveEvtChain->SetBranchAddress("TBevt", &WaveformEvt);

    TBevt<TBfastmode>* FastmodeEvt = new TBevt<TBfastmode>(); 
    FastEvtChain->SetBranchAddress("TBevt", &FastmodeEvt);

    // Check total # of events, limit # of events to process if maxEntry is specified
    int wave_totalEntry = WaveEvtChain->GetEntries();
    int fast_totalEntry = FastEvtChain->GetEntries();

    std::cout << std::to_string(runNum) << " " << wave_totalEntry << " " << fast_totalEntry << std::endl;
}
