/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:33:37 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/08 21:40:10 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	remove excessive data from mtime sting
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void			edit_mtime(const char *mtime)
{
	int			i;
	int			len;

	i = 4;
	len = (int)ft_strlen(mtime);
	while (i < len - 9)
		write(1, &mtime[i++], 1);
	write(1, " ", 1);
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	swap t_data structures
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void			fls_swap(t_data *a, t_data *b)
{
	t_data		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	general freeing and exit functions
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
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
