//
// AEntity.cpp for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Thu Jun  2 23:55:37 2016 Erik Dallemagne
// Last update Sun Jun  5 15:16:11 2016 Erik Dallemagne
//

#include "AEntity.hh"

AEntity::AEntity(irr::core::vector3df const &pos,
                 irr::core::vector3df const &rotation,
		             irr::core::vector3df const &scale)
{
  _position = pos;
  _rotation = rotation;
  _scale = scale;
}


AEntity::~AEntity()
{}

irr::core::vector3df	AEntity::getPosition() const
{
  if (getNode())
    return (getNode()->getPosition());
  return (_position);
}

irr::core::vector3df	AEntity::getRotation() const
{
  if (getNode())
    return (getNode()->getRotation());
  return (_rotation);
}

irr::core::vector3df	AEntity::getScale() const
{
  if (getNode())
    return (getNode()->getScale());
  return (_scale);
}

void			AEntity::setPosition(irr::core::vector3df const &pos)
{
  _position = pos;
  irr::scene::ISceneNode  *node = getNode();
  if (node != NULL)
    node->setPosition(_position);
}

void			AEntity::setRotation(irr::core::vector3df const &rotation)
{
  irr::scene::ISceneNode *node = getNode();
  if (node == NULL)
    _rotation = rotation;
  else
    node->setRotation(irr::core::vector3df(rotation.X + _rotation.X,
                                           rotation.Y + _rotation.Y,
                                           rotation.Z + _rotation.Z));
}

void			AEntity::setScale(irr::core::vector3df const &scale)
{
  irr::scene::ISceneNode *node = getNode();
   if (node == NULL)
    _scale = scale;
  else
    node->setRotation(irr::core::vector3df(scale.X + _scale.X,
                                           scale.Y + _scale.Y,
                                           scale.Z + _scale.Z));
}
