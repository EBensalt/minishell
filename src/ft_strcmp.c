/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:19:46 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/16 14:09:24 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			a;
	unsigned char	*b;
	unsigned char	*c;
	size_t			d;

	b = (unsigned char *)s1;
	c = (unsigned char *)s2;
	a = 0;
	d = 0;
	while (b[d] || c[d])
		d++;
	while (a < d)
	{
		if (b[a] > c[a])
			return (b[a] - c[a]);
		if (b[a] < c[a])
			return (b[a] - c[a]);
		a++;
	}
	return (0);
}
