
#include <stdlib.h>
#include <stdio.h>


int		xerror(char const *s)
{
  perror(s);
  return (EXIT_FAILURE);
}
