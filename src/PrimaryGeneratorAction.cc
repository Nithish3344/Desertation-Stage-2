#include "PrimaryGeneratorAction.hh"


#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

namespace TC
{
  PrimaryGeneratorAction::PrimaryGeneratorAction()
  {
    fParticleGun = new G4GeneralParticleSource();
  }  

  PrimaryGeneratorAction::~PrimaryGeneratorAction()
  {
    delete fParticleGun;
  }


  void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
  {
    fParticleGun->GeneratePrimaryVertex(anEvent);
  } 
}
