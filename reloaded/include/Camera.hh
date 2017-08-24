//
// Camera.hh for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Wed Jun  1 17:24:44 2016 Erik Dallemagne
// Last update Sun Jun  5 19:48:59 2016 romain semanaz
//

#ifndef CAMERA_HH_
# define CAMERA_HH_

#include <list>
#include "ACharacter.hh"

class				Camera : public AEntity
{
private:
  irr::scene::ICameraSceneNode	*_node;
  irr::core::vector3df		_target;
  std::list<ACharacter *>	&_list;
public:
  Camera(irr::core::vector3df const &pos,
	 irr::core::vector3df const &target, std::list<ACharacter *> &list);
  ~Camera();

  irr::core::vector3df	getPos() const;
  irr::core::vector3df	getTarget() const;

  bool			centerView();

  virtual void			addToSceneManager(irr::scene::ISceneManager *sceneManager,
					  irr::scene::ISceneNode *parent,
					  irr::video::IVideoDriver *);
  virtual void			addToSelector(irr::scene::ISceneManager *sceneManager,
					      irr::scene::IMetaTriangleSelector *m_selector);

  virtual irr::core::vector3df	getDirection();

  virtual irr::scene::ISceneNode	*getNode() const;
};

#endif
