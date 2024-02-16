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

// Run the script by
// ./TBanalysis_ex <run number> <max entry>
// For example, ./TBanalysis_ex 4234 -1
// <max entry> == -1 means run all the entries
// This example uses external pedestal

int main(int argc, char** argv) {
    gStyle->SetOptFit(1);

    int runNum = std::stoi(argv[1]);
    int maxEntry = std::stoi(argv[2]);

    // // Initial try on Equ. const (2023-Oct-18th)
    // float Equ_3D_C     = 0.0000786071;
    // float Equ_3D_mid_C = 0.0001133658;
    // float Equ_3D_W1_C  = 0.0004653327;
    // float Equ_3D_W2_C  = 0.0021822149;
    // float Equ_3D_W3_C  = 0.0018841262;
    // float Equ_HS_W_C   = 0.0000786071;
    // float Equ_HS_1_C   = 0.0000696088;
    // float Equ_HS_2_C   = 0.0000680052;
    // float Equ_HS_3_C   = 0.0000799504;
    // float Equ_L_1_C    = 0.0000951475;
    // float Equ_L_2_C    = 0.0005349739;
    // float Equ_L_3_C    = 0.0001070922;
    // float Equ_L_4_C    = 0.0001930968;

    // float Equ_3D_S     = 0.0000412490;
    // float Equ_3D_mid_S = 0.0000574853;
    // float Equ_3D_W1_S  = 0.0003013183;
    // float Equ_3D_W2_S  = 0.0005263851;
    // float Equ_3D_W3_S  = 0.0005937361;
    // float Equ_HS_W_S   = 0.0000476122;
    // float Equ_HS_1_S   = 0.0000415058;
    // float Equ_HS_2_S   = 0.0000438861;
    // float Equ_HS_3_S   = 0.0000457373;
    // float Equ_L_1_S    = 0.0000592575;
    // float Equ_L_2_S    = 0.0000344575;
    // float Equ_L_3_S    = 0.0000685084;
    // float Equ_L_4_S    = 0.0001009540;

    //  2024-Feb-06th Re-Calib integral result
    float Equ_3D_C     = 0.0000756001;
    float Equ_3D_mid_C = 0.0001183467;
    float Equ_3D_W1_C  = 0.0004967710;
    float Equ_3D_W2_C  = 0.0024096386;
    float Equ_3D_W3_C  = 0.0020714656;
    float Equ_HS_W_C   = 0.0000832293;
    float Equ_HS_1_C   = 0.0000725242;
    float Equ_HS_2_C   = 0.0000707126;
    float Equ_HS_3_C   = 0.0000800240;
    float Equ_L_1_C    = 0.0000963670;
    float Equ_L_2_C    = 0.0005427408;
    float Equ_L_3_C    = 0.0001085364;
    float Equ_L_4_C    = 0.0001991338;

    float Equ_3D_S     = 0.0000338404;
    float Equ_3D_mid_S = 0.0000575126;
    float Equ_3D_W1_S  = 0.0003144654;
    float Equ_3D_W2_S  = 0.0005885815;
    float Equ_3D_W3_S  = 0.0006098491;
    float Equ_HS_W_S   = 0.0000486446;
    float Equ_HS_1_S   = 0.0000420075;
    float Equ_HS_2_S   = 0.0000444069;
    float Equ_HS_3_S   = 0.0000454907;
    float Equ_L_1_S    = 0.0000584283;
    float Equ_L_2_S    = 0.0000356259;
    float Equ_L_3_S    = 0.0000666300;
    float Equ_L_4_S    = 0.0001013608;

    // Load mapping, pedestal info is not available for now, will be updated
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

    // Load pedestal
    TH2F* pedMap = (TH2F*) (TFile::Open(("/pnfs/knu.ac.kr/data/cms/store/user/sungwon/2023_DRC_TB_analysis/ped/Run_" + std::to_string(runNum) +"_pedestal.root").c_str()) )->Get("pedestal"); // By using pedestal map directly

    // Preparing histograms for ADC
    TH1F* Hist_C_counter_1_PeakADC = new TH1F("C_counter_1_PeakADC", "C_counter_1_PeakADC;PeakADC;Evt", 4096, 0, 4096);
    TH1F* Hist_C_counter_2_PeakADC = new TH1F("C_counter_2_PeakADC", "C_counter_2_PeakADC;PeakADC;Evt", 4096, 0, 4096);

    TH1F* Hist_C_IntADC   = new TH1F("C_response_IntADC", "C_response_IntADC;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_S_IntADC   = new TH1F("S_response_IntADC", "S_response_IntADC;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_Sum_IntADC = new TH1F("Sum_response_IntADC", "Sum_response_IntADC;IntADC;Evt", 2000, -10000, 400000);

    TH1F* Hist_3D_C_IntADC     = new TH1F("3D_C_IntADC",      "3D_C_IntADC;IntADC;Evt",     1000, -5000, 200000); // Add 3D MCP + Wings
    TH1F* Hist_3D_mid_C_IntADC = new TH1F("3D_sum_C_IntADC", "3D_sum_C_IntADC;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_C_IntADC  = new TH1F("3D_W1_C_IntADC",   "3D_W1_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_C_IntADC  = new TH1F("3D_W2_C_IntADC",   "3D_W2_C_IntADC;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_C_IntADC  = new TH1F("3D_W3_C_IntADC",   "3D_W3_C_IntADC;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_3D_S_IntADC     = new TH1F("3D_S_IntADC",     "3D_S_IntADC;IntADC;Evt",     1000, -5000, 200000); // Add 3D MCP + Wings
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

    TH1F* Hist_C_Equalized   = new TH1F("C_response_Equalized", "C_response_Equalized;GeV;Evt", 250, -5, 20); // Adding all (IntADC * Equ. Const.) including 3D Wings
    TH1F* Hist_S_Equalized   = new TH1F("S_response_Equalized", "S_response_Equalized;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Equalized = new TH1F("Sum_response_Equalized", "Sum_response_Equalized;GeV;Evt", 500, -10, 40);

    TH1F* Hist_C_Equalized_2   = new TH1F("C_response_Equalized_2", "C_response_Equalized_2;GeV;Evt", 250, -5, 20); // Regard 3D as single tower 3D response = (MCP + Wings) * 3D equ. const.
    TH1F* Hist_S_Equalized_2   = new TH1F("S_response_Equalized_2", "S_response_Equalized_2;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Equalized_2 = new TH1F("Sum_response_Equalized_2", "Sum_response_Equalized_2;GeV;Evt", 500, -10, 40);

    TH1F* Hist_3D_C_Equalized     = new TH1F("3D_C_Equalized", "3D_C_Equalized;GeV;Evt", 250, -5, 20); // Add 3D MCP + Wings IntADC and multiply its Equalization const
    TH1F* Hist_3D_mid_C_Equalized = new TH1F("3D_sum_C_Equalized", "3D_sum_C_Equalized;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_C_Equalized  = new TH1F("3D_W1_C_Equalized",   "3D_W1_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_C_Equalized  = new TH1F("3D_W2_C_Equalized",   "3D_W2_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_C_Equalized  = new TH1F("3D_W3_C_Equalized",   "3D_W3_C_Equalized;GeV;Evt",   250, -5, 20);

    TH1F* Hist_3D_S_Equalized     = new TH1F("3D_S_Equalized", "3D_S_Equalized;GeV;Evt", 250, -5, 20); // Add 3D MCP + Wings IntADC and multiply its Equalization const
    TH1F* Hist_3D_mid_S_Equalized = new TH1F("3D_sum_S_Equalized", "3D_sum_S_Equalized;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_S_Equalized  = new TH1F("3D_W1_S_Equalized",   "3D_W1_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_S_Equalized  = new TH1F("3D_W2_S_Equalized",   "3D_W2_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_S_Equalized  = new TH1F("3D_W3_S_Equalized",   "3D_W3_S_Equalized;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_C_Equalized  = new TH1F("HS_W_C_Equalized",   "HS_W_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_C_Equalized  = new TH1F("HS_1_C_Equalized",   "HS_1_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_C_Equalized  = new TH1F("HS_2_C_Equalized",   "HS_2_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_C_Equalized  = new TH1F("HS_3_C_Equalized",   "HS_3_C_Equalized;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_S_Equalized  = new TH1F("HS_W_S_Equalized",   "HS_W_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_S_Equalized  = new TH1F("HS_1_S_Equalized",   "HS_1_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_S_Equalized  = new TH1F("HS_2_S_Equalized",   "HS_2_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_S_Equalized  = new TH1F("HS_3_S_Equalized",   "HS_3_S_Equalized;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_C_Equalized  = new TH1F("L_1_C_Equalized",   "L_1_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_C_Equalized  = new TH1F("L_2_C_Equalized",   "L_2_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_C_Equalized  = new TH1F("L_3_C_Equalized",   "L_3_C_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_C_Equalized  = new TH1F("L_4_C_Equalized",   "L_4_C_Equalized;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_S_Equalized  = new TH1F("L_1_S_Equalized",   "L_1_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_S_Equalized  = new TH1F("L_2_S_Equalized",   "L_2_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_S_Equalized  = new TH1F("L_3_S_Equalized",   "L_3_S_Equalized;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_S_Equalized  = new TH1F("L_4_S_Equalized",   "L_4_S_Equalized;GeV;Evt",   250, -5, 20);
    // After cut
    TH1F* Hist_C_counter_1_PeakADC_cut = new TH1F("C_counter_1_PeakADC_cut", "C_counter_1_PeakADC_cut;PeakADC;Evt", 4096, 0, 4096);
    TH1F* Hist_C_counter_2_PeakADC_cut = new TH1F("C_counter_2_PeakADC_cut", "C_counter_2_PeakADC_cut;PeakADC;Evt", 4096, 0, 4096);

    TH1F* Hist_C_IntADC_cut   = new TH1F("C_response_IntADC_cut", "C_response_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_S_IntADC_cut   = new TH1F("S_response_IntADC_cut", "S_response_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_Sum_IntADC_cut = new TH1F("Sum_response_IntADC_cut", "Sum_response_IntADC_cut;IntADC;Evt", 2000, -10000, 400000);

    TH1F* Hist_3D_C_IntADC_cut = new TH1F("3D_C_IntADC_cut", "3D_C_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_mid_C_IntADC_cut = new TH1F("3D_sum_C_IntADC_cut", "3D_sum_C_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
    TH1F* Hist_3D_W1_C_IntADC_cut  = new TH1F("3D_W1_C_IntADC_cut",   "3D_W1_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W2_C_IntADC_cut  = new TH1F("3D_W2_C_IntADC_cut",   "3D_W2_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);
    TH1F* Hist_3D_W3_C_IntADC_cut  = new TH1F("3D_W3_C_IntADC_cut",   "3D_W3_C_IntADC_cut;IntADC;Evt",   1000, -5000, 200000);

    TH1F* Hist_3D_S_IntADC_cut = new TH1F("3D_S_IntADC_cut", "3D_S_IntADC_cut;IntADC;Evt", 1000, -5000, 200000);
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

    TH1F* Hist_C_Equalized_cut   = new TH1F("C_response_Equalized_cut", "C_response_Equalized_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_S_Equalized_cut   = new TH1F("S_response_Equalized_cut", "S_response_Equalized_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Equalized_cut = new TH1F("Sum_response_Equalized_cut", "Sum_response_Equalized_cut;GeV;Evt", 500, -10, 40);

    TH1F* Hist_C_Equalized_2_cut   = new TH1F("C_response_Equalized_2_cut", "C_response_Equalized_2_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_S_Equalized_2_cut   = new TH1F("S_response_Equalized_2_cut", "S_response_Equalized_2_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Equalized_2_cut = new TH1F("Sum_response_Equalized_2_cut", "Sum_response_Equalized_2_cut;GeV;Evt", 500, -10, 40);

    TH1F* Hist_3D_C_Equalized_cut     = new TH1F("3D_C_Equalized_cut", "3D_C_Equalized_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_mid_C_Equalized_cut = new TH1F("3D_sum_C_Equalized_cut", "3D_sum_C_Equalized_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_C_Equalized_cut  = new TH1F("3D_W1_C_Equalized_cut",   "3D_W1_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_C_Equalized_cut  = new TH1F("3D_W2_C_Equalized_cut",   "3D_W2_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_C_Equalized_cut  = new TH1F("3D_W3_C_Equalized_cut",   "3D_W3_C_Equalized_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_3D_S_Equalized_cut     = new TH1F("3D_S_Equalized_cut", "3D_S_Equalized_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_mid_S_Equalized_cut = new TH1F("3D_sum_S_Equalized_cut", "3D_sum_S_Equalized_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_S_Equalized_cut  = new TH1F("3D_W1_S_Equalized_cut",   "3D_W1_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_S_Equalized_cut  = new TH1F("3D_W2_S_Equalized_cut",   "3D_W2_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_S_Equalized_cut  = new TH1F("3D_W3_S_Equalized_cut",   "3D_W3_S_Equalized_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_C_Equalized_cut  = new TH1F("HS_W_C_Equalized_cut",   "HS_W_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_C_Equalized_cut  = new TH1F("HS_1_C_Equalized_cut",   "HS_1_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_C_Equalized_cut  = new TH1F("HS_2_C_Equalized_cut",   "HS_2_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_C_Equalized_cut  = new TH1F("HS_3_C_Equalized_cut",   "HS_3_C_Equalized_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_S_Equalized_cut  = new TH1F("HS_W_S_Equalized_cut",   "HS_W_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_S_Equalized_cut  = new TH1F("HS_1_S_Equalized_cut",   "HS_1_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_S_Equalized_cut  = new TH1F("HS_2_S_Equalized_cut",   "HS_2_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_S_Equalized_cut  = new TH1F("HS_3_S_Equalized_cut",   "HS_3_S_Equalized_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_C_Equalized_cut  = new TH1F("L_1_C_Equalized_cut",   "L_1_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_C_Equalized_cut  = new TH1F("L_2_C_Equalized_cut",   "L_2_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_C_Equalized_cut  = new TH1F("L_3_C_Equalized_cut",   "L_3_C_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_C_Equalized_cut  = new TH1F("L_4_C_Equalized_cut",   "L_4_C_Equalized_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_S_Equalized_cut  = new TH1F("L_1_S_Equalized_cut",   "L_1_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_S_Equalized_cut  = new TH1F("L_2_S_Equalized_cut",   "L_2_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_S_Equalized_cut  = new TH1F("L_3_S_Equalized_cut",   "L_3_S_Equalized_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_S_Equalized_cut  = new TH1F("L_4_S_Equalized_cut",   "L_4_S_Equalized_cut;GeV;Evt",   250, -5, 20);

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

    // C counter cut : 50 Peak ADC
    float Cut_C_counter_1 = 100.;
    float Cut_C_counter_2 = 80.;
    // Evt Loop start
    for (int iEvt = 0; iEvt < totalEntry; iEvt++) {
        printProgress(iEvt + 1, totalEntry); // Print progress bar
        evtChain->GetEntry(iEvt); // Get event

        // TBwaveform
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

        // Waveform vector
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
        
        // Fill Histo
        float PeakADC_C_counter_1 = GetPeakWithPed(Wave_C_counter.at(0), 390, 660, Ped_C_counter.at(0));
        float PeakADC_C_counter_2 = GetPeakWithPed(Wave_C_counter.at(1), 230, 450, Ped_C_counter.at(1));
                
        // 2024-Feb-06th Re-Calib integral result
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

        float IntADC_C = IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C + IntADC_HS_W_C + IntADC_HS_1_C + IntADC_HS_2_C + IntADC_HS_3_C + IntADC_L_1_C + IntADC_L_2_C + IntADC_L_3_C + IntADC_L_4_C;
        float IntADC_S = IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S + IntADC_HS_W_S + IntADC_HS_1_S + IntADC_HS_2_S + IntADC_HS_3_S + IntADC_L_1_S + IntADC_L_2_S + IntADC_L_3_S + IntADC_L_4_S;

        float Equalized_3D_C = (IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C) * Equ_3D_C;
        float Equalized_3D_mid_C = IntADC_3D_mid_C * Equ_3D_mid_C;
        float Equalized_3D_W1_C  = IntADC_3D_W1_C  * Equ_3D_W1_C;
        float Equalized_3D_W2_C  = IntADC_3D_W2_C  * Equ_3D_W2_C;
        float Equalized_3D_W3_C  = IntADC_3D_W3_C  * Equ_3D_W3_C;

        float Equalized_HS_W_C  = IntADC_HS_W_C  * Equ_HS_W_C;
        float Equalized_HS_1_C  = IntADC_HS_1_C  * Equ_HS_1_C;
        float Equalized_HS_2_C  = IntADC_HS_2_C  * Equ_HS_2_C;
        float Equalized_HS_3_C  = IntADC_HS_3_C  * Equ_HS_3_C;
        
        float Equalized_L_1_C  = IntADC_L_1_C  * Equ_L_1_C;
        float Equalized_L_2_C  = IntADC_L_2_C  * Equ_L_2_C;
        float Equalized_L_3_C  = IntADC_L_3_C  * Equ_L_3_C;
        float Equalized_L_4_C  = IntADC_L_4_C  * Equ_L_4_C;

        float Equalized_3D_S = (IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S) * Equ_3D_S;
        float Equalized_3D_mid_S = IntADC_3D_mid_S * Equ_3D_mid_S;
        float Equalized_3D_W1_S  = IntADC_3D_W1_S  * Equ_3D_W1_S;
        float Equalized_3D_W2_S  = IntADC_3D_W2_S  * Equ_3D_W2_S;
        float Equalized_3D_W3_S  = IntADC_3D_W3_S  * Equ_3D_W3_S;

        float Equalized_HS_W_S  = IntADC_HS_W_S  * Equ_HS_W_S;
        float Equalized_HS_1_S  = IntADC_HS_1_S  * Equ_HS_1_S;
        float Equalized_HS_2_S  = IntADC_HS_2_S  * Equ_HS_2_S;
        float Equalized_HS_3_S  = IntADC_HS_3_S  * Equ_HS_3_S;
        
        float Equalized_L_1_S  = IntADC_L_1_S  * Equ_L_1_S;
        float Equalized_L_2_S  = IntADC_L_2_S  * Equ_L_2_S;
        float Equalized_L_3_S  = IntADC_L_3_S  * Equ_L_3_S;
        float Equalized_L_4_S  = IntADC_L_4_S  * Equ_L_4_S;

        float Equalized_C = Equalized_3D_mid_C + Equalized_3D_W1_C + Equalized_3D_W2_C + Equalized_3D_W3_C + Equalized_HS_W_C + Equalized_HS_1_C + Equalized_HS_2_C + Equalized_HS_3_C + Equalized_L_1_C + Equalized_L_2_C + Equalized_L_3_C + Equalized_L_4_C;
        float Equalized_S = Equalized_3D_mid_S + Equalized_3D_W1_S + Equalized_3D_W2_S + Equalized_3D_W3_S + Equalized_HS_W_S + Equalized_HS_1_S + Equalized_HS_2_S + Equalized_HS_3_S + Equalized_L_1_S + Equalized_L_2_S + Equalized_L_3_S + Equalized_L_4_S;

        float Equalized_C_2 = Equalized_3D_C + Equalized_HS_W_C + Equalized_HS_1_C + Equalized_HS_2_C + Equalized_HS_3_C + Equalized_L_1_C + Equalized_L_2_C + Equalized_L_3_C + Equalized_L_4_C;
        float Equalized_S_2 = Equalized_3D_S + Equalized_HS_W_S + Equalized_HS_1_S + Equalized_HS_2_S + Equalized_HS_3_S + Equalized_L_1_S + Equalized_L_2_S + Equalized_L_3_S + Equalized_L_4_S;

        Hist_C_counter_1_PeakADC->Fill(PeakADC_C_counter_1);
        Hist_C_counter_2_PeakADC->Fill(PeakADC_C_counter_2);

        Hist_C_IntADC->Fill(IntADC_C);
        Hist_S_IntADC->Fill(IntADC_S);
        Hist_Sum_IntADC->Fill(IntADC_C + IntADC_S);

        Hist_3D_C_IntADC->Fill(IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C);
        Hist_3D_mid_C_IntADC->Fill(IntADC_3D_mid_C);
        Hist_3D_W1_C_IntADC ->Fill(IntADC_3D_W1_C);
        Hist_3D_W2_C_IntADC ->Fill(IntADC_3D_W2_C);
        Hist_3D_W3_C_IntADC ->Fill(IntADC_3D_W3_C);

        Hist_3D_S_IntADC->Fill(IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S);
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

        Hist_C_Equalized->Fill(Equalized_C);
        Hist_S_Equalized->Fill(Equalized_S);
        Hist_Sum_Equalized->Fill(Equalized_C + Equalized_S);

        Hist_C_Equalized_2->Fill(Equalized_C_2);
        Hist_S_Equalized_2->Fill(Equalized_S_2);
        Hist_Sum_Equalized_2->Fill(Equalized_C_2 + Equalized_S_2);
        
        Hist_3D_C_Equalized->Fill( (IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C) * Equ_3D_C );
        Hist_3D_mid_C_Equalized->Fill(Equalized_3D_mid_C);
        Hist_3D_W1_C_Equalized ->Fill(Equalized_3D_W1_C);
        Hist_3D_W2_C_Equalized ->Fill(Equalized_3D_W2_C);
        Hist_3D_W3_C_Equalized ->Fill(Equalized_3D_W3_C);

        Hist_3D_S_Equalized->Fill( (IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S) * Equ_3D_S );
        Hist_3D_mid_S_Equalized->Fill(Equalized_3D_mid_S);
        Hist_3D_W1_S_Equalized ->Fill(Equalized_3D_W1_S);
        Hist_3D_W2_S_Equalized ->Fill(Equalized_3D_W2_S);
        Hist_3D_W3_S_Equalized ->Fill(Equalized_3D_W3_S);

        Hist_HS_W_C_Equalized->Fill(Equalized_HS_W_C);
        Hist_HS_1_C_Equalized->Fill(Equalized_HS_1_C);
        Hist_HS_2_C_Equalized->Fill(Equalized_HS_2_C);
        Hist_HS_3_C_Equalized->Fill(Equalized_HS_3_C);

        Hist_HS_W_S_Equalized->Fill(Equalized_HS_W_S);
        Hist_HS_1_S_Equalized->Fill(Equalized_HS_1_S);
        Hist_HS_2_S_Equalized->Fill(Equalized_HS_2_S);
        Hist_HS_3_S_Equalized->Fill(Equalized_HS_3_S);
    
        Hist_L_1_C_Equalized->Fill(Equalized_L_1_C);
        Hist_L_2_C_Equalized->Fill(Equalized_L_2_C);
        Hist_L_3_C_Equalized->Fill(Equalized_L_3_C);
        Hist_L_4_C_Equalized->Fill(Equalized_L_4_C);

        Hist_L_1_S_Equalized->Fill(Equalized_L_1_S);
        Hist_L_2_S_Equalized->Fill(Equalized_L_2_S);
        Hist_L_3_S_Equalized->Fill(Equalized_L_3_S);
        Hist_L_4_S_Equalized->Fill(Equalized_L_4_S);

        if( (PeakADC_C_counter_1 < Cut_C_counter_1) || (PeakADC_C_counter_2 < Cut_C_counter_2) ) continue;

        Hist_C_counter_1_PeakADC_cut->Fill(PeakADC_C_counter_1);
        Hist_C_counter_2_PeakADC_cut->Fill(PeakADC_C_counter_2);

        Hist_C_IntADC_cut->Fill(IntADC_C);
        Hist_S_IntADC_cut->Fill(IntADC_S);
        Hist_Sum_IntADC_cut->Fill(IntADC_C + IntADC_S);

        Hist_3D_C_IntADC_cut->Fill(IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C);
        Hist_3D_mid_C_IntADC_cut->Fill(IntADC_3D_mid_C);
        Hist_3D_W1_C_IntADC_cut ->Fill(IntADC_3D_W1_C);
        Hist_3D_W2_C_IntADC_cut ->Fill(IntADC_3D_W2_C);
        Hist_3D_W3_C_IntADC_cut ->Fill(IntADC_3D_W3_C);

        Hist_3D_S_IntADC_cut->Fill(IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S);
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

        Hist_C_Equalized_cut->Fill(Equalized_C);
        Hist_S_Equalized_cut->Fill(Equalized_S);
        Hist_Sum_Equalized_cut->Fill(Equalized_C + Equalized_S);

        Hist_C_Equalized_2_cut->Fill(Equalized_C_2);
        Hist_S_Equalized_2_cut->Fill(Equalized_S_2);
        Hist_Sum_Equalized_2_cut->Fill(Equalized_C_2 + Equalized_S_2);

        Hist_3D_C_Equalized_cut->Fill( (IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C) * Equ_3D_C );
        Hist_3D_mid_C_Equalized_cut->Fill(Equalized_3D_mid_C);
        Hist_3D_W1_C_Equalized_cut ->Fill(Equalized_3D_W1_C);
        Hist_3D_W2_C_Equalized_cut ->Fill(Equalized_3D_W2_C);
        Hist_3D_W3_C_Equalized_cut ->Fill(Equalized_3D_W3_C);

        Hist_3D_S_Equalized_cut->Fill( (IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S) * Equ_3D_S );
        Hist_3D_mid_S_Equalized_cut->Fill(Equalized_3D_mid_S);
        Hist_3D_W1_S_Equalized_cut ->Fill(Equalized_3D_W1_S);
        Hist_3D_W2_S_Equalized_cut ->Fill(Equalized_3D_W2_S);
        Hist_3D_W3_S_Equalized_cut ->Fill(Equalized_3D_W3_S);

        Hist_HS_W_C_Equalized_cut->Fill(Equalized_HS_W_C);
        Hist_HS_1_C_Equalized_cut->Fill(Equalized_HS_1_C);
        Hist_HS_2_C_Equalized_cut->Fill(Equalized_HS_2_C);
        Hist_HS_3_C_Equalized_cut->Fill(Equalized_HS_3_C);

        Hist_HS_W_S_Equalized_cut->Fill(Equalized_HS_W_S);
        Hist_HS_1_S_Equalized_cut->Fill(Equalized_HS_1_S);
        Hist_HS_2_S_Equalized_cut->Fill(Equalized_HS_2_S);
        Hist_HS_3_S_Equalized_cut->Fill(Equalized_HS_3_S);
    
        Hist_L_1_C_Equalized_cut->Fill(Equalized_L_1_C);
        Hist_L_2_C_Equalized_cut->Fill(Equalized_L_2_C);
        Hist_L_3_C_Equalized_cut->Fill(Equalized_L_3_C);
        Hist_L_4_C_Equalized_cut->Fill(Equalized_L_4_C);

        Hist_L_1_S_Equalized_cut->Fill(Equalized_L_1_S);
        Hist_L_2_S_Equalized_cut->Fill(Equalized_L_2_S);
        Hist_L_3_S_Equalized_cut->Fill(Equalized_L_3_S);
        Hist_L_4_S_Equalized_cut->Fill(Equalized_L_4_S);
    }

    // Save the outputs
    std::string outFile = "./ScaleFactor/ScaleFactor_Run_" + std::to_string(runNum) + "_24Feb06ReCalib.root";
    TFile* outputRoot = new TFile(outFile.c_str(), "RECREATE");
    outputRoot->cd();

    // Write histogram before cut
    Hist_C_counter_1_PeakADC->Write();
    Hist_C_counter_2_PeakADC->Write();

    Hist_3D_C_IntADC->Write();
    Hist_3D_mid_C_IntADC->Write();
    Hist_3D_W1_C_IntADC ->Write();
    Hist_3D_W2_C_IntADC ->Write();
    Hist_3D_W3_C_IntADC ->Write();

    Hist_3D_S_IntADC->Write();
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

    Hist_C_IntADC->Write();
    Hist_S_IntADC->Write();
    Hist_Sum_IntADC->Write();

    Hist_3D_C_Equalized->Write();
    Hist_3D_mid_C_Equalized->Write();
    Hist_3D_W1_C_Equalized ->Write();
    Hist_3D_W2_C_Equalized ->Write();
    Hist_3D_W3_C_Equalized ->Write();

    Hist_3D_S_Equalized->Write();
    Hist_3D_mid_S_Equalized->Write();
    Hist_3D_W1_S_Equalized ->Write();
    Hist_3D_W2_S_Equalized ->Write();
    Hist_3D_W3_S_Equalized ->Write();

    Hist_HS_W_C_Equalized->Write();
    Hist_HS_1_C_Equalized->Write();
    Hist_HS_2_C_Equalized->Write();
    Hist_HS_3_C_Equalized->Write();

    Hist_HS_W_S_Equalized->Write();
    Hist_HS_1_S_Equalized->Write();
    Hist_HS_2_S_Equalized->Write();
    Hist_HS_3_S_Equalized->Write();

    Hist_L_1_C_Equalized->Write();
    Hist_L_2_C_Equalized->Write();
    Hist_L_3_C_Equalized->Write();
    Hist_L_4_C_Equalized->Write();

    Hist_L_1_S_Equalized->Write();
    Hist_L_2_S_Equalized->Write();
    Hist_L_3_S_Equalized->Write();
    Hist_L_4_S_Equalized->Write();

    Hist_C_Equalized->Write();
    Hist_S_Equalized->Write();
    Hist_Sum_Equalized->Write();

    Hist_C_Equalized_2->Write();
    Hist_S_Equalized_2->Write();
    Hist_Sum_Equalized_2->Write();

    // Write histogram after cut
    Hist_C_counter_1_PeakADC_cut->Write();
    Hist_C_counter_2_PeakADC_cut->Write();

    Hist_3D_C_IntADC_cut->Write();
    Hist_3D_mid_C_IntADC_cut->Write();
    Hist_3D_W1_C_IntADC_cut->Write();
    Hist_3D_W2_C_IntADC_cut->Write();
    Hist_3D_W3_C_IntADC_cut->Write();

    Hist_3D_S_IntADC_cut->Write();
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

    Hist_C_IntADC_cut->Write();
    Hist_S_IntADC_cut->Write();
    Hist_Sum_IntADC_cut->Write();

    Hist_3D_C_Equalized_cut->Write();
    Hist_3D_mid_C_Equalized_cut->Write();
    Hist_3D_W1_C_Equalized_cut->Write();
    Hist_3D_W2_C_Equalized_cut->Write();
    Hist_3D_W3_C_Equalized_cut->Write();

    Hist_3D_S_Equalized_cut->Write();
    Hist_3D_mid_S_Equalized_cut->Write();
    Hist_3D_W1_S_Equalized_cut->Write();
    Hist_3D_W2_S_Equalized_cut->Write();
    Hist_3D_W3_S_Equalized_cut->Write();

    Hist_HS_W_C_Equalized_cut->Write();
    Hist_HS_1_C_Equalized_cut->Write();
    Hist_HS_2_C_Equalized_cut->Write();
    Hist_HS_3_C_Equalized_cut->Write();

    Hist_HS_W_S_Equalized_cut->Write();
    Hist_HS_1_S_Equalized_cut->Write();
    Hist_HS_2_S_Equalized_cut->Write();
    Hist_HS_3_S_Equalized_cut->Write();

    Hist_L_1_C_Equalized_cut->Write();
    Hist_L_2_C_Equalized_cut->Write();
    Hist_L_3_C_Equalized_cut->Write();
    Hist_L_4_C_Equalized_cut->Write();

    Hist_L_1_S_Equalized_cut->Write();
    Hist_L_2_S_Equalized_cut->Write();
    Hist_L_3_S_Equalized_cut->Write();
    Hist_L_4_S_Equalized_cut->Write();

    Hist_C_Equalized_cut->Write();
    Hist_S_Equalized_cut->Write();
    Hist_Sum_Equalized_cut->Write();

    Hist_C_Equalized_2_cut->Write();
    Hist_S_Equalized_2_cut->Write();
    Hist_Sum_Equalized_2_cut->Write();

    outputRoot->Close();
}
