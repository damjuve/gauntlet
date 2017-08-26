
#include "Mob.hh"

Mob::Mob(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
	 irr::core::vector3df const& position)
  : AEnnemy(device, list, position, 50, 0.016f, 5, 500, 3, irr::core::vector3df(0.1f, 0.1f, 0.1f),
	    irr::core::vector3df(2.5f, 6, 2.5f))
{}

Mob::~Mob()
{}

void 	Mob::addToSceneManager(irr::scene::ISceneManager *sceneManager,
			       irr::scene::ISceneNode *parent,
			       irr::video::IVideoDriver *driver)
{
  ACharacter::addToSceneManager(sceneManager, parent, driver);
  _lifebar->setPosition(irr::core::vector3df(0, 80, 0));
  _lifebar->setScale(irr::core::vector3df(8, 8, 40));
}

void	Mob::setHp(int dmg)
{
  ACharacter::setHp(dmg);
  _lifebar->setScale(irr::core::vector3df(8, 8, (float)_hp*40/(float)_maxhp));
}
