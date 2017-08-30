#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "irc.h"

int		command_nick(char const *msg, t_server *server, t_client *client)
{
  int		i;

  msg = skipspace(msg);
  if (msg[0] == '\0')
    return (add_msg(client, "Invalid nickname", "SERVER"));
  i = 0;
  while (msg[i] != ' ' && msg[i] != '\0' && i < NICKNAME_MAX)
    {
      client->nickname[i] = msg[i];
      i++;
    }
  printf("** client #%d logged as '%s' **\n", client->fd, client->nickname);
  printclients(server);
  return (add_msg(client, "Logged", "SERVER"));
}

int		command_invalid(t_client *client)
{
  return (add_msg(client, "Invalid command", "SERVER"));
}

int		command_join(char const *msg, t_server *server, t_client *client)
{
  
  if (msg[0] != '#')
    return (add_msg(client, "Invalid chanel name", "SERVER"));
  if (add_client_to_chanel(server, client, msg))
    return (EXIT_FAILURE);
  printf("** Client %d (%s) join chanel %s **\n", client->fd, client->nickname, msg);
  printchannels(server);
  printclients(server);
  printclient(server, client);
  return (EXIT_SUCCESS);
}

int		command_part(char const *msg, t_server *server, t_client *client)
{
  
  if (msg[0] != '#')
    return (add_msg(client, "Invalid chanel name", "SERVER"));  
  if (remove_client_from_chanel(server, client, msg))
    return (add_msg(client, "Chanel not joined", "SERVER"));
  printf("** Client #%d (%s) leave chanel %s **\n", client->fd, client->nickname, msg);
  printchannels(server);
  printclients(server);
  printclient(server, client);
  return (EXIT_SUCCESS);
}

 int		command_quit(char const *msg, t_server *server, t_client *client)
{
  (void)(msg);
  (void)(server);
  (void)(client);
  return (EXIT_SUCCESS); 
}

int		command_privmsg(char const *msg, t_server *server, t_client *client)
{
  (void)(msg);
  (void)(server);
  (void)(client);
  return (EXIT_SUCCESS);
}
static t_command	cmds[] =
  {
    {"JOIN ", &command_join, true},
    {"PART ", &command_part, true},
    {"PRIVMSG ", &command_privmsg, true},
    {"QUIT ", &command_quit, false},
    {"NICK ", &command_nick, false},
    {NULL, NULL, false}
  };

int		execute_cmd(char const *cmd, t_server *server, t_client *client)
{
  int		i;
  bool		logged;
  
  logged = (client->nickname[0] == '\0');
  i = 0;
  while (cmds[i].cmd != NULL)
    {
      if (strncmp(cmd, cmds[i].cmd, strlen(cmds[i].cmd)) == 0)
	{
	  if (cmds[i].logged && !logged)
	    return (add_msg(client, "You are not logged in, use NICK", "SERVER"));	    	return (cmds[i].fct(&cmd[strlen(cmds[i].cmd)], server, client));
	}
      i++;
    }
  return (command_invalid(client));
}
