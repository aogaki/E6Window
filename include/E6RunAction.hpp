#ifndef E6RunAction_h
#define E6RunAction_h 1

#include <G4UserRunAction.hh>
#include <G4Run.hh>


class E6RunAction: public G4UserRunAction
{
public:
   E6RunAction();
   virtual ~E6RunAction();

   virtual void BeginOfRunAction(const G4Run *);
   virtual void EndOfRunAction(const G4Run *);

private:

};

#endif
