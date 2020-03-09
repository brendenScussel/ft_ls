/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 00:58:30 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/08 21:39:33 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

/*
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
**	this whole file is a lesson in poor planning
**	==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==__==
*/

void				long_single(t_data *ir)
{
	ft_putchar('-');
	(ir->stats.st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(ir->stats.st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(ir->stats.st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(ir->stats.st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(ir->stats.st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(ir->stats.st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(ir->stats.st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(ir->stats.st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(ir->stats.st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	if ((int)ir->stats.st_nlink > 9 && (int)ir->stats.st_nlink < 100)
		ft_putstr(" ");
	else if ((int)ir->stats.st_nlink < 10)
		ft_putstr("  ");
	else
		ft_putchar(' ');
	ft_printf("%d %s   %s   %d   ", (int)ir->stats.st_nlink,
			getpwuid(ir->stats.st_uid)->pw_name,
			getgrgid(ir->stats.st_gid)->gr_name, ir->stats.st_size);
	edit_mtime(ctime(&ir->stats.st_mtimespec.tv_sec));
}

void				r_single(t_data *ir, t_flag flg, DIR *stmp, int i)
{
	struct dirent	*dent;

	while ((dent = readdir(stmp)) != NULL)
	{
		if (ft_strcmp(dent->d_name, ir->arg + i + 1) == 0)
		{
			lstat(ir->arg, &ir->stats);
			if (flg.l == 1)
				long_single(ir);
			p_arg(*ir, ir->arg + i + 1, flg, 1);
			return ;
		}
	}
	ft_putendl(NOPE);
}

void				is_real(const char *arg, t_flag flg)
{
	t_data			*ir;
	DIR				*stmp;
	int				i;

	ir = (t_data *)malloc(sizeof(t_data));
	ft_bzero(ir, sizeof(t_data));
	ir->arg = ft_strdup(arg);
	ir->path = ft_strdup(arg);
	i = (int)ft_strlen(arg) - 1;
	while (i > 0 && ir->path[i] != '\0')
		(ir->path[i] == '/') ? ir->path[i] = '\0' : i--;
	stmp = opendir(ir->path);
	r_single(ir, flg, stmp, i);
	closedir(stmp);
	ft_strdel(&ir->arg);
	ft_strdel(&ir->path);
	free(ir);
	ir = NULL;
}
