//
// cube.cpp for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Tue May 31 18:20:41 2016 Erik Dallemagne
// Last update Sun Jun  5 03:33:04 2016 Erik Dallemagne
//

#include <iostream>
#include "../include/Cube.hh"

Cube::Cube(float size, irr::core::vector3df const &pos, irr::core::vector3df const &rotation,
	   irr::core::vector3df const &scale)
  : AEntity(pos, rotation, scale)
{
  _node = NULL;
  _cube_selector = NULL;
  _size = size;
}

Cube::~Cube()
{}

void	Cube::addToSceneManager(irr::scene::ISceneManager *sceneManager, irr::scene::ISceneNode *parent,
				irr::video::IVideoDriver *driver)
{
  _node = sceneManager->addCubeSceneNode(_size, parent,
					 -1, _pos,
					 irr::core::vector3df(0, 0, 0),
					 irr::core::vector3df(1, 1, 1));
  if (!_node)
    return ;
  _node->setMaterialTexture(0, driver->getTexture("./media/cube.jpg"));
  _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _cube_selector = sceneManager->createOctreeTriangleSelector(_node->getMesh(), _node);
}

void	Cube::addToSelector(irr::scene::IMetaTriangleSelector *m_selector)
{
  _node->setTriangleSelector(_cube_selector);
  m_selector->addTriangleSelector(_cube_selector);
}

irr::scene::ISceneNode const	*getNode() const
{
  return (_node)
}
