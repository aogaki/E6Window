#ifndef E6PrimaryGeneratorAction_h
#define E6PrimaryGeneratorAction_h 1

#include <G4Event.hh>
#include <G4GenericMessenger.hh>
#include <G4ParticleGun.hh>
#include <G4Threading.hh>
#include <G4ThreeVector.hh>
#include <G4VUserPrimaryGeneratorAction.hh>

class E6PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
 public:
  E6PrimaryGeneratorAction();
  virtual ~E6PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event *);

 private:
  G4ParticleGun *fParticleGun;
};

#endif
