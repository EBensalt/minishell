/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:33:53 by ebensalt          #+#    #+#             */
/*   Updated: 2022/10/29 12:10:32 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	char	*value;
	enum
	{
		TEXT,
		S_QUOT,
		D_QUOT,
		SI_RED,
		SO_RED,
		DI_RED,
		DO_RED,
		PIPE,
		ENV_VA,
		EXIT_C
	}	e_type;
}	t_token;

t_token	*init_token(char *value, int type);
#endif