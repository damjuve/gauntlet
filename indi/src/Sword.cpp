#include "Exceptions.hh"
#include "Sword.hh"

Sword::Sword(irr::video::IVideoDriver *driver, irr::core::vector3df const& position,
	     irr::core::vector3df const& direction, irr::core::vector3df const& rotation)
  : AProjectile(direction, position, rotation, irr::core::vector3df(0.5, 0.5, 0.5)),
    _driver(driver)
{}

Sword::~Sword()
{}


void	Sword::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				 irr::scene::ISceneNode *parent,
				 irr::video::IVideoDriver *driver)

{
  irr::scene::IMesh*	mesh =
    sceneManager->getMesh("./media/projectiles/sword.obj");
  if (!mesh)
    throw exception::LoadingDataException("StaticMesh", "./media/projectiles/sword.obj");
  _node = sceneManager->addMeshSceneNode(mesh, parent, -1,
					 _position, _rotation, _scale);
  if (!_node)
    throw exception::IrrlichtException("addMeshSceneNode");
  _node->setMaterialTexture(0, driver->getTexture("./media/projectiles/sword.mtl"));
}
