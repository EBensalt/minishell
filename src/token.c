/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:32:19 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 03:13:04 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/token.h"
#include "../include/minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = my_malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->e_type = type;
	return (token);
}
