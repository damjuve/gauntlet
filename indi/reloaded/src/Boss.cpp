#include "Boss.hh"

Boss::Boss(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
	   irr::core::vector3df const& position)
  : AEnnemy(device, list, position, 100, 0.005f, 22, 5000, 400,
	    irr::core::vector3df(0.4f, 0.4f, 0.4f),
	    irr::core::vector3df(7.5f, 10, 7.5f))
{}

Boss::~Boss()
{}

void 	Boss::addToSceneManager(irr::scene::ISceneManager *sceneManager,
			       irr::scene::ISceneNode *parent,
			       irr::video::IVideoDriver *driver)
{
  ACharacter::addToSceneManager(sceneManager, parent, driver);
  _lifebar->setPosition(irr::core::vector3df(35, 40, 0));
  _lifebar->setScale(irr::core::vector3df(8, 8, 40));
}


void	Boss::setHp(int dmg)
{
  ACharacter::setHp(dmg);
  _lifebar->setScale(irr::core::vector3df(8, 8, (float)_hp*40/(float)_maxhp));
}

void Boss::update(irr::scene::ISceneManager *sceneManager,
		    irr::video::IVideoDriver *driver,
		  irr::scene::IMetaTriangleSelector *m_selector)
{
  if (_nexthit == 0)
    AEnnemy::update(sceneManager, driver, m_selector);
  else
    _nexthit--;
}
