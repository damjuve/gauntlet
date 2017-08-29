#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char const	*skipspace(char const *str)
{
  int		i;

  i = 0;
  while (str[i] == ' ')
    i++;
  return (&str[i]);
}

int		xerror(char const *s)
{
  perror(s);
  return (EXIT_FAILURE);
}

void		*xmalloc(size_t len)
{
  void		*data;

  if ((data = malloc(len)) == NULL)
    perror("Malloc failed\n");
  return (data);
}

void		*xrealloc(void *src, size_t len)
{
  void		*data;

  if ((data = realloc(src, len)) == NULL)
    perror("Realloc failed\n");
  return (data);
}

char		*xncopy(char const *src, size_t len)
{
  char		*dest;

  dest = xmalloc(len + 1);
  if (dest == NULL)
    return (NULL);
  strncpy(dest, src, len);
  dest[len] = '\0';
  return (dest);
}
