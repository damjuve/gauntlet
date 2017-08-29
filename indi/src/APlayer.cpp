#include <iostream>
#include "APlayer.hh"

APlayer::APlayer(irr::IrrlichtDevice & device,
		 EventReceiver const& events,
		 Camera & camera,
		 irr::EKEY_CODE keymap[EKEYMAP_NB_KEY],
		 std::string const & path_mesh,
		 std::list<ACharacter *> & list,
		 irr::core::vector3df const& collisionBox,
		 irr::core::vector3df const& position,
		 irr::core::vector3df const& rotation,
		 irr::core::vector3df const& scale,
		 int hp,
		 int damage,
		 float speed)
  : ACharacter(device, path_mesh, collisionBox, position, rotation, scale, hp, damage),
    _joy(false), _camera(camera), _events(events), _list(list), _speed(speed)
{
	for (unsigned int i = 0; i < EKEYMAP_NB_KEY; i++)
		_keymap[i] = keymap[i];
}

APlayer::~APlayer()
{}

void        APlayer::setJoystick(bool active)
{
    _joy = active;
}

void 		APlayer::update(irr::scene::ISceneManager *sceneManager,
				irr::video::IVideoDriver *driver,
				irr::scene::IMetaTriangleSelector *m_selector)
{
  irr::core::vector3df dir(0, 0, 0);

    if (_joy)
    {
        irr::SEvent::SJoystickEvent const& joystickData = _events.getJoystickState();

        dir.X = (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f);
        dir.Z = (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f);
        if (dir.X <= 0.5f && dir.X >= -0.5f)
            dir.X = 0;
        else
          dir.X = dir.X < 0 ? -1 : 1;
        if(dir.Z <= 0.5f && dir.Z >= -0.5f)
          dir.Z = 0;
        else
          dir.Z = dir.Z < 0 ? -1 : 1;
          std::cout << "JOY : " << dir.X << " " << dir.Z << std::endl;
    }
    else
    {
        if (_events.IsKeyDown(_keymap[EKEYMAP_TOP]))
         	dir.Z = 1;
        else if (_events.IsKeyDown(_keymap[EKEYMAP_BOTTOM]))
            dir.Z = -1;
        if (_events.IsKeyDown(_keymap[EKEYMAP_LEFT]))
            dir.X = -1;
        else if (_events.IsKeyDown(_keymap[EKEYMAP_RIGHT]))
    	    dir.X = 1;
    }

    if (dir.X == 0 && dir.Z == 0)
        move(dir, 0);
    else
    {
        irr::core::vector3df lastpos = _node->getPosition();
        move(dir, _speed);
        if (!_camera.centerView())
     _node->setPosition(lastpos);
    }


    if (_events.IsKeyDown(_keymap[EKEYMAP_SHOOT]) && _projectile == NULL)
      {
	setAnimation(EANIM_SHOOT);
	_projectile = getProjectile(driver);
	_projectile->addToSceneManager(sceneManager, NULL, driver);
	_projectile->addCollision(sceneManager, m_selector);
      }
    if (_projectile != NULL)
      {
	if (_projectile->Launch(sceneManager, _list, _damage) == false ||
	    _projectile->getPosition().Z > getPosition().Z + 45 ||
	    _projectile->getPosition().Z < getPosition().Z - 45 ||
	    _projectile->getPosition().X > getPosition().X + 45 ||
	    _projectile->getPosition().X < getPosition().X - 45)
	  {
	    if (_projectile->getNode() != NULL)
	      sceneManager->addToDeletionQueue(_projectile->getNode());
	    delete _projectile;
	    _projectile = NULL;
	  }
      }
}
