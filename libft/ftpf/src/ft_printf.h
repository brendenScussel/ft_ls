/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 04:23:29 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 03:12:50 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

# define NSTR "(null)"
# define MAXINT 2147483647
# define MININT -2147483648

typedef struct		s_pf
{
	int				flag[5];
	int				width;
	int				prec;
	int				length;
	char			spec;
	unsigned int	index;
	unsigned int	printed;
	char			*format;
	va_list			arg;
}					t_pf;

int					ft_printf(const char *format, ...);

/*
**	_____Libft Functions_____
*/

long long			bs_absol(long long x);
void				bs_putchar(char c);
void				bs_putstr(const char *s);
size_t				bs_strlen(const char *s);
int					bs_atoi(const char *str);
int					bs_itoa(int n);
size_t				bs_size_nbr(long n);
long long			bs_pow(int x, unsigned int y);

/*
**	_____Arguement Parse_____
*/

void				flag_type(t_pf *pf, char *frm);
void				minimum_width(t_pf *pf, char *frm);
void				precision(t_pf *pf, char *frm);
void				length_conversion(t_pf *pf, char *frm);
void				specifier(t_pf *pf, char *frm);

/*
**	_____Arguement Printing_____
*/

void				bum_spec(t_pf *pf);
void				character_print(t_pf *pf);
void				number_setup(t_pf *pf);
void				sgn_print(t_pf *pf, long long nbr);
void				unsgn_start(t_pf *pf, unsigned long long nbr);
void				unsgn_print(t_pf *pf, char *str);
void				oct_print(t_pf *pf, char *str, unsigned long long nbr);
void				hex_print(t_pf *pf, char *str, unsigned long long nbr);
void				floating_point(t_pf *pf, long double nbr);
void				snbase(size_t uplo, long long nbr, size_t base,
				char **rn);
void				unsnbase(size_t uplo, unsigned long long nbr,
				size_t base, char **rn);

#endif
