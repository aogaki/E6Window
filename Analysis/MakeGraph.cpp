#include <iostream>

#include <TFile.h>
#include <TGraph.h>
#include <TH1.h>
#include <TTree.h>


void FillHis(TTree *tree, TH1D *his)
{
   tree->SetBranchStatus("*", kFALSE);
   Double_t ene;
   tree->SetBranchStatus("KineticEnergy", kTRUE);
   tree->SetBranchAddress("KineticEnergy", &ene);

   const auto nHit = tree->GetEntries();
   for (uint i = 0; i < nHit; i++) {
      tree->GetEntry(i);
      his->Fill(ene);
   }
}

void MakeGraph()
{
   Double_t arrayAve[30];
   Double_t arrayPeak[30];

   Int_t arrayT[3] = {3, 5, 10};
   for (auto i = 0, counter = 0; i < 3; i++) {
      auto T = arrayT[i];
      for (auto ene = 1; ene <= 10; ene++) {
         auto his = new TH1D(Form("His%02d", counter + 1),
                                 Form("T: %d mm, Ene: %d GeV", T, ene), 110000000,
                                 0. - 0.00005, 11000. - 0.00005);
         auto file = new TFile(Form("Ene%d.T%d.root", ene, T), "READ");
         auto tree = (TTree *)file->Get("E6Window");
         FillHis(tree, his);
         file->Close();
         delete file;

         auto ave = his->GetMean() / 1000.;
         auto peak =
            his->GetBinCenter(his->GetMaximumBin()) / 1000;
         arrayAve[counter] = ave;
         arrayPeak[counter] = peak;
         cout << dec << Form("T: %d mm, Ene: %d GeV", T, ene) << "\n"
            //<< scientific
              << "Ave: " << ave << " GeV\t" << 100 * (ene - ave) / ene << "\n"
              << "Peak: " << peak << " GeV\t" << 100 * (ene - peak) / ene << endl;

         delete his;
         counter++;
      }
   }

   TGraph *grAveT3 = new TGraph();
   TGraph *grAveT5 = new TGraph();
   TGraph *grAveT10 = new TGraph();
   TGraph *grPeakT3 = new TGraph();
   TGraph *grPeakT5 = new TGraph();
   TGraph *grPeakT10 = new TGraph();

   for (auto i = 0; i < 10; i++) {
      Double_t ene = i + 1;
      grAveT3->SetPoint(i, ene, 100 * (ene - arrayAve[i]) / ene);
      grAveT5->SetPoint(i, ene, 100 * (ene - arrayAve[i + 10]) / ene);
      grAveT10->SetPoint(i, ene, 100 * (ene - arrayAve[i + 20]) / ene);
      grPeakT3->SetPoint(i, ene, 100 * (ene - arrayPeak[i]) / ene);
      grPeakT5->SetPoint(i, ene, 100 * (ene - arrayPeak[i + 10]) / ene);
      grPeakT10->SetPoint(i, ene, 100 * (ene - arrayPeak[i + 20]) / ene);
   }

   auto outFile = new TFile("graph.root", "RECREATE");
   grAveT3->Write("AveT3");
   grAveT5->Write("AveT5");
   grAveT10->Write("AveT10");
   grPeakT3->Write("PeakT3");
   grPeakT5->Write("PeakT5");
   grPeakT10->Write("PeakT10");
   outFile->Close();

   cout << scientific;
   for(auto i = 0; i < 10; i++){
      cout << (arrayPeak[i]) <<","
           << (arrayPeak[i + 10]) <<","
           << (arrayPeak[i + 20]) << endl;
   }
   for(auto i = 0; i < 10; i++){
      cout << (arrayAve[i]) <<","
           << (arrayAve[i + 10]) <<","
           << (arrayAve[i + 20]) << endl;
   }
/*   
   for(auto i = 0; i < 10; i++){
      auto ene = i + 1;
      cout << (ene - arrayPeak[i]) / ene <<","
           << (ene - arrayPeak[i + 10]) / ene <<","
           << (ene - arrayPeak[i + 20]) / ene << endl;
   }
   for(auto i = 0; i < 10; i++){
      auto ene = i + 1;
      cout << (ene - arrayAve[i]) / ene <<","
           << (ene - arrayAve[i + 10]) / ene <<","
           << (ene - arrayAve[i + 20]) / ene << endl;
   }
  */ 
}
