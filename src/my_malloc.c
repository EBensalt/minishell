/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 08:50:12 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 03:12:14 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	*my_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	g_global.alloc[g_global.count] = ptr;
	g_global.count++;
	return (ptr);
}

void	my_free(void)
{
	while (g_global.count >= 0)
	{
		free(g_global.alloc[g_global.count]);
		g_global.count--;
	}
}
