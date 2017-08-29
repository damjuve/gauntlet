#include <iostream>
#include "Camera.hh"

Camera::Camera(irr::core::vector3df const &pos,
	       irr::core::vector3df const &target,std::list<ACharacter *> &list)
  : AEntity(pos, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 1, 1)), _list(list)
{
  _node = NULL;
  _target = target;
}

Camera::~Camera()
{}

bool			Camera::centerView()
{
  int			i = 0;
  float			z_tot = 0;
  float			x_tot = 0;

  for (std::list<ACharacter *>::const_iterator it = _list.begin(); it != _list.end(); it++)
    {
      x_tot += (*it)->getPosition().X;
      z_tot += (*it)->getPosition().Z;
      i++;
    }
  _target = irr::core::vector3df(x_tot / i, _target.Y, z_tot / i);
  _position = irr::core::vector3df(x_tot / i, _position.Y, (z_tot / i) - 25);
  _node->setPosition(_position);
  _node->setTarget(_target);
  for (std::list<ACharacter *>::const_iterator it = _list.begin(); it != _list.end(); it++)
    {
      if ((*it)->getPosition().X > _target.X + 45 || (*it)->getPosition().X < _target.X - 45)
	return (false);
      if ((*it)->getPosition().Z > _target.Z + 45 || (*it)->getPosition().Z < _target.Z - 45)
	return (false);
    }
  return (true);
}

void			Camera::addToSceneManager(irr::scene::ISceneManager *sceneManager,
					  irr::scene::ISceneNode *parent,
					  irr::video::IVideoDriver *)
{
  _node = sceneManager->addCameraSceneNode(parent, _position, _target);
}

void			Camera::addToSelector(irr::scene::ISceneManager *,
					      irr::scene::IMetaTriangleSelector *)
{}

irr::core::vector3df	Camera::getTarget() const
{
  return (_target);
}

irr::core::vector3df 	Camera::getDirection()
{
  return (irr::core::vector3df(0, 0, 0));
}

irr::scene::ISceneNode	*Camera::getNode() const
{
  return (_node);
}
