#ifndef	AENNEMY_HH_
# define AENNEMY_HH_

#include "ACharacter.hh"

# define	NORM(x,y) (x * x + y * y)

class		AEnnemy : public ACharacter
{
private:
  std::list<ACharacter *>	&_list;
  int				_range;

public:
  AEnnemy(irr::IrrlichtDevice & device, std::list<ACharacter *> &list,
	  irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0),
	  int range = 50, int hp = 50, int dmg = 50,
	  irr::core::vector3df const& scale = irr::core::vector3df(0.1f, 0.1f, 0.1f));
  virtual ~AEnnemy();

  virtual void	setAnimation(ACharacter::Animation anim);
  void		addToSceneManager(irr::scene::ISceneManager *sceneManager,
				  irr::scene::ISceneNode *parent,
				  irr::video::IVideoDriver *driver);
  void		update(irr::scene::ISceneManager *,
		       irr::video::IVideoDriver *,
		       irr::scene::IMetaTriangleSelector *);
};

#endif
