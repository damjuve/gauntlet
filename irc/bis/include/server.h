/*
** server.h for server in /home/abrun/delivery/Tek2/PSU/PSU_2016_myirc
** 
** Made by Alexandre Brun
** Login   <abrun@epitech.net>
** 
** Started on  Tue May 23 11:24:57 2017 Alexandre Brun
** Last update Sun Jun 11 20:58:16 2017 Etienne Labrot
*/

#ifndef SERVER_H_H
# define SERVER_H_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/time.h>
# include <netdb.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>

# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2
# define MAX_FD 255
# define MAX_CHANNAME 200
# define MAX_TOPIC 128
# define MAX_NICKNAME 9
# define MAX_USERNAME 52

# ifndef READ_SIZE
#  define READ_SIZE 100
# endif

typedef void(*my_fct)();

typedef struct		s_user
{
  char			nickname[MAX_NICKNAME + 1];
  char			username[MAX_USERNAME + 1];
  int			fd;
  int			connect;
  struct s_user		*next;
}			t_user;

typedef struct		s_channel
{
  char			name[MAX_CHANNAME + 1];
  char			topic[MAX_TOPIC + 1];
  t_user		*users[MAX_FD];
  struct s_channel	*next;
}			t_channel;

typedef struct	s_env
{
  char		fd_type[MAX_FD];
  my_fct	fct_read[MAX_FD];
  t_user	*users;
  int		port;
  t_channel	*chans;
}		t_env;

void		change_username(t_env *e, int fd, char *username);
void		change_nickname(t_env *e, int fd, char *nick);
int		close_connection(t_env *e, int fd, char *message);
void		part_command(t_env *e, int fd, char **commands, char *cmd);
void		join_command(t_env *e, int fd, char **commands, char *buf);
void		add_username(t_env *e, int fd, char **commands);
void		add_nickname(t_env *e, int fd, char **commands, char *buf);
void		list_nickname(t_env *e, int fd);
char		*look_for_nickname(t_env *e, int fd);
t_channel	*get_chan(t_env *e, char *name);
int		get_fd_by_nickname(t_env *e, char *name);
int		nickname_taken(t_env *e, char *nick);
int		is_connected(t_env *e, int fd);
void		write_to_user(t_env *e, int to, int fd, char *buf);
void		write_to_chan(t_channel *chan, t_user *us, char *buf, int ok);
void		while_write(t_env *e, int fd, char *buf, int ok);
void		privmsg(t_env *e, int fd, char **commands, char *cmd);
void		add_user(t_env *e, int fd);
int		delete_user(t_env *e, int fd);
int		connect_to(char *h, int p);
int		server_command(int *fd, char *infos);
void		new_command(int *fd, int *connected);
char		*get_next_line(const int fd);
void		free_tab(char **wordtab);
int		wordtab_len(char **wordtab);
char		**my_str_to_wordtab(char *str);
void		add_server(t_env *my_env);
void		join_channel(t_env *e, char *name, int fd);
int		leave_channel(t_env *e, char *name, int fd);
void		init_stuffs(t_env *my_env, char *av);
void		delete_from_all_chans(t_env *e, int fd);
t_user		*ptr_user(t_env *e, int fd);

#endif
