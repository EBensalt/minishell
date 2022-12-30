/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:27:18 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 09:53:11 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	checker_norm(t_line *ptr, t_line *ptr0)
{
	if ((ptr->type == SI_RED || ptr->type == SO_RED
			|| ptr->type == DI_RED || ptr->type == DO_RED)
		&& (ptr->next == NULL || ptr0->type == PIPE
			|| ptr0->type == SI_RED || ptr0->type == SO_RED
			|| ptr0->type == DI_RED || ptr0->type == DO_RED))
	{
		write(2, "error : redirections\n", 21);
		g_global.g_exit = 258;
		return (1);
	}
	if ((ptr->type == SI_RED || ptr->type == SO_RED || ptr->type == DO_RED)
		&& (!ptr->next->value || g_global.am_red == 1))
	{
		write(2, "error : ambiguous redirect\n", 27);
		g_global.g_exit = 1;
		g_global.am_red = 2;
		return (0);
	}
	return (0);
}

int	checker(t_line *line)
{
	t_line	*ptr;
	t_line	*ptr0;
	int		i;

	ptr = line;
	i = 0;
	while (ptr)
	{
		if (ptr->next)
			ptr0 = ptr->next;
		if (ptr->type == PIPE
			&& (ptr->next == NULL || ptr == line || ptr->type == ptr0->type))
		{
			write(2, "error : pipes error\n", 20);
			g_global.g_exit = 258;
			return (1);
		}
		i = checker_norm(ptr, ptr0);
		if (i != 0)
			return (i);
		ptr = ptr->next;
	}
	return (0);
}
