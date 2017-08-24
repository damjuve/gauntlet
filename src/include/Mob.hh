#ifndef MOB_HH
#define MOB_HH

#include <list>
#include "ACharacter.hh"

class Mob : public ACharacter
{
private:
  std::list<ACharacter *>	&_list;
  int		_range = 50;


public:
  Mob(irr::IrrlichtDevice & device, std::list<ACharacter *> &list, irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0));
  virtual ~Mob();

  virtual void	setAnimation(ACharacter::Animation anim);

  void		addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);

  void		update(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver,
		       irr::scene::IMetaTriangleSelector *m_selector);
};

#endif // MOB_HH
