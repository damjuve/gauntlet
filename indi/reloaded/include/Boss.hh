#ifndef BOSS_HH
#define BOSS_HH

#include <list>
#include "AEnnemy.hh"

class Boss : public AEnnemy
{
public:
  Boss(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
       irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Boss();

  virtual void addToSceneManager(irr::scene::ISceneManager *sceneManager,
				 irr::scene::ISceneNode *parent,
				 irr::video::IVideoDriver *driver);

  virtual void	setHp(int);
  virtual void update(irr::scene::ISceneManager *sceneManager,
		    irr::video::IVideoDriver *driver,
		      irr::scene::IMetaTriangleSelector *m_selector);
};

#endif // BOSS_HH
