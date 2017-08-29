//
// Porjectile.cpp for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Sat Jun  4 00:58:21 2016 Erik Dallemagne
// Last update Thu Jun  9 19:59:06 2016 adrien seguin
//

#include <iostream>
#include "Exceptions.hh"
#include "AProjectile.hh"

AProjectile::AProjectile( irr::core::vector3df const &direction,
			irr::core::vector3df const &pos, irr::core::vector3df const &rotation,
		       irr::core::vector3df const &scale)
  : AEntity(pos, rotation, scale)
{
  _node = NULL;
  _speed = 1;
  _direction = direction;
  _prev_pos = pos;
}

AProjectile::~AProjectile()
{}


bool	AProjectile::Launch(irr::scene::ISceneManager *sceneManager, std::list<ACharacter *> &list, int damage)
{
  irr::core::vector3df	pos;
  irr::core::vector3df	tmp;

  pos = getPosition();
  pos.X = pos.X + _speed *_direction.X;
  pos.Z = pos.Z + _speed *_direction.Z;

  setPosition(pos);
  if (pos == _prev_pos)
    return (false);
  _prev_pos = pos;
  for (std::list<ACharacter *>::iterator it = list.begin(); it != list.end(); it++)
    {
      if ((*it)->getNode() != NULL)
	{
	  tmp = (*it)->getPosition();
	  if ((tmp.X == pos.X || (tmp.X >= pos.X - 3 && tmp.X <= pos.X + 3)) &&
	      (tmp.Z == pos.Z || (tmp.Z >= pos.Z - 3 && tmp.Z <= pos.Z + 3)))
	    {
	      (*it)->setHp(damage);
	      if ((*it)->getHp() <= 0)
		{
		  (*it)->setAnimation(ACharacter::EANIM_DIE);
		  sceneManager->addToDeletionQueue((*it)->getNode());
		  // OnAnimationEnd((*it)->getNode());
		  list.erase(it);
		  return (false);
		}
	      return (false);
	    }
	}
    }
  return (true);
}

irr::core::vector3df	AProjectile::getDirection()
{
  return (_direction);
}

irr::scene::ISceneNode	* AProjectile::getNode() const
{
  return (_node);
}

void  AProjectile::addToSelector(irr::scene::ISceneManager *,
                              irr::scene::IMetaTriangleSelector *)
{}

void 	AProjectile::addCollision(irr::scene::ISceneManager *sceneManager,
							     irr::scene::IMetaTriangleSelector *meta_selector)
{
  irr::scene::ISceneNodeAnimator *anim =
    sceneManager->createCollisionResponseAnimator(
						  meta_selector,
						  _node,
						  irr::core::vector3df(1, 1, 1),
						  irr::core::vector3df(0, 0, 0),
						  irr::core::vector3df(0, 0, 0));
  _node->addAnimator(anim);
  anim->drop();
}
