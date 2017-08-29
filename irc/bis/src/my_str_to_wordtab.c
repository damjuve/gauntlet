/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/etienne.labrot/CPool_Day08/task04
** 
** Made by Etienne Labrot
** Login   <etienne.labrot@epitech.net>
** 
** Started on  Wed Oct 12 16:04:42 2016 Etienne Labrot
** Last update Sun Jun 11 19:28:09 2017 Alexandre Brun
*/

#include <stdlib.h>
#include "server.h"

static int	my_boolean_verify(char c)
{
  if (c >= 33 && c <= 126)
    return (1);
  else
    return (0);
}

static char	*put_word_in_tab(char *str, int i, int k)
{
  int		it;
  char		*word;

  it = 0;
  word = malloc(sizeof(char) * (k + 1));
  while (it < k)
    {
      word[it] = str[i + it];
      it++;
    }
  word[it] = '\0';
  return (word);
}

void		free_tab(char **wordtab)
{
  int		i;

  i = -1;
  while (wordtab[++i])
    free(wordtab[i]);
  free(wordtab);
}

int		wordtab_len(char **wordtab)
{
  int		i;

  i = -1;
  if (!wordtab)
    return (-1);
  while (wordtab[++i]);
  return (i);
}

char		**my_str_to_wordtab(char *str)
{
  char		**wordtab;
  int		i;
  int		j;
  int		n;

  i = 0;
  n = 0;
  wordtab = malloc(sizeof(char *) * (strlen(str) + 1));
  while (i < (int)strlen(str))
    {
      j = i + 1;
      if (my_boolean_verify(str[i]))
	{
	  while (my_boolean_verify(str[j]))
	    j++;
	  wordtab[n] = put_word_in_tab(str, i, (j - i));
	  i = j + 1;
	  n++;
	}
      else
	i++;
    }
  wordtab[n] = NULL;
  return (wordtab);
}
