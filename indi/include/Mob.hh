#ifndef MOB_HH
#define MOB_HH

#include <list>
#include "AEnnemy.hh"

class Mob : public AEnnemy
{
public:
  Mob(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
      irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Mob();
};

#endif
