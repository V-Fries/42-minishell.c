/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:08:31 by vfries            #+#    #+#             */
/*   Updated: 2023/01/14 18:08:50 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

enum e_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	OPERATOR = 2,
	PATH_FILE = 3,
};

enum e_operators
{
	OPEN_PARENTHESES = 0,
	CLOSE_PARENTHESES = 1,
	OR = 2,
	AND = 3,
	PIPE = 4,
	INPUT_REDIRECT = 5,
	OUTPUT_REDIRECT = 6,
	HERE_DOC = 7,
	APPEND = 8,
};

typedef struct s_token
{
	enum e_type			type;
	enum e_operators	operator;
	char				*name;
}	t_token;

#endif