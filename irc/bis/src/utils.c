/*
** utils.c for utils in /home/abrun/delivery/Tek2/PSU/PSU_2016_myirc
** 
** Made by Alexandre Brun
** Login   <abrun@epitech.net>
** 
** Started on  Tue May 23 11:18:42 2017 Alexandre Brun
** Last update Sun Jun 11 19:35:27 2017 Alexandre Brun
*/

#include "server.h"

void			exec_this(t_env *e, int fd, char *cmd)
{
  char			**commands;

  commands = my_str_to_wordtab(cmd);
  if (!strcasecmp(commands[0], "NICK"))
    add_nickname(e, fd, commands, cmd);
  else if (!strcasecmp(commands[0], "USER"))
    add_username(e, fd, commands);
  else if (!strcasecmp(commands[0], "NAMES"))
    list_nickname(e, fd);
  else if (!strcasecmp(commands[0], "QUIT"))
    close_connection(e, fd, cmd);
  else if (!is_connected(e, fd))
    dprintf(fd, ":HOSTSERVER 451 %s :You have not registered\r\n", commands[0]);
  else if (!strcasecmp(commands[0], "USERS"))
    list_nickname(e, fd);
  else if (!strcasecmp(commands[0], "JOIN"))
    join_command(e, fd, commands, cmd);
  else if (!strcasecmp(commands[0], "PART"))
    part_command(e, fd, commands, cmd);
  else if (!strcasecmp(commands[0], "PRIVMSG"))
    privmsg(e, fd, commands, cmd);
  else
    dprintf(fd, ":HOSTSERVER 421 %s %s :Unknow command\r\n",
	    look_for_nickname(e,fd), commands[0]);
  free_tab(commands);
}

void			client_read(t_env *e, int fd)
{
  int			i;
  int			j;
  int			retval;
  char			to_exec[512];
  char			buf[5000];

  memset(buf, 0, 5000);
  if ((retval = read(fd, buf, 4999)))
    {
      buf[retval] = 0;
      i = -1;
      j = 0;
      while (buf[++i])
	{
	  if (buf[i] == '\n')
	    {
	      memset(to_exec, 0, 512);
	      strncpy(to_exec, buf + j, i - j);
	      exec_this(e, fd, to_exec);
	      j = i + 1;
	    }
	}
    }
  else
    close_connection(e, fd, NULL);
}

void			add_client(t_env *my_env, int socket_id)
{
  int			cs;
  struct sockaddr_in	client_sin;
  unsigned		client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(socket_id, (struct sockaddr *)&client_sin, &client_sin_len);
  my_env->fd_type[cs] = FD_CLIENT;
  my_env->fct_read[cs] = client_read;
  add_user(my_env, cs);
}

void			server_read(t_env *my_env, int fd)
{
  printf("New Client\n");
  add_client(my_env, fd);
}

void			add_server(t_env *my_env)
{
  int			my_socket;
  struct sockaddr_in	sin;

  my_socket = socket(PF_INET, SOCK_STREAM, 0);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(my_env->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(my_socket, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      close(my_socket);
      perror("bind");
      exit(-1);
    }
  listen(my_socket, 42);
  my_env->fd_type[my_socket] = FD_SERVER;
  my_env->fct_read[my_socket] = server_read;
}
