#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4PVReplica.hh>
#include <G4RunManager.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Tubs.hh>

#include "E6DetectorConstruction.hpp"
#include "E6SD.hpp"

E6DetectorConstruction::E6DetectorConstruction()
    : fVacuumMat(nullptr),
      fWindowMat(nullptr),
      fAirMat(nullptr),
      fWindowPV(nullptr),
      fMessenger(nullptr)
{
  fCheckOverlap = true;
  fWindowT = 3. * mm;
  DefineMaterials();
  DefineCommands();
}

E6DetectorConstruction::~E6DetectorConstruction() {}

void E6DetectorConstruction::DefineMaterials()
{
  G4NistManager *manager = G4NistManager::Instance();

  // NIST database materials
  fVacuumMat = manager->FindOrBuildMaterial("G4_Galactic");
  fWindowMat = manager->FindOrBuildMaterial("G4_POLYCARBONATE");
  fAirMat = manager->FindOrBuildMaterial("G4_AIR");
}

G4VPhysicalVolume *E6DetectorConstruction::Construct()
{
  // world volume
  G4double worldX = 0.1 * m;
  G4double worldY = 0.1 * m;
  G4double worldZ = 3. * m;

  G4Box *worldS = new G4Box("World", worldX / 2., worldY / 2., worldZ / 2.);
  G4LogicalVolume *worldLV = new G4LogicalVolume(worldS, fVacuumMat, "World");

  G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour::White());
  visAttributes->SetVisibility(false);
  worldLV->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  // Air layer
  G4double airW = worldX;
  G4double airH = worldY;
  G4double airT = 1. * m;

  G4Box *airS = new G4Box("Air", airW / 2., airH / 2., airT / 2.);
  G4LogicalVolume *airLV = new G4LogicalVolume(airS, fAirMat, "Air");
  visAttributes = new G4VisAttributes(G4Colour::Magenta());
  airLV->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  G4double airZPos = airT / 2.;
  G4ThreeVector airPos = G4ThreeVector(0., 0., airZPos);
  new G4PVPlacement(nullptr, airPos, airLV, "Air", worldLV, false, 0,
                    fCheckOverlap);

  // Window
  G4double windowW = airW;
  G4double windowH = airH;

  G4Box *windowS =
      new G4Box("Window", windowW / 2., windowH / 2., fWindowT / 2.);
  G4LogicalVolume *windowLV =
      new G4LogicalVolume(windowS, fWindowMat, "Window");
  visAttributes = new G4VisAttributes(G4Colour::Green());
  windowLV->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  G4double windowZPos = -fWindowT / 2.;
  G4ThreeVector windowPos = G4ThreeVector(0., 0., windowZPos);
  fWindowPV = new G4PVPlacement(nullptr, windowPos, windowLV, "Window", worldLV,
                                false, 0, fCheckOverlap);

  G4VPhysicalVolume *worldPV = new G4PVPlacement(
      nullptr, G4ThreeVector(), worldLV, "World", 0, false, 0, fCheckOverlap);
  return worldPV;
}

void E6DetectorConstruction::ConstructSDandField()
{
  // Sensitive Detectors
  G4VSensitiveDetector *SD = new E6SD("SD", "HC");
  G4SDManager::GetSDMpointer()->AddNewDetector(SD);

  G4LogicalVolumeStore *lvStore = G4LogicalVolumeStore::GetInstance();
  for (auto &&lv : *lvStore) {
    if (lv->GetName().contains("Air")) SetSensitiveDetector(lv->GetName(), SD);
  }
}

void E6DetectorConstruction::DefineCommands()
{
  fMessenger = new G4GenericMessenger(this, "/E6/Geometry/", "For geometries");

  G4GenericMessenger::Command &windowTCmd = fMessenger->DeclareMethodWithUnit(
      "WindowThickness", "mm", &E6DetectorConstruction::SetWindowT,
      "Set the thickness of the window.");
  windowTCmd.SetParameterName("thickness", true);
  windowTCmd.SetRange("thickness>=0. && thickness<=2000.");
  windowTCmd.SetDefaultValue("3.0");
}

void E6DetectorConstruction::SetWindowT(G4double t)
{
  fWindowT = t;
  if (t > 0.) {
    G4Box *window = (G4Box *)(fWindowPV->GetLogicalVolume()->GetSolid());
    window->SetZHalfLength(fWindowT / 2.);

    // change position
    G4ThreeVector windowPos = G4ThreeVector(0., 0., -fWindowT / 2.);
    fWindowPV->SetTranslation(windowPos);
  } else {  // temporary.  exit is better?
    G4cout << "No thickness? OK, material of window is changed to vacuum."
           << G4endl;
    G4LogicalVolume *windowLV = fWindowPV->GetLogicalVolume();
    windowLV->SetMaterial(fVacuumMat);
  }

  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
