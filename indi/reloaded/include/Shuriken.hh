#ifndef SHURIKEN_HH
#define SHURIKEN_HH

#include "AProjectile.hh"

class Shuriken : public AProjectile
{
private:
  irr::video::IVideoDriver *_driver;
public:
  Shuriken(irr::video::IVideoDriver *driver, irr::core::vector3df const& directio,
	   irr::core::vector3df const& position, irr::core::vector3df const& rotation);
  ~Shuriken();


  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);
};

#endif // SHURIKEN_HH
