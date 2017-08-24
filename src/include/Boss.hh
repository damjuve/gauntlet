#ifndef BOSS_HH
#define BOSS_HH

#include <list>
#include "ACharacter.hh"

class Boss : public ACharacter
{
private:
  std::list<ACharacter *>	&_list;
  int		_range = 50;


public:
  Boss(irr::IrrlichtDevice & device, std::list<ACharacter *> &list, irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Boss();

  virtual void	setAnimation(ACharacter::Animation anim);

  void		addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);

  void		update(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver,
		       irr::scene::IMetaTriangleSelector *m_selector);
};

#endif // BOSS_HH
