/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 20:54:05 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/02 00:30:44 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

char			*arg_path(char *arg)
{
	if ((arg[0] == '/') || ft_strncmp(arg, "./", 2) == 0)
		return (ft_strdup(arg));
	else
		return (ft_strjoin("./", arg));
	return (NULL);
}

int				is_slash(char *str)
{
	if (ft_strlen(str) != 1)
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
			ft_printf("ft_ls -%s: Invalid flag\n%s\n", arg, USAGE);
			exit_ls(var, NULL);
		}
		arg++;
	}
}

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
		{
			v->argv[v->d_arg] = (is_slash(av[v->i]) == 0) ?
				arg_path(av[v->i]) : ft_strdup("/");
			v->d_arg++;
		}
	}
	if (v->d_arg == 0)
	{
		if (v->argv != NULL)
			free(v->argv);
		v->argv = NULL;
	}
	v->i = 0;
	o_dir(v);
}

int				main(int ac, char **av)
{
	t_vars		*var;

	var = (t_vars *)malloc(sizeof(t_vars));
	ft_bzero(&var->flag, sizeof(t_flag));
	var->argc = ac - 1;
	var->dcnt = 0;
	var->argv = (ac > 1) ? (char **)malloc(sizeof(char *) * ac) : NULL;
	var->entry = NULL;
	var->size = 0;
	find_arg(var, av);
	exit_ls(var, NULL);
	return (0);
}
