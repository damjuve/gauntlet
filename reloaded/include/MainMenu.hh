//
// MainMenu.hh for indie in /home/seguin_e/rendu/indie_menu
//
// Made by adrien seguin
// Login   <seguin_e@epitech.net>
//
// Started on  Sun Jun  5 10:12:15 2016 adrien seguin
// Last update Sun Jun  5 22:32:02 2016 adrien seguin
//

#ifndef MAINMENU_HH_
# define MAINMENU_HH_

# include <irrlicht.h>
# include "EventReceiver.hh"

class	MainMenu
{
public:
  MainMenu(void);

  void	run(void);
  bool	started(void);

private:

  bool				_start;
  irr::IrrlichtDevice		*MenuDevice;
  irr::gui::IGUIEnvironment	*guienv;
  bool				_fullscreen;
  bool				_sound;
  bool				_shadows;
  bool				_transparent;
  EventReceiver			_receiver;

  irr::video::SColor SkinColor[irr::gui::EGDC_COUNT];

  void	setTransparency();
  void	getOriginalSkinColor();
};

#endif /* !MAINMENU_HH_ */
