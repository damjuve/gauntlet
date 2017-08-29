#include "Faerie.hh"
#include "Fireball.hh"

Faerie::Faerie(irr::IrrlichtDevice & device,
	       EventReceiver const & events,
	       Camera & camera,
	       irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
	       std::list<ACharacter*> & list,
	       irr::core::vector3df const& position)
  : APlayer(device,
	    events,
	    camera,
	    keymap,
	    "./media/model/faerie.md2",
	    list,
	    irr::core::vector3df(1.5f, 5, 1.5f),
	    position,
	    irr::core::vector3df(0, 0, 0),
	    irr::core::vector3df(0.18f, 0.18f, 0.18f),
	    800,
	    400,
	    0.3f)
{}

Faerie::~Faerie()
{}

void 		Faerie::setAnimation(ACharacter::Animation anim)
{
	if (anim == ACharacter::EANIM_STAND)
			_node->setMD2Animation(irr::scene::EMAT_STAND);
	if (anim == ACharacter::EANIM_RUN)
			_node->setMD2Animation(irr::scene::EMAT_RUN);
	if (anim == ACharacter::EANIM_SHOOT)
			_node->setMD2Animation(irr::scene::EMAT_ATTACK);
	if (anim == ACharacter::EANIM_DIE)
			_node->setMD2Animation(irr::scene::EMAT_FALLBACK);
	_node->setAnimationSpeed(15);
}

void		Faerie::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				                      irr::scene::ISceneNode *parent,
		                              irr::video::IVideoDriver *driver)
{
  APlayer::addToSceneManager(sceneManager, parent, driver);
  _node->setMaterialTexture(0, driver->getTexture("./media/model/faerie.bmp"));
  _lifebar->setPosition(irr::core::vector3df(0, 50, 0));
  _lifebar->setScale(irr::core::vector3df(4, 4, 15));

}

AProjectile		*Faerie::getProjectile(irr::video::IVideoDriver *driver)
{
  return (new Fireball(driver, getDirection(), getPosition(), getRotation()));
}

void	Faerie::setHp(int dmg)
{
  ACharacter::setHp(dmg);
  _lifebar->setScale(irr::core::vector3df(4, 4, (float)_hp*15/(float)_maxhp));
}
