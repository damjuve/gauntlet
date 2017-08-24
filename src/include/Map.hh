#ifndef MAP_HH
#define MAP_HH

#include <string>
#include "AEntity.hh"

class Map : public AEntity
{
private:
	std::string  				_path_mesh;
	irr::scene::IMesh 			* _mesh;
	irr::scene::IMeshSceneNode 	* _node;

public:
  Map(std::string const & map_mesh,
      irr::core::vector3df const& _position = irr::core::vector3df(0, 0, 0),
      irr::core::vector3df const& _rotation = irr::core::vector3df(0, 0, 0),
      irr::core::vector3df const& _scale = irr::core::vector3df(1, 1, 1));
  ~Map();

  virtual void	addToSceneManager(irr::scene::ISceneManager *sceneManager,
					  irr::scene::ISceneNode *parent,
					  irr::video::IVideoDriver *driver);

  virtual void	addToSelector(irr::scene::ISceneManager *sceneManager,
                              irr::scene::IMetaTriangleSelector *m_selector);
  virtual    irr::core::vector3df getDirection();

private:
	virtual irr::scene::ISceneNode *	getNode() const;
};

#endif // MAP_HH
