#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "irc.h"

static void			init_data(t_server *server, int port)
{
  server->port = port;
  server->clients = NULL;
  server->chans = NULL;
  server->tv.tv_sec = 20;
  server->tv.tv_usec = 0;
}

static int			init_server(t_server *server, int port)
{
  struct sockaddr_in	sin;

  init_data(server, port);
  if ((server->fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return (xerror("Call to socket failed (init_server)\n"));
  server->maxfd = server->fd;
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

int		start_server(t_server *server)
{
  int		error;
  fd_set	readfd;
  fd_set	writefd;

  printf("## irc server started ##");
  error = EXIT_SUCCESS;
  while (error == EXIT_SUCCESS)
    {

      FD_ZERO(&readfd);
      FD_ZERO(&writefd);
      fdset_clients(server, &readfd);
      if (select(server->maxfd + 1, &readfd, &writefd, NULL, &(server->tv)) == -1)
	return (xerror("Call to select failed (start_server)\n"));
      
    }
  return (error);
}

int		main(int ac, char **av)
{
  t_server	server;

  if (ac != 2)
    return (dprintf(2, "Usage: ./server PORT\n"));
  if (init_server(&server, atoi(av[1])))
    return (EXIT_FAILURE);
  if (start_server(&server))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
