#ifndef TC_PRIMARY_GEN_HH
#define TC_PRIMARY_GEN_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh" 
#include "globals.hh"
namespace TC {


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  ~PrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource* fParticleGun;
};
}
#endif
