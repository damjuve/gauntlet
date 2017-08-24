#include "Exceptions.hh"
#include "Axe.hh"

Axe::Axe(irr::video::IVideoDriver *driver,
	 irr::core::vector3df const& direction,
	 irr::core::vector3df const& position,
	 irr::core::vector3df const& rotation)
  : AProjectile(direction, position, rotation, irr::core::vector3df(1, 1, 1)),
    _driver(driver)
{}

Axe::~Axe()
{}

void	Axe::addToSceneManager(irr::scene::ISceneManager *sceneManager,
			       irr::scene::ISceneNode *parent,
			       irr::video::IVideoDriver *driver)

{
  (void)driver;
  irr::scene::IMesh*	mesh =
    sceneManager->getMesh("./media/projectiles/axe.obj");
  if (!mesh)
    throw exception::LoadingDataException("StaticMesh", "./media/projectiles/axe.obj");
  _node = sceneManager->addMeshSceneNode(mesh, parent, -1,
					 _position, _rotation, _scale);
  if (!_node)
    throw exception::IrrlichtException("addMeshSceneNode");
  _node->setMaterialTexture(0, driver->getTexture("./media/projectiles/axe.jpg"));
	irr::scene::ISceneNodeAnimator *anim = sceneManager->createRotationAnimator(irr::core::vector3df(0, 15, 0));
	if (!anim)
	  throw exception::IrrlichtException("addRotateAnimatorSceneNode");
	_node->addAnimator(anim);
	anim->drop();
}
