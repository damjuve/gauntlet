#ifndef NINJA_HH
#define NINJA_HH

#include "APlayer.hh"

class Ninja : public APlayer
{
public:
  Ninja(irr::IrrlichtDevice & device,
	EventReceiver const & events,
	Camera & camera,
	irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
	std::list<ACharacter*> & list,
	irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Ninja();


  virtual void setAnimation(ACharacter::Animation anim);
  AProjectile	*getProjectile(irr::video::IVideoDriver *driver);
};

#endif // NINJA_HH
