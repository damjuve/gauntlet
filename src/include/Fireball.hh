#ifndef FIREBALL_HH
#define FIREBALL_HH

#include "AProjectile.hh"

class Fireball : public AProjectile
{
private:
  irr::video::IVideoDriver *_driver;
public:
  Fireball(irr::video::IVideoDriver *driver,
	   irr::core::vector3df const& direction,
	   irr::core::vector3df const& position,
	   irr::core::vector3df const& rotation);
  ~Fireball();

  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);

};

#endif // FIREBALL_HH
