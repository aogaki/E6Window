#include <G4AutoLock.hh>
#include <G4ChargedGeantino.hh>
#include <G4IonTable.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include <g4root.hh>

#include "E6PrimaryGeneratorAction.hpp"

static G4int nEveInPGA = 0;
G4Mutex mutexInPGA = G4MUTEX_INITIALIZER;

E6PrimaryGeneratorAction::E6PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr)
{
  fParticleGun = new G4ParticleGun(1);

  G4ParticleTable *parTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *electron = parTable->FindParticle("e-");
  fParticleGun->SetParticleDefinition(electron);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -1. * m));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleEnergy(5. * GeV);
}

E6PrimaryGeneratorAction::~E6PrimaryGeneratorAction() { delete fParticleGun; }

void E6PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
  fParticleGun->GeneratePrimaryVertex(event);

  G4AutoLock lock(&mutexInPGA);
  if (nEveInPGA++ % 10000 == 0)
    G4cout << nEveInPGA - 1 << " events done" << G4endl;
}
