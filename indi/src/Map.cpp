#include "Exceptions.hh"
#include "Map.hh"

Map::Map(std::string const & map_mesh,
	 irr::core::vector3df const& _position,
	 irr::core::vector3df const& _rotation,
	 irr::core::vector3df const& _scale)
  : 	AEntity::AEntity(_position, _rotation, _scale),
	_path_mesh(map_mesh),
	_mesh(NULL),
	_node(NULL)
{}

Map::~Map()
{}

void 		Map::addToSceneManager(irr::scene::ISceneManager *sceneManager,
				       irr::scene::ISceneNode *parent,
				       irr::video::IVideoDriver *driver)
{
  (void)(driver);
  _mesh = sceneManager->getMesh(_path_mesh.c_str());
  if (!_mesh)
    throw exception::LoadingDataException("StaticMesh", _path_mesh);
  _node = sceneManager->addMeshSceneNode(_mesh,
					 parent,
					 -1,
					 _position,
					 _rotation,
					 _scale);
  if (!_node)
    throw exception::IrrlichtException("addMeshSceneNode");
}

void 		Map::addToSelector(irr::scene::ISceneManager *sceneManager,
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

irr::core::vector3df 	Map::getDirection()
{
  return (irr::core::vector3df(0, 0, 0));
}

irr::scene::ISceneNode 				* Map::getNode() const
{
	return (_node);
}
