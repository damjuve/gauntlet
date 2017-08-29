/*
** write_functions.c for write_functions in /home/etienne.labrot/PSU/PSU_2016_myirc/src
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Sun Jun 11 20:28:10 2017 Etienne Labrot
** Last update Sun Jun 11 19:19:57 2017 Alexandre Brun
*/

#include "server.h"

void		privmsg(t_env *e, int fd, char **commands, char *cmd)
{
  t_channel	*tmp;
  int		to;
  char		*nick;

  nick = look_for_nickname(e, fd);
  if (wordtab_len(commands) < 2)
    dprintf(fd, ":HOSTSERVER 411 %s PRIVMSG :No recipient given\r\n",
	    nick);
  else if (wordtab_len(commands) < 3 || commands[2][0] != ':')
    dprintf(fd, ":HOSTSERVER 412 %s PRIVMSG :No text to send\r\n",
	    nick);
  else if (!(tmp = get_chan(e, commands[1])) &&
	   (to = get_fd_by_nickname(e, commands[1])) == -1)
    dprintf(fd, ":HOSTSERVER 401 %s PRIVMSG %s :No such nick/channel\r\n",
	    nick, commands[1]);
  else
    {
      if (tmp)
	write_to_chan(tmp, ptr_user(e, fd), cmd, 0);
      else
        write_to_user(e, to, fd, cmd);
    }
}

void		while_write(t_env *e, int fd, char *buf, int ok)
{
  t_user	*tmp;
  char		*nick;
  char		*user;

  tmp = e->users;
  while (tmp)
    {
      if (fd == tmp->fd)
	{
	  nick = tmp->nickname;
	  user = tmp->username;
	}
      tmp = tmp->next;
    }
  tmp = e->users;
  while (tmp)
    {
      if (tmp->fd != fd || ok)
	dprintf(tmp->fd, ":%s!%s %s\r\n", nick, user, buf);
      tmp = tmp->next;
    }
}

void		write_to_chan(t_channel *chan, t_user *us, char *buf, int ok)
{
  int		i;

  if (!chan || !us)
    return ;
  i = -1;
  while (++i < MAX_FD)
    {
      if (chan->users[i] && (chan->users[i]->fd != us->fd || ok))
	dprintf(i, ":%s!%s %s\r\n", us->nickname, us->username, buf);
    }
}

void		write_to_user(t_env *e, int to, int fd, char *buf)
{
  t_user	*tmp;
  t_user	*send;

  tmp = e->users;
  while (tmp)
    {
      if (fd == tmp->fd)
	send = tmp;
      tmp = tmp->next;
    }
  dprintf(to, ":%s!%s %s\r\n", send->nickname, send->username, buf);
}
