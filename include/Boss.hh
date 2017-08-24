#ifndef BOSS_HH
#define BOSS_HH

#include <list>
#include "AEnnemy.hh"

class Boss : public AEnnemy
{
public:
  Boss(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
       irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Boss();
};

#endif // BOSS_HH
