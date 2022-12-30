/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:00:25 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 03:12:42 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_line	*parser_norm2(t_token *token, t_line *line)
{
	char	**str;
	int		i;

	str = ft_split(token->value, 32);
	i = -1;
	while (str[++i])
	{
		token->value = str[i];
		if (!line)
			line = new_nood(token);
		else
			add_nood(&line, token);
	}
	return (line);
}

t_line	*parser_norm1(t_token *token, t_line *line)
{
	if (token->e_type == ENV_VA && check_space(token) == 1)
	{
		line = parser_norm2(token, line);
		g_global.am_red = 1;
	}
	else
	{
		if (!line)
			line = new_nood(token);
		else
			add_nood(&line, token);
	}
	return (line);
}
