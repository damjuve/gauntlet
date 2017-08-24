#include "Exceptions.hh"
#include "Dwarf.hh"
#include "Axe.hh"

Dwarf::Dwarf(irr::IrrlichtDevice & device,
	     EventReceiver const & events,
	     Camera & camera,
	     irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
	     std::list<ACharacter*> & list,
	     irr::core::vector3df const& position)
  : APlayer(device,
	    events,
	    camera,
	    keymap,
	    "./media/model/dwarf.x",
	    list,
	    irr::core::vector3df(3.0f, 1, 3.0f),
	    position,
	    irr::core::vector3df(0, -90, 0),
	    irr::core::vector3df(0.1f, 0.1f, 0.1f),
	    4000,
	    45,
	    0.1f)
{}

Dwarf::~Dwarf()
{}

void 		Dwarf::setAnimation(ACharacter::Animation anim)
{
  if (anim == ACharacter::EANIM_STAND)
    _node->setFrameLoop(0, 0);
  if (anim == ACharacter::EANIM_RUN)
    _node->setFrameLoop(0, 10);
  if (anim == ACharacter::EANIM_SHOOT)
    _node->setFrameLoop(35, 49);
  if (anim == ACharacter::EANIM_DIE)
    _node->setFrameLoop(0, 0);
  _node->setAnimationSpeed(15);
}

void		Dwarf::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				                      irr::scene::ISceneNode *parent,
		                              irr::video::IVideoDriver *driver)
{
	APlayer::addToSceneManager(sceneManager, parent, driver);
	//_node->setMaterialTexture(0, driver->getTexture("./media/model/sydney.bmp"));
}

AProjectile		*Dwarf::getProjectile(irr::video::IVideoDriver *driver)
{
  return (new Axe(driver, getDirection(), getPosition(), getRotation()));
}
