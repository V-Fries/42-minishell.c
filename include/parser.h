/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:14:45 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 21:59:12 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <stdbool.h>

bool				parse_tokens(t_list	**tokens, t_hashmap env_variables);

// quote
int					remove_quotes(t_list *tokens);
int					is_valid_quote(char *command);

//	simplify_tokens
//	{
//		add_command
//		{
//			add_path
//			{
//				absolute_path.c
bool				is_absolute_path(t_token *command, t_hashmap env_variables);
int					command_is_absolute_path(t_token *command);
//				add_path.c
int					add_path(t_token *command, t_hashmap env_variables);
//				builtin.c
enum e_builtin		is_builtin(char *command_name);
//				command.c
int					command_is_in_path(t_token *command,
						t_hashmap env_variables);
//			}
//			add_args.c
int					add_args(t_token *token, t_list **args);
//			add_command.c
int					get_new_command(t_list **tokens, t_hashmap env_variables,
						t_token **new_command);
//			get_files.c
int					get_files(t_list **files, t_list **simplified_files,
						t_list **tokens);
//		}
//		get_subshells.c
t_list				*get_subshells(t_list *tokens);
//		simplify_tokens.c
int					simplify_tokens(t_list **tokens, t_hashmap env_variables);
//	}

//	syntax
//	{
//		is_syntax_ok.c
bool				is_syntax_ok(t_list *tokens);
//		syntax_tools.c
bool				syntax_is_operator(t_list *token_lst);
bool				syntax_is_empty(t_list *token_lst);
enum e_operators	syntax_get_operator(t_list *token_lst);
void				print_syntax_error(t_list *token);
//	}

#endif
