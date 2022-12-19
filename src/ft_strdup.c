/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:19:15 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/06 12:15:02 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *s1)
{
	int		a;
	char	*b;

	if (!s1)
		return (0);
	a = 0;
	while (s1[a] != '\0')
		a++;
	b = malloc(a + 1 * sizeof(char));
	if (b == NULL)
		return (0);
	a = 0;
	while (s1[a] != '\0')
	{
		b[a] = s1[a];
		a++;
	}
	b[a] = '\0';
	return (b);
}
