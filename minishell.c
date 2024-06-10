/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:00:38 by mzouine           #+#    #+#             */
/*   Updated: 2024/06/10 10:58:12 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_list	*envp;
	t_token	*linked;

	(void)av;
	if (ac != 1)
	{
		printf("Error!\nPlease execute the program without arguments!\n");
		return (1);
	}
	envp = env_parse(env);
	while (1)
	{
		s = readline("minishell:");
		if (!s)
		{
			printf("Error!\nreadline returned NULL\n");
			return (1);
		}
		linked = mz_parser(s);
		free(s);

		int i = 0;
		while (linked)
		{
			i = 0;
			printf("\n\n%s  --> %i\n", linked->cmd, linked->nature);
			while (linked->args && linked->args[i])
			{
				printf("arg_%i ->> %s\n", i, linked->args[i]);
				i++;
			}
			printf("[%s]\n", linked->cmd);
			linked = linked->next;
		}
	}
	return (0);
}





// ls -la | ( cat -e && wc -l && echo '$VAR') | grep "something i want" > outfile || < infile cat

/*  !! TO FREE ENVP !!!!

	t_list	*test2;
	test2 = envp;
	while (envp)
	{
		printf("%s\n", envp->s);
		envp = envp->next;
	}
	envp = NULL;
	while (test2)
	{
		envp = test2;
		free(test2->s);
		test2 = test2->next;
		free(envp);
	}
*/
