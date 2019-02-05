#include <G4HCofThisEvent.hh>
#include <G4Material.hh>
#include <G4SDManager.hh>
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>
#include <G4TouchableHistory.hh>
#include <G4VProcess.hh>
#include <G4ios.hh>
#include <g4root.hh>

#include "E6Hit.hpp"
#include "E6SD.hpp"

E6SD::E6SD(const G4String &name, const G4String &hitsCollectionName)
    : G4VSensitiveDetector(name)
{
  collectionName.insert(hitsCollectionName);
}

E6SD::~E6SD() {}

void E6SD::Initialize(G4HCofThisEvent *hce)
{
  fHitsCollection =
      new E6HitsCollection(SensitiveDetectorName, collectionName[0]);

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool E6SD::ProcessHits(G4Step *step, G4TouchableHistory * /*history*/)
{
  G4Track *track = step->GetTrack();
  if (track->GetTrackID() != 1) return false;  // only the primal particle
  G4StepPoint *postStepPoint = step->GetPostStepPoint();
  if (postStepPoint->GetStepStatus() != fGeomBoundary) return false;

  E6Hit *newHit = new E6Hit();

  G4double kineticEnergy = postStepPoint->GetKineticEnergy();
  newHit->SetKineticEnergy(kineticEnergy);

  G4ThreeVector position = postStepPoint->GetPosition();
  newHit->SetPosition(position);

  G4ThreeVector momentum = postStepPoint->GetMomentum();
  newHit->SetMomentum(momentum);

  fHitsCollection->insert(newHit);
  return true;
}
