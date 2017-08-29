#include "Exceptions.hh"
#include "Shuriken.hh"

Shuriken::Shuriken(irr::video::IVideoDriver *driver, irr::core::vector3df const& position,
		   irr::core::vector3df const& direction, irr::core::vector3df const& rotation)
  : AProjectile(direction, position, rotation, irr::core::vector3df(0.5, 0.5, 0.5)),
    _driver(driver)
{}

Shuriken::~Shuriken()
{}

void	Shuriken::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				    irr::scene::ISceneNode *parent,
				    irr::video::IVideoDriver *driver)

{
  (void)driver;
  irr::scene::IMesh* mesh =
    sceneManager->getMesh("./media/projectiles/shuriken.obj");
  if (!mesh)
    throw exception::LoadingDataException("StaticMesh", "./media/projectiles/shuriken.obj");
  _node = sceneManager->addMeshSceneNode(mesh, parent, -1,
					 _position, _rotation, _scale);
  if (!_node)
    throw exception::IrrlichtException("addCubeSceneNode");
  _node->setMaterialTexture(0, driver->getTexture("./media/projectiles/shuriken.mtl"));

  irr::scene::ISceneNodeAnimator *anim = sceneManager->createRotationAnimator(irr::core::vector3df(0, 15, 0));
  if (!anim)
    throw exception::IrrlichtException("addRotateAnimatorSceneNode");
  _node->addAnimator(anim);
  anim->drop();
}

