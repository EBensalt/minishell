/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:44:53 by hkhalil           #+#    #+#             */
/*   Updated: 2022/12/29 09:36:57 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*sub;

	if (!s)
		return (0);
	if (ft_strlen(s) <= start || !len)
		sub = my_malloc(1);
	else if (ft_strlen(s) <= len + start)
		sub = my_malloc(ft_strlen(s) - start + 1);
	else
		sub = my_malloc(len + 1);
	if (!sub)
		return (0);
	i = 0;
	if (ft_strlen(s) > start)
	{
		while (s[i + start] && len > 0)
		{
			sub[i] = s[start + i];
			i++;
			len--;
		}
	}
	sub[i] = 0;
	return ((char *)sub);
}
