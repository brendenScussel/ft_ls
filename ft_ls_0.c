/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:33:37 by bscussel          #+#    #+#             */
/*   Updated: 2020/02/07 19:43:27 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void			free_arg(t_vars *v)
{
	v->i = 0;
	while ((int)v->i < v->argc)
	{
		(v->argv[v->i] != NULL) ? free(v->argv[v->i]) : 0;
		v->argv[v->i++] = NULL;
	}
	free(v->argv);
	v->argv = NULL;
}

int				is_slash(char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	if (i != 1)
		return (0);
	if (str[0] != '/')
		return (0);
	if (str[1] != '\0')
		return (0);
	return (1);
}

void			check_flags(t_vars *var, char *arg)
{
	arg++;
	while (*arg)
	{
		if (*arg == 'a')
			var->flag.a = 1;
		else if (*arg == 'l')
			var->flag.l = 1;
		else if (*arg == 'r')
			var->flag.r = 1;
		else if (*arg == 't')
			var->flag.t = 1;
		else if (*arg == 'R')
			var->flag.recur = 1;
		else
		{
			ft_printf("ft_ls -%s: Invalid flag\n", arg);
			exit_ls(var);
		}
		arg++;
	}
}

/*
**	freeing *DIR (despite being malloced within *var
**	causes 17k leak.
*/

void			exit_ls(t_vars *var)
{
	free_arg(var);
	var->dir = NULL;
	var->dent = NULL;
	free(var);
	var = NULL;
	exit(0);
}
