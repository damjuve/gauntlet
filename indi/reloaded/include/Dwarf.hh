#ifndef DWARF_HH
#define DWARF_HH

#include "APlayer.hh"

class Dwarf : public APlayer
{
public:
  Dwarf(irr::IrrlichtDevice & device,
	EventReceiver const & events,
	Camera & camera,
	irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
	std::list<ACharacter*> & list,
	irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Dwarf();
  
  virtual void setAnimation(ACharacter::Animation anim);
  
  void 		 addToSceneManager(irr::scene::ISceneManager *sceneManager,
				   irr::scene::ISceneNode *parent,
				   irr::video::IVideoDriver *driver);
  AProjectile	*getProjectile(irr::video::IVideoDriver *driver);
  virtual void	setHp(int dmg);
};

#endif // DWARF_HH
