#ifndef E6Hit_h
#define E6Hit_h 1

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"
#include "G4VHit.hh"

class E6Hit : public G4VHit
{
 public:
  E6Hit();
  virtual ~E6Hit();
  E6Hit(const E6Hit &right);
  const E6Hit &operator=(const E6Hit &right);
  int operator==(const E6Hit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *);

  // add setter/getter methods
  void SetKineticEnergy(G4double ene) { fKineticEnergy = ene; };
  G4double GetKineticEnergy() { return fKineticEnergy; };

  void SetPosition(G4ThreeVector pos) { fPosition = pos; };
  G4ThreeVector GetPosition() { return fPosition; };

  void SetMomentum(G4ThreeVector p) { fMomentum = p; };
  G4ThreeVector GetMomentum() { return fMomentum; };

 private:
  G4double fKineticEnergy;
  G4ThreeVector fPosition;
  G4ThreeVector fMomentum;
};

typedef G4THitsCollection<E6Hit> E6HitsCollection;

extern G4ThreadLocal G4Allocator<E6Hit> *E6HitAllocator;

inline void *E6Hit::operator new(size_t)
{
  if (!E6HitAllocator) E6HitAllocator = new G4Allocator<E6Hit>;
  return (void *)E6HitAllocator->MallocSingle();
}

inline void E6Hit::operator delete(void *hit)
{
  E6HitAllocator->FreeSingle((E6Hit *)hit);
}

#endif
