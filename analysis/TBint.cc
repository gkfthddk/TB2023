#include "TLegend.h"
#include "TColor.h"

#include "drawFunction.h"

#include "TBread.h"

int main(int argc, char* argv[]) {
    TApplication app("app", &argc, argv);

    gStyle->SetPalette(kVisibleSpectrum);

    std::string runNum = argv[1];
    int start_bin      = std::stoi(argv[2]);
    int end_bin        = std::stoi(argv[3]);
	std::string channel_name = argv[4];
    
	gStyle->SetOptStat(1);
    gStyle->SetStatFormat("6.6g");

    auto map = getModuleConfigMap();
    if (map.find(channel_name) == map.end()) {
        std::cout << "Plot Name error : " << channel_name << " not found" << std::endl;
        return 0;
	}
	std::vector<int> MIDandCh = map.at(channel_name);
	int MID = MIDandCh.at(0);
	int Ch  = MIDandCh.at(1);
	TH1F* hist = new TH1F( (TString) (runNum + "_" + channel_name), (TString) channel_name, 1000, -6000., 250000.);

    TBread<TBwaveform> readerWave = TBread<TBwaveform>(std::stoi(runNum), -1, -1, "/eos/user/s/sungwon/public/TB2023_data", std::vector<int> {MID} );
    std::cout << "Total # of entry : " << readerWave.GetMaxEvent() << std::endl;



    TCanvas* c = new TCanvas("c", "c", 800, 600);
    c->cd();

    for(int iEvt = 0; iEvt < readerWave.GetMaxEvent(); iEvt++) {
        printProgress(iEvt, readerWave.GetMaxEvent());

        auto anEvent = readerWave.GetAnEvent();

        TBcid cid = TBcid(MID, Ch);
        auto single_waveform = anEvent.GetData(cid).waveform();

        float IntADC = GetInt(single_waveform, start_bin, end_bin);
        hist->Fill(IntADC);
    }
    

    hist->GetXaxis()->SetTitle("IntADC");
    hist->GetYaxis()->SetTitle("Evt");
    hist->SetLineWidth(2);

    c->cd();
    hist->Draw("Hist");
    c->Update();
	
	gSystem->mkdir((TString) ("IntADC/Run_" + runNum), true);
	TFile* output = new TFile( (TString) ("IntADC/Run_" + runNum + "/Run_" + runNum + "_" + channel_name + ".root") , "RECREATE");
	output->cd();
	hist->Write();
	output->Close();

    app.Run();

    return 0;
}
