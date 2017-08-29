#include <iostream>
#include "Exceptions.hh"
#include "ACharacter.hh"

ACharacter::ACharacter(irr::IrrlichtDevice & device,
			   std::string const& path_mesh,
		       irr::core::vector3df const& collisionBox,
		       irr::core::vector3df const& position,
		       irr::core::vector3df const& rotation,
		       irr::core::vector3df const& scale,
		       int hp,
		       int damage)
  : AEntity(position, rotation, scale),
    _path_mesh(path_mesh),
    _box(collisionBox),
    _hp(hp),
    _damage(damage),
    _direction(0, 0, 0),
    _text(NULL),
    _device(device),
    _mesh(NULL),
    _node(NULL),
    _projectile(NULL)
{}

ACharacter::~ACharacter()
{}

void 	ACharacter::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				      irr::scene::ISceneNode *parent,
				      irr::video::IVideoDriver *driver)
{
  (void)(driver);
  _mesh = sceneManager->getMesh(_path_mesh.c_str());
  if (!_mesh)
    throw exception::LoadingDataException("AnimatedMesh",  _path_mesh);

  _node = sceneManager->addAnimatedMeshSceneNode(_mesh,
						 parent,
						 -1,
						 _position,
						 _rotation,
						 _scale);
  if (!_node)
    throw exception::IrrlichtException("addAnimatedSceneNode");
  setAnimation(EANIM_STAND);

  irr::gui::IGUIFont * font = _device.getGUIEnvironment()->getFont("./media/menu/fonthaettenschweiler.bmp");
  if (!font)
    throw exception::LoadingDataException("Font", "./media/menu/fonthaettenschweiler.bmp");

  std::wstring str(std::to_wstring(_hp));
  _text = sceneManager->addTextSceneNode(font, (const wchar_t *)str.c_str(),
  										 irr::video::SColor(255, 64, 64, 0),
  										 _node,
  										 irr::core::vector3df(0, 14, 0),
  										 -1);
  if (!_text)
    throw exception::IrrlichtException("addTextSceneNode");
  _text->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void 	ACharacter::addToSelector(irr::scene::ISceneManager *sceneManager,
				  irr::scene::IMetaTriangleSelector *meta_selector)
{
  irr::scene::ITriangleSelector *selector =
    sceneManager->createOctreeTriangleSelector(_mesh, _node);
  if (!selector)
    throw exception::IrrlichtException("createOctreeTriangleSelector");
  _node->setTriangleSelector(selector);
  meta_selector->addTriangleSelector(selector);
  selector->drop();
}

int					ACharacter::getHp() const
{
  return (_hp);
}

void					ACharacter::setHp(int dmg)
{
  _hp = _hp - dmg;
  std::wstring str(std::to_wstring(_hp));
  if (_text)
  	_text->setText((const wchar_t *)str.c_str());
}

irr::scene::ISceneNode 		*	ACharacter::getNode() const
{
  return (_node);
}

void 	ACharacter::addCollision(irr::scene::ISceneManager *sceneManager,
				 irr::scene::IMetaTriangleSelector *meta_selector)
{
  irr::scene::ISceneNodeAnimator *anim =
    sceneManager->createCollisionResponseAnimator(meta_selector,
						  _node,
						  _box,
						  irr::core::vector3df(0, -0.3f, 0),
						  irr::core::vector3df(0, 0, 0));
  _node->addAnimator(anim);
  anim->drop();
}

void 	ACharacter::move(irr::core::vector3df const& direction,
					 	 irr::f32 range)
{
	if (_direction != direction)
	{
		if (direction.X == 0 && direction.Z == 0)
		{
			_direction = direction;
			setAnimation(EANIM_STAND);
			return ;
		}
		else if (_direction.X == 0 && _direction.Z == 0)
			setAnimation(EANIM_RUN);

		_direction = direction;

		irr::core::vector3df rotate(0, 0, 0);
		if (_direction.X != 0 && _direction.Z == 0)
		{
			if (_direction.X == 1)
				rotate.Y = 0;
			else
				rotate.Y = 180;
		}
		else if (_direction.Z != 0 && _direction.X == 0)
		{
			if (_direction.Z == 1)
				rotate.Y = 270;
			else
				rotate.Y = 90;
		}
		else
		{
			if (_direction.X == 1 && _direction.Z == 1)
				rotate.Y = 315;
			if (_direction.X == 1 && _direction.Z == -1)
				rotate.Y = 45;
			if (_direction.X == -1 && _direction.Z == 1)
				rotate.Y = 225;
			if (_direction.X == -1 && _direction.Z == -1)
				rotate.Y = 135;
		}
		setRotation(rotate);
	}

	irr::core::vector3df 	pos;
	pos = getPosition();
	pos.X = pos.X + range * _direction.X;
	pos.Z = pos.Z + range * _direction.Z;
	setPosition(pos);
}

irr::core::vector3df	ACharacter::getDirection()
{
  if (_direction.X == 0 && _direction.Z == 0)
    {
      irr::core::vector3df dir(0, 0, 0);
      irr::core::vector3df rot = getRotation();
      rot.Y -= _rotation.Y;
      if (rot.Y == 0 || rot.Y == 45 || rot.Y == 315)
	dir.X = 1;
      else if (rot.Y == 135 || rot.Y == 180 || rot.Y == 225)
	dir.X = -1;
      else
	dir.X = 0;
      if (rot.Y == 270 || rot.Y == 225 || rot.Y == 315)
	dir.Z = 1;
      else if (rot.Y == 90 || rot.Y == 45 || rot.Y == 135)
	dir.Z = -1;
      else
	dir.Z = 0;
      return (dir);
    }
  return (_direction);
}
