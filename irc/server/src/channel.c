
#include "irc.h"

int		add_client_to_channel(t_server *server, t_client *client,
				      const char *name)
{
  t_channel	*channel;
  t_chanclient	*tmp;
  t_chanclient	*new;

  if ((channel = get_channel_from_name(server, name)) == NULL)
    add_channel(server, name, &channel);
  tmp = channel->clients;
  while (tmp != NULL)
    {
      if (tmp->client == client)
	return (EXIT_FAILURE);
      tmp = tmp->next;
    }
  if ((new = xmalloc(sizeof(*new))) == NULL)
    return (perror("Malloc failed (add_client_to_channel)\n"));
  new->client = client;
  new->next = NULL;
  tmp = channel->clients;
  if (!tmp)
    channel->clients = new;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
    }
  return (EXIT_SUCCESS);
}


int		remove_client_from_channel(t_server *server, t_client *client,
					   const char *name)
{
  t_channel	*channel;
  t_chanclient	*tmp;
  t_chanclient	*prev;

  if ((channel = get_channel_from_name(server, name)) == NULL)
    return (EXIT_FAILURE);
  tmp = channel->clients;
  prev = NULL
  while (tmp != NULL && tmp->client != client)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return (EXIT_FAILURE);
  else
    {
      if (prev == NULL)
	channel->clients = tmp->next;
      else
	prev->next = tmp->next;
      free(tmp);
    }
  return (EXIT_SUCCESS);
}

t_channel	*get_channel_from_name(t_server *server, const char *name)
{
  t_channel	*channel;

  if (!server->chans)
    return (NULL);
  channel = server->chans;
  while (channel->next != NULL && strcmp(channel->name, name))
    channel = channel->next;
  if (!strcmp(channel->nickname, name))
    return (channel);
  return (NULL);
}


int		add_channel(t_server *server, const char *name, t_channel **chan)
{
  t_channel	*tmp;

  if ((*chan = xmalloc(sizeof(**chan))) == NULL)
    return (xerror("Malloc failed (add_channel)\n"));
  memset(*chan->name, 0, CHANNAME_MAX);
  strcpy(*chan->name, name, CHANNAME_MAX);
  memset(*chan->topic, 0, TOPIC_MAX);
  // Topic vide
  *chan->clients = NULL;
  *chan->next = NULL;
  tmp = server->chans;
  if (tmp == NULL)
    server->chans = *chan;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = *chan;
    }
  return (EXIT_SUCCESS);
}
