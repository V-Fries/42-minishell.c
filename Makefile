NAME			=	minishell


SRC_PATH		=	src/

SRC				=\
	builtins/alias/alias.c				\
	builtins/alias/get_all_aliases.c		\
\
	builtins/cd/cd.c							\
	builtins/cd/get_cleaned_path.c			\
	builtins/cd/handle_cwd_doesnt_exist.c	\
\
	builtins/export/export.c		\
	builtins/export/print.c		\
	builtins/export/variables.c	\
	builtins/export/variable.c	\
\
	builtins/echo.c						\
	builtins/env.c						\
	builtins/exit.c						\
	builtins/pwd.c						\
	builtins/unalias.c					\
	builtins/unset.c					\
\
\
	env_variables/get_env_variables.c	\
	env_variables/get_envp.c			\
	env_variables/print_env_variables.c	\
\
\
	error/error.c	\
\
\
	execution/exec_here_docs_tools.c	\
	execution/execute_command.c			\
	execution/execute_command_no_pipe.c	\
	execution/execute_piped_command.c	\
	execution/execute_pipes.c			\
	execution/execution.c				\
	execution/io_save.c					\
	execution/open_and_dup_files.c		\
	execution/run_builtin.c				\
\
\
	expansions/lexer/expressions.c		\
	expansions/lexer/tokens.c			\
	expansions/lexer/utils.c			\
\
	expansions/parameters/replace.c				\
	expansions/parameters/strdup_parameters.c	\
\
	expansions/paths/absolute_path.c	\
	expansions/paths/add_path.c			\
	expansions/paths/builtin.c			\
	expansions/paths/command.c			\
\
	expansions/wildcards/add.c				\
	expansions/wildcards/list.c				\
	expansions/wildcards/match.c			\
	expansions/wildcards/pattern_lexer.c	\
	expansions/wildcards/replace.c			\
	expansions/wildcards/slash.c			\
	expansions/wildcards/utils.c			\
\
	expansions/words/merge.c			\
	expansions/words/splitting.c		\
	expansions/alias.c					\
	expansions/arguments.c				\
	expansions/files.c					\
	expansions/here_docs.c				\
	expansions/quotes.c					\
	expansions/tildes.c					\
	expansions/token.c					\
	expansions/utils.c					\
\
\
	interactive/delimiters.c		\
	interactive/here_docs.c			\
	interactive/here_docs_syntax.c	\
	interactive/input.c				\
	interactive/parsing.c			\
	interactive/shell.c				\
	interactive/utils.c				\
\
	lexer/identifier.c \
	lexer/operator.c	\
	lexer/token.c		\
\
\
\
	parser/simplify_tokens/get_subshells.c			\
	parser/simplify_tokens/simplify_tokens.c		\
\
	parser/simplify_tokens/add_command/add_args.c		\
	parser/simplify_tokens/add_command/add_command.c	\
	parser/simplify_tokens/add_command/get_files.c		\
\
	parser/syntax.c			\
	parser/quotes.c			\
\
\
	prompt/add_directory_to_path.c	\
	prompt/add_elem_to_prompt.c		\
	prompt/add_git_branch.c			\
	prompt/get_command_result.c		\
	prompt/get_prompt.c				\
	prompt/is_valid_term.c			\
\
\
	signals/execution_fork.c				\
	signals/fork_signal_handling.c			\
	signals/general_signal_handling.c		\
	signals/get_cursor_x_pos.c				\
	signals/interactive_signal_handling.c	\
	signals/pipes_signal_handling.c			\
\
\
	execute_single_line_command.c	\
	exit_code.c						\
	main.c							\
	run_minishellrc.c				\
	terminal.c						\
	free_minishell.c


DIR_INCS =\
	include/			\
	$(LIBFT_INCLUDES)

OS	= $(shell uname -s)

ifeq ($(OS), Linux)
	LIBS = \
		-l readline	\
		$(LIBFT_L)
	INCLUDES =\
	$(addprefix -I , $(DIR_INCS))
endif
ifeq ($(OS), Darwin)
	LIBS = \
		$(LDFLAGS) -l readline	\
		$(LIBFT_L)
	INCLUDES =\
		$(addprefix -I , $(DIR_INCS))	\
		$(CPPFLAGS)
endif


DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS		=	-MMD -MP
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address
RM				=	rm -rf
AR				=	ar rcs

LIBFT_PATH		=	lib/libft/
LIBFT_INCLUDES	=	$(LIBFT_PATH)include
LIBFT_L			=	-L $(LIBFT_PATH) -l ft
LIBFT_L_DEBUG	=	-L $(LIBFT_PATH) -l ft_debug
LIBFT_A			=	$(LIBFT_PATH)libft.a
LIBFT_A_DEBUG	=	$(LIBFT_PATH)libft_debug.a
MAKE_LIBFT		=	$(MAKE) -C $(LIBFT_PATH)

DEPENDENCIES	=	$(LIBFT_A)

.PHONY:		all
all:
			$(MAKE_LIBFT)
			$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

.PHONY:	bonus
bonus:	all

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
		@mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
