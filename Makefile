#PUSH_SWAP_PATH	=	~/42cursus/inner_circles/my_push_swap/
#TESTER			=	./utils/run.sh
INCS				=	minitalk.h
BONUS_INCS			=	minitalk_bonus.h
SRCS				=	error.c utils_server.c
BONUS_SRCS			=	error_bonus.c utils_server_bonus.c utils_client_bonus.c
BONUS_SERVER_SRC	= 	server_bonus.c
BONUS_CLIENT_SRC	=	client_bonus.c
SERVER_SRC			=	server.c
CLIENT_SRC			=	client.c

OBJS				=	$(patsubst %.c, %.o, $(SRCS))
SERVER_OBJ			=	$(patsubst %.c, %.o, $(SERVER_SRC))
CLIENT_OBJ			=	$(patsubst %.c, %.o, $(CLIENT_SRC))
BONUS_OBJS			=	$(patsubst %.c, %.o, $(BONUS_SRCS))
BONUS_SERVER_OBJ	=	$(patsubst %.c, %.o, $(BONUS_SERVER_SRC))
BONUS_CLIENT_OBJ	=	$(patsubst %.c, %.o, $(BONUS_CLIENT_SRC))

SRCS_DIR		=	./srcs/
OBJS_DIR		=	./objs/
INCS_DIR		=	./includes/

SRCS_FILE			=	$(addprefix $(SRCS_DIR), $(SRCS))
SERVER_SRC_FILE		=	$(addprefix $(SRCS_DIR), $(SERVER_SRC))
CLIENT_SRC_FILE		=	$(addprefix $(SRCS_DIR), $(CLIENT_SRC))
OBJS_FILE			=	$(addprefix $(OBJS_DIR), $(OBJS))
SERVER_OBJ_FILE		=	$(addprefix $(OBJS_DIR), $(SERVER_OBJ))
CLIENT_OBJ_FILE		=	$(addprefix $(OBJS_DIR), $(CLIENT_OBJ))
INCS_FILE			= 	$(addprefix $(INCS_DIR), $(INCS))

BONUS_SRCS_FILE			=	$(addprefix $(SRCS_DIR), $(BONUS_SRCS))
BONUS_SERVER_SRC_FILE	=	$(addprefix $(SRCS_DIR), $(BONUS_SERVER_SRC))
BONUS_CLIENT_SRC_FILE	=	$(addprefix $(SRCS_DIR), $(BONUS_CLIENT_SRC))
BONUS_OBJS_FILE			=	$(addprefix $(OBJS_DIR), $(BONUS_OBJS))
BONUS_SERVER_OBJ_FILE	=	$(addprefix $(OBJS_DIR), $(BONUS_SERVER_OBJ))
BONUS_CLIENT_OBJ_FILE	=	$(addprefix $(OBJS_DIR), $(BONUS_CLIENT_OBJ))
BONUS_INCS_FILE			= 	$(addprefix $(INCS_DIR), $(BONUS_INCS))

LIBFT			=	./libft/libft.a
LIBFT_DIR		=	./libft
LIBFT_INCS		=	./includes/libft.h

CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
HEADER_FLAG		=	-I$(INCS_DIR) -I$(LIBFT_INCS)
LIB_FLAG		=	-lft -L$(LIBFT_DIR)
NAME			=	server
CLIENT			=	client
BONUS_NAME		=	server_bonus
BONUS_CLIENT	=	client_bonus

BLACK			=	"\033[1;30m"
RED				=	"\033[1;31m"
GREEN			=	"\033[1;32m"
YELLOW			=	"\033[1;33m"
BLUE			=	"\033[1;34m"
CYAN			=	"\033[1;35m"
PURPLE			=	"\033[1;36m"
WHITE			=	"\033[1;37m"
EOC				=	"\033[0;0m"


all:			$(NAME) $(CLIENT)

bonus:			$(BONUS_NAME) $(BONUS_CLIENT)

$(BONUS_NAME):	$(LIBFT) $(OBJS_DIR) $(BONUS_OBJS_FILE) $(BONUS_SERVER_OBJ_FILE)
				@echo $(YELLOW) " - Compiling $@"
				@$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(BONUS_OBJS_FILE) $(BONUS_SERVER_OBJ_FILE) -o $@
				@echo $(GREEN) " - OK" $(EOC)

$(BONUS_CLIENT):$(LIBFT) $(OBJS_DIR) $(BONUS_OBJS_FILE) $(BONUS_CLIENT_OBJ_FILE)
				@echo $(YELLOW) " - Compiling $@"
				@$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(BONUS_OBJS_FILE) $(BONUS_CLIENT_OBJ_FILE) -o $@
				@echo $(GREEN) " - OK" $(EOC)

$(LIBFT):
				@make -C ./libft

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS_FILE) $(SERVER_OBJ_FILE)
				@echo $(YELLOW) " - Compiling $@"
				@$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS_FILE) $(SERVER_OBJ_FILE) -o $@
				@echo $(GREEN) " - OK" $(EOC)

$(CLIENT):		$(LIBFT) $(OBJS_DIR) $(OBJS_FILE) $(CLIENT_OBJ_FILE)
				@echo $(YELLOW) " - Compiling $@"
				@$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS_FILE) $(CLIENT_OBJ_FILE) -o $@
				@echo $(GREEN) " - OK" $(EOC)

$(SERVER_OBJ_FILE):
				@$(CC) -c $(CFLAGS) $(HEADER_FLAG) $(SERVER_SRC_FILE) -o $(SERVER_OBJ_FILE)

$(CLIENT_OBJ_FILE):
				@$(CC) -c $(CFLAGS) $(HEADER_FLAG) $(CLIENT_SRC_FILE) -o $(CLIENT_OBJ_FILE)

$(BONUS_SERVER_OBJ_FILE):
				@$(CC) -c $(CFLAGS) $(HEADER_FLAG) $(BONUS_SERVER_SRC_FILE) -o $(BONUS_SERVER_OBJ_FILE)

$(BONUS_CLIENT_OBJ_FILE):
				@$(CC) -c $(CFLAGS) $(HEADER_FLAG) $(BONUS_CLIENT_SRC_FILE) -o $(BONUS_CLIENT_OBJ_FILE)

$(OBJS_DIR) :
					@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.c $(INCS_FILE)
					@$(CC) -c $(CFLAGS) $(HEADER_FLAG) $< -o $@

norm:			$(SRCS_FILE) $(INCS_FILE) $(SERVER_SRC_FILE) $(CLIENT_SRC_FILE)
				@echo $(CYAN) " - push swap norm check"$(EOC)
				@norminette $(SRCS_FILE) $(INCS_FILE) $(CLIENT_SRC_FILE) $(SERVER_SRC_FILE)
				@make norm -C $(LIBFT_DIR)

# leaks:
# 	@osascript -e 'tell app "Terminal" to do script "while true; do leaks push_swap; sleep 2; clear; done"'
# 	@osascript -e 'tell app "Terminal" to do script "while true; do leaks checker; sleep 2; clear; done"'
# 	@./utils/leaks.sh

clean:
				@make clean -C $(LIBFT_DIR)
				@echo $(YELLOW) " - clean push_swap" $(EOC)
				@$(RM) $(OBJS_FILE) $(SERVER_OBJ_FILE) $(CLIENT_OBJ_FILE) $(BONUS_OBJS_FILE) $(BONUS_SERVER_OBJ_FILE) $(BONUS_CLIENT_OBJ_FILE)
				@echo $(GREEN) " - OK" $(EOC)

fclean:
				@make fclean -C $(LIBFT_DIR)
				@echo $(YELLOW) " - fclean minitalk" $(EOC)
				@$(RM) $(NAME) $(CLIENT) $(OBJS_DIR) $(BONUS_NAME) $(BONUS_CLIENT)
				@echo $(GREEN) " - OK" $(EOC)

re:				fclean $(NAME) $(CLIENT)

.PHONY:			all clean fclean re norm debug tester num leaks
