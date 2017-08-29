
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "irc.h"

int		add_msg(t_client *client, char const *msg, const char *nickname)
{
  t_msg		*new;
  t_msg		*tmp;

  if ((new = xmalloc(sizeof(*new))) == NULL)
    return (EXIT_FAILURE);
  if ((new->msg = xncopy(msg, strlen(msg))) == NULL)
      return (EXIT_FAILURE);
  new->next = NULL;
  memset(new->from, 0, NICKNAME_MAX);
  strncpy(new->from, nickname, NICKNAME_MAX);
  if ((tmp = client->msgq) == NULL)
    client->msgq = new;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
    }
  return (EXIT_SUCCESS);
}

t_msg		*get_msg(t_client *client)
{
  t_msg		*ret;

  ret = client->msgq;
  client->msgq = client->msgq->next;
  return (ret);
}

void		send_msg(t_client *client)
{
  t_msg		*msg;

  if (client->msgq != NULL)
    {
      msg = get_msg(client);
      if (dprintf(client->fd, "FROM %s: %s", msg->from, msg->msg) < 0)
	perror("Write failed (send_msg)\n");
      free(msg);
    }
}

int		add_msg_to_chan(t_server *server, t_client *except,
				char const *msg, char const* from)
{
  

}
