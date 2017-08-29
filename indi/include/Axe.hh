#ifndef AXE_HH
#define AXE_HH

#include "AProjectile.hh"

class Axe : public AProjectile
{
private:
  irr::video::IVideoDriver *_driver;
public:
  Axe(irr::video::IVideoDriver *driver,
      irr::core::vector3df const& direction,
      irr::core::vector3df const& position,
      irr::core::vector3df const& rotation);
  ~Axe();

  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);
};

#endif // AXE_HH
