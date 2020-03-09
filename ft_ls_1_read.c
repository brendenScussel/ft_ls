/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:46:45 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/08 18:48:26 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	a string is made from the given file and the starting path, I mean... duh.
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

char				*ls_makepath(const char *var, const char *file)
{
	char			*p;
	int				i;
	int				j;

	p = ft_strnew(sizeof(char) * (ft_strlen(var) + ft_strlen(file) + 2));
	i = 0;
	while (var[i])
	{
		p[i] = var[i];
		i++;
	}
	p[i++] = '/';
	j = 0;
	while (file[j])
		p[i++] = file[j++];
	return (p);
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	printing controller
**	struct array is sorted
**	array is printed
**	if recurrison is true, array is checked for directories
**		ignoring the .git and navigation items
**	else the data array is freed
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void				ls_print_cntrl(t_vars *var, t_data *fls, int size)
{
	int				i;

	i = 0;
	(var->flag.l == 1) ? ft_printf("total %d\n", var->dir_blocks) : 0;
	var->dir_blocks = 0;
	ls_sort(var->flag, fls, size);
	p_dir(var->flag, fls, size);
	ft_strdel(&var->entry);
	if (var->flag.recur == 1)
	{
		while (i < size)
		{
			if (fls[i].isdir == 1)
			{
				if (ft_strcmp(fls[i].arg, ".") != 0 &&
						ft_strcmp(fls[i].arg, "..") != 0 &&
						ft_strcmp(fls[i].arg, ".git") != 0)
					o_sub(var, fls[i].path, fls[i].arg);
			}
			i++;
		}
		fls_free(fls, size);
	}
	else
		fls_free(fls, size);
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**  the current directory is read and the contents parsed into the array fls
**	if the current file being read is hidden (first character is '.') or
**		is a directory, those values are set to true
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void				r_dir(t_vars *var, t_data *fls)
{
	DIR				*tmp;

	var->i = 0;
	tmp = NULL;
	while ((var->dent = readdir(var->dir)) != NULL)
	{
		fls[var->i].arg = ft_strdup(var->dent->d_name);
		fls[var->i].path = ls_makepath(var->entry, fls[var->i].arg);
		(lstat(fls[var->i].path, &fls[var->i].stats) != 0) ?
			exit_ls(var, SE) : 0;
		fls[var->i].hidden = (fls[var->i].arg[0] == '.') ? 1 : 0;
		tmp = opendir(fls[var->i].path);
		fls[var->i].isdir = (tmp != NULL) ? 1 : 0;
		(tmp != NULL) ? closedir(tmp) : 0;
		var->dir_blocks += (var->flag.a == 0 && fls[var->i].arg[0] == '.') ? 0 :
			fls[var->i].stats.st_blocks;
		var->i++;
	}
	closedir(var->dir);
	ls_print_cntrl(var, fls, var->i);
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	fls is an array of data structs, c_dir() counts the contents of a
**		directory so the correct amount of memory can be allocated
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

int					c_dir(t_vars *var, const char *path)
{
	int				n;
	struct dirent	*dtmp;

	n = 0;
	while ((dtmp = readdir(var->dir)) != NULL)
		n++;
	closedir(var->dir);
	var->dir = NULL;
	var->dir = opendir(path);
	var->fcnt = n;
	var->entry = ft_strdup(path);
	var->size = n;
	return (n);
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	if there are directory arguements (var->d_arg > 0), then the list of
**		arguements is cycled through
**	else the current directory is emptied
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void				o_dir(t_vars *v)
{
	t_data			*fls;

	fls = NULL;
	if (v->d_arg > 0)
	{
		while (v->dcnt < v->d_arg)
		{
			(v->d_arg > 1) ? ft_printf("%s:\n", v->argv[v->dcnt] + 2) : 0;
			if ((v->dir = opendir(v->argv[v->dcnt])) != NULL)
			{
				fls = (t_data *)malloc(sizeof(t_data) *
					c_dir(v, v->argv[v->dcnt]));
				r_dir(v, fls);
			}
			(v->dir == NULL) ? is_real(v->argv[v->dcnt], v->flag) : 0;
			v->dcnt++;
			(v->dcnt < v->d_arg) ? ft_putchar('\n') : 0;
		}
	}
	else
	{
		((v->dir = opendir(".")) == NULL) ? exit_ls(v, DIR_EXIT) : 0;
		fls = (t_data *)malloc(sizeof(t_data) * c_dir(v, "."));
		r_dir(v, fls);
	}
}
