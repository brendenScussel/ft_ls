/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:46:45 by bscussel          #+#    #+#             */
/*   Updated: 2020/02/07 00:53:49 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void			r_dir(t_vars *var)
{
	var->i = 0;
	if (var->d_arg == 0)
	{
		((var->dir = opendir(".")) == NULL) ? exit_ls(var) : 0;
		stat(".", &var->stat_buff);
	}
	else
	{
		stat(var->argv[var->cnt], &var->stat_buff);
		if ((var->dir = opendir(var->argv[var->cnt])) == NULL)
		{
			var->cnt++;
			return ;
		}
		var->cnt++;
	}
	while ((var->dent = readdir(var->dir)) != NULL)
	{
		if (var->flag.a == 0 && var->dent->d_name[0] == '.')
			;
		else
		{
			(var->i % 5 == 0) ? ft_printf("[%s]\n", var->dent->d_name) :
				ft_printf("[%s]\t", var->dent->d_name);
			var->i++;
		}
	}
	(var->cnt < var->d_arg) ? r_dir(var) : 0;
}
