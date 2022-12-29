/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:49:53 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/29 16:03:25 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

int	count_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

void	is_numeric(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] != NULL)
	{
		while (args[1][j])
		{
			if ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] == '0'
			&& !ft_atoi(&args[1][1]))
				(printf("exit\n"), exit(0));
			if (args[1][j] != '0' && !ft_atoi(&args[1][j]))
			{
				write(2, "exit\nminishell: exit: ", 22);
				write(2, args[1], ft_strlen(args[1]));
				write(2, ": numeric argument required\n", 28);
				exit(255);
			}
			j++;
		}
		i++;
	}
}

int	ft_exit(char **args)
{
	long long	len;

	len = count_args(args);
	if (!args[1])
		(printf("exit\n"), exit(g_exit_c));
	is_numeric(args);
	write(2, &len, 4);
	if (len > 3)
		write(2, "exit\nminishell: exit: too many arguments\n", 41);
	else if (len == 3)
	{
		len = ft_atoi(args[1]);
		if (args[1][0] != '-' && len < 0)
		{
			write(2, "exit\nminishell: exit: ", 22);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		else
			(printf("exit\n"), exit(ft_atoi(args[1])));
	}
	g_exit = 1;
	return (1);
}

int	check_opt(char *str)
{
	int	i;

	i = 2;
	if (str && (str[0] == '-' && str[1] == 'n'))
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void    ft_echo(char **str)
{
    int i;
	int p;

    i = 1;
	p = 1;
	while(p)
	{
		p = check_opt(str[i]);
		if(p == 1)
			i++;
		else
			break;
	}
	p = i;
	if(!str[i])
	{
		if(p != 1)
			return;
		ft_putstr_fd("\n", 1);
		return;
	}
    while (str[i])
    {
        ft_putstr_fd(str[i], 1);
        if (str[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        i++;
    }
	if(p == 1)
    	ft_putstr_fd("\n", 1);
}

// void	ft_env(t_list *list)
// {
// 	list->original = list;
// 	while (list->original)
// 	{
// 		ft_putstr_fd(list->original->first, 1);
// 		ft_putstr_fd("=", 1);
// 		ft_putstr_fd(list->original->second, 1);
// 		ft_putstr_fd("\n", 1);
// 		list->original = list->original->next;
// 	}
// }

t_list    *ft_exportvar(char *str, t_list *list)
{
    t_list *tmp;
    char *word;

    tmp = NULL;
    list->original = list;
    while (list->original->next != NULL)
    {
        word = first_node(str, 1);
        if (list->original->first == word)
        {
            // free(list->original->second);
            list->original->second = first_node(str, 2);
            return (list);
        }
        list->original = list->original->next;
    }
    tmp = new_list(str);
    list->original->next = tmp;
    return(list);
}

// void	ft_export(t_list *list)
// {
// 	list->original = list;
// 	while(list->original)
// 	{
// 		ft_putstr_fd("declare -x ", 1);
// 		ft_putstr_fd(list->original->first, 1);
// 		ft_putstr_fd("=\"", 1);
// 		ft_putstr_fd(list->original->second, 1);
// 		ft_putstr_fd("\"\n", 1);
// 		list->original = list->original->next;
// 	}
// }

// t_list	*help_ft_unset_env(t_list *list, char *str)
// {
// 	t_list	*tmp;

// 	list->original = list;
// 	while (list->original->next)
// 	{
// 		if (ft_strcmp(str, list->original->next->first) == 0)
// 		{
// 			tmp = list->original->next;
// 			list->original->next = tmp->next;
// 			// free(tmp->first);
// 			// free(tmp->second);
// 			// free(tmp);
// 			return (list);
// 		}
// 		list->original = list->original->next;
// 	}
// 	return (list);
// }

// t_list	*ft_unset_env(t_list *list, char *str)
// {
// 	t_list	*tmp;

// 	list->original = list;
// 	if (ft_strcmp(str, list->original->first) == 0)
// 	{
// 		tmp = list->original;
// 		list = tmp->next;
// 		// free(tmp->first);
// 		// free(tmp->second);
// 		// free(tmp);
// 		return (list);
// 	}
// 	return (help_ft_unset_env(list, str));
// }

// t_list	*ft_unset(char **av, t_list *list)
// {
// 	int	i;

// 	i = 0;
// 	if (list == NULL)
// 		return (list);
// 	while (av[++i])
// 		list = ft_unset_env(list, av[i]);
// 	return (list);
// }

// t_list  *abdellatif_execution(t_cmd *cmd, t_list *list)
// {
// 	int	i;

// 	i = 0;
// 	if (!ft_strcmp(cmd->cmd, "exit"))
// 		ft_exit();
// 	else if (!ft_strcmp(cmd->cmd, "echo"))
// 		ft_echo(cmd->cmd_line);
// 	else if (!ft_strcmp(cmd->cmd, "env"))
// 		ft_env(list);
// 	else if (!ft_strcmp(cmd->cmd, "export") && cmd->cmd_line[1])
// 	{
// 		while (cmd->cmd_line[++i])
// 			list = ft_exportvar(cmd->cmd_line[i], list);
// 	}
// 	else if (!ft_strcmp(cmd->cmd, "export") && !cmd->cmd_line[1])
// 	{
// 		ft_export(list);
// 	}
// 	else if (!ft_strcmp(cmd->cmd, "unset"))
// 		list = ft_unset(cmd->cmd_line, list);
// 	else if (search_commande(list, cmd->cmd, cmd->cmd_line) == 0)
// 		ft_mini_help_ft_trait(cmd->cmd_line, list, cmd->cmd);
// 	wait(NULL);
// 	return (list);
// }

t_cmd	*command_creation(t_cmd *cmd, t_list *list)
{
	char	*str;
	char	**path;
	int		i;

	str = my_getenv("PATH", list);
	path = ft_split_exec(str, ':');
	i = -1;
	if (!path)
	{
		return (cmd);
	}
	str = ft_strdup(cmd->cmd);
	while (path[++i])
	{
		if (!access(ft_strjoin(path[i], cmd->cmd), F_OK))
		{
			cmd->cmd = ft_strjoin(path[i], cmd->cmd);
			cmd->cmd_line[0] = cmd->cmd;
			break ;
		}
	}
	if (opendir(cmd->cmd))
	{
		printf("minishell: %s: is a directory\n", cmd->cmd);
		exit(126);
	}
	if (!ft_strcmp(cmd->cmd, str))
	{
		i = -1;
		if (cmd->cmd[1] == '/' && cmd->cmd[0] == '.')
			return (cmd);
		while (cmd->cmd[++i] && cmd->cmd[i] != '/')
			;
			// write(1, "ok1\n", 4);
			// printf("%d\n", i);
		if (!cmd->cmd[i])
		{
		// write(1, "ok\n", 3);
			printf("minishell: %s: commad not found\n", cmd->cmd);
			exit(126);
		}
	}
	return (cmd);
}

int	count_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**env_creat(t_list *list)
{
	char	**env;
	int		i;

	env = my_malloc((count_list(list) + 1) * sizeof(char *));
	i = 0;
	while (list)
	{
		if (list->sepr == '=')
		{
			env[i] = ft_strjoin(list->first, "=");
			env[i] = ft_strjoin(env[i], list->second);
		}
		else
			env[i] = ft_strdup(list->first);
		i++;
		list = list->next;
	}
	return (env);
}

void	my_execve(t_cmd *cmd, char **envp, t_list *list)
{
	char	*ptr;
	char	**env;

	(void)envp;
	ptr = ft_strdup(cmd->cmd);
	if (cmd->fd_i != 0)
	{
		dup2(cmd->fd_i, 0);
		close(cmd->fd_i);
	}
	if (cmd->fd_o != 1)
	{
		dup2(cmd->fd_o, 1);
		close(cmd->fd_o);
	}
	list = builtins_exec(cmd, list);
	if (built == 1)
	{
		cmd = command_creation(cmd, list);
		// if (!ft_strcmp(cmd->cmd, ptr))
		// {
		// 	exit(127)
		// }
		env = env_creat(list);
		if (execve(cmd->cmd, cmd->cmd_line, env))
		{
			printf("minishell: %s", cmd->cmd);
			perror("");
			// printf("\033[0;31merror\033[0m : %s command not found\n",
			// 	cmd->cmd);
		}
		exit(127);
	}
	else
		exit(0);
}

void	handler0(int i)
{
	if (i == SIGQUIT)
		printf("Quit: 3\n");
}

void	pipe_exec(t_cmd *cmd, char **env, t_list *list)
{
	t_cmd	*ptr;
	int		fd[2];
	// int		id;
	int		status;

	ptr = cmd;
	status = 0;
	while (cmd)
	{
		// while (!cmd->error && cmd->next)
		// 	cmd = cmd->next;
		// if (!cmd->error && !cmd->next)
		// 	break ;
		if (cmd->next)
		{
			pipe(fd);
			cmd->next->tem = fd[0];
		}
		if (cmd->error == 0)
		{
			cmd->id = fork();
			if (cmd->id == -1)
			{
				printf("error : fork :Resource temporarily unavailable\n");
				break ;
			}
			if (cmd->id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (cmd != ptr)
				{
					dup2(cmd->tem, 0);
					close(cmd->tem);
				}
				if (cmd->next)
				{
					dup2(fd[1], 1);
					close(fd[1]);
					close(fd[0]);
				}
				if (cmd && cmd->error == 0)
					my_execve(cmd, env, list);
			}
		}
		if (cmd != ptr)
			close(cmd->tem);
		if (cmd->next)
			close(fd[1]);
		cmd = cmd->next;
		// waitpid(id, &status, 0);
		// if (WIFEXITED(status))
		// 	g_exit = WEXITSTATUS(status);
		// else
		// 	g_exit = 128 + WTERMSIG(status);
	}
	signal(SIGINT, handler0);
	signal(SIGQUIT, handler0);
	// if (ptr->next)
	// 	close(fd[0]);
	while (ptr)
	{
		waitpid(ptr->id, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else
			g_exit = 128 + WTERMSIG(status);
		ptr = ptr->next;
	}
	// while (wait(&status) != -1)
	// 	;
	// if (WIFEXITED(status)/* || WTERMSIG(status) == 13*/)
	// {
	// 	g_exit = WEXITSTATUS(status);
	// 	printf("ok_1\n");
	// }
	// else
	// {
	// 	g_exit = 128 + WTERMSIG(status);
	// 	printf("ok_2\n");
	// }
	// printf("%d\n", g_exit);
	// waitpid(id, NULL, 0);
}

void	change_pwd(t_list *list, char *s)
{
	char	*ptr;

	while (ft_strcmp(list->first, s))
		list = list->next;
	if (!ft_strcmp(list->first, s))
	{
		ptr = getcwd(NULL, 0);
		list->second = ft_strdup(ptr);
		free(ptr);
	}
}

void	ft_cd(t_cmd *cmd, t_list *list)
{
	DIR		*ptr;
	char	*ptr0;

	if (!cmd->cmd_line[1])
	{
		if (!my_getenv("HOME", list))
		{
			printf("minishell: cd: HOME not set\n");
			g_exit = 1;
			return ;
		}
		ptr = opendir(my_getenv("HOME", list));
		if (!ptr)
		{
			printf("minishell: cd: %s: No such file or directory\n",
				my_getenv("HOME", list));
			g_exit = 1;
			return ;
		}
		free(ptr->__dd_buf);
		free(ptr);
		change_pwd(list, "OLDPWD");
		chdir(my_getenv("HOME", list));
	}
	else
	{
		ptr = opendir(cmd->cmd_line[1]);
		if (!ptr)
		{
			printf("minishell: %s: No such file or directory\n",
				cmd->cmd_line[1]);
			g_exit = 1;
			return ;
		}
		free(ptr->__dd_buf);
		free(ptr);
		change_pwd(list, "OLDPWD");
		chdir(cmd->cmd_line[1]);
		ptr0 = getcwd(NULL, 0);
		if (!ptr0)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			return ;
		}
		free(ptr0);
	}
	change_pwd(list, "PWD");
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("pwd: .: No such file or directory\n");
		g_exit = 1;
		return ;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}

void	ft_export_uni(t_list *list)
{
	// t_list	*ptr;

	while (list)
	{
		// printf("ok1\n");
		// ptr = list;
		// while (ptr)
		// {
		// 	printf("declare -x %s\n", ptr->first);
		// 	// if (*list->sepr == '=')
		// 	// 	printf("=\"%s\"\n", list->second);
		// 	// else
		// 	// 	printf("\n");
		// 	ptr = ptr->next;
		// }
		// exit(0);
		printf("declare -x %s", list->first);
		if (list->sepr == '=')
			printf("=\"%s\"\n", list->second);
		else
			printf("\n");
		list = list->next;
	}
}

void	add_list_nood(t_list **list, char *new)
{
	t_list	*ptr;
	t_list	*ptr0;

	ptr = *list;
	ptr0 = new_list(new);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ptr0;
}

void	delete_env(t_list **list, char *str)
{
	t_list	*ptr;
	t_list	*ptr0;

	ptr = *list;
	while (ptr)
	{
		if (!ft_strcmp(ptr->first, str))
		{
			if (ptr == *list)
			{
				printf("ok\n");
				*list = (*list)->next;
				free(ptr);
				return ;
			}
			else if (!ptr->next)
			{
				ptr0->next = NULL;
				free(ptr);
			}
			else
			{
				ptr0->next = ptr->next;
				free(ptr);
			}
		}
		ptr0 = ptr;
		ptr = ptr->next;
	}
}

int	env_srch(t_list *list, char *str)
{
	while (list)
	{
		if (!ft_strcmp(list->first, str))
			return (1);
		list = list->next;
	}
	return (0);
}

void	list_checker(t_cmd *cmd, t_list **list)
{
	int		i;
	int		j;
	int		plus;
	char	*str;
	char	*ptr;

	j = 0;
	plus = 0;
	while (cmd->cmd_line[++j])
	{
		if (!ft_isalpha(cmd->cmd_line[j][0]))
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				cmd->cmd_line[j]);
			j++;
			g_exit = 1;
		}
		if (!cmd->cmd_line[j])
			return ;
		i = -1;
		while (cmd->cmd_line[j][++i] && cmd->cmd_line[j][i] != '=')
		{
			if (!ft_isalnum_2(cmd->cmd_line[j][i])
				|| (cmd->cmd_line[j][i] == '+'
					&& cmd->cmd_line[j][i + 1] != '='))
			{
				printf("minishell: export: '%s': not a valid identifier\n",
					cmd->cmd_line[j]);
				j++;
				g_exit = 1;
			}
			if (!cmd->cmd_line[j])
				return ;
			else if (cmd->cmd_line[j][i] == '+'
				&& cmd->cmd_line[j][i + 1] == '=')
			{
				plus = 1;
				break ;
			}
		}
		ptr = my_malloc((i + 1) * sizeof(char));
		ft_strlcpy(ptr, cmd->cmd_line[j], (i + 1));
		if (plus == 1)
		{
			str = ft_strjoin(my_getenv(ptr, *list),
					&cmd->cmd_line[j][i + 2]);
			delete_env(list, ptr);
			ptr = ft_strjoin(ptr, "=");
			str = ft_strjoin(ptr, str);
			add_list_nood(list, str);
		}
		else if (!env_srch(*list, ptr))
		{
			// delete_env(&list, ptr);
			add_list_nood(list, cmd->cmd_line[j]);
			// while (list)
			// {
			// 	printf("-----%s%c%s\n", list->first, list->sepr, list->second);
			// 	list = list->next;
			// }
			// while (list)
			// {
			// 	printf("+++++%s%c%s\n", list->first, list->sepr, list->second);
			// 	list = list->next;
			// }
			// exit(0);
		}
		else
		{
			str = my_getenv(ptr, *list);
			if (!str || (!cmd->cmd_line[j][i + 1] && cmd->cmd_line[j][i] == '=') || (cmd->cmd_line[j][i + 1] != 0 && ft_strcmp(str, &cmd->cmd_line[j][i + 1])))
			{
				delete_env(list, ptr);
				add_list_nood(list, cmd->cmd_line[j]);
			}
		}
	}
}

void	ft_export(t_cmd *cmd, t_list *list)
{
	if (!cmd->cmd_line[1])
		ft_export_uni(list);
	else
		list_checker(cmd, &list);
}

void	ft_unset(t_cmd *cmd, t_list **list)
{
	int		i;
	int		j;
	char	*ptr;

	j = 0;
	while (cmd->cmd_line[++j])
	{
		if (!ft_isalpha(cmd->cmd_line[j][0]))
		{
			printf("minishell: unset: '%s': not a valid identifier\n",
				cmd->cmd_line[j]);
			j++;
			g_exit = 1;
		}
		if (!cmd->cmd_line[j])
			return ;
		i = -1;
		while (cmd->cmd_line[j][++i])
		{
			if (!ft_isalnum_2(cmd->cmd_line[j][i]))
			{
				printf("minishell: unset: '%s': not a valid identifier\n",
					cmd->cmd_line[j]);
				j++;
				g_exit = 1;
			}
			if (!cmd->cmd_line[j])
				return ;
		}
		ptr = my_malloc((i + 1) * sizeof(char));
		ft_strlcpy(ptr, cmd->cmd_line[j], (i + 1));
		if (env_srch(*list, ptr))
			delete_env(list, ptr);
				// while (*list)
				// {
				// 	printf("declare -x %s\n", (*list)->first);
				// 	// if (*list->sepr == '=')
				// 	// 	printf("=\"%s\"\n", list->second);
				// 	// else
				// 	// 	printf("\n");
				// 	*list = (*list)->next;
				// }
				// exit(0);
	}
}

void	ft_env(t_list *list)
{
	while (list)
	{
		if (list->sepr == '=')
			printf("%s=%s\n", list->first, list->second);
		list = list->next;
	}
}

int	check_built(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "cd")
		|| !ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "export")
		|| !ft_strcmp(cmd->cmd, "unset") || !ft_strcmp(cmd->cmd, "env")
		|| !ft_strcmp(cmd->cmd, "exit"))
		return (0);
	else
		built = 1;
	return (1);
}

t_list	*builtins_exec(t_cmd *cmd, t_list *list)
{
	int	i;

	i = 0;
	// if (cmd->fd_i != 0)
	// {
	// 	dup2(cmd->fd_i, 0);
	// 	close(cmd->fd_i);
	// }
	// if (cmd->fd_o != 1)
	// {
	// 	dup2(cmd->fd_o, 1);
	// 	close(cmd->fd_o);
	// }
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd->cmd_line);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd, list);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd, list);
	else if (!ft_strcmp(cmd->cmd, "unset"))
	{
		ft_unset(cmd, &list);
		// while (list)
		// 		{
		// 			printf("declare -x %s\n", (list)->first);
		// 			// if (*list->sepr == '=')
		// 			// 	printf("=\"%s\"\n", list->second);
		// 			// else
		// 			// 	printf("\n");
		// 			list = (list)->next;
		// 		}
		// 		exit(0);
	}
	else if (!ft_strcmp(cmd->cmd, "env"))
	{
		ft_env(list);
	}
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd->cmd_line);
	// else if (!ft_strcmp(cmd->cmd, "env"))
	// 	ft_env(list);
	// else if (!ft_strcmp(cmd->cmd, "export") && cmd->cmd_line[1])
	// {
	// 	while (cmd->cmd_line[++i])
	// 		list = ft_exportvar(cmd->cmd_line[i], list);
	// }
	// else if (!ft_strcmp(cmd->cmd, "export") && !cmd->cmd_line[1])
	// {
	// 	ft_export(list);
	// }
	else
		built = 1;
	return (list);
}

t_list	*abdellatif_execution(t_cmd *cmd, t_list *list, char **env)
{
	t_list	*ptr;
	int		tmp0;
	int		tmp1;

	ptr = list;
	if (cmd->next)
		pipe_exec(cmd, env, list);
	if (!check_built(cmd))
	{
		printf("ok\n");
		tmp0 = dup(0);
		tmp1 = dup(1);
		if (cmd->fd_i != 0)
		{
			dup2(cmd->fd_i, 0);
			close(cmd->fd_i);
		}
		if (cmd->fd_o != 1)
		{
			dup2(cmd->fd_o, 1);
			close(cmd->fd_o);
		}
		list = builtins_exec(cmd, list);
		dup2(tmp0, 0);
		close(tmp0);
		dup2(tmp1, 1);
		close(tmp1);
		// while (list)
		// 		{
		// 			printf("declare -x %s\n", (list)->first);
		// 			// if (*list->sepr == '=')
		// 			// 	printf("=\"%s\"\n", list->second);
		// 			// else
		// 			// 	printf("\n");
		// 			list = (list)->next;
		// 		}
		// 		exit(0);
	}
	if (built == 1)
	{
		list = ptr;
		pipe_exec(cmd, env, list);
	}
	ptr = list;
	return (list);
}
