/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:29:19 by bscussel          #+#    #+#             */
/*   Updated: 2020/03/02 17:36:30 by bscussel         ###   ########.fr       */
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
# include <sys/xattr.h>

# define BA "(bad access)"
# define SE "STAT ERROR..."
# define NOPE "no such file or directory..."
# define DIR_EXIT "cannot open directory...\nstopping..."
# define SUB_EXIT "cannot open subdirectory...\nstopping..."
# define USAGE "usage: [-alrtR] [file ...]"

/*
**	current file name
**	path to file
**	stat buffer of the current file
**	owner name
**	group name
**	time buffer
**	is the file hidden
**	is the file a directory?
*/

typedef struct				s_data
{
	char					*arg;
	char					*path;
	struct stat				stats;
	char					*owner;
	char					*groupie;
	time_t					f_time;
	int						hidden;
	int						isdir;
}							t_data;

typedef struct				s_flag
{
	int						a;
	int						l;
	int						r;
	int						t;
	int						recur;
}							t_flag;

/*
**	DIR *dir - current directory
**	dirent *dent - information from said directory
**	total number of directory (not flag) arguements
**	arguement count - 1 (argv[0] is the executable name)
**	array of arguement strings
**	first part of an arguement path. Defaults to the current directory.
**	current arguement within argv
**	number of files counted from directory
**	flags from arguement
**	variable 'i' becauce line limits
**	size of directory, because line limits
*/

typedef struct				s_vars
{
	DIR						*dir;
	struct dirent			*dent;
	int						d_arg;
	int						argc;
	char					**argv;
	char					*entry;
	int						dcnt;
	int						fcnt;
	t_flag					flag;
	unsigned int			i;
	unsigned int			size;
}							t_vars;

void						exit_ls(t_vars *var, char *msg);
void						check_flags(t_vars *var, char *arg);
int							is_slash(char *str);
void						free_arg(t_vars *v);
void						fls_free(t_data *fls, int size);

void						o_dir(t_vars *v);
int							c_dir(t_vars *var, const char *path);
void						r_dir(t_vars *var, t_data *fls);
void						o_sub(t_vars *var, char *fls_path, char *fl);

void						ls_print_cntrl(t_vars *var, t_data *fls, int size);
void						ls_sort(t_flag flag, t_data *fls, int size);

#endif
