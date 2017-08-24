#ifndef SWORD_HH
#define SWORD_HH

#include "AProjectile.hh"

class Sword : public AProjectile
{
private:
  irr::video::IVideoDriver *_driver;
public:
  Sword(irr::video::IVideoDriver *driver, irr::core::vector3df const& direction,
	irr::core::vector3df const& position, irr::core::vector3df const& rotation);
  ~Sword();

  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);
};

#endif // SHURIKEN_HH
