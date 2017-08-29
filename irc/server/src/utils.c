
#include <stdlib.h>
#include <stdio.h>


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
