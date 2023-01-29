/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:02:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/29 01:30:42 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "lexer.h"

void				execute_command(t_token *command, t_hashmap env_variables,
						t_list *here_docs);

int					execute_pipes(t_list **tokens, t_hashmap env_variables,
						t_list **here_docs);

void				execute_commands(t_list **tokens, t_hashmap env_variables,
						t_list **here_docs);

enum e_operators	get_next_operator(t_list *tokens);
void				get_next_command(t_list **tokens, int exit_code);

int					open_and_dup_files(t_list *files, t_hashmap env_variables,
						t_list *here_docs);

void				run_builtin(t_token *command, t_hashmap env_variables,
						t_list *here_docs);

#endif
