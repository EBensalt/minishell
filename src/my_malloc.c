/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 08:50:12 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/29 09:11:45 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	*my_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	alloc[count] = ptr;
	count++;
	return (ptr);
}

void	my_free(void)
{
	while (count >= 0)
	{
		free(alloc[count]);
		count--;
	}
}