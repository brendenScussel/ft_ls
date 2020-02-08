/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:54:05 by bscussel          #+#    #+#             */
/*   Updated: 2020/02/07 19:43:38 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	parse the given arguements
**	if '-' is present, a flag is assumed and searched
**		invalid flags will result in termination of program
**	else the mpath is joined with the arguement to create the assumed path
**		validity is checked later, and the path is ignored if not valid
**	no flags results in flag.none being true
**	likewise, if flag.none is true, the arguement variable is NULL
*/

void			find_arg(t_vars *v, char **av)
{
	v->i = 0;
	v->d_arg = 0;
	while ((int)v->i++ < v->argc)
	{
		if (*av[v->i] == '-')
			check_flags(v, av[v->i]);
		else
			v->argv[v->d_arg++] = (is_slash(v->argv[v->d_arg]) == 0) ?
				ft_strjoin("./", av[v->i]) : ft_strjoin("/", "\0");
	}
	v->flag.none = (v->flag.a == 0 && v->flag.l == 0 &&
		v->flag.r == 0 && v->flag.t == 0 && v->flag.recur == 0) ? 1 : 0;
	if (v->d_arg == 0 && v->argc > -1)
		free_arg(v);
	if (v->d_arg > 0)
	{
		while (v->cnt <= v->d_arg)
			r_dir(v);
	}
	else
		r_dir(v);
}

int				main(int ac, char **av)
{
	t_vars		*var;

	var = (t_vars *)malloc(sizeof(t_vars));
	ft_bzero(&var->flag, sizeof(t_flag));
	var->argc = ac - 1;
	var->cnt = 0;
	var->argv = (char **)malloc(sizeof(char *) * ac);
	find_arg(var, av);
	exit_ls(var);
	return (0);
}
