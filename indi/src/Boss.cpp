#include "Boss.hh"

Boss::Boss(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
	   irr::core::vector3df const& position)
  : AEnnemy(device, list, position, 100, 10000, 200, irr::core::vector3df(0.5f, 0.5f, 0.5f))
{}

Boss::~Boss()
{}
