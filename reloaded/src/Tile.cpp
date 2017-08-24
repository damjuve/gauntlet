//
// Tile.cpp for indie in /home/seguin_e/rendu/indie_menu
//
// Made by adrien seguin
// Login   <seguin_e@epitech.net>
//
// Started on  Thu Jun  2 19:19:08 2016 adrien seguin
// Last update Sun Jun  5 22:17:40 2016 adrien seguin
//

#include <string>
#include <irrlicht.h>
#include "Tile.hh"

Tile::Tile(std::string const & path, irr::core::vector3df const& pos, irr::core::vector3df const& rotation, irr::core::vector3df const& scale) : AEntity(pos, rotation, scale), _path(path), _node(NULL)
{
}

void	Tile::addToSceneManager(irr::scene::ISceneManager *sceneManager, irr::scene::ISceneNode *parent, irr::video::IVideoDriver *driver)
{
  _node = sceneManager->addCubeSceneNode(20, parent,
					 -1, _position,
					 irr::core::vector3df(0, 0, 0),
					 irr::core::vector3df(1, 1, 1));
  if (!_node)
    return ;
  _node->setMaterialTexture(0, driver->getTexture(_path.c_str()));
  _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _node->setScale(irr::core::vector3df(3.75f, 0.57f, 0.10f));
}

void	Tile::addToSelector(irr::scene::ISceneManager *sceneManager,
			    irr::scene::IMetaTriangleSelector *m_selector)
{
  (void)sceneManager;
  (void)m_selector;
}

irr::core::vector3df	Tile::getDirection()
{
  return (irr::core::vector3df(0, 0, 0));
}


irr::scene::ISceneNode	*Tile::getNode() const
{
  return (this->_node);
}
