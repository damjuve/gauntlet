#include <math.h>
#include "AEnnemy.hh"

AEnnemy::AEnnemy(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
		 irr::core::vector3df const& position,
		 int range, int hp, int dmg, irr::core::vector3df const& scale)
  : ACharacter(device, "./media/model/yodan.mdl",
	       irr::core::vector3df(7.5f, 20, 7.5f),
	       position,
	       irr::core::vector3df(0, 0, 0),
	       scale,
	       hp,
	       dmg),
    _list(list),
    _range(range)
{}

AEnnemy::~AEnnemy()
{}

void	AEnnemy::setAnimation(ACharacter::Animation anim)
{
  if (anim == ACharacter::EANIM_STAND)
    _node->setFrameLoop(0, 0);
  if (anim == ACharacter::EANIM_RUN)
    _node->setFrameLoop(100, 121);
  if (anim == ACharacter::EANIM_SHOOT)
    _node->setFrameLoop(691, 703);
  if (anim == ACharacter::EANIM_DIE)
    _node->setFrameLoop(450, 465);
  _node->setAnimationSpeed(15);
}

void	AEnnemy::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				   irr::scene::ISceneNode *parent,
				   irr::video::IVideoDriver *driver)
{
  ACharacter::addToSceneManager(sceneManager, parent, driver);
  _node->getMaterial(0).Lighting = true;
}

void	AEnnemy::update(irr::scene::ISceneManager *sceneManager,
		    irr::video::IVideoDriver *driver,
		    irr::scene::IMetaTriangleSelector *m_selector)
{
  (void)(*m_selector);
  (void)(*driver);
  (void)(*sceneManager);
  irr::core::vector3df	dir(0, 0, 0);
  irr::core::vector3df	tmp(0, 0, 0);
  std::list<ACharacter *>::iterator it = _list.begin();
  float		norme;

  dir = (*it)->getPosition() - _node->getPosition();
  norme = NORM(dir.X, dir.Z);
  while (++it != _list.end())
    {
      tmp = (*it)->getPosition() - _node->getPosition();
      if (NORM(tmp.X, tmp.Z) < norme)
   	{
   	  dir = tmp;
	  norme = NORM(dir.X, dir.Z);
  	}
    }
  if (norme > 25 && norme < _range * _range)
    move(dir, 0.01f);
  else
    move(irr::core::vector3df(0, 0, 0), 0);
  for (it = _list.begin(); it != _list.end();)
    {
      tmp = (*it)->getPosition() - _node->getPosition();
      if (NORM(tmp.X, tmp.Z) <= 26)
	{
	  setAnimation(ACharacter::EANIM_SHOOT);
	  (*it)->setHp(_damage);
	}
      if ((*it)->getHp() <= 0)
	{
	  (*it)->setAnimation(ACharacter::EANIM_DIE);
	  sceneManager->addToDeletionQueue((*it)->getNode());
	  std::list<ACharacter *>::iterator  old = it;
	  ++it;
	  _list.erase(old);
	}
      else
	++it;
    }
  float	angle = atan2(dir.X, dir.Z) * 180 / 3.14159265;
  _node->setRotation(irr::core::vector3df(0, angle - 90, 0));
}
