//
// MenuFX.hh for indie in /home/seguin_e/rendu/indie_menu
//
// Made by adrien seguin
// Login   <seguin_e@epitech.net>
//
// Started on  Sat Jun  4 21:04:04 2016 adrien seguin
// Last update Sun Jun  5 22:16:30 2016 adrien seguin
//

#ifndef MENUFX_HH
# define MENUFX_HH

# include "AEntity.hh"
# include "EventReceiver.hh"

class		MenuFX : public AEntity
{
public:

  enum KeyMap
    {
      EKEYMAP_UP = 0,
      EKEYMAP_DOWN,
      EKEYMAP_NB_KEY
    };

private:
  EventReceiver*				 _receiver;
  irr::EKEY_CODE				_keymap[EKEYMAP_NB_KEY];
  irr::scene::IVolumeLightSceneNode*		_node;
  irr::scene::ISceneNodeAnimator*		_glow;
  irr::core::array<irr::video::ITexture*>	textures;

public:
  MenuFX(irr::core::vector3df const& pos,
	 irr::core::vector3df const& rotation = irr::core::vector3df(0, 0, 0),
	 irr::core::vector3df const& scale = irr::core::vector3df(16.5f, 16.5f, 16.5f));
  virtual ~MenuFX(void) {};

  void  addToSceneManager(irr::scene::ISceneManager *sceneManager,
			    irr::scene::ISceneNode *parent,
			    irr::video::IVideoDriver *driver);

  void	addToSelector(irr::scene::ISceneManager *sceneManager,
		      irr::scene::IMetaTriangleSelector *m_selector);
  void	update(void);
  void	setReceiver(EventReceiver *receiver);

  irr::scene::ISceneNode	*getNode(void) const;
  virtual irr::core::vector3df	getDirection();

};

#endif /* !MENUFX_HH_ */
