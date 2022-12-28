#include "../include/minishell.h"
#include "../include/parser.h"


void	ft_fresh(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
    {
		// free(tab[i]);
        i++;
    }
	// free(tab);
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

	env = (char **)malloc(sizeof(char *) * my_magic2(list) + 1);
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

int	ft_joinandsearch(char *path, char *commande, char **argv, t_list *l)
{
	struct stat	sb;
	char		*newpath;
	char		**env;
	int			pid;

	if (commande[0] == '/')
		return (0);
	newpath = join_path(path, commande);
	if (lstat(newpath, &sb) > -1)
	{
		pid = fork();
		if (pid == 0)
		{
			env = my_magic(l);
			execve(newpath, argv, env);
		}
		free(newpath);
		return (1);
	}
	// free(newpath);
	return (0);
}


int	search_commande(t_list *list, char *commande, char **argv)
{
	char	**path;
	int		len;

	path = NULL;
	len = 0;
	
	if (serach_env2(list))
	{
		
		path = ft_split(serach_env2(list), ':');
		len = 0;
		while (path[len])
		{
			if (ft_joinandsearch(path[len++], commande, argv, list) == 1)
			{
				// ft_fresh(path);
				return (1);
			}
		}
		if (path[0])
		{
			// ft_fresh(path);
		}
	}
	return (0);
}
