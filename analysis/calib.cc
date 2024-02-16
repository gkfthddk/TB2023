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

// This script is for measuring energy (w/o scale factor)
// Calculate equalization constants before running this script!
//
// 1. Compile the script
// ./compile calib
//
// 2. Run the compiled script
// ./calib <run number> <max entry>
// Ex) ./calib 4234 -1
// <max entry> == -1 means run all the entries
//
// This example uses run pedestal

int main(int argc, char** argv) {
    int runNum = std::stoi(argv[1]);
    int maxEntry = std::stoi(argv[2]);

    // Sample equalization constants
    float Calib_3D_mid_C = 0.0000871742;
    float Calib_3D_W1_C  = 0.0000068554;
    float Calib_3D_W2_C  = 0.0000197590;
    float Calib_3D_W3_C  = 0.0000169860;
    float Calib_HS_W_C   = 0.0000683645;
    float Calib_HS_1_C   = 0.0000597309;
    float Calib_HS_2_C   = 0.0000582106;
    float Calib_HS_3_C   = 0.0000626588;
    float Calib_L_1_C    = 0.0000686133;
    float Calib_L_2_C    = 0.0003871370;
    float Calib_L_3_C    = 0.0000734357;
    float Calib_L_4_C    = 0.0001356897;

    float Calib_3D_mid_S = 0.0000423638;
    float Calib_3D_W1_S  = 0.0000043396;
    float Calib_3D_W2_S  = 0.0000048264;
    float Calib_3D_W3_S  = 0.0000050008;
    float Calib_HS_W_S   = 0.0000399567;
    float Calib_HS_1_S   = 0.0000345974;
    float Calib_HS_2_S   = 0.0000365558;
    float Calib_HS_3_S   = 0.0000356192;
    float Calib_L_1_S    = 0.0000416009;
    float Calib_L_2_S    = 0.0000254119;
    float Calib_L_3_S    = 0.0000450819;
    float Calib_L_4_S    = 0.0000690672;

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

    // Load run-pedestal
    TH2F* pedMap = loadPed(runNum); // By using pedestal map directly

    // Preparing histograms for ADC
    TH1F* Hist_C_counter_1_PeakADC = new TH1F("C_counter_1_PeakADC", "C_counter_1_PeakADC;PeakADC;Evt", 4096, 0, 4096);
    TH1F* Hist_C_counter_2_PeakADC = new TH1F("C_counter_2_PeakADC", "C_counter_2_PeakADC;PeakADC;Evt", 4096, 0, 4096);

    TH1F* Hist_3D_mid_C_IntADC = new TH1F("3D_sum_C_IntADC", "3D_sum_C_IntADC;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_C_IntADC  = new TH1F("3D_W1_C_IntADC",   "3D_W1_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_C_IntADC  = new TH1F("3D_W2_C_IntADC",   "3D_W2_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_C_IntADC  = new TH1F("3D_W3_C_IntADC",   "3D_W3_C_IntADC;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_3D_mid_S_IntADC = new TH1F("3D_sum_S_IntADC", "3D_sum_S_IntADC;IntADC;Evt", 1000, -5000, 200000);
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

    TH1F* Hist_C_Energy   = new TH1F("C_Energy", "C_Energy;GeV;Evt", 250, -5, 20); // Adding all (IntADC * Equ. Const.) including 3D Wings
    TH1F* Hist_S_Energy   = new TH1F("S_Energy", "S_Energy;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Energy = new TH1F("Sum_Energy", "Sum_Energy;GeV;Evt", 500, -10, 40);

    TH1F* Hist_3D_mid_C_Calibrated = new TH1F("3D_sum_C_Calibrated", "3D_sum_C_Calibrated;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_C_Calibrated  = new TH1F("3D_W1_C_Calibrated",   "3D_W1_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_C_Calibrated  = new TH1F("3D_W2_C_Calibrated",   "3D_W2_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_C_Calibrated  = new TH1F("3D_W3_C_Calibrated",   "3D_W3_C_Calibrated;GeV;Evt",   250, -5, 20);

    TH1F* Hist_3D_mid_S_Calibrated = new TH1F("3D_sum_S_Calibrated", "3D_sum_S_Calibrated;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_S_Calibrated  = new TH1F("3D_W1_S_Calibrated",   "3D_W1_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_S_Calibrated  = new TH1F("3D_W2_S_Calibrated",   "3D_W2_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_S_Calibrated  = new TH1F("3D_W3_S_Calibrated",   "3D_W3_S_Calibrated;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_C_Calibrated  = new TH1F("HS_W_C_Calibrated",   "HS_W_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_C_Calibrated  = new TH1F("HS_1_C_Calibrated",   "HS_1_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_C_Calibrated  = new TH1F("HS_2_C_Calibrated",   "HS_2_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_C_Calibrated  = new TH1F("HS_3_C_Calibrated",   "HS_3_C_Calibrated;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_S_Calibrated  = new TH1F("HS_W_S_Calibrated",   "HS_W_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_S_Calibrated  = new TH1F("HS_1_S_Calibrated",   "HS_1_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_S_Calibrated  = new TH1F("HS_2_S_Calibrated",   "HS_2_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_S_Calibrated  = new TH1F("HS_3_S_Calibrated",   "HS_3_S_Calibrated;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_C_Calibrated  = new TH1F("L_1_C_Calibrated",   "L_1_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_C_Calibrated  = new TH1F("L_2_C_Calibrated",   "L_2_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_C_Calibrated  = new TH1F("L_3_C_Calibrated",   "L_3_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_C_Calibrated  = new TH1F("L_4_C_Calibrated",   "L_4_C_Calibrated;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_S_Calibrated  = new TH1F("L_1_S_Calibrated",   "L_1_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_S_Calibrated  = new TH1F("L_2_S_Calibrated",   "L_2_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_S_Calibrated  = new TH1F("L_3_S_Calibrated",   "L_3_S_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_S_Calibrated  = new TH1F("L_4_S_Calibrated",   "L_4_S_Calibrated;GeV;Evt",   250, -5, 20);
    
    // After cut
    TH1F* Hist_C_counter_1_PeakADC_cut = new TH1F("C_counter_1_PeakADC_cut", "C_counter_1_PeakADC_cut;PeakADC;Evt", 4096, 0, 4096);
    TH1F* Hist_C_counter_2_PeakADC_cut = new TH1F("C_counter_2_PeakADC_cut", "C_counter_2_PeakADC_cut;PeakADC;Evt", 4096, 0, 4096);

    TH1F* Hist_3D_mid_C_IntADC_cut = new TH1F("3D_sum_C_IntADC_cut", "3D_sum_C_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_C_IntADC_cut  = new TH1F("3D_W1_C_IntADC_cut",   "3D_W1_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_C_IntADC_cut  = new TH1F("3D_W2_C_IntADC_cut",   "3D_W2_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_C_IntADC_cut  = new TH1F("3D_W3_C_IntADC_cut",   "3D_W3_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_3D_mid_S_IntADC_cut = new TH1F("3D_sum_S_IntADC_cut", "3D_sum_S_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
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

    TH1F* Hist_C_Energy_cut   = new TH1F("C_Energy_cut", "C_Energy_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_S_Energy_cut   = new TH1F("S_Energy_cut", "S_Energy_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Energy_cut = new TH1F("Sum_Energy_cut", "Sum_Energy_cut;GeV;Evt", 500, -10, 40);

    TH1F* Hist_3D_mid_C_Calibrated_cut = new TH1F("3D_sum_C_Calibrated_cut", "3D_sum_C_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_C_Calibrated_cut  = new TH1F("3D_W1_C_Calibrated_cut",   "3D_W1_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_C_Calibrated_cut  = new TH1F("3D_W2_C_Calibrated_cut",   "3D_W2_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_C_Calibrated_cut  = new TH1F("3D_W3_C_Calibrated_cut",   "3D_W3_C_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_3D_mid_S_Calibrated_cut = new TH1F("3D_sum_S_Calibrated_cut", "3D_sum_S_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_S_Calibrated_cut  = new TH1F("3D_W1_S_Calibrated_cut",   "3D_W1_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_S_Calibrated_cut  = new TH1F("3D_W2_S_Calibrated_cut",   "3D_W2_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_S_Calibrated_cut  = new TH1F("3D_W3_S_Calibrated_cut",   "3D_W3_S_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_C_Calibrated_cut  = new TH1F("HS_W_C_Calibrated_cut",   "HS_W_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_C_Calibrated_cut  = new TH1F("HS_1_C_Calibrated_cut",   "HS_1_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_C_Calibrated_cut  = new TH1F("HS_2_C_Calibrated_cut",   "HS_2_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_C_Calibrated_cut  = new TH1F("HS_3_C_Calibrated_cut",   "HS_3_C_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_S_Calibrated_cut  = new TH1F("HS_W_S_Calibrated_cut",   "HS_W_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_S_Calibrated_cut  = new TH1F("HS_1_S_Calibrated_cut",   "HS_1_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_S_Calibrated_cut  = new TH1F("HS_2_S_Calibrated_cut",   "HS_2_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_S_Calibrated_cut  = new TH1F("HS_3_S_Calibrated_cut",   "HS_3_S_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_C_Calibrated_cut  = new TH1F("L_1_C_Calibrated_cut",   "L_1_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_C_Calibrated_cut  = new TH1F("L_2_C_Calibrated_cut",   "L_2_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_C_Calibrated_cut  = new TH1F("L_3_C_Calibrated_cut",   "L_3_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_C_Calibrated_cut  = new TH1F("L_4_C_Calibrated_cut",   "L_4_C_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_S_Calibrated_cut  = new TH1F("L_1_S_Calibrated_cut",   "L_1_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_S_Calibrated_cut  = new TH1F("L_2_S_Calibrated_cut",   "L_2_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_S_Calibrated_cut  = new TH1F("L_3_S_Calibrated_cut",   "L_3_S_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_S_Calibrated_cut  = new TH1F("L_4_S_Calibrated_cut",   "L_4_S_Calibrated_cut;GeV;Evt",   250, -5, 20);

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

    // Get run pedestals for each readouts
    std::vector<float> Ped_C_counter;
    for(TBcid cid : CID_C_counter) {
        Ped_C_counter.push_back( pedMap->GetBinContent(cid.mid(), cid.channel()) );
    }

    std::vector<float> Ped_3D_C;
    for(TBcid cid : CID_3D_C) {
        Ped_3D_C.push_back( pedMap->GetBinContent(cid.mid(), cid.channel()) );
    }
    std::vector<float> Ped_3D_S;
    for(TBcid cid : CID_3D_S) {
        Ped_3D_S.push_back( pedMap->GetBinContent(cid.mid(), cid.channel()) );
    }

    std::vector<float> Ped_HeatSink_C;
    for(TBcid cid : CID_HeatSink_C) {
        Ped_HeatSink_C.push_back( pedMap->GetBinContent(cid.mid(), cid.channel()) );
    }
    std::vector<float> Ped_HeatSink_S;
    for(TBcid cid : CID_HeatSink_S) {
        Ped_HeatSink_S.push_back( pedMap->GetBinContent(cid.mid(), cid.channel()) );
    }

    std::vector<float> Ped_Lego_C;
    for(TBcid cid : CID_Lego_C) {
        Ped_Lego_C.push_back( pedMap->GetBinContent(cid.mid(), cid.channel()) );
    }
    std::vector<float> Ped_Lego_S;
    for(TBcid cid : CID_Lego_S) {
        Ped_Lego_S.push_back( pedMap->GetBinContent(cid.mid(), cid.channel()) );
    }

    // PID selection criteria
    float Cut_C_counter_1 = 100.;
    float Cut_C_counter_2 = 80.;

    // Event Loop start
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
        
        // PID uses "Peak ADC count"!!
        // GetPeakWithPed(waveform, peak range start, peak range end, pedestal value)
        // this function returns PeakADC count of provided waveform
        // searched within provided peak range and pedestal
        // Here we use run-pedestal to calculate PeakADC
        float PeakADC_C_counter_1 = GetPeakWithPed(Wave_C_counter.at(0), 390, 660, Ped_C_counter.at(0));
        float PeakADC_C_counter_2 = GetPeakWithPed(Wave_C_counter.at(1), 230, 450, Ped_C_counter.at(1));
        
        // Get "Integrated ADC count"
        // GetIntWithPed(waveform, integral range start, integral range end, pedestal value)
        // this function retuns IntADC count of provided waveform
        // integrated within [start, end), with provided pedestal value
        float IntADC_3D_mid_C = GetIntWithPed(Wave_3D_C.at(0), 140, 270, Ped_3D_C.at(0));
        float IntADC_3D_W1_C  = GetIntWithPed(Wave_3D_C.at(1), 130, 270, Ped_3D_C.at(1));
        float IntADC_3D_W2_C  = GetIntWithPed(Wave_3D_C.at(2), 150, 260, Ped_3D_C.at(2));
        float IntADC_3D_W3_C  = GetIntWithPed(Wave_3D_C.at(3), 140, 250, Ped_3D_C.at(3));

        float IntADC_3D_mid_S = GetIntWithPed(Wave_3D_S.at(0), 140, 320, Ped_3D_S.at(0));
        float IntADC_3D_W1_S  = GetIntWithPed(Wave_3D_S.at(1), 150, 320, Ped_3D_S.at(1));
        float IntADC_3D_W2_S  = GetIntWithPed(Wave_3D_S.at(2), 160, 300, Ped_3D_S.at(2));
        float IntADC_3D_W3_S  = GetIntWithPed(Wave_3D_S.at(3), 150, 300, Ped_3D_S.at(3));

        float IntADC_HS_W_C  = GetIntWithPed(Wave_HeatSink_C.at(0), 130, 280, Ped_HeatSink_C.at(0));
        float IntADC_HS_1_C  = GetIntWithPed(Wave_HeatSink_C.at(1), 150, 300, Ped_HeatSink_C.at(1));
        float IntADC_HS_2_C  = GetIntWithPed(Wave_HeatSink_C.at(2), 145, 300, Ped_HeatSink_C.at(2));
        float IntADC_HS_3_C  = GetIntWithPed(Wave_HeatSink_C.at(3), 140, 290, Ped_HeatSink_C.at(3));

        float IntADC_HS_W_S  = GetIntWithPed(Wave_HeatSink_S.at(0), 140, 330, Ped_HeatSink_S.at(0));
        float IntADC_HS_1_S  = GetIntWithPed(Wave_HeatSink_S.at(1), 160, 340, Ped_HeatSink_S.at(1));
        float IntADC_HS_2_S  = GetIntWithPed(Wave_HeatSink_S.at(2), 155, 335, Ped_HeatSink_S.at(2));
        float IntADC_HS_3_S  = GetIntWithPed(Wave_HeatSink_S.at(3), 155, 330, Ped_HeatSink_S.at(3));

        float IntADC_L_1_C  = GetIntWithPed(Wave_Lego_C.at(0), 150, 330, Ped_Lego_C.at(0));
        float IntADC_L_2_C  = GetIntWithPed(Wave_Lego_C.at(1), 210, 350, Ped_Lego_C.at(1));
        float IntADC_L_3_C  = GetIntWithPed(Wave_Lego_C.at(2), 140, 300, Ped_Lego_C.at(2));
        float IntADC_L_4_C  = GetIntWithPed(Wave_Lego_C.at(3), 150, 290, Ped_Lego_C.at(3));

        float IntADC_L_1_S  = GetIntWithPed(Wave_Lego_S.at(0), 170, 360, Ped_Lego_S.at(0));
        float IntADC_L_2_S  = GetIntWithPed(Wave_Lego_S.at(1), 215, 410, Ped_Lego_S.at(1));
        float IntADC_L_3_S  = GetIntWithPed(Wave_Lego_S.at(2), 160, 340, Ped_Lego_S.at(2));
        float IntADC_L_4_S  = GetIntWithPed(Wave_Lego_S.at(3), 155, 340, Ped_Lego_S.at(3));

        // (IntADC * Equalization constant) = Energy measured (not scaled yet) within that tower
        float Calibrated_3D_mid_C = IntADC_3D_mid_C * Calib_3D_mid_C;
        float Calibrated_3D_W1_C  = IntADC_3D_W1_C  * Calib_3D_W1_C;
        float Calibrated_3D_W2_C  = IntADC_3D_W2_C  * Calib_3D_W2_C;
        float Calibrated_3D_W3_C  = IntADC_3D_W3_C  * Calib_3D_W3_C;

        float Calibrated_HS_W_C  = IntADC_HS_W_C  * Calib_HS_W_C;
        float Calibrated_HS_1_C  = IntADC_HS_1_C  * Calib_HS_1_C;
        float Calibrated_HS_2_C  = IntADC_HS_2_C  * Calib_HS_2_C;
        float Calibrated_HS_3_C  = IntADC_HS_3_C  * Calib_HS_3_C;
        
        float Calibrated_L_1_C  = IntADC_L_1_C  * Calib_L_1_C;
        float Calibrated_L_2_C  = IntADC_L_2_C  * Calib_L_2_C;
        float Calibrated_L_3_C  = IntADC_L_3_C  * Calib_L_3_C;
        float Calibrated_L_4_C  = IntADC_L_4_C  * Calib_L_4_C;

        float Calibrated_3D_mid_S = IntADC_3D_mid_S * Calib_3D_mid_S;
        float Calibrated_3D_W1_S  = IntADC_3D_W1_S  * Calib_3D_W1_S;
        float Calibrated_3D_W2_S  = IntADC_3D_W2_S  * Calib_3D_W2_S;
        float Calibrated_3D_W3_S  = IntADC_3D_W3_S  * Calib_3D_W3_S;

        float Calibrated_HS_W_S  = IntADC_HS_W_S  * Calib_HS_W_S;
        float Calibrated_HS_1_S  = IntADC_HS_1_S  * Calib_HS_1_S;
        float Calibrated_HS_2_S  = IntADC_HS_2_S  * Calib_HS_2_S;
        float Calibrated_HS_3_S  = IntADC_HS_3_S  * Calib_HS_3_S;
        
        float Calibrated_L_1_S  = IntADC_L_1_S  * Calib_L_1_S;
        float Calibrated_L_2_S  = IntADC_L_2_S  * Calib_L_2_S;
        float Calibrated_L_3_S  = IntADC_L_3_S  * Calib_L_3_S;
        float Calibrated_L_4_S  = IntADC_L_4_S  * Calib_L_4_S;

        // Sum up Cherenkov channel energy
        float Calibrated_C =    Calibrated_3D_mid_C + Calibrated_3D_W1_C + Calibrated_3D_W2_C + Calibrated_3D_W3_C + 
                                Calibrated_HS_W_C + Calibrated_HS_1_C + Calibrated_HS_2_C + Calibrated_HS_3_C +
                                Calibrated_L_1_C + Calibrated_L_2_C + Calibrated_L_3_C + Calibrated_L_4_C;
        // Sum up scintillation channel energy
        float Calibrated_S =    Calibrated_3D_mid_S + Calibrated_3D_W1_S + Calibrated_3D_W2_S + Calibrated_3D_W3_S +
                                Calibrated_HS_W_S + Calibrated_HS_1_S + Calibrated_HS_2_S + Calibrated_HS_3_S +
                                Calibrated_L_1_S + Calibrated_L_2_S + Calibrated_L_3_S + Calibrated_L_4_S;

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

        // Here we fill energy histograms before PID selection
        Hist_C_Energy->Fill(Calibrated_C);
        Hist_S_Energy->Fill(Calibrated_S);
        Hist_Sum_Energy->Fill(Calibrated_C + Calibrated_S);

        Hist_3D_mid_C_Calibrated->Fill(Calibrated_3D_mid_C);
        Hist_3D_W1_C_Calibrated ->Fill(Calibrated_3D_W1_C);
        Hist_3D_W2_C_Calibrated ->Fill(Calibrated_3D_W2_C);
        Hist_3D_W3_C_Calibrated ->Fill(Calibrated_3D_W3_C);

        Hist_3D_mid_S_Calibrated->Fill(Calibrated_3D_mid_S);
        Hist_3D_W1_S_Calibrated ->Fill(Calibrated_3D_W1_S);
        Hist_3D_W2_S_Calibrated ->Fill(Calibrated_3D_W2_S);
        Hist_3D_W3_S_Calibrated ->Fill(Calibrated_3D_W3_S);

        Hist_HS_W_C_Calibrated->Fill(Calibrated_HS_W_C);
        Hist_HS_1_C_Calibrated->Fill(Calibrated_HS_1_C);
        Hist_HS_2_C_Calibrated->Fill(Calibrated_HS_2_C);
        Hist_HS_3_C_Calibrated->Fill(Calibrated_HS_3_C);

        Hist_HS_W_S_Calibrated->Fill(Calibrated_HS_W_S);
        Hist_HS_1_S_Calibrated->Fill(Calibrated_HS_1_S);
        Hist_HS_2_S_Calibrated->Fill(Calibrated_HS_2_S);
        Hist_HS_3_S_Calibrated->Fill(Calibrated_HS_3_S);
    
        Hist_L_1_C_Calibrated->Fill(Calibrated_L_1_C);
        Hist_L_2_C_Calibrated->Fill(Calibrated_L_2_C);
        Hist_L_3_C_Calibrated->Fill(Calibrated_L_3_C);
        Hist_L_4_C_Calibrated->Fill(Calibrated_L_4_C);

        Hist_L_1_S_Calibrated->Fill(Calibrated_L_1_S);
        Hist_L_2_S_Calibrated->Fill(Calibrated_L_2_S);
        Hist_L_3_S_Calibrated->Fill(Calibrated_L_3_S);
        Hist_L_4_S_Calibrated->Fill(Calibrated_L_4_S);

        // PID selection here
        // To find e+ : reject the events which doesn't make Cherenkov lights in Cherenkov counters
        // (heavier particles such as proton, pion etc... will not make Cherenkov light)
        // That is, veto the events with low PeakADC counts
        if( (PeakADC_C_counter_1 < Cut_C_counter_1) || (PeakADC_C_counter_2 < Cut_C_counter_2) ) continue;

        // Fill the histograms after the PID selection
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

        // Here we fill energy histograms after PID selection
        Hist_C_Energy_cut->Fill(Calibrated_C);
        Hist_S_Energy_cut->Fill(Calibrated_S);
        Hist_Sum_Energy_cut->Fill(Calibrated_C + Calibrated_S);

        Hist_3D_mid_C_Calibrated_cut->Fill(Calibrated_3D_mid_C);
        Hist_3D_W1_C_Calibrated_cut ->Fill(Calibrated_3D_W1_C);
        Hist_3D_W2_C_Calibrated_cut ->Fill(Calibrated_3D_W2_C);
        Hist_3D_W3_C_Calibrated_cut ->Fill(Calibrated_3D_W3_C);

        Hist_3D_mid_S_Calibrated_cut->Fill(Calibrated_3D_mid_S);
        Hist_3D_W1_S_Calibrated_cut ->Fill(Calibrated_3D_W1_S);
        Hist_3D_W2_S_Calibrated_cut ->Fill(Calibrated_3D_W2_S);
        Hist_3D_W3_S_Calibrated_cut ->Fill(Calibrated_3D_W3_S);

        Hist_HS_W_C_Calibrated_cut->Fill(Calibrated_HS_W_C);
        Hist_HS_1_C_Calibrated_cut->Fill(Calibrated_HS_1_C);
        Hist_HS_2_C_Calibrated_cut->Fill(Calibrated_HS_2_C);
        Hist_HS_3_C_Calibrated_cut->Fill(Calibrated_HS_3_C);

        Hist_HS_W_S_Calibrated_cut->Fill(Calibrated_HS_W_S);
        Hist_HS_1_S_Calibrated_cut->Fill(Calibrated_HS_1_S);
        Hist_HS_2_S_Calibrated_cut->Fill(Calibrated_HS_2_S);
        Hist_HS_3_S_Calibrated_cut->Fill(Calibrated_HS_3_S);
    
        Hist_L_1_C_Calibrated_cut->Fill(Calibrated_L_1_C);
        Hist_L_2_C_Calibrated_cut->Fill(Calibrated_L_2_C);
        Hist_L_3_C_Calibrated_cut->Fill(Calibrated_L_3_C);
        Hist_L_4_C_Calibrated_cut->Fill(Calibrated_L_4_C);

        Hist_L_1_S_Calibrated_cut->Fill(Calibrated_L_1_S);
        Hist_L_2_S_Calibrated_cut->Fill(Calibrated_L_2_S);
        Hist_L_3_S_Calibrated_cut->Fill(Calibrated_L_3_S);
        Hist_L_4_S_Calibrated_cut->Fill(Calibrated_L_4_S);
    }

    // Prepare output directory
    fs::path dir("./Calib");
    if ( !(fs::exists(dir)) ) fs::create_directory(dir);
    // Create output root file
    std::string outFile = "./Calib/Calib_Run_" + std::to_string(runNum) + ".root";
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

    Hist_3D_mid_C_Calibrated->Write();
    Hist_3D_W1_C_Calibrated ->Write();
    Hist_3D_W2_C_Calibrated ->Write();
    Hist_3D_W3_C_Calibrated ->Write();

    Hist_3D_mid_S_Calibrated->Write();
    Hist_3D_W1_S_Calibrated ->Write();
    Hist_3D_W2_S_Calibrated ->Write();
    Hist_3D_W3_S_Calibrated ->Write();

    Hist_HS_W_C_Calibrated->Write();
    Hist_HS_1_C_Calibrated->Write();
    Hist_HS_2_C_Calibrated->Write();
    Hist_HS_3_C_Calibrated->Write();

    Hist_HS_W_S_Calibrated->Write();
    Hist_HS_1_S_Calibrated->Write();
    Hist_HS_2_S_Calibrated->Write();
    Hist_HS_3_S_Calibrated->Write();

    Hist_L_1_C_Calibrated->Write();
    Hist_L_2_C_Calibrated->Write();
    Hist_L_3_C_Calibrated->Write();
    Hist_L_4_C_Calibrated->Write();

    Hist_L_1_S_Calibrated->Write();
    Hist_L_2_S_Calibrated->Write();
    Hist_L_3_S_Calibrated->Write();
    Hist_L_4_S_Calibrated->Write();

    Hist_C_Energy->Write();
    Hist_S_Energy->Write();
    Hist_Sum_Energy->Write();

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

    Hist_3D_mid_C_Calibrated_cut->Write();
    Hist_3D_W1_C_Calibrated_cut->Write();
    Hist_3D_W2_C_Calibrated_cut->Write();
    Hist_3D_W3_C_Calibrated_cut->Write();

    Hist_3D_mid_S_Calibrated_cut->Write();
    Hist_3D_W1_S_Calibrated_cut->Write();
    Hist_3D_W2_S_Calibrated_cut->Write();
    Hist_3D_W3_S_Calibrated_cut->Write();

    Hist_HS_W_C_Calibrated_cut->Write();
    Hist_HS_1_C_Calibrated_cut->Write();
    Hist_HS_2_C_Calibrated_cut->Write();
    Hist_HS_3_C_Calibrated_cut->Write();

    Hist_HS_W_S_Calibrated_cut->Write();
    Hist_HS_1_S_Calibrated_cut->Write();
    Hist_HS_2_S_Calibrated_cut->Write();
    Hist_HS_3_S_Calibrated_cut->Write();

    Hist_L_1_C_Calibrated_cut->Write();
    Hist_L_2_C_Calibrated_cut->Write();
    Hist_L_3_C_Calibrated_cut->Write();
    Hist_L_4_C_Calibrated_cut->Write();

    Hist_L_1_S_Calibrated_cut->Write();
    Hist_L_2_S_Calibrated_cut->Write();
    Hist_L_3_S_Calibrated_cut->Write();
    Hist_L_4_S_Calibrated_cut->Write();

    Hist_C_Energy_cut->Write();
    Hist_S_Energy_cut->Write();
    Hist_Sum_Energy_cut->Write();

    outputRoot->Close();
}
