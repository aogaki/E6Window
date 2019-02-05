#ifndef E6EventAction_h
#define E6EventAction_h 1

#include <G4UserEventAction.hh>

#include "E6Hit.hpp"

class E6EventAction : public G4UserEventAction
{
public:
   E6EventAction();
   virtual ~E6EventAction();

   virtual void BeginOfEventAction(const G4Event *);
   virtual void EndOfEventAction(const G4Event *);

private:
   E6HitsCollection *GetHitsCollection(G4int hcID, const G4Event *event) const;
   
   G4int fHitsCollectionID;
};

#endif
