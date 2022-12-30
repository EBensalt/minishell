/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 05:16:15 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/30 05:21:29 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

void	ft_fresh(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	tab = NULL;
}

char	*serach_env2(t_list *list)
{
	list->original = list;
	while (list->original)
	{
		if (ft_strcmp(list->original->first, "PATH") == 0)
			return (list->original->second);
		list->original = list->original->next;
	}
	return (NULL);
}

int	my_magic2(t_list *list)
{
	int	cont;

	cont = 0;
	list->original = list;
	while (list->original)
	{
		cont++;
		list->original = list->original->next;
	}
	return (cont);
}

char	**my_magic(t_list *list)
{
	char	**env;
	int		i;

	env = (char **)my_malloc(sizeof(char *) * my_magic2(list) + 1);
	env[my_magic2(list)] = NULL;
	list->original = list;
	i = 0;
	while (list->original)
	{
		env[i] = ft_strjoin(list->original->first, list->original->second);
		list->original = list->original->next;
		i++;
	}
	return (env);
}

char	*join_path(char *path1, char *path2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path1, "/");
	tmp2 = ft_strjoin(tmp, path2);
	return (tmp2);
}
