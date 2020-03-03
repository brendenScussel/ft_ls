/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:42:56 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/02 17:33:17 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	-l
**	1st column will give detailed information regarding file permission,
**	2nd column will tell you about the number of links to the file,
**	3rd and 4th columns are associated with owner and group of the file,
**	5th column will be displaying the size of the file in bytes,
**	6th column display recent time and date at which the file was modified,
**	7th column is the actual file/directory name.
*/

/*
**	create data array for subfiles. o_dir was not modular
*/

void			o_sub(t_vars *var, char *fls_path, char *fl)
{
	t_data		*subfls;
	int			size;

	subfls = NULL;
	ft_printf("%s:\n", fl);
	((var->dir = opendir(fls_path)) == NULL) ? exit_ls(var, SUB_EXIT) : 0;
	size = c_dir(var, fls_path);
	subfls = (t_data *)malloc(sizeof(t_data) * size);
	r_dir(var, subfls);
}

/*
**	remove excessive data from mtime sting
*/

void			edit_mtime(const char *mtime)
{
	int			i;
	int			len;

	i = 4;
	len = (int)ft_strlen(mtime);
	while (i < len - 9)
		write(1, &mtime[i++], 1);
	write(1, "  ", 2);
}

/*
**	printing of permissions
*/

void			long_p(t_data fls)
{
	fls.isdir == 1 ? ft_putchar('d') : ft_putchar('-');
	(fls.stats.st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(fls.stats.st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(fls.stats.st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(fls.stats.st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(fls.stats.st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(fls.stats.st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(fls.stats.st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(fls.stats.st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(fls.stats.st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	if ((int)fls.stats.st_nlink > 10 && (int)fls.stats.st_nlink < 100)
		ft_putstr("  ");
	else if ((int)fls.stats.st_nlink > 99)
		ft_putchar(' ');
	else
		ft_putstr("   ");
	ft_putnbr((int)fls.stats.st_nlink);
	ft_putchar(' ');
	(fls.owner != NULL) ? ft_putstr(fls.owner) : ft_putstr(BA);
	(ft_strlen(fls.owner) > 6) ? ft_putchar('\t') : ft_putstr("  ");
	(fls.groupie != NULL) ? ft_putstr(fls.groupie) : ft_putstr(BA);
	ft_printf("\t%d\t", fls.stats.st_size);
	edit_mtime(ctime(&fls.stats.st_mtimespec.tv_sec));
	ft_putendl(fls.arg);
}

/*
**	ic[2] counts the array and printed items respectively
**	if the item is hidden and flag.a is false, the item is skipped
**	if flag.l is true, the content is printed in list format
**	else, contents are printed normally with 7 items per line.
**	I do not have the patience for actual collumn formating
*/

void			p_dir(t_flag flag, t_data *fls, int size)
{
	int			ic[2];

	ic[0] = 0;
	ic[1] = 1;
	while (ic[0] < size)
	{
		if (flag.a == 0 && fls[ic[0]].hidden == 1)
			;
		else
		{
			(flag.l == 1) ? long_p(fls[ic[0]]) : ft_putstr(fls[ic[0]].arg);
			if (flag.l == 0)
			{
				if (ic[1] % 7 == 0 || ic[0] == size - 1)
					ft_putchar('\n');
				else
					(ic[1] > 7 && ft_strlen(fls[ic[0]].arg) - 3 >
					(ft_strlen(fls[ic[0] - 7].arg))) ?
						ft_putstr("\t") : ft_putstr("\t\t");
			}
			ic[1]++;
		}
		ic[0]++;
	}
}

/*
**	printing controller
**	struct array is sorted
**	array is printed
**	if recurrison is true, array is checked for directories
**		ignoring the .git and navigation items
**	else the data array is freed
*/

void			ls_print_cntrl(t_vars *var, t_data *fls, int size)
{
	int			i;

	i = 0;
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
