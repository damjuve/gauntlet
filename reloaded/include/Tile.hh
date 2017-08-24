//
// Tile.hh for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Tue May 31 18:20:37 2016 Erik Dallemagne
// Last update Sun Jun  5 22:33:14 2016 adrien seguin
//

#ifndef MENU_TILE_HH_
# define MENU_TILE_HH_

# include <string>
# include "AEntity.hh"

class				Tile : public AEntity
{
private:
  std::string			_path;
  irr::scene::ISceneNode*	_node;

public:
  Tile(std::string const& path,
       irr::core::vector3df const& pos,
       irr::core::vector3df const& rotation = irr::core::vector3df(0, 0, 0),
       irr::core::vector3df const& scale = irr::core::vector3df(1, 1, 1));
  virtual ~Tile() {};

  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);
  virtual void	addToSelector(irr::scene::ISceneManager *sceneManager,
		      irr::scene::IMetaTriangleSelector *m_selector);
  irr::scene::ISceneNode	*getNode(void) const;
  virtual irr::core::vector3df	getDirection();
};

#endif /* !MENU_TILE_HH_ */
