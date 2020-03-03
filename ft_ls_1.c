/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:46:45 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/02 17:06:30 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	a string is made from the given file and the starting path, I mean... duh.
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
**  the current directory is read and the contents parsed into the array fls
**	if the current file being read is hidden (first character is '.') or
**		is a directory, those values are set to true
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
		fls[var->i].owner = getpwuid(fls[var->i].stats.st_uid) ?
			ft_strdup(getpwuid(fls[var->i].stats.st_uid)->pw_name) : NULL;
		fls[var->i].groupie = getgrgid(fls[var->i].stats.st_gid) ?
			ft_strdup(getgrgid(fls[var->i].stats.st_gid)->gr_name) : NULL;
		time(&(fls[var->i].f_time));
		fls[var->i].hidden = (fls[var->i].arg[0] == '.') ? 1 : 0;
		tmp = opendir(fls[var->i].path);
		fls[var->i].isdir = (tmp != NULL) ? 1 : 0;
		(tmp != NULL) ? closedir(tmp) : 0;
		var->i++;
	}
	closedir(var->dir);
	ls_print_cntrl(var, fls, var->i);
}

/*
**	fls is an array of data structs, c_dir() counts the contents of a
**		directory so the correct amount of memory can be allocated
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
**	if there are directory arguements (var->d_arg > 0), then the list of
**		arguements is cycled through
**	else the current directory is emptied
*/

void				o_dir(t_vars *v)
{
	t_data			*fls;

	fls = NULL;
	if (v->d_arg > 0)
	{
		while (v->dcnt < v->d_arg)
		{
			ft_printf("%s:\n", v->argv[v->dcnt]);
			if ((v->dir = opendir(v->argv[v->dcnt])) != NULL)
			{
				fls = (t_data *)malloc(sizeof(t_data) *
					c_dir(v, v->argv[v->dcnt]));
				r_dir(v, fls);
			}
			(v->dir == NULL) ? ft_putendl(NOPE) : 0;
			v->dcnt++;
		}
	}
	else
	{
		((v->dir = opendir(".")) == NULL) ? exit_ls(v, DIR_EXIT) : 0;
		fls = (t_data *)malloc(sizeof(t_data) * c_dir(v, "."));
		r_dir(v, fls);
	}
}
