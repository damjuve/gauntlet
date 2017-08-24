#include <iostream>
#include <unistd.h>
#include "Game.hh"

Game::Game(irr::IrrlichtDevice * device, EventReceiver * receiver)
  : _device(device), _receiver(receiver)
{
  _driver = device->getVideoDriver();
  _sceneManager = device->getSceneManager();

  _cam = NULL;
  _map = NULL;
}

Game::~Game()
{
  if (_cam != NULL)
    delete _cam;
  if (_map != NULL)
    delete _map;
}

void Game::load() {
  // Loading sunlight
  _sceneManager->addLightSceneNode(0,
          irr::core::vector3df(25,500,25),
          irr::video::SColorf(255, 255, 255, 255),
          50.0f);

  // Loading map
  _map = new Map("./media/maps/map2.obj",
    	 irr::core::vector3df(0, 0, 0),
       irr::core::vector3df(0, 0, 0),
    	 irr::core::vector3df(2, 2, 2));
  _map->addToSceneManager(_sceneManager, 0, _driver);

  // Loading Camera
  _cam = new Camera(irr::core::vector3df(0, 50, -25),
                    irr::core::vector3df(0, 0, 0),
                    _plist);
  _cam->addToSceneManager(_sceneManager, NULL, _driver);

  // Map collision selector
  _selector = _sceneManager->createMetaTriangleSelector();
  _map->addToSelector(_sceneManager, _selector);
}

void Game::setup(unsigned int nbplayers) {
  this->setupPlayers(nbplayers);
  this->setupMobs();
}

void Game::setupPlayers(unsigned int number) {
  if (number == 0 || number > 4)
    return ;
  for (; number != 0; number --) {
    ACharacter *player;
    // Dwarf player
    if (number == 4) {
      // setting keymap
      irr::EKEY_CODE  keymap[APlayer::EKEYMAP_NB_KEY];
      keymap[APlayer::EKEYMAP_LEFT] = irr::KEY_KEY_Q;
      keymap[APlayer::EKEYMAP_RIGHT] = irr::KEY_KEY_D;
      keymap[APlayer::EKEYMAP_TOP] = irr::KEY_KEY_Z;
      keymap[APlayer::EKEYMAP_BOTTOM] = irr::KEY_KEY_S;
      keymap[APlayer::EKEYMAP_SHOOT] = irr::KEY_KEY_A;
      // Creating player
      player = new Dwarf(*_device, *_receiver, *_cam, keymap, _mlist, irr::core::vector3df(-8, 5, 15));
    }
    // Sydney player
    if (number == 3) {
      // setting keymap
      irr::EKEY_CODE  keymap[APlayer::EKEYMAP_NB_KEY];
      keymap[APlayer::EKEYMAP_LEFT] = irr::KEY_KEY_K;
      keymap[APlayer::EKEYMAP_RIGHT] = irr::KEY_KEY_M;
      keymap[APlayer::EKEYMAP_TOP] = irr::KEY_KEY_O;
      keymap[APlayer::EKEYMAP_BOTTOM] = irr::KEY_KEY_L;
      keymap[APlayer::EKEYMAP_SHOOT] = irr::KEY_KEY_I;
      // Creating player
      player = new Sydney(*_device, *_receiver, *_cam, keymap, _mlist, irr::core::vector3df(-8, 5, 5));
    }
    // Ninja player
    if (number == 1) {
      // setting keymap
      irr::EKEY_CODE  keymap[APlayer::EKEYMAP_NB_KEY];
      keymap[APlayer::EKEYMAP_LEFT] = irr::KEY_LEFT;
      keymap[APlayer::EKEYMAP_RIGHT] = irr::KEY_RIGHT;
      keymap[APlayer::EKEYMAP_TOP] = irr::KEY_UP;
      keymap[APlayer::EKEYMAP_BOTTOM] = irr::KEY_DOWN;
      keymap[APlayer::EKEYMAP_SHOOT] = irr::KEY_RSHIFT;
      // Creating player
      player = new Ninja(*_device, *_receiver, *_cam, keymap, _mlist, irr::core::vector3df(-8, 5, -5));
    }
    // Faerie player
    if (number == 2) {
      // setting keymap
      irr::EKEY_CODE  keymap[APlayer::EKEYMAP_NB_KEY];
      keymap[APlayer::EKEYMAP_LEFT] = irr::KEY_KEY_V;
      keymap[APlayer::EKEYMAP_RIGHT] = irr::KEY_KEY_N;
      keymap[APlayer::EKEYMAP_TOP] = irr::KEY_KEY_G;
      keymap[APlayer::EKEYMAP_BOTTOM] = irr::KEY_KEY_B;
      keymap[APlayer::EKEYMAP_SHOOT] = irr::KEY_KEY_F;
      // Creating player
      player = new Faerie(*_device, *_receiver, *_cam, keymap, _mlist, irr::core::vector3df(-8, 5, -15));
    }
    player->addToSceneManager(_sceneManager, 0, _driver);
    player->addCollision(_sceneManager, _selector);
    _plist.push_back(player);
  }
}

void Game::setupMobs() {
  _mlist.push_back(new Mob(*_device, _plist, irr::core::vector3df(94, 5, -8)));
  for(std::list<ACharacter *>::iterator it = _mlist.begin(); it != _mlist.end(); ++it)
  {
    (*it)->addToSceneManager(_sceneManager, 0, _driver);
    (*it)->addCollision(_sceneManager, _selector);
  }
}

unsigned int Game::nbplayeralive() const {
  unsigned int nb = 0;
  for (std::list<ACharacter *>::const_iterator it = _plist.begin(); it != _plist.end(); ++it) {
    if ((*it)->getHp() > 0)
      nb++;
  }
  return nb;
}

unsigned int Game::nbmobalive() const {
  unsigned int nb = 0;
  for (std::list<ACharacter *>::const_iterator it = _mlist.begin(); it != _mlist.end(); ++it) {
    if ((*it)->getHp() > 0)
      nb++;
  }
  return nb;
}

void Game::start() {
  while (_device->run() && this->nbplayeralive() > 0 && this->nbmobalive() > 0) {
    irr::core::vector3df dir(0, 0, 0);

    // update all players
    for (std::list<ACharacter *>::iterator it = _plist.begin(); it != _plist.end(); ++it) {
      if ((*it)->getHp() > 0)
        (*it)->update(_sceneManager, _driver, _selector);
    }

    // update all mobs
    for (std::list<ACharacter *>::iterator it = _mlist.begin(); it != _mlist.end(); ++it) {
      if ((*it)->getHp() > 0)
        (*it)->update(_sceneManager, _driver, _selector);
    }

    // draw
    _driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
    _sceneManager->drawAll();
    _driver->endScene();
  }

  if (_device->run()) {
    if (this->nbplayeralive() > 0)
      std::cout << "### Victoire :) ###" << std::endl;
    else
      std::cout << "### Defaite :( ###" << std::endl;
  }
  else {
    std::cout << "### Goodbye ###" << std::endl;
  }
}
