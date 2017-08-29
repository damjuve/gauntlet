//
// Projectile.hh for indie in /home/dallem_e/rendu/cpp_indie_studio/rendu
//
// Made by Erik Dallemagne
// Login   <dallem_e@epitech.net>
//
// Started on  Sat Jun  4 00:58:24 2016 Erik Dallemagne
// Last update Thu Jun  9 20:00:02 2016 adrien seguin
//

#ifndef PROJECTILE_HH_
# define PROJECTILE_HH_

# include <list>
# include "AEntity.hh"
# include "ACharacter.hh"

class				ACharacter;

class				AProjectile : public AEntity
{
protected:
  irr::f32			_speed;
  irr::core::vector3df		_direction;
  irr::scene::IMeshSceneNode	*_node;
  irr::core::vector3df		_prev_pos;
public:
  AProjectile(irr::core::vector3df const &direction,
	     irr::core::vector3df const &pos = irr::core::vector3df(0, 0, 0),
	     irr::core::vector3df const &rotation = irr::core::vector3df(0, 0, 0),
	     irr::core::vector3df const &scale = irr::core::vector3df(1, 1, 1));
  ~AProjectile();

  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver) = 0;

  virtual void  addToSelector(irr::scene::ISceneManager *sceneManager,
                              irr::scene::IMetaTriangleSelector *m_selector);

  void		addCollision(irr::scene::ISceneManager *sceneManager,
			     irr::scene::IMetaTriangleSelector *meta_selector);
  bool		Launch(irr::scene::ISceneManager *sceneManager, std::list<ACharacter *> &list, int damage);
  virtual irr::core::vector3df getDirection();

  irr::scene::ISceneNode 	*getNode() const;
};

#endif
