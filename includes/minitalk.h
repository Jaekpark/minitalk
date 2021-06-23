#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

# define SERV_ARG_ERR "Server program cannot receive parameters.\n"
# define SERV_RUN "Start minitalk server...\n"
# define CLIENT_ARG_ERR "Client program requires 3 parameters.\n./client [PID] [Message].\n"
# define SIGNAL_ERR "Signal error.\n"
# define SIGACTION_ERR "Sigaction error.\n"
# define MSG_ERR "Message transfer error.\n"

typedef struct s_flag
{
	int len;
	int len_bit;
	char *str;
	int str_bit;
	int is_null;
	int is_char;
	int is_end;
} t_flag;

void handle_error(char *err_msg);

#endif
