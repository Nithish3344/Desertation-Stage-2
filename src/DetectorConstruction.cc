#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"

namespace TC {
    G4VPhysicalVolume* DetectorConstruction::Construct() {

        // Get nist material manager
        G4NistManager* nist = G4NistManager::Instance();


        // Start with constructing the world:
        G4double worldSize = 150 * cm,shieldSize=50.0 * cm;
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
        G4Material* Osmium = nist->FindOrBuildMaterial("G4_Os");
        G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");
        G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
        G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");
        G4Material* gold = nist->FindOrBuildMaterial("G4_Au");

        G4Element* elementO = nist->FindOrBuildElement("O");
        G4Element* elementSi = nist->FindOrBuildElement("Si");
        G4Element* elementAl = nist->FindOrBuildElement("Al");
        G4Element* elementCa = nist->FindOrBuildElement("Ca");
        G4Element* elementC = nist->FindOrBuildElement("C");
        G4Element* elementH = nist->FindOrBuildElement("H");    
        G4Element* elementMg = nist->FindOrBuildElement("Mg");    
        G4Element* elementFe = nist->FindOrBuildElement("Fe");    
        G4Element* elementB = nist->FindOrBuildElement("B");
        G4Element* elementP = nist->FindOrBuildElement("P");  
        G4Element* elementS = nist->FindOrBuildElement("S");       

        G4double density = 2.34*g/cm3;

        G4Material* concreteMaterial = new G4Material("Concrete", density, 6); // "Concrete" is the material name, and 6 is the number of elements.

        concreteMaterial->AddElement(elementO, 0.40);  
        concreteMaterial->AddElement(elementSi, 0.12);
        concreteMaterial->AddElement(elementCa, 0.12);
        concreteMaterial->AddElement(elementC, 0.23);
        concreteMaterial->AddElement(elementH, 0.10);
        concreteMaterial->AddElement(elementMg, 0.03);


        G4double density_env = 4.0 * g/cm3;
        G4Material* FeB = new G4Material("FeB", 4.0* g/cm3, 7);
            FeB->AddElement(elementAl, 0.01);  
            FeB->AddElement(elementSi, 0.02);
            FeB->AddElement(elementP, 0.0005);
            FeB->AddElement(elementC, 0.005);
            FeB->AddElement(elementS, 0.0005);
            FeB->AddElement(elementFe, 0.794);
            FeB->AddElement(elementB, 0.17);
        G4Material* env_mat = new G4Material("env_mat", density_env,  2);
        env_mat->AddMaterial(concreteMaterial,  0* perCent);
        env_mat->AddMaterial(FeB , 100* perCent);
       

        auto solidWorld = new G4Box("World",
            worldSize,
            worldSize,
            worldSize);

        auto logicWorld = new G4LogicalVolume(solidWorld,
            vacuum,
            "World");

        auto physWorld = new G4PVPlacement(nullptr,
            G4ThreeVector(),
            logicWorld,
            "World",
            nullptr,
            false,
            0);
 G4double  radius =10.0*cm,detXYZ = radius ,ht = 0.0001 * cm;
 shieldSize=radius;
// This is sheilder 
        auto solidshield = new G4Box("Shield",
            shieldSize,
            shieldSize,
            shieldSize);

        auto logicShield = new G4LogicalVolume(solidshield,concreteMaterial
            ,
            "Shield");

        auto physShield = new G4PVPlacement(nullptr,
            G4ThreeVector(),
            logicShield,
            "Shield",
            logicWorld,
            false,
            0);


        // create our detector
       
        

        // different material options to test out
       

        G4Material* detectorMat = vacuum;

        G4ThreeVector detPos1 = G4ThreeVector(0, 0, radius);
        G4ThreeVector detPos2 = G4ThreeVector(0, 0,-1*radius);
        G4ThreeVector detPos3 = G4ThreeVector(0, radius,0);
        G4ThreeVector detPos4 = G4ThreeVector(0,-1*radius,0);
        G4ThreeVector detPos5 = G4ThreeVector(radius,0, 0);
        G4ThreeVector detPos6 = G4ThreeVector(-1*radius,0, 0);

        
        auto solidDetector1 = new G4Box("SolidDetector1",
            detXYZ,
            detXYZ,
            ht
        );
        auto solidDetector2 = new G4Box("SolidDetector2",
            detXYZ,
            ht,
            detXYZ
        );

        auto solidDetector3 = new G4Box("SolidDetector3",
            ht,
            detXYZ,
            detXYZ
        );
        
        auto logicDetector1 = new G4LogicalVolume(solidDetector1,
            detectorMat,
            "LogicDetector1"
        );
        auto logicDetector2 = new G4LogicalVolume(solidDetector2,
            detectorMat,
            "LogicDetector2"
        );
        auto logicDetector3 = new G4LogicalVolume(solidDetector3,
            detectorMat,
            "LogicDetector3"
        );


        auto physDetector1 = new G4PVPlacement(nullptr,
            detPos1,
            logicDetector1,
            "PhysDetector1",
            logicWorld,
            false,
        0);
        auto physDetector2 = new G4PVPlacement(nullptr,
            detPos2,
            logicDetector1,
            "PhysDetector2",
            logicWorld,
            false,
        0);
        auto physDetector3 = new G4PVPlacement(nullptr,
            detPos3,
            logicDetector2,
            "PhysDetector3",
            logicWorld,
            false,
        0);
        auto physDetector4 = new G4PVPlacement(nullptr,
            detPos4,
            logicDetector2,
            "PhysDetector4",
            logicWorld,
            false,
        0);
        auto physDetector5 = new G4PVPlacement(nullptr,
            detPos5,
            logicDetector3,
            "PhysDetector5",
            logicWorld,
            false,
        0);
        auto physDetector6 = new G4PVPlacement(nullptr,
            detPos6,
            logicDetector3,
            "PhysDetector6",
            logicWorld,
            false,
        0);









        return physWorld;
    }


    void DetectorConstruction::ConstructSDandField() {

        // Add our sensitive detector to the detector of our choice

        // Name our SD and our hitsCollection
        G4String SDname1 = "SD1";
        G4String HCname1 = "SDHitsCollection1";
        G4String SDname2 = "SD2";
        G4String HCname2 = "SDHitsCollection2";
        G4String SDname3 = "SD3";
        G4String HCname3 = "SDHitsCollection3";

        // Create our SD
        auto SD1 = new SensitiveDetector(SDname1, HCname1);
        auto SD2 = new SensitiveDetector(SDname2, HCname2);
        auto SD3 = new SensitiveDetector(SDname3, HCname3);

        // Add it to the SDManager Singleton
        G4SDManager::GetSDMpointer()->AddNewDetector(SD1);
        G4SDManager::GetSDMpointer()->AddNewDetector(SD2);
        G4SDManager::GetSDMpointer()->AddNewDetector(SD3);


        

        // Assign SD to the volume we want
        SetSensitiveDetector("LogicDetector1", SD1);
        SetSensitiveDetector("LogicDetector2", SD2);
        SetSensitiveDetector("LogicDetector3", SD3);
    }
}