#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TStyle.h>

void MakeFigure()
{
  gStyle->SetOptStat(kFALSE);

  auto file = new TFile("histo.root", "READ");
  auto hisRef = new TH1D("hisRef", "", 110000, 0. - 0.05, 11000. - 0.05);
  auto canvas = new TCanvas();

  for (auto T = 3; T <= 5; T += 2) {
    for (auto ene = 1; ene <= 10; ene++) {
      auto targetBin = ene * 10000 + 1;
      hisRef->SetBinContent(targetBin, 1.e+7);

      auto his = (TH1D *)file->Get(Form("HisT%dEne%d", T, ene));
      his->SetMaximum(9.e+6);
      his->GetXaxis()->SetRange(targetBin - 50, targetBin + 50);
      his->SetLineColor(kRed);
      his->Draw();

      canvas->SetLogy(kTRUE);
      canvas->SetGrid(kTRUE, kTRUE);

      hisRef->Draw("SAME");

      canvas->Print(Form("T%dEne%d.pdf", T, ene), "pdf");
    }
  }
}
