#ifndef A_PLAYER_HH
#define A_PLAYER_HH

#include "ACharacter.hh"
#include "Mob.hh"
#include "Camera.hh"
#include "EventReceiver.hh"

class APlayer : public ACharacter
{
public:
	enum KeyMap
	{
		EKEYMAP_LEFT = 0,
		EKEYMAP_RIGHT,
		EKEYMAP_TOP,
		EKEYMAP_BOTTOM,
		EKEYMAP_SHOOT,
		EKEYMAP_NB_KEY
	};

private:
	bool 				 _joy;
  Camera 	  	  & 	_camera;
  EventReceiver	const&		_events;
  irr::EKEY_CODE		_keymap[EKEYMAP_NB_KEY];
  std::list<ACharacter* > &	_list;
  float				_speed;

public:
  APlayer(irr::IrrlichtDevice & device,
	  EventReceiver const & events,
	  Camera & camera,
	  irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
	  std::string const & path_mesh,
	  std::list<ACharacter *> & _list,
	  irr::core::vector3df const& collisionBox,
	  irr::core::vector3df const& position = irr::core::vector3df(0, 0, 0),
	  irr::core::vector3df const& rotation = irr::core::vector3df(0, 0, 0),
	  irr::core::vector3df const& scale = irr::core::vector3df(1, 1, 1),
	  int hp = 2000,
	  int damage = 75,
	  float speed = 0.2f);
  virtual ~APlayer();

public:
  virtual void setAnimation(ACharacter::Animation anim) = 0;

  virtual void update(irr::scene::ISceneManager *sceneManager,
		      irr::video::IVideoDriver *driver,
		      irr::scene::IMetaTriangleSelector *m_selector);
  virtual AProjectile	*getProjectile(irr::video::IVideoDriver *driver) = 0;

  void 			setJoystick(bool active);
};

#endif // A_PLAYER_HH
