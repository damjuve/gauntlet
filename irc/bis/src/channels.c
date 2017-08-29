/*
** channels.c for channels in /home/etienne.labrot/PSU/PSU_2016_myirc
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Tue May 30 17:44:09 2017 Etienne Labrot
** Last update Sun Jun 11 19:22:22 2017 Alexandre Brun
*/

#include "server.h"

t_channel	*init_chan(t_env *e, char *name, int fd)
{
  int		i;
  t_channel	*curr;

  curr = malloc(sizeof(*curr));
  strcpy(curr->name, name);
  memset(curr->topic, 0, MAX_TOPIC);
  i = -1;
  while (++i < MAX_FD)
    curr->users[i] = NULL;
  curr->users[fd] = ptr_user(e, fd);
  curr->next = NULL;
  return (curr);
}

void		join_channel(t_env *e, char *name, int fd)
{
  t_channel	*curr;
  t_channel	*prev;

  curr = e->chans;
  prev = NULL;
  while (curr)
    {
      prev = curr;
      if (!strcmp(curr->name, name))
	{
	  curr->users[fd] = ptr_user(e, fd);
	  return ;
	}
      curr = curr->next;
    }
  curr = init_chan(e, name, fd);
  if (!prev)
    e->chans = curr;
  else
    prev->next = curr;
}

int		leave_chan(t_env *e, t_channel *curr, t_channel *prev, int fd)
{
  int		i;

  i = -1;
  if (curr->users[fd] == NULL)
    return (0);
  curr->users[fd] = NULL;
  while (++i < MAX_FD)
    if (curr->users[i])
      return (1);
  if (prev)
    prev->next = curr->next;
  else
    e->chans = curr->next;
  curr = prev;
  free(curr);
  return (1);
}

int		leave_channel(t_env *e, char *name, int fd)
{
  t_channel	*curr;
  t_channel	*prev;

  curr = e->chans;
  prev = NULL;
  while (curr)
    {
      if (!strcmp(curr->name, name))
        return (leave_chan(e, curr, prev, fd));
      prev = curr;
      curr = curr->next;
    }
  return (-1);
}

void		delete_from_all_chans(t_env *e, int fd)
{
  t_channel	*chan;
  t_channel	*prev;

  chan = e->chans;
  prev = NULL;
  while (chan)
    {
      leave_chan(e, chan, prev, fd);
      prev = chan;
      if (chan)
	chan = chan->next;
    }
}
