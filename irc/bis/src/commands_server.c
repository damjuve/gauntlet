/*
** commands_server.c for commands_server in /home/etienne.labrot/PSU/PSU_2016_myirc/src
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Sun Jun 11 20:42:38 2017 Etienne Labrot
** Last update Sun Jun 11 19:26:48 2017 Alexandre Brun
*/

#include "server.h"

void		part_command(t_env *e, int fd, char **commands, char *cmd)
{
  int		ret;
  char		*nick;

  nick = look_for_nickname(e, fd);
  if (wordtab_len(commands) < 2)
    dprintf(fd, ":HOSTSERVER 461 %s PART :Need more params\r\n", nick);
  else if ((ret = leave_channel(e, commands[1], fd)) == -1)
    dprintf(fd, ":HOSTSERVER 403 %s PART %s:No such channel\r\n",
	    nick, commands[1]);
  else
    {
      if (ret == 0)
	dprintf(fd, ":HOSTSERVER 442 %s PART %s :You're not on that channel\r\n",
		nick, commands[1]);
      else
	write_to_chan(get_chan(e, commands[1]), ptr_user(e, fd), cmd, 1);
    }
}

void		join_command(t_env *e, int fd, char **commands, char *buf)
{
  char		*nick;

  nick = look_for_nickname(e, fd);
  if (wordtab_len(commands) < 2)
    dprintf(fd, ":HOSTSERVER 461 %s JOIN :Not enough parameters\r\n", nick);
  else if (commands[1][0] != '#' || strlen(commands[1]) < 2)
    dprintf(fd, ":HOSTSERVER 403 %s JOIN %s :Channel name invalid\r\n",
	    nick, commands[1]);
  else
    {
      join_channel(e, commands[1], fd);
      write_to_chan(get_chan(e, commands[1]), ptr_user(e, fd), buf, 1);
    }
}

void		add_username(t_env *e, int fd, char **commands)
{
  char		*nick;

  nick = look_for_nickname(e, fd);
  if (wordtab_len(commands) < 2)
    dprintf(fd, ":HOSTSERVER 461 %s USER :Not enough parameters\r\n", nick);
  else if (is_connected(e, fd))
    dprintf(fd, ":HOSTSERVER 462 %s USER :You may not reregister\r\n", nick);
  else
    change_username(e, fd, commands[1]);
}

void		add_nickname(t_env *e, int fd, char **commands, char *buf)
{
  char		*nick;

  nick = look_for_nickname(e, fd);
  if (wordtab_len(commands) < 2)
    dprintf(fd, ":HOSTSERVER 431 %s NICK :No Nick name given\r\n", nick);
  else if (strlen(commands[1]) > MAX_NICKNAME)
    dprintf(fd, ":HOSTSERVER 432 %s NICK %s :Erroneus nickname\r\n",
	    nick, commands[1]);
  else if (nickname_taken(e, commands[1]))
    dprintf(fd, ":HOSTSERVER 433 %s NICK %s :Nickname is already in use\r\n",
	    nick, commands[1]);
  else
    {
      if (strcmp(nick, "*") != 0)
	while_write(e, fd, buf, 1);
      change_nickname(e, fd, commands[1]);
    }
}

void		list_nickname(t_env *e, int fd)
{
  t_user	*tmp;

  tmp = e->users;
  while (tmp)
    {
      if (tmp->username)
	dprintf(fd, "%s %s\n", tmp->nickname, tmp->username);
      tmp = tmp->next;
    }
}
