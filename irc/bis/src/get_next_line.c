/*
** get_next_line.c for get_next_line in /home/etienne.labrot/CPE/CPE_2016_getnextline
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Tue Nov 29 10:26:19 2016 Etienne Labrot
** Last update Wed May 31 20:56:56 2017 Etienne Labrot
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

static char	*my_strcat(char *dest, char *src)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (dest[i] != '\0')
    i++;
  while (src[j] != '\0')
    {
      dest[i] = src[j];
      i++;
      j++;
    }
  dest[i] = '\0';
  free(src);
  return (dest);
}

static char	*init_my_buf(char buf[])
{
  int		i;

  i = 0;
  while (i < READ_SIZE)
    {
      buf[i] = 0;
      i++;
    }
  return (buf);
}

static int	read_my_buf(char buf[], int *nb, char **tmp, int fd)
{
  int		i;
  int		j;

  i = 0;
  j = -1;
  while (buf[(*nb) + i] != 0 && buf[(*nb) + i] != '\n' &&
	 ((*nb) + i) < READ_SIZE)
    i++;
  if ((*tmp = malloc(sizeof(char) * (i + 1))) == NULL)
    return (-3);
  while (++j < i)
    (*tmp)[j] = buf[*nb + j];
  (*tmp)[j] = 0;
  if (buf[(*nb) + i] != 0 && ((*nb) + i) < READ_SIZE)
    {
      buf[(*nb) + i] = 0;
      (*nb) += i + 1;
      return (-2);
    }
  *nb = 0;
  buf = init_my_buf(buf);
  return (read(fd, buf, READ_SIZE));
}

char		*get_next_line(const int fd)
{
  static char	buf[READ_SIZE];
  static int	nb = 0;
  static int	end = 1;
  char		*tmp;
  char		*str;

  if ((str = malloc(sizeof(char) * 2000)) == (tmp = NULL) || fd == -1)
    return (NULL);
  str[0] = 0;
  while ((end = read_my_buf(buf, &nb, &tmp, fd)) != -2  && end > 0)
    my_strcat(str, tmp);
  my_strcat(str, tmp);
  if (buf[0] == 0 && (end == -3 || end == -1 || end == 0) && str[0] == 0)
    {
      free(str);
      return (NULL);
    }
  return (str);
}
