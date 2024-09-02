/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_unit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:44:00 by ymassiou          #+#    #+#             */
/*   Updated: 2024/09/01 05:54:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_name(char *name, t_shell *data)
{
	char	*value;

	value = search_fetch_add(data->envp, name, data);
	if (value == NULL)
		value = ft_strdup("", GLOBAL, data);
	else
	{
		value = ft_strchr(search_fetch_add(data->envp, name, data), '=');
		if (value == NULL)
		{
			value = ft_strdup("", GLOBAL, data);
			gc_add(&data->l_gc, gc_new(value, data));
		}
		else
			value++;
	}
	return (value);
}

void	expand_append(char **input, char **final, char **tmp, t_shell *data)
{
	int		name_len;
	char	*name;

	if (**input == '?')
	{
		*final = ft_strjoin(*final,
				ft_itoa(data->status, LOOP, data), LOOP, data);
		(*input)++;
		cpy_incr(input, tmp, final, data);
	}
	else if (*tmp != *input && ft_isdigit(**input))
	{
		if (**input == '0')
			*final = ft_strjoin(*final, "bash", LOOP, data);
		(*input)++;
		cpy_incr(input, tmp, final, data);
	}
	else if (*tmp != *input && **input == '*')
	{
		(*input)++;
		cpy_incr(input, tmp, final, data);
	}
	else
	{
		name_len = extract_name(input, tmp, &name, data);
		if (name_len == 0)
			*final = ft_strjoin(*final, "$", LOOP, data);
		else
			*final = ft_strjoin(*final, expand_name(name, data), LOOP, data);
	}
}

char	*ex_assign(char *input, char *flag, t_shell *data)
{
	int		i;
	char	*final;
	char	*tmp;

	i = 0;
	final = NULL;
	while (input && *input)
	{
		tmp = input;
		tmp = ft_strnstr(input, flag, ft_strlen(input));
		if (tmp != input)
			cpy_incr(&input, &tmp, &final, data);
		input += ft_strlen(flag);
		tmp = input;
		tmp = ft_strnstr(input, flag, ft_strlen(input));
		expand_append(&input, &final, &tmp, data);
		input += ft_strlen(flag);
		tmp = input;
		tmp = ft_strnstr(input, flag, ft_strlen(input));
		join_remain(&input, &tmp, &final, data);
	}
	return (final);
}
