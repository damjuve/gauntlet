//
// Porjectile.cpp for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Sat Jun  4 00:58:21 2016 Erik Dallemagne
// Last update Sun Jun  5 14:06:55 2016 Erik Dallemagne
//

#include <iostream>
#include "Exceptions.hh"
#include "Projectile.hh"

Projectile::Projectile( irr::core::vector3df const &direction,
			irr::core::vector3df const &pos, irr::core::vector3df const &rotation,
		       irr::core::vector3df const &scale)
  : AEntity(pos, rotation, scale)
{
  _node = NULL;
  _speed = 1;
  _direction = direction;
  _prev_pos = pos;
}

Projectile::~Projectile()
{}

void	Projectile::addToSceneManager(irr::scene::ISceneManager *sceneManager, irr::scene::ISceneNode *parent,
				irr::video::IVideoDriver *driver)
{
  _node = sceneManager->addCubeSceneNode(1, parent,
					 -1, _position,
					 irr::core::vector3df(0, 0, 0),
					 irr::core::vector3df(1, 1, 1));
  if (!_node)
    throw exception::IrrlichtException("addCubeSceneNode");

  _node->setMaterialTexture(0, driver->getTexture("./media/cube.jpg"));
}

bool	Projectile::Launch(irr::scene::ISceneManager *sceneManager, std::list<ACharacter *> &list)
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
	  if ((tmp.X == pos.X || (tmp.X >= pos.X - 1 && tmp.X <= pos.X + 1)) &&
	      (tmp.Z == pos.Z || (tmp.Z >= pos.Z - 1 && tmp.Z <= pos.Z + 1)))
	    {
	      sceneManager->addToDeletionQueue((*it)->getNode());
	      (*it)->_isAlive = false;
	      list.erase(it);
	      return (false);
	    }
	}
    }
  return (true);
}

irr::scene::ISceneNode	* Projectile::getNode() const
{
  return (_node);
}

void  Projectile::addToSelector(irr::scene::ISceneManager *,
                              irr::scene::IMetaTriangleSelector *)
{}

void 	Projectile::addCollision(irr::scene::ISceneManager *sceneManager,
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
