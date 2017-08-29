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
  t_channel		*channel;
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

typedef struct	s_channel
{
  char			name[CHANNAME_MAX];
  char			topic[TOPIC_MAX];
  t_client		*clients;
  struct s_channel	*next;
}		t_chanel;

typedef struct	s_msg
{
  char		*msg;
  char		from[NICKNAME_MAX];
  struct s_msg	*next;
}		t_msg;

// Utils
int		xerror(char const *s);
void		*xmalloc(size_t len);
void		*xrealloc(void* data, size_t len);
char		*xncopy(char const *src, size_t len);

// client
int		client_join(t_server *server);
void		fdset_client(t_server *serv,
			     fd_set *rfds,
			     fd_set *wfds);

#endif

