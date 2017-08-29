#include <stdlib.h>
#include <string.h>
#include "irc.h"


static void	remove_client_from_server(t_client **clients, t_client *torm)
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


static void	remove_client_from_chans(t_chanclient **clients, t_client *torm)
{
  t_chanclient	*prev;
  t_chanclient	*tmp;

  tmp = *clients;
  if (!tmp)
    return ;
  prev = NULL;
  while (tmp->client != torm && tmp != NULL)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (!tmp)
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

  chan = server->chans;
  while (chan != NULL)
    {
      remove_client_from_chans(&chan->clients, torm);
      chan = chan->next;
    }
  remove_client_from_server(&server->clients, torm);
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
