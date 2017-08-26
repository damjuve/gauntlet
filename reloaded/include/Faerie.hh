#ifndef FAERIE_HH
#define FAERIE_HH

#include "APlayer.hh"

class Faerie : public APlayer
{
public:
  Faerie(irr::IrrlichtDevice & device,
	 EventReceiver const & events,
	 Camera & camera,
	 irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
	 std::list<ACharacter*> & list,
	 irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Faerie();


  virtual void setAnimation(ACharacter::Animation anim);

  virtual void		addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);

  virtual void	setHp(int dmg);
  
  AProjectile	*getProjectile(irr::video::IVideoDriver *driver);
};

#endif // FAERIE_HH
