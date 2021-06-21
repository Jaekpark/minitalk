#PUSH_SWAP_PATH	=	~/42cursus/inner_circles/my_push_swap/
#TESTER			=	./utils/run.sh
INCS				=	minitalk.h
SRCS				=	error.c
SERVER_SRC			=	server.c
CLIENT_SRC			=	client.c

OBJS				=	$(patsubst %.c, %.o, $(SRCS))
SERVER_OBJ			=	$(patsubst %.c, %.o, $(SERVER_SRC))
CLIENT_OBJ			=	$(patsubst %.c, %.o, $(CLIENT_SRC))

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
				@$(RM) $(OBJS_FILE) $(SERVER_OBJ_FILE) $(CLIENT_OBJ_FILE)
				@echo $(GREEN) " - OK" $(EOC)

fclean:
				@make fclean -C $(LIBFT_DIR)
				@echo $(YELLOW) " - fclean minitalk" $(EOC)
				@$(RM) $(NAME) $(CLIENT) $(OBJS_DIR)
				@echo $(GREEN) " - OK" $(EOC)

re:				fclean $(NAME) $(CLIENT)

.PHONY:			all clean fclean re norm debug tester num leaks
