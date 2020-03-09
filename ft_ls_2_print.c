/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:42:56 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/08 21:45:19 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	printing
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	-l
**	1st column will give detailed information regarding file permission,
**	2nd column will tell you about the number of links to the file,
**	3rd and 4th columns are associated with owner and group of the file,
**	5th column will be displaying the size of the file in bytes,
**	6th column display recent time and date at which the file was modified,
**	7th column is the actual file/directory name.
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	create data array for subfiles. o_dir was not modular
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
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
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	quick check for 'F' flag
**	if true, an '*' is placed after executables
**		or a '/' after directories
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void			p_arg(t_data fls, const char *arg, t_flag flag, int nl)
{
	int			exe;

	exe = ((fls.stats.st_mode & S_IXUSR) || (fls.stats.st_mode & S_IXGRP) ||
			(fls.stats.st_mode & S_IXOTH)) ? 1 : 0;
	ft_putstr(arg);
	if (flag.f == 1)
	{
		(fls.isdir == 1) ? ft_putchar('/') : 0;
		(exe == 1 && fls.isdir == 0) ? ft_putchar('*') : 0;
	}
	(nl == 1) ? ft_putchar('\n') : 0;
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	printing of permissions
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void			long_p(t_data fls, t_flag flag)
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
	(fls.stats.st_mode & S_IXOTH) ? ft_putstr("x ") : ft_putstr("- ");
	if ((int)fls.stats.st_nlink > 9 && (int)fls.stats.st_nlink < 100)
		ft_putstr(" ");
	else if ((int)fls.stats.st_nlink < 10)
		ft_putstr("  ");
	ft_printf("%d %s  %s\t%d\t", (int)fls.stats.st_nlink,
		getpwuid(fls.stats.st_uid)->pw_name,
		getgrgid(fls.stats.st_gid)->gr_name, fls.stats.st_size);
	edit_mtime(ctime(&fls.stats.st_mtimespec.tv_sec));
	p_arg(fls, fls.arg, flag, 1);
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	an attempt at formatting
**
**	given arguements:	flag values (only need 'a'), file data, number of
**		non-hidden files (0 if flag.a is true), and array size
**	interger array 'impp':
**		imp[0]: int counter for fls
**		imp[1]: max length of files to be printed
**		imp[2]: padding of files (2 + max length - current length)
**		imp[3]: number of files actually printed
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void			short_p(t_flag flag, t_data *fls, int nhid, int size)
{
	int			imp[4];

	imp[0] = -1;
	imp[1] = 0;
	while (++imp[0] < size)
	{
		if (flag.a == 0 && fls[imp[0]].hidden == 1)
			;
		else if ((int)ft_strlen(fls[imp[0]].arg) > imp[1])
			imp[1] = (int)ft_strlen(fls[imp[0]].arg);
	}
	imp[0] = -1;
	imp[3] = 1;
	while (++imp[0] < size)
	{
		if (!(flag.a == 0) || !(fls[imp[0]].hidden == 1))
		{
			imp[2] = 2 + (imp[1] - ft_strlen(fls[imp[0]].arg));
			p_arg(fls[imp[0]], fls[imp[0]].arg, flag, 0);
			((imp[3] % 6 == 0) || (nhid == imp[3])) ?
				ft_putchar('\n') : write(1, PADDING, imp[2]);
			imp[3]++;
		}
	}
}

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	ic[0]: interger counter for fls
**	ic[1]: hidden files (if flag.a is true the value is 0)
**	if the item is hidden and flag.a is false, the item is skipped
**	if flag.l is true, the content is printed in list format
**	else, we print in standard collumn format
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void			p_dir(t_flag flag, t_data *fls, int size)
{
	int			ic[2];

	ic[0] = 0;
	ic[1] = 0;
	while (flag.a == 0 && ic[0] < size)
	{
		if (fls[ic[0]].hidden == 1)
			ic[1]++;
		ic[0]++;
	}
	ic[0] = 0;
	if (flag.l == 1)
	{
		while (ic[0] < size)
		{
			if (!(flag.a == 0) || !(fls[ic[0]].hidden == 1))
				long_p(fls[ic[0]], flag);
			ic[0]++;
		}
	}
	else
		short_p(flag, fls, size - ic[1], size);
}
