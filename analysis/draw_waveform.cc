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
#include "TCanvas.h"

namespace fs = std::filesystem;

// This script is for drawing event-by-event waveform of DRC towers and auxiliary detectors
//
// 1. Compile script
// ./compile.sh draw_waveform.cc
//
// 2. Execute compiled script
// ./draw_waveform <run number> <max entry>
// Ex) ./draw_waveform 953 100   -> this will draw total 100 waveforms (event 1 ~ 100) of Run953 data.
// if <max entry> is -1, then it will run over all events in the run

int main(int argc, char** argv) {
    gStyle->SetOptStat(0);

    int runNum   = std::stoi(argv[1]);
    int maxEntry = std::stoi(argv[2]);

    // Load Ntuple using TChain
    TChain* evtChain = loadNtuple(runNum);
    TBevt<TBwaveform>* anEvt = new TBevt<TBwaveform>(); // Event data will be delivered in "TBwaveform" format
    evtChain->SetBranchAddress("TBevt", &anEvt);

    // Check total # of events, limit # of events to process if maxEntry is specified
    int totalEntry = evtChain->GetEntries();
    std::cout << "Total entries : " << totalEntry << std::endl;
    if ( (maxEntry > 0) && (maxEntry < totalEntry) ) {
        totalEntry = maxEntry;
        std::cout << "Will process maximum " << std::to_string(totalEntry) << " events" << std::endl;
    }

    // Prepare canvas to draw waveform
    TCanvas* c = new TCanvas("c", "c", 1000, 800);
    // Prepare output directory
    fs::path dir("./Waveform");
    if ( !(fs::exists(dir)) ) fs::create_directory(dir);

    // Load mapping info
    // Mapping info can be found at "functions.cc"
    // map.at("<tower name>") will give pair of int, (int MID, int Ch) where MID is DAQ board number & Ch is channel number
    // TBcid : stores MID and Ch info, and works as a "key" to load event data of corresponding detector
    // For example, MCP-PMT summation Scintillation signal is linked to MID 8 Ch 2 -> TBcid(8, 2) will represent that channel
    auto map = getModuleConfigMap();
    TBcid CID_3D_S = TBcid( map.at("mid-Scint").at(0),  map.at("mid-Scint").at(1) );

    // Start event loop
    for (int iEvt = 0; iEvt < totalEntry; iEvt++) {
        printProgress(iEvt + 1, totalEntry); // print progress bar
        evtChain->GetEntry(iEvt); // Load event data to "anEvt"

        // Get TBwaveform of each event
        // passing TBcid to anEvt->GetData() function will return TBwaveform data of corresponding TBcid
        TBwaveform Data_3D_S = anEvt->GetData(CID_3D_S);

        // Get waveform vector
        // From TBwaveform, one can get actual waveform data (which has std::vector<short> format)
        // waveform is stored as array with length 1024
        // From bin 1 ~ 1000 : Actual ADC value recorded per time bin
        std::vector<short> Waveform_3D_S = Data_3D_S.waveform();

        // Declare histogram to store waveform
        TH1F* h_3D_S_waveform = new TH1F( (TString) ("3D_S_waveform_Evt_" + std::to_string(iEvt)), (TString) ("3D_S_waveform_Evt_" + std::to_string(iEvt) + ";bin;ADC"), 1000, 0, 1000);
        
        // Fill waveform histograms
        // Get waveform bin 1 ~ 1000 to fill histogram
        for(int bin = 1; bin < 1001; bin++) {
            h_3D_S_waveform->Fill(bin, Waveform_3D_S[bin]);
        }

        c->cd();
        h_3D_S_waveform->SetLineColor(kBlack); // Set line color
        h_3D_S_waveform->GetYaxis()->SetRangeUser(0, 4095); // Set Y-axis range
        h_3D_S_waveform->Draw("hist"); // Draw waveform
        c->SaveAs((TString) ("./Waveform/3D_S_waveform_Evt_" + std::to_string(iEvt) + ".png")); // Save waveform image
    }
}