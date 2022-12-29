/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:34:52 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/29 09:01:54 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	f1(int n)
{
	int				a;
	unsigned int	b;

	a = 0;
	if (n < 0)
		b = n * -1;
	else
		b = n;
	while (b / 10 > 0)
	{
		a++;
		b = b / 10;
	}
	if (n < 0)
		return (a + 2);
	return (a + 1);
}

static char	*f2(int b, unsigned int d, char *a)
{
	while (b > 0 && d > 0)
	{
		a[b - 1] = (d % 10) + '0';
		b--;
		d = d / 10;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char			*a;
	int				b;
	int				c;
	unsigned int	d;

	b = f1(n);
	a = (char *)my_malloc((b + 1) * sizeof(char));
	if (a == NULL)
		return (0);
	if (n < 0)
	{
		d = n * -1;
		a[0] = '-';
	}
	else
		d = n;
	if (n == 0)
		a[0] = '0';
	c = b;
	a = f2(b, d, a);
	a[c] = '\0';
	return (a);
}
