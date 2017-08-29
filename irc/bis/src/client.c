/*
** client.c for client in /home/abrun/delivery/Tek2/PSU/PSU_2016_myirc
** 
** Made by Alexandre Brun
** Login   <abrun@epitech.net>
** 
** Started on  Wed May 31 09:19:02 2017 Alexandre Brun
** Last update Sun Jun 11 19:22:56 2017 Alexandre Brun
*/

#include "server.h"

int			connect_to(char *h, int p)
{
  struct sockaddr_in	s;
  struct protoent	*pe;
  int			fd;

  if (!(pe = getprotobyname("TCP")))
    return (-1);
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  s.sin_family = AF_INET;
  s.sin_addr.s_addr = inet_addr(h);
  s.sin_port = htons(p);
  if (connect(fd, (struct sockaddr *)&s, sizeof(s)) == -1)
    {
      close(fd);
      return (-1);
    }
  printf("Successfully connected to %s\r\n", h);
  return (fd);
}

void			read_fd(int *fd)
{
  int			ret;
  char			buff[4096];

  memset(buff, 0, 4096);
  if ((ret = read(*fd, buff, 4095)) != -1)
    printf("%s", buff);
}

void			task(int *fd)
{
  struct timeval	tv;
  int			connected;
  fd_set		fd_read;

  connected = 0;
  *fd = 0;
  while (1)
    {
      tv.tv_sec = 20;
      tv.tv_usec = 0;
      FD_ZERO(&fd_read);
      FD_SET(0, &fd_read);
      if (connected && *fd > 0)
	FD_SET(*fd, &fd_read);
      if (select(*fd + 1, &fd_read, NULL, NULL, &tv) == -1)
	perror("select");
      if (FD_ISSET(0, &fd_read))
	new_command(fd, &connected);
      if (connected && FD_ISSET(*fd, &fd_read))
	read_fd(fd);
    }
}

int			main()
{
  int			fd;

  task(&fd);
  if (close(fd) == -1)
    {
      perror("close");
      return (1);
    }
  return (0);
}
