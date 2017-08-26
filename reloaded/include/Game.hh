#ifndef GAME_HH
#define GAME_HH

#include <list>
#include <irrlicht.h>

#include "Exceptions.hh"
#include "ACharacter.hh"
#include "Camera.hh"
#include "Map.hh"
#include "Sydney.hh"
#include "Dwarf.hh"
#include "Ninja.hh"
#include "Faerie.hh"
#include "Mob.hh"
#include "Boss.hh"

class Game
{
private:
  irr::IrrlichtDevice *_device;
  EventReceiver *_receiver;
  irr::video::IVideoDriver *_driver;
  irr::scene::ISceneManager *_sceneManager;

  irr::scene::IMetaTriangleSelector *_selector;
  Camera *_cam;
  Map *_map;

  std::list<ACharacter *> _plist;
  std::list<ACharacter *> _mlist;

private:
  void setupPlayers(unsigned int nbplayers);
  void setupMobs();

  unsigned int nbplayeralive() const;

  unsigned int nbmobalive() const;

public:
  Game(irr::IrrlichtDevice * device, EventReceiver * receiver);
  ~Game();

  void load();
  void setup(unsigned int nbplayers);
  void start();
};

#endif
