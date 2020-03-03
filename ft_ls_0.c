/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:33:37 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/02 17:38:11 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	general freeing and exit functions
*/

void			fls_free(t_data *fls, int size)
{
	int			i;

	i = 0;
	if (fls != NULL)
	{
		while (i < size && (fls[i].arg))
		{
			ft_strdel(&fls[i].arg);
			ft_strdel(&fls[i].path);
			ft_strdel(&fls[i].owner);
			ft_strdel(&fls[i].groupie);
			i++;
		}
		free(fls);
	}
	fls = NULL;
}

void			free_arg(t_vars *v)
{
	v->i = 0;
	if (v->argv != NULL)
	{
		while ((int)v->i < v->d_arg)
		{
			ft_strdel(&v->argv[v->i]);
			v->i++;
		}
		free(v->argv);
	}
	v->argv = NULL;
}

void			exit_ls(t_vars *var, char *msg)
{
	(msg != NULL) ? ft_putendl(msg) : 0;
	free_arg(var);
	ft_strdel(&var->entry);
	var->dir = NULL;
	var->dent = NULL;
	free(var);
	var = NULL;
	exit(0);
}
