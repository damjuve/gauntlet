//
// IEntity.hh for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Tue May 31 18:15:05 2016 Erik Dallemagne
// Last update Wed Jun  1 14:37:49 2016 Erik Dallemagne
//

#ifndef IENTITY_HH_
# define IENTITY_HH_

# include <irrlicht.h>

class		IEntity
{
public:
  virtual ~IEntity() {}
  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver) = 0;

  virtual void	addToSelector(irr::scene::IMetaTriangleSelector *m_selector) = 0;
};

#endif
