/*
** getters.c for getters in /home/etienne.labrot/PSU/PSU_2016_myirc/src
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Sun Jun 11 20:35:00 2017 Etienne Labrot
** Last update Sun Jun 11 19:17:32 2017 Alexandre Brun
*/

#include "server.h"

char		*look_for_nickname(t_env *e, int fd)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (tmp->fd == fd)
	return (tmp->nickname);
      tmp = tmp->next;
    }
  return (NULL);
}

t_channel	*get_chan(t_env *e, char *name)
{
  t_channel	*tmp;

  tmp = e->chans;
  while (tmp)
    {
      if (!strcmp(tmp->name, name))
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

int		get_fd_by_nickname(t_env *e, char *name)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (!strcmp(tmp->nickname, name))
	return (tmp->fd);
      tmp = tmp->next;
    }
  return (-1);
}

int		nickname_taken(t_env *e, char *nick)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (strcmp(tmp->nickname, nick) == 0)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

int		is_connected(t_env *e, int fd)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (tmp->fd == fd)
	return (tmp->connect);
      tmp = tmp->next;
    }
  return (0);
}
