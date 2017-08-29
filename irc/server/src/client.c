#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "irc.h"


static void	remove_client_from_list(t_client **clients, t_client *torm)
{
  t_client	*tmp;
  t_client	*prev;

  tmp = *clients;
  prev = NULL;
  while (tmp != torm && tmp != NULL)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return ;
  if (prev == NULL)
    *clients = tmp->next;
  else
    prev->next = tmp->next;
}

void		remove_client(t_server *server, t_client *torm)
{
  t_channel	*chan;
  t_msg		*msg;
  t_msg		*old;

  printf("## client #%d leave ##\n", torm->fd);
  chan = server->chans;
  while (chan != NULL)
    {
      remove_client_from_list(&chan->clients, torm);
      chan = chan->next;
    }
  remove_client_from_list(&server->clients, torm);
  msg = torm->msgq;
  while (msg != NULL)
    {
      old = msg;
      msg = msg->next;
      free(old->msg);
      free(old);
    }
  free(torm);
}

void		fdset_client(t_server *serv,
			     fd_set *rfds,
			     fd_set *wfds)
{
  t_client	*tmp;

  serv->maxfd = serv->fd;
  FD_SET(serv->fd, rfds);
  tmp = serv->clients;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, rfds);
      if (tmp->fd > serv->maxfd)
	serv->maxfd = tmp->fd;
      if (tmp->msgq != NULL)
	FD_SET(tmp->fd, wfds);
      tmp = tmp->next;
    }
}

static void		init_client(t_client *new, int fd)
{
  new->fd = fd;
  memset(new->nickname, 0, NICKNAME_MAX);
  new->msgq = NULL;
  new->channel = NULL;
  new->next = NULL;
}

int			client_join(t_server *server)
{
  int			client_fd;
  struct sockaddr_in	sin;
  socklen_t		len;
  t_client		*new;
  t_client		*tmp;

  len = sizeof(sin);
  if ((client_fd =
       accept(server->fd, (struct sockaddr *)&sin, &len)) == -1)
    return (xerror("Call to accept failed (client_join)\n"));
  if ((new = xmalloc(sizeof(*new))) == NULL)
    return (EXIT_FAILURE);
  init_client(new, client_fd);
  if ((tmp = server->clients) == NULL)
    server->clients = new;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;

    }
  printf("## new client #%d ##\n", new->fd);
  return (EXIT_SUCCESS);
}
