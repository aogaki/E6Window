#include <g4root.hh>

#include "E6RunAction.hpp"

E6RunAction::E6RunAction() : G4UserRunAction()
{
  auto anaMan = G4AnalysisManager::Instance();
  // anaMan->SetNtupleMerging(true);
  anaMan->SetVerboseLevel(1);
  G4String fileName = "result";
  anaMan->SetFileName(fileName);

  anaMan->CreateNtuple("E6Window", "particle info");

  anaMan->CreateNtupleDColumn("KineticEnergy");

  anaMan->CreateNtupleDColumn("x");
  anaMan->CreateNtupleDColumn("y");
  anaMan->CreateNtupleDColumn("z");

  anaMan->CreateNtupleDColumn("Px");
  anaMan->CreateNtupleDColumn("Py");
  anaMan->CreateNtupleDColumn("Pz");

  anaMan->FinishNtuple();
}

E6RunAction::~E6RunAction() { delete G4AnalysisManager::Instance(); }

void E6RunAction::BeginOfRunAction(const G4Run *)
{
  G4AnalysisManager *anaMan = G4AnalysisManager::Instance();
  anaMan->OpenFile();
}

void E6RunAction::EndOfRunAction(const G4Run *)
{
  G4AnalysisManager *anaMan = G4AnalysisManager::Instance();
  anaMan->Write();
  anaMan->CloseFile();
}
