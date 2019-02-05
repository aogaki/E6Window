#ifndef E6ActionInitialization_h
#define E6ActionInitialization_h 1

#include <G4VUserActionInitialization.hh>
#include <globals.hh>


class E6ActionInitialization : public G4VUserActionInitialization
{
public:
   E6ActionInitialization();
   virtual ~E6ActionInitialization();

   virtual void BuildForMaster() const;
   virtual void Build() const;

private:
      
};

#endif
