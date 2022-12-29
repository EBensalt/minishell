/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:27:18 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/15 16:19:52 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	checker_norm(t_line *ptr, t_line *ptr0, t_line *line)
{
	if ((ptr->type == SI_RED || ptr->type == SO_RED
			|| ptr->type == DI_RED || ptr->type == DO_RED)
		&& (ptr->next == NULL || ptr0->type == PIPE
			|| ptr0->type == SI_RED || ptr0->type == SO_RED
			|| ptr0->type == DI_RED || ptr0->type == DO_RED))
	{
		printf("\033[0;31merror\033[0m : redirections\n");
		g_exit = 4;
		return (1);
	}
	if ((ptr->type == SI_RED || ptr->type == SO_RED || ptr->type == DO_RED)
		&& (!ptr->next->value || line->am_red == 1))
	{
		printf("\033[0;31merror\033[0m : ambiguous redirect\n");
		g_exit = 5;
		return (1);
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
			printf("\033[0;31merror\033[0m : pipes error\n");
			g_exit = 3;
			return (1);
		}
		i = checker_norm(ptr, ptr0, line);
		if (i != 0)
			return (i);
		ptr = ptr->next;
	}
	return (0);
}
