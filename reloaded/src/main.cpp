#include <iostream>
#include <unistd.h>
#include <irrlicht.h>
#include "EventReceiver.hh"
#include "Game.hh"

int main(int ac, char **av)
{
    unsigned int nbplayers = 4;
    if (ac == 2) {
      int nb = std::stoi(std::string(av[1]));
      if (nb > 0 && nb <= 4)
        nbplayers = nb;
    }

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

      try {
        Game game(device, &receiver);
        game.load();
        game.setup(nbplayers);
        game.start();
      }
      catch (std::runtime_error e) {
        std::cerr << "Exception encountred" << std::endl;
        std::cerr << e.what() << std::endl;
        return (1);
      }
      return (0);
}
