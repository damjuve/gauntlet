/*
** users.c for users in /home/etienne.labrot/PSU/PSU_2016_myirc/src
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Thu Jun  8 14:38:45 2017 Etienne Labrot
** Last update Sun Jun 11 19:29:29 2017 Alexandre Brun
*/

#include "server.h"

t_user		*ptr_user(t_env *e, int fd)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (fd == tmp->fd)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

void		add_user(t_env *e, int fd)
{
  t_user	*tmp;
  t_user	*prev;

  tmp = e->users;
  prev = tmp;
  while (tmp)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  tmp = calloc(1, sizeof(t_user));
  strcpy(tmp->nickname, "*");
  strcpy(tmp->username, "*");
  tmp->fd = fd;
  tmp->connect = 0;
  tmp->next = NULL;
  if (!prev)
    e->users = tmp;
  else
    prev->next = tmp;
}

int		delete_user(t_env *e, int fd)
{
  t_user	*tmp;
  t_user	*prev;

  tmp = e->users;
  prev = tmp;
  while (tmp && tmp->fd != fd)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (!tmp)
    return (-1);
  if (prev != tmp)
    prev->next = tmp->next;
  else
    e->users = tmp->next;
  free(tmp);
  e->fd_type[fd] = FD_FREE;
  return (0);
}
