/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:58:10 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/12 19:26:08 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*f1(char *a, const char *s)
{
	int	b;

	b = 0;
	while (s[b] != '\0')
	{
		a[b] = s[b];
		b++;
	}
	return (a);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		c;
	int		b;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	c = 0;
	while (s1[c] != '\0')
		c++;
	b = 0;
	while (s2[b] != '\0')
		b++;
	a = malloc(((c + b) + 1) * sizeof(char));
	if (a == NULL)
		return (0);
	f1(a, s1);
	f1((a + c), s2);
	free((char *)s1);
	a[c + b] = '\0';
	return (a);
}
