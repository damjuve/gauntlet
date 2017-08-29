
#include <stdio.h>
#include <stdlib.h>
#include "irc.h"

int		main(int ac, char **av)
{
  int		port;

  if (ac != 2)
    return (dprintf(2, "Usage: ./server PORT"));
  port = atoi(av[1]);
  return (0);
}
