//
// IEntity.hh for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Tue May 31 18:15:05 2016 Erik Dallemagne
// Last update Sun Jun  5 19:49:38 2016 romain semanaz
//

#ifndef AENTITY_HH_
# define AENTITY_HH_

# include <irrlicht.h>

class				AEntity
{
protected:
  irr::core::vector3df		_position;
  irr::core::vector3df		_rotation;
  irr::core::vector3df		_scale;

public:
  AEntity(irr::core::vector3df const &pos = irr::core::vector3df(0, 0, 0),
          irr::core::vector3df const &rotation = irr::core::vector3df(0, 0, 0),
      	  irr::core::vector3df const &scale = irr::core::vector3df(1, 1, 1));
  virtual ~AEntity();

  irr::core::vector3df		getPosition() const;
  irr::core::vector3df		getRotation() const;
  irr::core::vector3df		getScale() const;

  void				setPosition(irr::core::vector3df const &pos);
  void				setRotation(irr::core::vector3df const &rotation);
  void				setScale(irr::core::vector3df const &scale);

  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver) = 0;

  virtual void	addToSelector(irr::scene::ISceneManager *sceneManager,
                              irr::scene::IMetaTriangleSelector *m_selector) = 0;
  virtual    irr::core::vector3df getDirection() = 0;

private:
  virtual irr::scene::ISceneNode	*getNode() const = 0;
};

#endif
