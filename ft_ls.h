/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:29:19 by bscussel          #+#    #+#             */
/*   Updated: 2020/02/07 19:36:29 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "./libft/lib/libft.h"
# include "./libft/ftpf/src/ft_printf.h"
# include <dirent.h>
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include <sys/stat.h>
# include <sys/types.h>

# define BUFF_SIZE 255
/*
typedef struct				s_data
{
	char					*name;
	time_t					time;
	struct stat				stats;
	int						isdir;
}							t_data;

typedef struct				s_hash
{
	int						i;
	//t_data					data;
}							t_hash;
*/
typedef struct				s_flag
{
	int						none;
	int						a;
	int						l;
	int						r;
	int						t;
	int						recur;
}							t_flag;

/*
**	DIR *dir - current directory
**	dirent *dent - information from said directory
**	stat stat_buff - stats of current file or directory
**	char *mpath - main file path (duh)
**	count of non-flag arguements
**	copy of main arguement int argc minus 1
**	2d array of non-flag arguements
**	current location within aguement array
**	t_hash *cont - (hash) table of contents
**	flags from arguement
*/

typedef struct				s_vars
{
	DIR						*dir;
	struct dirent			*dent;
	struct stat				stat_buff;
	int						d_arg;
	int						argc;
	char					**argv;
	int						cnt;
//	t_hash					*cont;
	t_flag					flag;
	unsigned int			i;
}							t_vars;

void						exit_ls(t_vars *var);
void						check_flags(t_vars *var, char *arg);
int							is_slash(char *str);
void						free_arg(t_vars *v);

void						r_dir(t_vars *var);

#endif
