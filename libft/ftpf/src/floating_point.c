/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floating_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:28:53 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 03:06:03 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			contostr(char **s, char *con, size_t *cd)
{
	int			i;
	int			j;

	i = -1;
	while (++i < (int)cd[1])
		s[0][i] = con[i];
	j = i;
	s[0][i++] = '.';
	while (i < (int)cd[0])
		s[0][i++] = con[j++];
}

int				f_value(t_pf *pf, int neg)
{
	int			tr;

	tr = 0;
	if (neg == 1)
	{
		bs_putchar('-');
		pf->printed++;
		tr = 1;
	}
	else if (pf->flag[1] == 1 || pf->flag[2] == 1)
	{
		(pf->flag[1] == 0 && pf->flag[2] == 1) ? bs_putchar(' ') : 0;
		(pf->flag[1] == 1) ? bs_putchar('+') : 0;
		pf->printed++;
		tr = 1;
	}
	return (tr);
}

void			ftoa(t_pf *pf, char *f, int len, int neg)
{
	int			i;
	int			pad;
	int			val;

	i = 0;
	pad = pf->width - len;
	pad -= (neg == 1 || pf->flag[1] == 1 || pf->flag[2] == 1) ? 1 : 0;
	val = ((pf->flag[3] == 1 && pad > 0) || (pf->flag[0] == 1))
		? f_value(pf, neg) : 0;
	(pf->flag[0] == 1) ? bs_putstr(f) : 0;
	while (i < pad)
	{
		(pf->flag[0] == 0 && pf->flag[3] == 1) ?
			bs_putchar('0') : bs_putchar(' ');
		i++;
	}
	(val == 0) ? f_value(pf, neg) : 0;
	(pf->flag[0] == 0) ? bs_putstr(f) : 0;
	pf->printed += len + i;
}

/*
**	cdn[0] - length of the number converted to a whole number
**	cdn[1] - length of the interger portion of the arguement (decimal location)
**	cdn[2] - is the value negative
**	con is the arguement value multiplied by 10 to the power of the precision.
**	This provides a while number to work with and applies the precission early.
**	The converted string is printed like any other specifier
*/

void			floating_point(t_pf *pf, long double nbr)
{
	char		*str;
	long		con;
	char		*con_s;
	size_t		cdn[3];
	size_t		f_prec;

	f_prec = (pf->prec > -1) ? pf->prec : 6;
	con = nbr * bs_pow(10, f_prec);
	cdn[0] = (con < 0) ? bs_size_nbr(con) - 1 : bs_size_nbr(con);
	cdn[1] = (con < 0) ? bs_size_nbr((long)nbr) - 1 : bs_size_nbr((long)nbr);
	cdn[2] = (con < 0) ? 1 : 0;
	cdn[2] == 1 ? con = con * -1 : 0;
	str = (char*)malloc(sizeof(char) * cdn[0] + 2);
	str[cdn[0] + 1] = '\0';
	snbase(0, con, 10, &con_s);
	contostr(&str, con_s, cdn);
	ftoa(pf, str, (int)cdn[0], cdn[2]);
	free(str);
	str = NULL;
}
