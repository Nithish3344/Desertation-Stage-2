#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

namespace TC {
	void ActionInitialization::Build() const {
		SetUserAction(new PrimaryGeneratorAction);
	}

	void ActionInitialization::BuildForMaster() const {

	}
}