/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 01:33:47 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/12 16:59:03 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static int	fword(char const *s, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] != '\0')
	{
		while (s[a] == c && s[a] != '\0')
			a++;
		while (s[a] != c && s[a] != '\0')
		{
			a++;
			if (s[a] == c || s[a] == '\0')
				b++;
		}
	}
	return (b);
}

static int	fchr(char const *s, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] == c && s[a] != '\0')
		a++;
	while (s[a] != c && s[a] != '\0')
	{
		b++;
		a++;
	}
	return (b);
}

static char	*fcpy(char const *s, char c, char *b)
{
	int		a;
	int		d;

	a = 0;
	while (s[a] == c && s[a] != '\0')
		a++;
	d = 0;
	while (s[a] != c && s[a] != '\0')
	{
		b[d] = s[a];
		d++;
		a++;
	}
	b[d] = '\0';
	return (b);
}

static char	**falloc(char const *s, char c, int a, int f)
{
	char	**b;
	int		d;
	int		e;

	d = 0;
	e = 0;
	b = (char **)malloc((a + 1) * sizeof(char *));
	if (b == NULL)
		return (0);
	while (d < a && s[e] != '\0')
	{
		while (s[e] == c && s[e] != '\0')
			e++;
		f = fchr(&s[e], c);
		b[d] = (char *)malloc((f + 1) * sizeof(char));
		if (b[d] == NULL)
			return (0);
		b[d] = fcpy(&s[e], c, b[d]);
		while (s[e] != c && s[e] != '\0')
			e++;
		d++;
	}
	return (b);
}

char	**ft_split(char const *s, char c)
{
	int		a;
	char	**b;

	if (!s)
		return (0);
	a = fword(s, c);
	b = falloc(s, c, a, a);
	if (b == NULL)
		return (0);
	b[a] = NULL;
	return (b);
}
