NAME			=	minishell


SRC_PATH		=	src/

SRC				=\
	env_variables/get_env_variables.c	\
	env_variables/get_envp.c			\
	env_variables/print_env_variables.c	\
\
\
	error/error.c	\
\
\
	built-in/echo.c		\
	built-in/cd.c		\
	built-in/pwd.c		\
	built-in/export.c	\
	built-in/env.c		\
	built-in/exit.c		\
	built-in/unset.c	\
\
\
	execution/execute_command.c		\
	execution/execute_pipes.c		\
\
\
	lexer/identifier.c \
	lexer/operator.c	\
	lexer/token.c		\
\
\
	parser/quote/remove.c	\
	parser/quote/valid.c	\
\
\
	parser/operator/valid.c \
\
	parser/simplify_tokens/add_command/add_path/absolute_path.c		\
	parser/simplify_tokens/add_command/add_path/add_path.c			\
	parser/simplify_tokens/add_command/add_path/builtin.c			\
	parser/simplify_tokens/add_command/add_path/command.c			\
\
	parser/simplify_tokens/add_command/add_args.c		\
	parser/simplify_tokens/add_command/add_command.c	\
	parser/simplify_tokens/add_command/get_files.c		\
\
	parser/simplify_tokens/simplify_tokens.c		\
\
	parser/wildcard/match.c	\
\
	get_here_docs.c	\
	main.c


DIR_INCS		=\
	include/	\
	$(LIBFT_INCLUDES)

INCLUDES		=	$(addprefix -I , $(DIR_INCS))

DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS		=	-MMD -MP
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g3
RM				=	rm -rf
AR				=	ar rcs


LIBFT_PATH		=	lib/libft/
LIBFT_INCLUDES	=	$(LIBFT_PATH)include
LIBFT_L			=	-L$(LIBFT_PATH) -lft
LIBFT_L_DEBUG	=	-L$(LIBFT_PATH) -lft_debug
LIBFT_A			=	$(LIBFT_PATH)libft.a
LIBFT_A_DEBUG	=	$(LIBFT_PATH)libft_debug.a
MAKE_LIBFT		=	$(MAKE) -C $(LIBFT_PATH)

DEPENDENCIES	=	$(LIBFT_A)

.PHONY:		all
all:
			$(MAKE_LIBFT)
			$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_L) -o $(NAME) -lreadline


.PHONY:	clean
clean:
		$(MAKE_LIBFT) clean
		$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
		$(MAKE_LIBFT) fclean
		$(RM) $(NAME)

.PHONY:	re
re:		fclean
		$(MAKE) all

-include $(DEPS)

$(DIR_BUILD)%.o : $(SRC_PATH)%.c $(LIBFT_A)
		mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
