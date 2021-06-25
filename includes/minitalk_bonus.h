#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

# define SERV_ARG_ERR "Server program cannot receive parameters.\n"
# define SERV_RUN "Start minitalk server...\n"
# define CLIENT_ARG_ERR "Client program requires 3 parameters.\n./client [PID] [Message].\n"
# define SIGNAL_ERR1 "Signal error (code 1).\n"
# define SIGNAL_ERR2 "Signal error (code 2).\n"
# define SIGNAL_ERR3 "Signal error (code 3).\n"
# define SIGACTION_ERR "Sigaction error.\n"
# define MSG_ERR "Message transfer error.\n"
# define ASCII_ERR "Client can only handle ascii characters.\n"

typedef struct	s_flag
{
	int		len;
	int		len_bit;
	int		total_bit;
	char	*str;
	int		str_bit;
	int		idx;

}				t_flag;

void	handle_error(char *err_msg);
void	init_flag(t_flag *flag);
void	start_minitalk(t_flag *flag, int *is_start);
void	parse_len(int signum, t_flag *flag);
void	parse_str(int signum, t_flag *flag);
void	end_minitalk(t_flag *flag, int *is_start, siginfo_t *siginfo);
int		check_ascii(char *str);
void	print_client_msg(pid_t client, int cnt, int is_null);

#endif
