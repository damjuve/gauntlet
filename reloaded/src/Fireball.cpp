#include "Exceptions.hh"
#include "Fireball.hh"

Fireball::Fireball(irr::video::IVideoDriver *driver,
		   irr::core::vector3df const& direction,
		   irr::core::vector3df const& position,
		   irr::core::vector3df const& rotation)
  : AProjectile(direction, position, rotation, irr::core::vector3df(1, 1, 1)),
    _driver(driver)
{}

Fireball::~Fireball()
{}

void	Fireball::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				    irr::scene::ISceneNode *parent,
				    irr::video::IVideoDriver *driver)

{
  (void)parent;
  _node = sceneManager->addSphereSceneNode(5, 16, 0,
					   -1, _position,_rotation,_scale);
  if (!_node)
    throw exception::IrrlichtException("addCubeSceneNode");
  _node->setMaterialTexture(0, driver->getTexture("./media/projectiles/fireball.bmp"));
}
