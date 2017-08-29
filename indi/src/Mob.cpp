
#include "Mob.hh"

Mob::Mob(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
	   irr::core::vector3df const& position)
  : AEnnemy(device, list, position, 50, 500, 3, irr::core::vector3df(0.1f, 0.1f, 0.1f))
{}

Mob::~Mob()
{}
