#ifndef E6DetectorConstruction_h
#define E6DetectorConstruction_h 1

#include <vector>

#include <G4GenericMessenger.hh>
#include <G4Material.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4VisAttributes.hh>

class E6DetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  E6DetectorConstruction();
  virtual ~E6DetectorConstruction();

  virtual G4VPhysicalVolume *Construct();
  virtual void ConstructSDandField();

 private:
  G4bool fCheckOverlap;

  // Materials
  void DefineMaterials();
  G4Material *fVacuumMat;
  G4Material *fWindowMat;
  G4Material *fAirMat;

  void DefineCommands();
  void SetWindowT(G4double t);
  G4VPhysicalVolume *fWindowPV;
  G4double fWindowT;
  G4GenericMessenger *fMessenger;

  std::vector<G4VisAttributes *> fVisAttributes;
};

#endif
