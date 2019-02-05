#include "E6ActionInitialization.hpp"
#include "E6PrimaryGeneratorAction.hpp"
#include "E6RunAction.hpp"
#include "E6EventAction.hpp"


E6ActionInitialization::E6ActionInitialization()
   : G4VUserActionInitialization()
{}

E6ActionInitialization::~E6ActionInitialization()
{}

void E6ActionInitialization::BuildForMaster() const
{
   SetUserAction(new E6RunAction());
}

void E6ActionInitialization::Build() const
{
   SetUserAction(new E6PrimaryGeneratorAction());
   SetUserAction(new E6RunAction());
   SetUserAction(new E6EventAction());
}
