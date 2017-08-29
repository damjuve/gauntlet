

#ifndef		IRC_H_
# define	IRC_H_

# define	CHANNAME_MAX	256
# define	TOPIC_MAX	256
# define	NICKNAME_MAX	256

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

typedef struct	s_server
{
  t_client	*clients;
  int		port;
  t_channel	*chans;
}		t_server;

struct s_channel
{
  char		name[CHANNAME_MAX];
  char		topic[TOPIC_MAX];
  t_client	*clients;
};

struct		s_msg
{
  char		*msg;
  char		from[NICKNAME_MAX];
}		t_msg;

#endif
