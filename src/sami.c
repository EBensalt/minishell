/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sami.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:49:53 by ebensalt          #+#    #+#             */
/*   Updated: 2022/12/24 16:14:04 by ebensalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

// void ft_exit()
// {
//     exit(0);
// }

// void    ft_echo(char **str)
// {
//     int i;

//     i = 1;
//     while (str[i])
//     {
//         ft_putstr_fd(str[i], 1);
//         if (str[i + 1] != NULL)
//             ft_putstr_fd(" ", 1);
//         i++;
//     }
//     ft_putstr_fd("\n", 1);
// }

// void    ft_env(t_list *list)
// {
//     list->original = list;
//     while (list->original)
//     {
//         ft_putstr_fd(list->original->first, 1);
//         ft_putstr_fd("=", 1);
//         ft_putstr_fd(list->original->second, 1);
//         ft_putstr_fd("\n", 1);
//         list->original = list->original->next;
//     }
// }

// t_list	*ft_export(char *str, t_list *list)
// {
// 	t_list	*tmp;

// 	tmp = NULL;
// 	list->original = list;
// 	while (list->original->next != NULL)
// 		list->original = list->original->next;
// 	tmp = new_list(str);
// 	list->original->next = tmp;
// 	return (list);
// }

void ft_exit()
{
    exit(0);
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

void	ft_env(t_list *list)
{
	list->original = list;
	while (list->original)
	{
		ft_putstr_fd(list->original->first, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(list->original->second, 1);
		ft_putstr_fd("\n", 1);
		list->original = list->original->next;
	}
}

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
            free(list->original->second);
            list->original->second = first_node(str, 2);
            return (list);
        }
        list->original = list->original->next;
    }
    tmp = new_list(str);
    list->original->next = tmp;
    return(list);
}

void	ft_export(t_list *list)
{
	list->original = list;
	while(list->original)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(list->original->first, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(list->original->second, 1);
		ft_putstr_fd("\"\n", 1);
		list->original = list->original->next;
	}
}

t_list	*help_ft_unset_env(t_list *list, char *str)
{
	t_list	*tmp;

	list->original = list;
	while (list->original->next)
	{
		if (ft_strcmp(str, list->original->next->first) == 0)
		{
			tmp = list->original->next;
			list->original->next = tmp->next;
			free(tmp->first);
			free(tmp->second);
			free(tmp);
			return (list);
		}
		list->original = list->original->next;
	}
	return (list);
}

t_list	*ft_unset_env(t_list *list, char *str)
{
	t_list	*tmp;

	list->original = list;
	if (ft_strcmp(str, list->original->first) == 0)
	{
		tmp = list->original;
		list = tmp->next;
		free(tmp->first);
		free(tmp->second);
		free(tmp);
		return (list);
	}
	return (help_ft_unset_env(list, str));
}

t_list	*ft_unset(char **av, t_list *list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (list);
	while (av[++i])
		list = ft_unset_env(list, av[i]);
	return (list);
}

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

t_cmd	*command_creation(t_cmd *cmd)
{
	char	*str;
	char	**path;
	int		i;

	str = getenv("PATH");
	path = ft_split_exec(str, ':');
	i = -1;
	while (path[++i])
	{
		if (!access(ft_strjoin(path[i], cmd->cmd), F_OK))
		{
			cmd->cmd = ft_strjoin(path[i], cmd->cmd);
			cmd->cmd_line[0] = cmd->cmd;
			break ;
		}
	}
	return (cmd);
}

void	my_execve(t_cmd *cmd, char **env, t_list *list)
{
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
	if (!list)
	{
		cmd = command_creation(cmd);
		if (execve(cmd->cmd, cmd->cmd_line, env))
			printf("\033[0;31merror\033[0m : %s command not found\n",
				cmd->cmd);
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
		if (cmd->next)
		{
			pipe(fd);
			cmd->next->tem = fd[0];
		}
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
	if (ptr->next)
		close(fd[0]);
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

t_list	*builtins_exec(t_cmd *cmd, t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit();
	else if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd->cmd_line);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(list);
	else if (!ft_strcmp(cmd->cmd, "export") && cmd->cmd_line[1])
	{
		while (cmd->cmd_line[++i])
			list = ft_exportvar(cmd->cmd_line[i], list);
	}
	else if (!ft_strcmp(cmd->cmd, "export") && !cmd->cmd_line[1])
	{
		ft_export(list);
	}
	else if (!ft_strcmp(cmd->cmd, "unset"))
		list = ft_unset(cmd->cmd_line, list);
	else
		return (0);
	return (list);
}

t_list	*abdellatif_execution(t_cmd *cmd, t_list *list, char **env)
{
	t_list	*ptr;

	ptr = list;
	if (cmd->next)
		pipe_exec(cmd, env, list);
	else
	{
		list = builtins_exec(cmd, list);
		if (!list)
		{
			list = ptr;
			pipe_exec(cmd, env, list);
		}
		ptr = list;
	}
	return (list);
}
