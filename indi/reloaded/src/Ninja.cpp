#include "Ninja.hh"
#include "Sword.hh"

Ninja::Ninja(irr::IrrlichtDevice & device,
	     EventReceiver const & events,
	     Camera & camera,
	     irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
	     std::list<ACharacter*> & list,
	     irr::core::vector3df const& position)
  : APlayer(device,
	    events,
	    camera,
	    keymap,
	    "./media/model/ninja.b3d",
	    list,
	    irr::core::vector3df(1.5f, 0.2f, 1.5f),
	    position,
	    irr::core::vector3df(0, 90, 0),
	    irr::core::vector3df(0.8f, 0.8f, 0.8f),
	    2800,
	    80,
	    0.6f)
{}

Ninja::~Ninja()
{}

void 		Ninja::setAnimation(ACharacter::Animation anim)
{
  if (anim == ACharacter::EANIM_STAND)
    _node->setFrameLoop(0, 0);
  if (anim == ACharacter::EANIM_RUN)
    _node->setFrameLoop(0, 12);
  if (anim == ACharacter::EANIM_SHOOT)
    _node->setFrameLoop(58, 66);
  if (anim == ACharacter::EANIM_DIE)
    _node->setFrameLoop(173, 180);
  _node->setAnimationSpeed(15);
}

AProjectile		*Ninja::getProjectile(irr::video::IVideoDriver *driver)
{
  return (new Sword(driver, getPosition(), getDirection(), getRotation()));
}
