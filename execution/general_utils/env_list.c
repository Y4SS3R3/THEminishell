/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:01:19 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/29 13:26:39 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	lst_size(t_list *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	*search_fetch_add(char **env, char *to_find, t_shell *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		tmp = split_var(env[i], data);
		if (!ft_strcmp(tmp, to_find))
			return (env[i]);
		i++;
	}
	return (NULL);
}

t_list	*search_fetch_list(t_list *head, char *to_find, t_shell *data)
{
	char	*tmp;

	tmp = NULL;
	while (head)
	{
		tmp = split_var(head->s, data);
		if (!ft_strcmp(tmp, to_find))
			return (head);
		head = head->next;
	}
	return (NULL);
}

char	**list_to_arr(t_list *head, t_shell *data)
{
	int		size;
	char	**res;
	int		i;

	size = lst_size(head);
	res = which_malloc(GLOBAL, (size + 1) * sizeof(char *), data);
	i = 0;
	while (head && i < size)
	{
		res[i] = which_malloc(GLOBAL, ft_strlen(head->s), data);
		res[i] = ft_strdup(head->s, GLOBAL, data);
		head = head->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
