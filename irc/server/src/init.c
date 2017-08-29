#include <string.h>
#include "irc.h"

void		init_channel(t_channel *chan)
{
  memset(chan->name, 0, CHANNAME_MAX);
  memset(chan->topic, 0, TOPIC_MAX);
  chan->clients = NULL;
}  

void	init_msg(t_msg *msg)
{
  msg->msg = NULL;
  memset(msg->from, 0, NICKNAME_MAX);
}

void		init_client(t_client *client)
{
  client->fd = -1;
  memset(client->nickname, 0, NICKNAME_MAX);
  init_msg(client->msg);
  init_channel(client->channel);
  client->next = NULL;
}

void		init_server(t_server *server)
{
  init_client(server->clients);
  port = 0;
  init_channel(server->chans);
}
