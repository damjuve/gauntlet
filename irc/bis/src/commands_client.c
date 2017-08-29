/*
** commands.c for commands in /home/etienne.labrot/PSU/PSU_2016_myirc
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Tue May 30 17:32:21 2017 Etienne Labrot
** Last update Sun Jun 11 19:20:59 2017 Alexandre Brun
*/

#include "server.h"

int		server_command(int *fd, char *infos)
{
  int		ret;
  char		*host;
  int		port;

  ret = 0;
  if (sscanf(infos, " %*s %m[0123456789.][:%d]", &host, &port) == 2)
    {
      if ((*fd = connect_to(host, port)) != -1)
	ret = 1;
      else
	{
	  *fd = 0;
	  dprintf(2, "Error: Could not connect to server.");
	  dprintf(2, "Verify your host and port\n");
	}
    }
  else
    dprintf(2, "USAGE : /server $host[:$port]\n");
  free(host);
  return (ret);
}

int		send_to_server(int *fd, char *line, char *command)
{
  int		i;
  i = -1;
  while (line[++i] && !(line[i] >= 33 && line[i] <= 126));
  while (line[i] && line[i] >= 33 && line[i] <= 126)
    i++;
  while (line[i] && !(line[i] >= 33 && line[i] <= 126))
    i++;
  if (!strcmp(command, "/nick"))
    {
      if (line[i])
	dprintf(*fd, "NICK %s\r\n", line + i);
      else
	dprintf(*fd, "NICK\r\n");
    }
  else if (!strcmp(command, "/quit"))
    {
      if (line[i])
	dprintf(*fd, "QUIT %s\r\n", line + i);
      else
	dprintf(*fd, "QUIT\r\n");
      return (1);
    }
  else
    dprintf(*fd, "%s\r\n", line);
  return (0);
}

void		new_command(int *fd, int *connected)
{
  char		*line;
  char		*command;
  int		quit;

  command = NULL;
  line = get_next_line(0);
  quit = 0;
  sscanf(line, "%ms", &command);
  if (command && !strcmp(command, "/server"))
    {
      if (*connected)
	dprintf(2, "Already connected to a server\n");
      else
	*connected = server_command(fd, line);
    }
  else if (command && *connected)
    quit = send_to_server(fd, line, command);
  else if (command)
    dprintf(2, "Please connect to a server\n");
  free(line);
  free(command);
  if (quit)
    exit(0);
}
