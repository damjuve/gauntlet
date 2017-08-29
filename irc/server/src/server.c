
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "irc.h"


int			init_server(t_server *server, int port)
{
  struct sockaddr_in	sin;

  server->port = port;
  server->clients = NULL;
  server->chans = NULL;
  if ((server->fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return (xerror("Call to socker failed (init_server)\n"));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(server->fd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      close(server->fd);
      return (xerror("Call to bind failed (init_server)\n"));
    }
  if (listen(server->fd, LISTEN_MAX) == -1)
    return (xerror("Call to listen failed (init_server)\n"));
  return (EXIT_SUCCESS);
}


int		main(int ac, char **av)
{
  t_server	server;

  if (ac != 2)
    return (dprintf(2, "Usage: ./server PORT"));
  if (init_server(&server, atoi(av[1])))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
