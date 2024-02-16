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

    // Initial try on Equ. const (2023-Oct-18th)
    // Try 01
    // float Calib_3D_C     = 0.0000641164;
    // float Calib_3D_mid_C = 0.0000835053;
    // float Calib_3D_W1_C  = 0.0000064216;
    // float Calib_3D_W2_C  = 0.0000178942;
    // float Calib_3D_W3_C  = 0.0000154498;
    // float Calib_HS_W_C   = 0.0000645679;
    // float Calib_HS_1_C   = 0.0000573298;
    // float Calib_HS_2_C   = 0.0000559819;
    // float Calib_HS_3_C   = 0.0000626012;
    // float Calib_L_1_C    = 0.0000677450;
    // float Calib_L_2_C    = 0.0003815969;
    // float Calib_L_3_C    = 0.0000724586;
    // float Calib_L_4_C    = 0.0001315762;

    // float Calib_3D_S     = 0.0000316297;
    // float Calib_3D_mid_S = 0.0000423437;
    // float Calib_3D_W1_S  = 0.0000041582;
    // float Calib_3D_W2_S  = 0.0000043164;
    // float Calib_3D_W3_S  = 0.0000048686;
    // float Calib_HS_W_S   = 0.0000391087;
    // float Calib_HS_1_S   = 0.0000341842;
    // float Calib_HS_2_S   = 0.0000361271;
    // float Calib_HS_3_S   = 0.0000358123;
    // float Calib_L_1_S    = 0.0000421913;
    // float Calib_L_2_S    = 0.0000245785;
    // float Calib_L_3_S    = 0.0000463528;
    // float Calib_L_4_S    = 0.0000687901;

    // Try02
    // float Calib_3D_C     = 0.0000679020;
    // float Calib_3D_mid_C = 0.0000877270;
    // float Calib_3D_W1_C  = 0.0000066562;
    // float Calib_3D_W2_C  = 0.0000195006;
    // float Calib_3D_W3_C  = 0.0000155819;
    // float Calib_HS_W_C   = 0.0000683731;
    // float Calib_HS_1_C   = 0.0000581156;
    // float Calib_HS_2_C   = 0.0000567910;
    // float Calib_HS_3_C   = 0.0000621084;
    // float Calib_L_1_C    = 0.0000688122;
    // float Calib_L_2_C    = 0.0003758166;
    // float Calib_L_3_C    = 0.0000731954;
    // float Calib_L_4_C    = 0.0001290469;

    // float Calib_3D_S     = 0.0000321260;
    // float Calib_3D_mid_S = 0.0000422702;
    // float Calib_3D_W1_S  = 0.0000042383;
    // float Calib_3D_W2_S  = 0.0000045148;
    // float Calib_3D_W3_S  = 0.0000049629;
    // float Calib_HS_W_S   = 0.0000398390;
    // float Calib_HS_1_S   = 0.0000348551;
    // float Calib_HS_2_S   = 0.0000369434;
    // float Calib_HS_3_S   = 0.0000356663;
    // float Calib_L_1_S    = 0.0000423230;
    // float Calib_L_2_S    = 0.0000255801;
    // float Calib_L_3_S    = 0.0000455753;
    // float Calib_L_4_S    = 0.0000705785;

    // Try03
    // float Calib_3D_C     = 1;
    // float Calib_3D_mid_C = 0.0000798050;
    // float Calib_3D_W1_C  = 0.0000062120;
    // float Calib_3D_W2_C  = 0.0000176249;
    // float Calib_3D_W3_C  = 0.0000134096;
    // float Calib_HS_W_C   = 0.0000648303;
    // float Calib_HS_1_C   = 0.0000572889;
    // float Calib_HS_2_C   = 0.0000558017;
    // float Calib_HS_3_C   = 0.0000598784;
    // float Calib_L_1_C    = 0.0000665203;
    // float Calib_L_2_C    = 0.0003648127;
    // float Calib_L_3_C    = 0.0000705987;
    // float Calib_L_4_C    = 0.0001265543;

    // float Calib_3D_S     = 1;
    // float Calib_3D_mid_S = 0.0000407976;
    // float Calib_3D_W1_S  = 0.0000040741;
    // float Calib_3D_W2_S  = 0.0000041890;
    // float Calib_3D_W3_S  = 0.0000044384;
    // float Calib_HS_W_S   = 0.0000386123;
    // float Calib_HS_1_S   = 0.0000321364;
    // float Calib_HS_2_S   = 0.0000340141;
    // float Calib_HS_3_S   = 0.0000332650;
    // float Calib_L_1_S    = 0.0000387135;
    // float Calib_L_2_S    = 0.0000228340;
    // float Calib_L_3_S    = 0.0000433121;
    // float Calib_L_4_S    = 0.0000649989;

    // // Try04
    // float Calib_3D_C     = 0.0000605245;
    // float Calib_3D_mid_C = 0.0000790502;
    // float Calib_3D_W1_C  = 0.0000057960;
    // float Calib_3D_W2_C  = 0.0000085102;
    // float Calib_3D_W3_C  = 0.0000072414;
    // float Calib_HS_1_C   = 0.0000649834;
    // float Calib_HS_W_C   = 0.0000573900;
    // float Calib_HS_2_C   = 0.0000560097;
    // float Calib_HS_3_C   = 0.0000598268;
    // float Calib_L_1_C    = 0.0000676033;
    // float Calib_L_2_C    = 0.0003962618;
    // float Calib_L_3_C    = 0.0000710030;
    // float Calib_L_4_C    = 0.0001351508;

    // float Calib_3D_S     = 0.0000304815;
    // float Calib_3D_mid_S = 0.0000416411;
    // float Calib_3D_W1_S  = 0.0000042019;
    // float Calib_3D_W2_S  = 0.0000039131;
    // float Calib_3D_W3_S  = 0.0000041259;
    // float Calib_HS_W_S   = 0.0000392981;
    // float Calib_HS_1_S   = 0.0000342780;
    // float Calib_HS_2_S   = 0.0000360018;
    // float Calib_HS_3_S   = 0.0000346124;
    // float Calib_L_1_S    = 0.0000419087;
    // float Calib_L_2_S    = 0.0000308894;
    // float Calib_L_3_S    = 0.0000446008;
    // float Calib_L_4_S    = 0.0000687108;

    // Try05
    // float Calib_3D_C     = 0.0000670690;
    // float Calib_3D_mid_C = 0.0000876149;
    // float Calib_3D_W1_C  = 0.0000066029;
    // float Calib_3D_W2_C  = 0.0000199635;
    // float Calib_3D_W3_C  = 0.0000155894;
    // float Calib_HS_W_C   = 0.0000680347;
    // float Calib_HS_1_C   = 0.0000580910;
    // float Calib_HS_2_C   = 0.0000566386;
    // float Calib_HS_3_C   = 0.0000612484;
    // float Calib_L_1_C    = 0.0000667307;
    // float Calib_L_2_C    = 0.0003648127;
    // float Calib_L_3_C    = 0.0000713487;
    // float Calib_L_4_C    = 0.0001265543;

    // float Calib_3D_S     = 0.0000319407;
    // float Calib_3D_mid_S = 0.0000425129;
    // float Calib_3D_W1_S  = 0.0000042273;
    // float Calib_3D_W2_S  = 0.0000045455;
    // float Calib_3D_W3_S  = 0.0000049450;
    // float Calib_HS_W_S   = 0.0000398486;
    // float Calib_HS_1_S   = 0.0000349984;
    // float Calib_HS_2_S   = 0.0000368850;
    // float Calib_HS_3_S   = 0.0000341556;
    // float Calib_L_1_S    = 0.0000392822;
    // float Calib_L_2_S    = 0.0000230948;
    // float Calib_L_3_S    = 0.0000440861;
    // float Calib_L_4_S    = 0.0000651652;

    //  2024-Feb-06th Re-Calib integral result
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

    TH1F* Hist_C_Energy   = new TH1F("C_response_Energy", "C_response_Energy;GeV;Evt", 250, -5, 20); // Adding all (IntADC * Equ. Const.) including 3D Wings
    TH1F* Hist_S_Energy   = new TH1F("S_response_Energy", "S_response_Energy;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Energy = new TH1F("Sum_response_Energy", "Sum_response_Energy;GeV;Evt", 500, -10, 40);

    TH1F* Hist_C_Energy_2   = new TH1F("C_response_Energy_2", "C_response_Energy_2;GeV;Evt", 250, -5, 20); // For 3D, use (3D + Wings) * Calib.Const and regard 3D as single tower
    TH1F* Hist_S_Energy_2   = new TH1F("S_response_Energy_2", "S_response_Energy_2;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Energy_2 = new TH1F("Sum_response_Energy_2", "Sum_response_Energy_2;GeV;Evt", 500, -10, 40);

    // TH1F* Hist_3D_C_Calibrated     = new TH1F("3D_C_Calibrated", "3D_C_Calibrated;GeV;Evt", 250, -5, 20); // Add 3D MCP + Wings IntADC and multiply its Equalization const
    TH1F* Hist_3D_mid_C_Calibrated = new TH1F("3D_sum_C_Calibrated", "3D_sum_C_Calibrated;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_C_Calibrated  = new TH1F("3D_W1_C_Calibrated",   "3D_W1_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_C_Calibrated  = new TH1F("3D_W2_C_Calibrated",   "3D_W2_C_Calibrated;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_C_Calibrated  = new TH1F("3D_W3_C_Calibrated",   "3D_W3_C_Calibrated;GeV;Evt",   250, -5, 20);

    // TH1F* Hist_3D_S_Calibrated     = new TH1F("3D_S_Calibrated", "3D_S_Calibrated;GeV;Evt", 250, -5, 20); // Add 3D MCP + Wings IntADC and multiply its Equalization const
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

    TH1F* Hist_C_Energy_cut   = new TH1F("C_response_Energy_cut", "C_response_Energy_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_S_Energy_cut   = new TH1F("S_response_Energy_cut", "S_response_Energy_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Energy_cut = new TH1F("Sum_response_Energy_cut", "Sum_response_Energy_cut;GeV;Evt", 500, -10, 40);

    TH1F* Hist_C_Energy_2_cut   = new TH1F("C_response_Energy_2_cut", "C_response_Energy_2_cut;GeV;Evt", 250, -5, 20); // For 3D, use (3D + Wings) * Calib.Const and regard 3D as single tower
    TH1F* Hist_S_Energy_2_cut   = new TH1F("S_response_Energy_2_cut", "S_response_Energy_2_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_Energy_2_cut = new TH1F("Sum_response_Energy_2_cut", "Sum_response_Energy_2_cut;GeV;Evt", 500, -10, 40);

    // TH1F* Hist_3D_C_Calibrated_cut     = new TH1F("3D_C_Calibrated_cut", "3D_C_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_mid_C_Calibrated_cut = new TH1F("3D_sum_C_Calibrated_cut", "3D_sum_C_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_C_Calibrated_cut  = new TH1F("3D_W1_C_Calibrated_cut",   "3D_W1_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_C_Calibrated_cut  = new TH1F("3D_W2_C_Calibrated_cut",   "3D_W2_C_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_C_Calibrated_cut  = new TH1F("3D_W3_C_Calibrated_cut",   "3D_W3_C_Calibrated_cut;GeV;Evt",   250, -5, 20);

    // TH1F* Hist_3D_S_Calibrated_cut     = new TH1F("3D_S_Calibrated_cut", "3D_S_Calibrated_cut;GeV;Evt", 250, -5, 20);
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

    // For investigating high E tail problem...
    TH1F* Hist_C_High_Energy_cut   = new TH1F("C_response_High_Energy_cut", "C_response_High_Energy_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_S_High_Energy_cut   = new TH1F("S_response_High_Energy_cut", "S_response_High_Energy_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_Sum_High_Energy_cut = new TH1F("Sum_response_High_Energy_cut", "Sum_response_High_Energy_cut;GeV;Evt", 500, -10, 40);

    TH1F* Hist_3D_C_High_Calibrated_cut     = new TH1F("3D_C_High_Calibrated_cut", "3D_C_High_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_mid_C_High_Calibrated_cut = new TH1F("3D_sum_C_High_Calibrated_cut", "3D_sum_C_High_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_C_High_Calibrated_cut  = new TH1F("3D_W1_C_High_Calibrated_cut",   "3D_W1_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_C_High_Calibrated_cut  = new TH1F("3D_W2_C_High_Calibrated_cut",   "3D_W2_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_C_High_Calibrated_cut  = new TH1F("3D_W3_C_High_Calibrated_cut",   "3D_W3_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_3D_S_High_Calibrated_cut     = new TH1F("3D_S_High_Calibrated_cut", "3D_S_High_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_mid_S_High_Calibrated_cut = new TH1F("3D_sum_S_High_Calibrated_cut", "3D_sum_S_High_Calibrated_cut;GeV;Evt", 250, -5, 20);
    TH1F* Hist_3D_W1_S_High_Calibrated_cut  = new TH1F("3D_W1_S_High_Calibrated_cut",   "3D_W1_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W2_S_High_Calibrated_cut  = new TH1F("3D_W2_S_High_Calibrated_cut",   "3D_W2_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_3D_W3_S_High_Calibrated_cut  = new TH1F("3D_W3_S_High_Calibrated_cut",   "3D_W3_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_C_High_Calibrated_cut  = new TH1F("HS_W_C_High_Calibrated_cut",   "HS_W_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_C_High_Calibrated_cut  = new TH1F("HS_1_C_High_Calibrated_cut",   "HS_1_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_C_High_Calibrated_cut  = new TH1F("HS_2_C_High_Calibrated_cut",   "HS_2_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_C_High_Calibrated_cut  = new TH1F("HS_3_C_High_Calibrated_cut",   "HS_3_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_HS_W_S_High_Calibrated_cut  = new TH1F("HS_W_S_High_Calibrated_cut",   "HS_W_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_1_S_High_Calibrated_cut  = new TH1F("HS_1_S_High_Calibrated_cut",   "HS_1_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_2_S_High_Calibrated_cut  = new TH1F("HS_2_S_High_Calibrated_cut",   "HS_2_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_HS_3_S_High_Calibrated_cut  = new TH1F("HS_3_S_High_Calibrated_cut",   "HS_3_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_C_High_Calibrated_cut  = new TH1F("L_1_C_High_Calibrated_cut",   "L_1_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_C_High_Calibrated_cut  = new TH1F("L_2_C_High_Calibrated_cut",   "L_2_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_C_High_Calibrated_cut  = new TH1F("L_3_C_High_Calibrated_cut",   "L_3_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_C_High_Calibrated_cut  = new TH1F("L_4_C_High_Calibrated_cut",   "L_4_C_High_Calibrated_cut;GeV;Evt",   250, -5, 20);

    TH1F* Hist_L_1_S_High_Calibrated_cut  = new TH1F("L_1_S_High_Calibrated_cut",   "L_1_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_2_S_High_Calibrated_cut  = new TH1F("L_2_S_High_Calibrated_cut",   "L_2_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_3_S_High_Calibrated_cut  = new TH1F("L_3_S_High_Calibrated_cut",   "L_3_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);
    TH1F* Hist_L_4_S_High_Calibrated_cut  = new TH1F("L_4_S_High_Calibrated_cut",   "L_4_S_High_Calibrated_cut;GeV;Evt",   250, -5, 20);

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

    // C counter cut : 100 Peak ADC
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
        // Try01
        // float IntADC_3D_mid_C = GetIntWithPed(Wave_3D_C.at(0), 120, 300, Ped_3D_C.at(0));
        // float IntADC_3D_W1_C  = GetIntWithPed(Wave_3D_C.at(1), 120, 300, Ped_3D_C.at(1));
        // float IntADC_3D_W2_C  = GetIntWithPed(Wave_3D_C.at(2), 140, 300, Ped_3D_C.at(2));
        // float IntADC_3D_W3_C  = GetIntWithPed(Wave_3D_C.at(3), 130, 260, Ped_3D_C.at(3));

        // float IntADC_3D_mid_S = GetIntWithPed(Wave_3D_S.at(0), 140, 340, Ped_3D_S.at(0));
        // float IntADC_3D_W1_S  = GetIntWithPed(Wave_3D_S.at(1), 140, 340, Ped_3D_S.at(1));
        // float IntADC_3D_W2_S  = GetIntWithPed(Wave_3D_S.at(2), 150, 330, Ped_3D_S.at(2));
        // float IntADC_3D_W3_S  = GetIntWithPed(Wave_3D_S.at(3), 140, 310, Ped_3D_S.at(3));

        // float IntADC_HS_W_C  = GetIntWithPed(Wave_HeatSink_C.at(0), 120, 350, Ped_HeatSink_C.at(0));
        // float IntADC_HS_1_C  = GetIntWithPed(Wave_HeatSink_C.at(1), 130, 350, Ped_HeatSink_C.at(1));
        // float IntADC_HS_2_C  = GetIntWithPed(Wave_HeatSink_C.at(2), 130, 350, Ped_HeatSink_C.at(2));
        // float IntADC_HS_3_C  = GetIntWithPed(Wave_HeatSink_C.at(3), 130, 320, Ped_HeatSink_C.at(3));

        // float IntADC_HS_W_S  = GetIntWithPed(Wave_HeatSink_S.at(0), 130, 370, Ped_HeatSink_S.at(0));
        // float IntADC_HS_1_S  = GetIntWithPed(Wave_HeatSink_S.at(1), 140, 360, Ped_HeatSink_S.at(1));
        // float IntADC_HS_2_S  = GetIntWithPed(Wave_HeatSink_S.at(2), 140, 350, Ped_HeatSink_S.at(2));
        // float IntADC_HS_3_S  = GetIntWithPed(Wave_HeatSink_S.at(3), 140, 350, Ped_HeatSink_S.at(3));

        // float IntADC_L_1_C  = GetIntWithPed(Wave_Lego_C.at(0), 140, 350, Ped_Lego_C.at(0));
        // float IntADC_L_2_C  = GetIntWithPed(Wave_Lego_C.at(1), 200, 360, Ped_Lego_C.at(1));
        // float IntADC_L_3_C  = GetIntWithPed(Wave_Lego_C.at(2), 130, 330, Ped_Lego_C.at(2));
        // float IntADC_L_4_C  = GetIntWithPed(Wave_Lego_C.at(3), 140, 330, Ped_Lego_C.at(3));

        // float IntADC_L_1_S  = GetIntWithPed(Wave_Lego_S.at(0), 155, 360, Ped_Lego_S.at(0));
        // float IntADC_L_2_S  = GetIntWithPed(Wave_Lego_S.at(1), 210, 450, Ped_Lego_S.at(1));
        // float IntADC_L_3_S  = GetIntWithPed(Wave_Lego_S.at(2), 155, 330, Ped_Lego_S.at(2));
        // float IntADC_L_4_S  = GetIntWithPed(Wave_Lego_S.at(3), 150, 355, Ped_Lego_S.at(3));
        
        // Try02, 05
        // float IntADC_3D_mid_C = GetIntWithPed(Wave_3D_C.at(0), 140, 270, Ped_3D_C.at(0));
        // float IntADC_3D_W1_C  = GetIntWithPed(Wave_3D_C.at(1), 130, 275, Ped_3D_C.at(1));
        // float IntADC_3D_W2_C  = GetIntWithPed(Wave_3D_C.at(2), 145, 260, Ped_3D_C.at(2));
        // float IntADC_3D_W3_C  = GetIntWithPed(Wave_3D_C.at(3), 140, 250, Ped_3D_C.at(3));

        // float IntADC_3D_mid_S = GetIntWithPed(Wave_3D_S.at(0), 150, 330, Ped_3D_S.at(0));
        // float IntADC_3D_W1_S  = GetIntWithPed(Wave_3D_S.at(1), 165, 325, Ped_3D_S.at(1));
        // float IntADC_3D_W2_S  = GetIntWithPed(Wave_3D_S.at(2), 160, 305, Ped_3D_S.at(2));
        // float IntADC_3D_W3_S  = GetIntWithPed(Wave_3D_S.at(3), 150, 295, Ped_3D_S.at(3));

        // float IntADC_HS_W_C  = GetIntWithPed(Wave_HeatSink_C.at(0), 135, 280, Ped_HeatSink_C.at(0));
        // float IntADC_HS_1_C  = GetIntWithPed(Wave_HeatSink_C.at(1), 150, 325, Ped_HeatSink_C.at(1));
        // float IntADC_HS_2_C  = GetIntWithPed(Wave_HeatSink_C.at(2), 145, 325, Ped_HeatSink_C.at(2));
        // float IntADC_HS_3_C  = GetIntWithPed(Wave_HeatSink_C.at(3), 145, 300, Ped_HeatSink_C.at(3));

        // float IntADC_HS_W_S  = GetIntWithPed(Wave_HeatSink_S.at(0), 140, 335, Ped_HeatSink_S.at(0));
        // float IntADC_HS_1_S  = GetIntWithPed(Wave_HeatSink_S.at(1), 160, 330, Ped_HeatSink_S.at(1));
        // float IntADC_HS_2_S  = GetIntWithPed(Wave_HeatSink_S.at(2), 155, 325, Ped_HeatSink_S.at(2));
        // float IntADC_HS_3_S  = GetIntWithPed(Wave_HeatSink_S.at(3), 170, 330, Ped_HeatSink_S.at(3));

        // float IntADC_L_1_C  = GetIntWithPed(Wave_Lego_C.at(0), 155, 330, Ped_Lego_C.at(0));
        // float IntADC_L_2_C  = GetIntWithPed(Wave_Lego_C.at(1), 215, 370, Ped_Lego_C.at(1));
        // float IntADC_L_3_C  = GetIntWithPed(Wave_Lego_C.at(2), 145, 300, Ped_Lego_C.at(2));
        // float IntADC_L_4_C  = GetIntWithPed(Wave_Lego_C.at(3), 150, 395, Ped_Lego_C.at(3));

        // float IntADC_L_1_S  = GetIntWithPed(Wave_Lego_S.at(0), 170, 340, Ped_Lego_S.at(0));
        // float IntADC_L_2_S  = GetIntWithPed(Wave_Lego_S.at(1), 220, 405, Ped_Lego_S.at(1));
        // float IntADC_L_3_S  = GetIntWithPed(Wave_Lego_S.at(2), 155, 330, Ped_Lego_S.at(2));
        // float IntADC_L_4_S  = GetIntWithPed(Wave_Lego_S.at(3), 160, 340, Ped_Lego_S.at(3));

        // // Try 03, 04
        // float IntADC_3D_mid_C = GetIntWithPed(Wave_3D_C.at(0), 120, 340, Ped_3D_C.at(0));
        // float IntADC_3D_W1_C  = GetIntWithPed(Wave_3D_C.at(1), 110, 340, Ped_3D_C.at(1));
        // float IntADC_3D_W2_C  = GetIntWithPed(Wave_3D_C.at(2), 120, 310, Ped_3D_C.at(2));
        // float IntADC_3D_W3_C  = GetIntWithPed(Wave_3D_C.at(3), 140, 360, Ped_3D_C.at(3));

        // float IntADC_3D_mid_S = GetIntWithPed(Wave_3D_S.at(0), 120, 420, Ped_3D_S.at(0));
        // float IntADC_3D_W1_S  = GetIntWithPed(Wave_3D_S.at(1), 140, 380, Ped_3D_S.at(1));
        // float IntADC_3D_W2_S  = GetIntWithPed(Wave_3D_S.at(2), 130, 360, Ped_3D_S.at(2));
        // float IntADC_3D_W3_S  = GetIntWithPed(Wave_3D_S.at(3), 150, 420, Ped_3D_S.at(3));

        // float IntADC_HS_W_C  = GetIntWithPed(Wave_HeatSink_C.at(0), 110, 360, Ped_HeatSink_C.at(0));
        // float IntADC_HS_1_C  = GetIntWithPed(Wave_HeatSink_C.at(1), 120, 360, Ped_HeatSink_C.at(1));
        // float IntADC_HS_2_C  = GetIntWithPed(Wave_HeatSink_C.at(2), 130, 380, Ped_HeatSink_C.at(2));
        // float IntADC_HS_3_C  = GetIntWithPed(Wave_HeatSink_C.at(3), 130, 400, Ped_HeatSink_C.at(3));

        // float IntADC_HS_W_S  = GetIntWithPed(Wave_HeatSink_S.at(0), 120, 420, Ped_HeatSink_S.at(0));
        // float IntADC_HS_1_S  = GetIntWithPed(Wave_HeatSink_S.at(1), 130, 490, Ped_HeatSink_S.at(1));
        // float IntADC_HS_2_S  = GetIntWithPed(Wave_HeatSink_S.at(2), 130, 480, Ped_HeatSink_S.at(2));
        // float IntADC_HS_3_S  = GetIntWithPed(Wave_HeatSink_S.at(3), 130, 480, Ped_HeatSink_S.at(3));

        // float IntADC_L_1_C  = GetIntWithPed(Wave_Lego_C.at(0), 140, 400, Ped_Lego_C.at(0));
        // float IntADC_L_2_C  = GetIntWithPed(Wave_Lego_C.at(1), 200, 400, Ped_Lego_C.at(1));
        // float IntADC_L_3_C  = GetIntWithPed(Wave_Lego_C.at(2), 130, 380, Ped_Lego_C.at(2));
        // float IntADC_L_4_C  = GetIntWithPed(Wave_Lego_C.at(3), 130, 480, Ped_Lego_C.at(3));

        // float IntADC_L_1_S  = GetIntWithPed(Wave_Lego_S.at(0), 145, 500, Ped_Lego_S.at(0));
        // float IntADC_L_2_S  = GetIntWithPed(Wave_Lego_S.at(1), 200, 550, Ped_Lego_S.at(1));
        // float IntADC_L_3_S  = GetIntWithPed(Wave_Lego_S.at(2), 130, 420, Ped_Lego_S.at(2));
        // float IntADC_L_4_S  = GetIntWithPed(Wave_Lego_S.at(3), 130, 480, Ped_Lego_S.at(3));

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

        // float Calibrated_3D_C     = (IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C) * Calib_3D_C;
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

        // float Calibrated_3D_S     = (IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S) * Calib_3D_S;
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

        float Calibrated_C =    Calibrated_3D_mid_C + Calibrated_3D_W1_C + Calibrated_3D_W2_C + Calibrated_3D_W3_C + 
                                Calibrated_HS_W_C + Calibrated_HS_1_C + Calibrated_HS_2_C + Calibrated_HS_3_C +
                                Calibrated_L_1_C + Calibrated_L_2_C + Calibrated_L_3_C + Calibrated_L_4_C;

        float Calibrated_S =    Calibrated_3D_mid_S + Calibrated_3D_W1_S + Calibrated_3D_W2_S + Calibrated_3D_W3_S +
                                Calibrated_HS_W_S + Calibrated_HS_1_S + Calibrated_HS_2_S + Calibrated_HS_3_S +
                                Calibrated_L_1_S + Calibrated_L_2_S + Calibrated_L_3_S + Calibrated_L_4_S;

        // float Calibrated_C_2 =  Calibrated_3D_C + 
        //                         Calibrated_HS_W_C + Calibrated_HS_1_C + Calibrated_HS_2_C + Calibrated_HS_3_C +
        //                         Calibrated_L_1_C + Calibrated_L_2_C + Calibrated_L_3_C + Calibrated_L_4_C;

        // float Calibrated_S_2 =  Calibrated_3D_S +
        //                         Calibrated_HS_W_S + Calibrated_HS_1_S + Calibrated_HS_2_S + Calibrated_HS_3_S +
        //                         Calibrated_L_1_S + Calibrated_L_2_S + Calibrated_L_3_S + Calibrated_L_4_S;

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

        Hist_C_Energy->Fill(Calibrated_C);
        Hist_S_Energy->Fill(Calibrated_S);
        Hist_Sum_Energy->Fill(Calibrated_C + Calibrated_S);

        // Hist_C_Energy_2->Fill(Calibrated_C_2);
        // Hist_S_Energy_2->Fill(Calibrated_S_2);
        // Hist_Sum_Energy_2->Fill(Calibrated_C_2 + Calibrated_S_2);

        // Hist_3D_C_Calibrated->Fill( (IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C) * Calib_3D_C );
        Hist_3D_mid_C_Calibrated->Fill(Calibrated_3D_mid_C);
        Hist_3D_W1_C_Calibrated ->Fill(Calibrated_3D_W1_C);
        Hist_3D_W2_C_Calibrated ->Fill(Calibrated_3D_W2_C);
        Hist_3D_W3_C_Calibrated ->Fill(Calibrated_3D_W3_C);

        // Hist_3D_S_Calibrated->Fill( (IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S) * Calib_3D_S );
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

        Hist_C_Energy_cut->Fill(Calibrated_C);
        Hist_S_Energy_cut->Fill(Calibrated_S);
        Hist_Sum_Energy_cut->Fill(Calibrated_C + Calibrated_S);

        // Hist_C_Energy_2_cut->Fill(Calibrated_C_2);
        // Hist_S_Energy_2_cut->Fill(Calibrated_S_2);
        // Hist_Sum_Energy_2_cut->Fill(Calibrated_C_2 + Calibrated_S_2);

        // Hist_3D_C_Calibrated_cut->Fill( (IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C) * Calib_3D_C );
        Hist_3D_mid_C_Calibrated_cut->Fill(Calibrated_3D_mid_C);
        Hist_3D_W1_C_Calibrated_cut ->Fill(Calibrated_3D_W1_C);
        Hist_3D_W2_C_Calibrated_cut ->Fill(Calibrated_3D_W2_C);
        Hist_3D_W3_C_Calibrated_cut ->Fill(Calibrated_3D_W3_C);

        // Hist_3D_S_Calibrated_cut->Fill( (IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S) * Calib_3D_S );
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

        if(Calibrated_C > 5) {
            Hist_C_High_Energy_cut->Fill(Calibrated_C);

            // Hist_3D_C_High_Calibrated_cut->Fill( (IntADC_3D_mid_C + IntADC_3D_W1_C + IntADC_3D_W2_C + IntADC_3D_W3_C) * Calib_3D_C );
            Hist_3D_mid_C_High_Calibrated_cut->Fill(Calibrated_3D_mid_C);
            Hist_3D_W1_C_High_Calibrated_cut ->Fill(Calibrated_3D_W1_C);
            Hist_3D_W2_C_High_Calibrated_cut ->Fill(Calibrated_3D_W2_C);
            Hist_3D_W3_C_High_Calibrated_cut ->Fill(Calibrated_3D_W3_C);

            Hist_HS_W_C_High_Calibrated_cut->Fill(Calibrated_HS_W_C);
            Hist_HS_1_C_High_Calibrated_cut->Fill(Calibrated_HS_1_C);
            Hist_HS_2_C_High_Calibrated_cut->Fill(Calibrated_HS_2_C);
            Hist_HS_3_C_High_Calibrated_cut->Fill(Calibrated_HS_3_C);

            Hist_L_1_C_High_Calibrated_cut->Fill(Calibrated_L_1_C);
            Hist_L_2_C_High_Calibrated_cut->Fill(Calibrated_L_2_C);
            Hist_L_3_C_High_Calibrated_cut->Fill(Calibrated_L_3_C);
            Hist_L_4_C_High_Calibrated_cut->Fill(Calibrated_L_4_C);
        }

        if(Calibrated_S > 5) {
            Hist_S_High_Energy_cut->Fill(Calibrated_S);

            // Hist_3D_S_High_Calibrated_cut->Fill( (IntADC_3D_mid_S + IntADC_3D_W1_S + IntADC_3D_W2_S + IntADC_3D_W3_S) * Calib_3D_S );
            Hist_3D_mid_S_High_Calibrated_cut->Fill(Calibrated_3D_mid_S);
            Hist_3D_W1_S_High_Calibrated_cut ->Fill(Calibrated_3D_W1_S);
            Hist_3D_W2_S_High_Calibrated_cut ->Fill(Calibrated_3D_W2_S);
            Hist_3D_W3_S_High_Calibrated_cut ->Fill(Calibrated_3D_W3_S);

            Hist_HS_W_S_High_Calibrated_cut->Fill(Calibrated_HS_W_S);
            Hist_HS_1_S_High_Calibrated_cut->Fill(Calibrated_HS_1_S);
            Hist_HS_2_S_High_Calibrated_cut->Fill(Calibrated_HS_2_S);
            Hist_HS_3_S_High_Calibrated_cut->Fill(Calibrated_HS_3_S);

            Hist_L_1_S_High_Calibrated_cut->Fill(Calibrated_L_1_S);
            Hist_L_2_S_High_Calibrated_cut->Fill(Calibrated_L_2_S);
            Hist_L_3_S_High_Calibrated_cut->Fill(Calibrated_L_3_S);
            Hist_L_4_S_High_Calibrated_cut->Fill(Calibrated_L_4_S);
        }

        if ( (Calibrated_C + Calibrated_S) > 10 ) Hist_Sum_High_Energy_cut->Fill(Calibrated_C + Calibrated_S); 
    }

    // Save the outputs
    std::string outFile = "./CalibAtOnce/CalibAtOnce_Run_" + std::to_string(runNum) + "_24Feb06ReCalib.root";
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

    // Hist_3D_C_Calibrated->Write();
    Hist_3D_mid_C_Calibrated->Write();
    Hist_3D_W1_C_Calibrated ->Write();
    Hist_3D_W2_C_Calibrated ->Write();
    Hist_3D_W3_C_Calibrated ->Write();

    // Hist_3D_S_Calibrated->Write();
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

    Hist_C_Energy_2->Write();
    Hist_S_Energy_2->Write();
    Hist_Sum_Energy_2->Write();

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

    // Hist_3D_C_Calibrated_cut->Write();
    Hist_3D_mid_C_Calibrated_cut->Write();
    Hist_3D_W1_C_Calibrated_cut->Write();
    Hist_3D_W2_C_Calibrated_cut->Write();
    Hist_3D_W3_C_Calibrated_cut->Write();

    // Hist_3D_S_Calibrated_cut->Write();
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

    Hist_C_Energy_2_cut->Write();
    Hist_S_Energy_2_cut->Write();
    Hist_Sum_Energy_2_cut->Write();

    // Investigating
    Hist_C_High_Energy_cut->Write();
    Hist_S_High_Energy_cut->Write();
    Hist_Sum_High_Energy_cut->Write();

    Hist_3D_C_High_Calibrated_cut->Write();
    Hist_3D_mid_C_High_Calibrated_cut->Write();
    Hist_3D_W1_C_High_Calibrated_cut->Write();
    Hist_3D_W2_C_High_Calibrated_cut->Write();
    Hist_3D_W3_C_High_Calibrated_cut->Write();

    Hist_HS_W_C_High_Calibrated_cut->Write();
    Hist_HS_1_C_High_Calibrated_cut->Write();
    Hist_HS_2_C_High_Calibrated_cut->Write();
    Hist_HS_3_C_High_Calibrated_cut->Write();

    Hist_L_1_C_High_Calibrated_cut->Write();
    Hist_L_2_C_High_Calibrated_cut->Write();
    Hist_L_3_C_High_Calibrated_cut->Write();
    Hist_L_4_C_High_Calibrated_cut->Write();

    Hist_3D_S_High_Calibrated_cut->Write();
    Hist_3D_mid_S_High_Calibrated_cut->Write();
    Hist_3D_W1_S_High_Calibrated_cut->Write();
    Hist_3D_W2_S_High_Calibrated_cut->Write();
    Hist_3D_W3_S_High_Calibrated_cut->Write();

    Hist_HS_W_S_High_Calibrated_cut->Write();
    Hist_HS_1_S_High_Calibrated_cut->Write();
    Hist_HS_2_S_High_Calibrated_cut->Write();
    Hist_HS_3_S_High_Calibrated_cut->Write();

    Hist_L_1_S_High_Calibrated_cut->Write();
    Hist_L_2_S_High_Calibrated_cut->Write();
    Hist_L_3_S_High_Calibrated_cut->Write();
    Hist_L_4_S_High_Calibrated_cut->Write();

    outputRoot->Close();
}
