#ifndef		IRC_H_
# define	IRC_H_

# define	SIZE_READ	1024
# define	CHANNAME_MAX	256
# define	TOPIC_MAX	256
# define	NICKNAME_MAX	256
# define	LISTEN_MAX	50


typedef struct s_msg t_msg;
typedef struct s_channel t_channel;

typedef struct		s_client
{
  int			fd;
  char			nickname[NICKNAME_MAX];
  t_msg			*msgq;
  struct s_client	*next;
}			t_client;

typedef struct		s_server
{
  t_client		*clients;
  int			port;
  t_channel		*chans;
  int			fd;
  int			maxfd;
  struct timeval	tv;
}			t_server;

typedef struct		s_chanclient
{
  t_client		*client;
  struct s_chanclient	*next;
}			t_chanclient;

typedef struct	s_channel
{
  char			name[CHANNAME_MAX];
  char			topic[TOPIC_MAX];
  t_chanclient		*clients;
  struct s_channel	*next;
}		t_chanel;


typedef struct	s_msg
{
  char		*msg;
  char		from[NICKNAME_MAX];
  struct s_msg	*next;
}		t_msg;

typedef struct	s_command
{
  char		*cmd;
  int		(*fct)(char const *msg, t_server *server, t_client *client);
}		t_command;

// Utils
int		xerror(char const *s);
void		*xmalloc(size_t len);
void		*xrealloc(void* data, size_t len);
char		*xncopy(char const *src, size_t len);
char const	*skipspace(char const *str);

// client
int		client_join(t_server *server);
void		fdset_client(t_server *serv,
			     fd_set *rfds,
			     fd_set *wfds);
void		remove_client(t_server *server, t_client *torm);

// msg
void		send_msg(t_client *client);
int		add_msg(t_client *client, char const *msg, const char *nickname);

// command
int		execute_cmd(char const *cmd, t_server *server, t_client *client);

#endif

