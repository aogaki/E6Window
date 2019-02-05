#include <iomanip>

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "E6Hit.hpp"


G4ThreadLocal G4Allocator<E6Hit> *E6HitAllocator = 0;


E6Hit::E6Hit()
   : G4VHit()
{}

E6Hit::~E6Hit()
{}

E6Hit::E6Hit(const E6Hit & /*right*/)
   : G4VHit()
{}

const E6Hit &
E6Hit::operator=(const E6Hit & /*right*/)
{
   return *this;
}

int E6Hit::operator==(const E6Hit & /*right*/) const
{
   return 0;
}
