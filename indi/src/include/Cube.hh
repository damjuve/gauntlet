//
// cube.hh for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Tue May 31 18:20:37 2016 Erik Dallemagne
// Last update Sat Jun  4 00:52:33 2016 Erik Dallemagne
//

#ifndef CUBE_HH_
# define CUBE_HH_

# include "AEntity.hh"

class				Cube : private AEntity
{
private:
  float				_size;
  irr::scene::ITriangleSelector	*_cube_selector;

public:
  Cube(float size, irr::core::vector3df const &pos, irr::core::vector3df const &rotation,
       irr::core::vector3df const &scale);
  ~Cube();

  void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);

  void	addToSelector(irr::scene::IMetaTriangleSelector *m_selector);

  irr::scene::ISceneNode const	*getNode() const;
};

#endif
