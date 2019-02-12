#include <iostream>

#include <TFile.h>
#include <TH1.h>
#include <TTree.h>

TH1D *His[20];

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

void MakeHis()
{
  for (auto T = 3, counter = 0; T <= 5; T += 2) {
    for (auto ene = 1; ene <= 10; ene++) {
      His[counter] = new TH1D(Form("HisT%dEne%d", T, ene),
                              Form("T: %d mm, Ene: %d GeV", T, ene), 110000,
                              0. - 0.05, 11000. - 0.05);
      auto file = new TFile(Form("Ene%d.T%d.root", ene, T), "READ");
      auto tree = (TTree *)file->Get("E6Window");
      FillHis(tree, His[counter]);
      file->Close();
      delete file;

      auto ave = His[counter]->GetMean() / 1000.;
      auto peak =
          His[counter]->GetBinCenter(His[counter]->GetMaximumBin()) / 1000;
      cout << Form("T: %d mm, Ene: %d GeV", T, ene) << "\n"
           << "Ave: " << ave << " GeV\t" << 100 * (ene - ave) / ene << "\n"
           << "Peak: " << peak << " GeV\t" << 100 * (ene - peak) / ene << endl;
      counter++;
    }
  }

  auto outFile = new TFile("histo.root", "RECREATE");
  for (auto &&his : His) his->Write();
  outFile->Close();
}
