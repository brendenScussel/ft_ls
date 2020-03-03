/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:34:04 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/01 00:27:00 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	sort by least recently modified
*/

void			sort_r_t(t_data *fls, int size)
{
	int			i;
	t_data		tmp;
	long		ntime[2];

	i = 0;
	if (size == 1)
		return ;
	while (i < size - 1)
	{
		ntime[0] = fls[i].stats.st_mtimespec.tv_sec;
		ntime[1] = fls[i + 1].stats.st_mtimespec.tv_sec;
		if (ntime[0] > ntime[1])
		{
			tmp = fls[i];
			fls[i] = fls[i + 1];
			fls[i + 1] = tmp;
		}
		i++;
	}
	sort_r_t(fls, size - 1);
}

/*
**	sort by most recently modified
*/

void			sort_t(t_data *fls, int size)
{
	int			i;
	t_data		tmp;
	long		ntime[2];

	i = 0;
	if (size == 1)
		return ;
	while (i < size - 1)
	{
		ntime[0] = fls[i].stats.st_mtimespec.tv_sec;
		ntime[1] = fls[i + 1].stats.st_mtimespec.tv_sec;
		if (ntime[0] < ntime[1])
		{
			tmp = fls[i];
			fls[i] = fls[i + 1];
			fls[i + 1] = tmp;
		}
		i++;
	}
	sort_t(fls, size - 1);
}

/*
**	sort reverse alphabetical
*/

void			sort_r(t_data *fls, int size)
{
	int			i;
	t_data		tmp;

	i = 0;
	if (size == 1)
		return ;
	while (i < size - 1)
	{
		if (ft_strcmp(fls[i].arg, fls[i + 1].arg) < 0)
		{
			tmp = fls[i];
			fls[i] = fls[i + 1];
			fls[i + 1] = tmp;
		}
		i++;
	}
	sort_r(fls, size - 1);
}

/*
**	alphabetical sorting
*/

void			sort_normal(t_data *fls, int size)
{
	int			i;
	t_data		tmp;

	i = 0;
	if (size == 1)
		return ;
	while (i < size - 1)
	{
		if (ft_strcmp(fls[i].arg, fls[i + 1].arg) > 0)
		{
			tmp = fls[i];
			fls[i] = fls[i + 1];
			fls[i + 1] = tmp;
		}
		i++;
	}
	sort_normal(fls, size - 1);
}

/*
**	sorting controller
*/

void			ls_sort(t_flag flag, t_data *fls, int size)
{
	(flag.t == 1 && flag.r == 1) ? sort_r_t(fls, size) : 0;
	(flag.t == 1 && flag.r == 0) ? sort_t(fls, size) : 0;
	(flag.t == 0 && flag.r == 1) ? sort_r(fls, size) : 0;
	(flag.t == 0 && flag.r == 0) ? sort_normal(fls, size) : 0;
}
