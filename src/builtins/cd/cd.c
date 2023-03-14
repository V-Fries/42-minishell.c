/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/05 19:55:03 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "exit_code.h"
#include "error.h"
#include "builtin.h"

static int	change_directory(char *path, t_hashmap env_variables);
static bool	does_cwd_exist(void);
static char	*get_new_path(t_hashmap env_variables, char *path);

int	cd(char **args, t_hashmap env_variables)
{
	char	*path;

	if (args[1] != NULL && args[2] != NULL)
	{
		print_error("cd", NULL, "too many arguments");
		return (set_exit_code(1));
	}
	if (args[1] == NULL)
		path = ft_hm_get_content(env_variables, "HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		print_error("cd", NULL, "HOME not set");
		return (set_exit_code(1));
	}
	return (set_exit_code(change_directory(path, env_variables)));
}

static int	change_directory(char *path, t_hashmap env_variables)
{
	char	*pwd;
	char	*cleaned_path;

	if (does_cwd_exist() == false && path[0] == '.')
		return (handle_cwd_doesnt_exist(path, env_variables));
	cleaned_path = get_new_path(env_variables, path);
	if (cleaned_path == NULL)
		return (print_error("cd", "failed to get new path", get_error()), -1);
	if (chdir(cleaned_path) < 0)
	{
		print_error("cd", path, strerror(errno));
		free(cleaned_path);
		return (1);
	}
	pwd = ft_hm_get_content(env_variables, "PWD");
	if (ft_hm_add_elem(env_variables, "OLDPWD", pwd, &free) < 0)
		return (print_error("cd", "failed to update OLDPWD", get_error()),
			free(cleaned_path),
			-1);
	if (ft_hm_add_elem(env_variables, "PWD", cleaned_path, NULL) < 0)
		return (print_error("cd", "failed to update PWD", get_error()),
			free(cleaned_path),
			-1);
	return (0);
}

static bool	does_cwd_exist(void)
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
	free(cwd);
	return (cwd != NULL);
}

static char	*get_new_path(t_hashmap env_variables, char *path)
{
	char	*new_path;
	char	*pwd;
	char	*tmp;

	if (path[0] == '/')
		return (get_cleaned_path(path));
	pwd = ft_hm_get_content(env_variables, "PWD");
	if (pwd == NULL)
		return (getcwd(NULL, 0));
	tmp = ft_strjoin_three(pwd, "/", path);
	if (tmp == NULL)
		return (NULL);
	new_path = get_cleaned_path(tmp);
	free(tmp);
	return (new_path);
}
