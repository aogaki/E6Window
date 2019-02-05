#ifndef E6SD_h
#define E6SD_h 1

#include <G4VSensitiveDetector.hh>
#include <G4ThreeVector.hh>
#include <G4LogicalVolume.hh>

#include "E6Hit.hpp"


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class E6SD: public G4VSensitiveDetector
{
public:
   E6SD(const G4String &name,
            const G4String &hitsCollectionName);
   virtual ~E6SD();

   virtual void Initialize(G4HCofThisEvent *hce);
   virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);

private:
   E6HitsCollection *fHitsCollection;
};

#endif
