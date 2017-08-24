#include <iostream>
#include <unistd.h>
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
#include "AProjectile.hh"
#include "EventReceiver.hh"
#include "Mob.hh"
#include "Boss.hh"

int main(void)
{

    if (true)
    {
      EventReceiver receiver;

      irr::IrrlichtDevice* device = irr::createDevice(
						      irr::video::EDT_OPENGL,
						      irr::core::dimension2d<irr::u32>(1200,1000),
						      32,
						      false,
						      true, // Shadow
						      false,
						      &receiver);
      if (!device)
      {
            std::cerr << "Cannot create irrlicht device" << std::endl;
            return (1);
      }

      irr::video::IVideoDriver* driver = device->getVideoDriver ();
      irr::scene::ISceneManager* sceneManager = device->getSceneManager ();

      sceneManager->addLightSceneNode(0,
				      irr::core::vector3df(25,500,25),
				      irr::video::SColorf(255, 255, 255, 255),
				      50.0f);


      Map mp("./media/maps/map2.obj",
	     irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0),
	     irr::core::vector3df(2, 2, 2));


      mp.addToSceneManager(sceneManager, 0, driver);
      irr::EKEY_CODE  keymap[APlayer::EKEYMAP_NB_KEY];

      keymap[APlayer::EKEYMAP_LEFT] = irr::KEY_KEY_Q;
      keymap[APlayer::EKEYMAP_RIGHT] = irr::KEY_KEY_D;
      keymap[APlayer::EKEYMAP_TOP] = irr::KEY_KEY_Z;
      keymap[APlayer::EKEYMAP_BOTTOM] = irr::KEY_KEY_S;
      keymap[APlayer::EKEYMAP_SHOOT] = irr::KEY_KEY_A;

      irr::EKEY_CODE  keymap2[APlayer::EKEYMAP_NB_KEY];

      keymap2[APlayer::EKEYMAP_LEFT] = irr::KEY_KEY_K;
      keymap2[APlayer::EKEYMAP_RIGHT] = irr::KEY_KEY_M;
      keymap2[APlayer::EKEYMAP_TOP] = irr::KEY_KEY_O;
      keymap2[APlayer::EKEYMAP_BOTTOM] = irr::KEY_KEY_L;
      keymap2[APlayer::EKEYMAP_SHOOT] = irr::KEY_KEY_I;

      irr::EKEY_CODE  keymap3[APlayer::EKEYMAP_NB_KEY];

      keymap3[APlayer::EKEYMAP_LEFT] = irr::KEY_LEFT;
      keymap3[APlayer::EKEYMAP_RIGHT] = irr::KEY_RIGHT;
      keymap3[APlayer::EKEYMAP_TOP] = irr::KEY_UP;
      keymap3[APlayer::EKEYMAP_BOTTOM] = irr::KEY_DOWN;
      keymap3[APlayer::EKEYMAP_SHOOT] = irr::KEY_RSHIFT;

      irr::EKEY_CODE  keymap4[APlayer::EKEYMAP_NB_KEY];

      keymap4[APlayer::EKEYMAP_LEFT] = irr::KEY_KEY_V;
      keymap4[APlayer::EKEYMAP_RIGHT] = irr::KEY_KEY_N;
      keymap4[APlayer::EKEYMAP_TOP] = irr::KEY_KEY_G;
      keymap4[APlayer::EKEYMAP_BOTTOM] = irr::KEY_KEY_B;
      keymap4[APlayer::EKEYMAP_SHOOT] = irr::KEY_KEY_F;

      std::list<ACharacter *> plist;
      std::list<ACharacter *> mlist;

      Camera *cam = new Camera(irr::core::vector3df(0, 50, -25), irr::core::vector3df(0, 0, 0), plist);
      cam->addToSceneManager(sceneManager, NULL, driver);

      Dwarf s1(*device, receiver, *cam, keymap, mlist, irr::core::vector3df(-3, 5, 1.5f));
      Sydney s2(*device, receiver, *cam, keymap2, mlist, irr::core::vector3df(-3, 5, -1.5f));
      Ninja s3(*device, receiver, *cam, keymap3, mlist, irr::core::vector3df(1.5f, 5, -4));
      Faerie sy(*device, receiver, *cam, keymap4, mlist, irr::core::vector3df(1.5f, 5, 1.5f));

      sy.addToSceneManager(sceneManager, 0, driver);
      s1.addToSceneManager(sceneManager, 0, driver);
      s2.addToSceneManager(sceneManager, 0, driver);
      s3.addToSceneManager(sceneManager, 0, driver);

      irr::scene::IMetaTriangleSelector *m_selector = sceneManager->createMetaTriangleSelector();
      mp.addToSelector(sceneManager, m_selector);

      sy.addCollision(sceneManager, m_selector);
      s1.addCollision(sceneManager, m_selector);
      s2.addCollision(sceneManager, m_selector);
      s3.addCollision(sceneManager, m_selector);

      plist.push_back(&sy);
      plist.push_back(&s1);
      plist.push_back(&s2);
      plist.push_back(&s3);

      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, -8)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, -2)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 7)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 17)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 27)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 37)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 47)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 57)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 67)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 77)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 87)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 97)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 107)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(94, 5, 117)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 115)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 105)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 109)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 99)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 89)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 79)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 69)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 59)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 49)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 39)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 29)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 19)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 9)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, 1)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(129, 5, -5)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 1)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 10)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 20)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 30)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 40)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 50)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 60)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 70)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 80)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 90)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 100)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 110)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 120)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 130)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(152, 5, 1.5f)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(194, 5, 68)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(194, 5, 72)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(175, 5, 75)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(175, 5, 80)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(195, 5, 133)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(195, 5, 123)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(195, 5, 113)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(195, 5, 104)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(100, 5, 170)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(110, 5, 1.5f)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(120, 5, 170)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(130, 5, 170)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(140, 5, 170)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(8, 5, 243)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(8, 5, 253)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(8, 5, 263)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(8, 5, 273)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(8, 5, 283)));
      mlist.push_back(new Mob(*device, plist, irr::core::vector3df(8, 5, 293)));
      mlist.push_back(new Boss(*device, plist, irr::core::vector3df(8, 50, 295)));

      for(std::list<ACharacter *>::iterator it = mlist.begin(); it != mlist.end(); ++it)
	{
	  (*it)->addToSceneManager(sceneManager, 0, driver);
	  (*it)->addCollision(sceneManager, m_selector);
	}

      while (device->run())
	{
	  irr::core::vector3df dir(0, 0, 0);

	  if (sy.getHp() > 0)
	    sy.update(sceneManager, driver, m_selector);
	  if (s1.getHp() > 0)
	    s1.update(sceneManager, driver, m_selector);
	  if (s2.getHp() > 0)
	    s2.update(sceneManager, driver, m_selector);
	  if (s3.getHp() > 0)
	    s3.update(sceneManager, driver, m_selector);

	  for (std::list<ACharacter *>::iterator it = mlist.begin();
	       it != mlist.end() &&
		 (sy.getHp() > 0 || s1.getHp() > 0 || s2.getHp() > 0 || s3.getHp() > 0);
	       ++it)
	    {
	      if ((*it)->getHp() > 0)
		(*it)->update(sceneManager, driver, m_selector);
	    }

	  driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
	  sceneManager->drawAll();
	  driver->endScene();
	}

      device->drop();
    }
  return 0;
}
