/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:08:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/14 02:42:02 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "lexer.h"
#include "get_here_docs.h"
#include "minishell_signal.h"
#include "parser.h"

static int	get_input(char **input);
static int	get_forked_input(int *pipe_fd);
static int	read_input(int *pipe_fd, char **input);
static void	close_pipe(int *fd);

int	get_input_command(char **command, char *join, t_list **here_docs)
{
	char	*new_input;
	char	*new_command;
	int		return_code;

	return_code = get_input(&new_input);
	if (return_code != 0)
		return (return_code);
	if (ft_strlen(new_input) > 0)
	{
		return_code = get_here_docs(new_input, here_docs);
		if (return_code != 0)
			return (free(new_input), return_code);
	}
	new_command = ft_strjoin_three(*command, join, new_input);
	free(*command);
	free(new_input);
	*command = new_command;
	return (*command == NULL);
}

static int	get_input(char **input)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		exit_code;

	if (pipe(pipe_fd) < 0)
		return (1);
	pid = fork();
	if (pid == -1)
		return (close_pipe(pipe_fd), 1);
	else if (pid == 0)
		exit(get_forked_input(pipe_fd));
	if (waitpid(pid, &exit_code, 0) < 0)
		return (close_pipe(pipe_fd), 1);
	exit_code = WEXITSTATUS(exit_code);
	if (exit_code == 130 || exit_code == 1)
		return (close_pipe(pipe_fd), exit_code);
	return (read_input(pipe_fd, input));
}

static int	get_forked_input(int *pipe_fd)
{
	char	*input;

	errno = 0;
	init_interactive_signal_handling();
	if (errno != 0)
		return (close_pipe(pipe_fd), 1);
	input = readline("> ");
	ft_putstr_fd(input, pipe_fd[1]);
	if (errno != 0)
		return (free(input), close_pipe(pipe_fd), 1);
	free(input);
	close_pipe(pipe_fd);
	if (errno != 0)
		return (1);
	return (0);
}

static int	read_input(int *pipe_fd, char **input)
{
	if (close(pipe_fd[1]) < 0)
	{
		close(pipe_fd[0]);
		return (1);
	}
	*input = get_next_line(pipe_fd[0]);
	if (close(pipe_fd[0]) < 0)
		return (1);
	if (*input == NULL)
	{
		ft_printf("bash: syntax error: unexpected end of file\n");
		return (2);
	}
	return (0);
}

static void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}