#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "irc.h"

void	printchannels(t_server *server)
{
  t_chanel *chan;
  
  printf("--------------\n");
  printf("chanels :\n");
  chan = server->chans;
  while  (chan != NULL)
    {
      printf("- %s\n", chan->name);
      chan = chan->next;
    }
}

void	printclients(t_server *server)
{
  t_client	*cli;

  printf("--------------\n");
  printf("clients :\n");
  cli = server->clients;
  while (cli != NULL)
    {
      printf("- #%d (%s)\n", cli->fd, cli->nickname);
      cli = cli->next;
    }
}

bool	hasclient(t_channel *chan, t_client *cli)
{
  t_chanclient	*cl;

  cl = chan->clients;
  while (cl != NULL)
    {
      if (cl->client == cli)
	return (true);
      cl = cl->next;
    }
  return (false);
}


void	printclient(t_server *server, t_client *client)
{
  t_chanel *chan;

  printf("--------------\n");
  printf("clients #%d (%s)\n", client->fd, client->nickname);
  chan = server->chans;
  printf("- channels : ");
  while  (chan != NULL)
    {
      if (hasclient(chan, client))
	printf("%s ", chan->name);
      chan = chan->next;
    }
  printf("\n");
}
  
