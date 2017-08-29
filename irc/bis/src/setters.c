/*
** setters.c for setters in /home/etienne.labrot/PSU/PSU_2016_myirc/src
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Sun Jun 11 20:45:00 2017 Etienne Labrot
** Last update Sun Jun 11 19:29:05 2017 Alexandre Brun
*/

#include "server.h"

void		change_username(t_env *e, int fd, char *username)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  strncpy(tmp->username, username, 25);
	  strcat(tmp->username, "@");
	  strncat(tmp->username, username, 25);
	  if (strcmp(tmp->nickname, "*") != 0)
	    {
	      dprintf(fd, ":HOSTSERVER 001 %s :Welcome to the \
Internet Relay Network %s!%s\r\n", tmp->nickname, tmp->nickname, tmp->username);
	      tmp->connect = 1;
	    }
	  return ;
	}
      tmp = tmp->next;
    }
}

void		change_nickname(t_env *e, int fd, char *nick)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  strcpy(tmp->nickname, nick);
	  if (strcmp(tmp->username, "*") != 0 && !tmp->connect)
	    {
	      dprintf(fd, ":HOSTSERVER 001 %s :Welcome to the \
Internet Relay Network %s!%s\r\n", tmp->nickname, tmp->nickname, tmp->username);
	      tmp->connect = 1;
	    }
	  return ;
	}
      tmp = tmp->next;
    }
}

int		close_connection(t_env *e, int fd, char *message)
{
  if (!message)
    while_write(e, fd, "default quit", 0);
  else
    while_write(e, fd, message, 0);
  e->fd_type[fd] = FD_FREE;
  close(fd);
  delete_from_all_chans(e, fd);
  delete_user(e, fd);
  return (0);
}
