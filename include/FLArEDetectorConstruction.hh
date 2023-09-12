#ifndef FLAREDETECTORCONSTRUCTION_HH
#define FLAREDETECTORCONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4String.hh>
#include <G4UniformMagField.hh>
#include <G4FieldManager.hh>
#include <G4AssemblyVolume.hh>

class G4LogicalVolume;
class FLArEDetectorConstructionMessenger;
class DetectorConstructionMaterial;

/**
 *
 * Obligatory class responsible for geometry - volumes, materials, fields, etc.
 *
 */

class FLArEDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    // Main method that has to be override in all detectors
    FLArEDetectorConstruction();
    ~FLArEDetectorConstruction();
    G4VPhysicalVolume* Construct() override;

    void ConstructSDandField() override;
    void SetDetMaterial(G4String detMaterial);
    void SetGeomOption(G4String detGeomOption);
    void saveGDML(G4bool i) { m_saveGdml = i; };
    void SetFieldValue(G4double val) { fFieldValue = val; }
    void UpdateGeometry();

  private:
    void DefineMaterial();

    G4LogicalVolume* worldLog;
    G4LogicalVolume* lArBoxLog;
    G4LogicalVolume* cryoInsulationLog;
    G4LogicalVolume* hadCatcherLogical;
    G4LogicalVolume* HadCalXCellLogical;
    G4LogicalVolume* HadCalYCellLogical;
    G4LogicalVolume* muonFinderLogical;
    G4LogicalVolume* MuonFinderXCellLogical;
    G4LogicalVolume* MuonFinderYCellLogical;
    G4LogicalVolume* HadAbsorLayersLogical;
    G4LogicalVolume* MuonFinderAbsorLayersLogical;
    G4LogicalVolume* TPCModuleLogical;
    G4String fDetMaterialName;
    G4String fDetGeomOption;
    G4double fFieldValue;
    G4bool m_saveGdml;

    G4LogicalVolume* FASER2MagnetLogical;
    G4LogicalVolume* TrackingVerScinBarLogical;
    G4LogicalVolume* TrackingHorScinBarLogical; 

    DetectorConstructionMaterial* LArBoxMaterials;
    FLArEDetectorConstructionMessenger* messenger;

    static G4ThreadLocal G4UniformMagField* magField;
    static G4ThreadLocal G4FieldManager* fieldMgr;
    static G4ThreadLocal G4UniformMagField* magFieldFASER2;
    static G4ThreadLocal G4FieldManager* fieldMgrFASER2;
};

#endif
