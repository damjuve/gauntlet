#include <stdbool.h>
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

char		*read_buff(t_client *client, bool *disconected)
{
  char		*buff;
  int		len;
  int		size;

  size = 0;
  if ((buff = xmalloc(sizeof(*buff) * (SIZE_READ + 1))) == NULL)
    return (NULL);
  len = SIZE_READ;
  while (len == SIZE_READ && (len = read(client->fd, &(buff[size]), SIZE_READ)) > 0)
    {
      size += len;
      if (len == SIZE_READ &&
	  (buff = xrealloc(buff, sizeof(*buff) * (SIZE_READ + size + 1))) == NULL)
	return (NULL);
    }
  if (len == -1)
    {
      xerror("Call to read failed (read_buff)\n");
      return (NULL);
    }
  if (size == 0)
    *disconected = true;
  buff[size] = '\0';
  return (buff);
}

char		**read_cmd(char *buff)
{
  char		**cmd;
  int		i;
  int		j;
  int		off;

  if ((cmd = xmalloc(sizeof(*cmd) * 1)) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  cmd[j] = NULL;
  off = 0;
  while (buff[i] != '\0')
    {
      if (buff[i] == '\n')
	{
	  if ((cmd = xrealloc(cmd, sizeof(*cmd) * (j + 2))) == NULL)
	    return (NULL);
	  if ((cmd[j] = xncopy(&buff[off], i - off - 1)) == NULL)
	    return (NULL);
	  off = i;
	  j++;
	  cmd[j] = NULL;
	}
      i++;
    }
  return (cmd);
}

int		receive_msg(t_server *server, t_client *client)
{
  char		*buff;
  char		**cmd;
  int		i;
  bool		disconected;

  disconected = false;
  if ((buff = read_buff(client, &disconected)) == NULL)
    return (EXIT_FAILURE);
  if (disconected) {
    free(buff);
    remove_client(server, client);
    return (EXIT_SUCCESS);
  }
  if ((cmd = read_cmd(buff)) == NULL)
    return (EXIT_FAILURE);
  free(buff);
  i = 0;
  while (cmd[i] != NULL)
    {
      if (execute_cmd(cmd[i], server, client))
	return (EXIT_FAILURE);
      free(cmd[i]);
      i++;
    }
  free(cmd);
  return (EXIT_SUCCESS);
}

int		start_server(t_server *server)
{
  int		error;
  fd_set	readfd;
  fd_set	writefd;
  t_client	*client;

  printf("## irc server started ##\n");
  error = EXIT_SUCCESS;
  while (error == EXIT_SUCCESS)
    {

      FD_ZERO(&readfd);
      FD_ZERO(&writefd);
      fdset_client(server, &readfd, &writefd);
      if (select(server->maxfd + 1, &readfd, &writefd, NULL, &(server->tv)) == -1)
	return (xerror("Call to select failed (start_server)\n"));
      if (FD_ISSET(server->fd, &readfd) && client_join(server))
	return (EXIT_FAILURE);
      client = server->clients;
      while (client != NULL)
	{
	  if (FD_ISSET(client->fd, &writefd))
	    send_msg(client);
	  if (FD_ISSET(client->fd, &readfd) && receive_msg(server, client))
	    return (EXIT_FAILURE);
	  client = client->next;
	}
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
