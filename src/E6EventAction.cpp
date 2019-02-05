#include <G4Event.hh>
#include <G4SDManager.hh>
#include <g4root.hh>

#include "E6EventAction.hpp"

E6EventAction::E6EventAction() : G4UserEventAction(), fHitsCollectionID(-1) {}

E6EventAction::~E6EventAction() {}

E6HitsCollection *E6EventAction::GetHitsCollection(G4int hcID,
                                                   const G4Event *event) const
{
  E6HitsCollection *hitsCollection =
      static_cast<E6HitsCollection *>(event->GetHCofThisEvent()->GetHC(hcID));

  if (!hitsCollection) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    // check how to use G4Exception
    G4Exception("E6EventAction::GetHitsCollection()", "E6Code0003",
                FatalException, msg);
  }

  return hitsCollection;
}

void E6EventAction::BeginOfEventAction(const G4Event *) {}

void E6EventAction::EndOfEventAction(const G4Event *event)
{
  if (fHitsCollectionID == -1)
    fHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID("HC");

  G4AnalysisManager *anaMan = G4AnalysisManager::Instance();

  E6HitsCollection *hc = GetHitsCollection(fHitsCollectionID, event);
  const G4int kHit = hc->entries();
  for (G4int iHit = 0; iHit < kHit; iHit++) {
    E6Hit *newHit = (*hc)[iHit];

    G4double ene = newHit->GetKineticEnergy();
    anaMan->FillNtupleDColumn(0, 0, ene);

    G4ThreeVector position = newHit->GetPosition();
    anaMan->FillNtupleDColumn(0, 1, position.x());
    anaMan->FillNtupleDColumn(0, 2, position.y());
    anaMan->FillNtupleDColumn(0, 3, position.z());

    G4ThreeVector momentum = newHit->GetMomentum();
    anaMan->FillNtupleDColumn(0, 4, momentum.x());
    anaMan->FillNtupleDColumn(0, 5, momentum.y());
    anaMan->FillNtupleDColumn(0, 6, momentum.z());

    anaMan->AddNtupleRow(0);
  }
}
