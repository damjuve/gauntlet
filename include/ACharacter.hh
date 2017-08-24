#ifndef ACHARACTER_HH
#define ACHARACTER_HH

#include <string>
#include <irrlicht.h>
#include "AEntity.hh"
#include "AProjectile.hh"

class		AProjectile;

class ACharacter : public AEntity
{
private:
  std::string 					_path_mesh;
  irr::core::vector3df 			_box;
  int							_hp;

protected:
  int					_damage;
  irr::core::vector3df 			_direction;
  irr::scene::ITextSceneNode	*_text;

protected:
  irr::IrrlichtDevice & 		_device;
  irr::scene::IAnimatedMesh 			* _mesh;
  irr::scene::IAnimatedMeshSceneNode		* _node;
  AProjectile					*_projectile;

public:
  ACharacter(irr::IrrlichtDevice & device,
	     std::string const& path_mesh,
	     irr::core::vector3df const& collisionBox,
	     irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0),
	     irr::core::vector3df const& rotation = irr::core::vector3df(0, 0, 0),
	     irr::core::vector3df const& scale = irr::core::vector3df(1, 1, 1),
	     int hp = 600,
	     int damage = 3);
	virtual ~ACharacter();

	virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
					  irr::scene::ISceneNode *parent,
					  irr::video::IVideoDriver *driver);

  virtual void	addToSelector(irr::scene::ISceneManager *sceneManager,
			      irr::scene::IMetaTriangleSelector *m_selector);

  void 			addCollision(irr::scene::ISceneManager *sceneManager,
				     irr::scene::IMetaTriangleSelector *meta_selector);


  int				getHp() const;
  void				setHp(int dmg);

  virtual irr::scene::ISceneNode 	*getNode() const;

public:
	void 			move(irr::core::vector3df const& direction,
						 irr::f32 range = 1.0f);

public:
	enum Animation
	{
		EANIM_STAND,
		EANIM_RUN,
		EANIM_SHOOT,
		EANIM_DIE
	};

  virtual void 	setAnimation(Animation anim) = 0;
  irr::core::vector3df getDirection();

  virtual void update(irr::scene::ISceneManager *sm,
		      irr::video::IVideoDriver *d,
		      irr::scene::IMetaTriangleSelector *s) = 0;
};

#endif // ACHARACTER_HH
