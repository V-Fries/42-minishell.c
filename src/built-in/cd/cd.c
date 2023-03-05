/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/03 16:52:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "exit_code.h"
#include "error.h"
#include "built_in.h"

static int	change_directory(char *path, t_hashmap env_variables);
static int	getcwd_error(char *path, t_hashmap env_variables);

int	cd(char **args, t_hashmap env_variables)
{
	char	*path;

	if (args[1] != NULL && args[2] != NULL)
	{
		print_error("cd", NULL, "too many arguments");
		return (exit_code(1));
	}
	if (args[1] == NULL)
		path = ft_hm_get_content(env_variables, "HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		print_error("cd", NULL, "HOME not set");
		return (exit_code(1));
	}
	return (exit_code(change_directory(path, env_variables)));
}

static int	change_directory(char *path, t_hashmap env_variables)
{
	char	*old_path;
	int		tmp;

	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
	{
		tmp = getcwd_error(path, env_variables);
		if (tmp <= 0)
			return (tmp < 0);
	}
	if (chdir(path) < 0)
	{
		print_error("cd", path, strerror(errno));
		free(old_path);
		return (1);
	}
	path = getcwd(NULL, 0);
	if (old_path == NULL)
		return (free(old_path), 1);
	if (ft_hm_add_elem(env_variables, "OLDPWD", old_path, &free) < 0)
		return (free(old_path), free(path), 1);
	if (ft_hm_add_elem(env_variables, "PWD", path, &free) < 0)
		return (free(old_path), free(path), 1);
	return (0);
}

static int	getcwd_error(char *path, t_hashmap env_variables)
{
	char	*pwd;
	char	*new_pwd;
	char	*chdir_input;

	if (path[0] != '.')
		return (1);
	pwd = ft_hm_get_content(env_variables, "PWD");
	if (ft_hm_add_elem(env_variables, "OLDPWD", pwd, &free) < 0)
		return (-1);
	new_pwd = ft_strjoin_three(pwd, "/", path);
	if (new_pwd == NULL || ft_hm_add_elem(env_variables, "PWD", new_pwd, NULL)
		< 0)
		return (free(new_pwd), -1);
	chdir_input = get_chdir_input(new_pwd);
	if (chdir_input == NULL)
		perror("cd: error retrieving chdir_input");
	else if (chdir(chdir_input) < 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		perror("getcwd: cannot access parent directories");
	}
	free(chdir_input);
	return (0);
}
