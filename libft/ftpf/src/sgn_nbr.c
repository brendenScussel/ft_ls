/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgn_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 22:23:00 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 02:39:43 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			point_print(t_pf *pf, char *str)
{
	int			i;
	int			len;
	int			pad;

	i = 0;
	len = (int)bs_strlen(str);
	pad = (pf->width - len - 2);
	if (pf->flag[0] == 1)
	{
		write(1, "0x", 2);
		bs_putstr(str);
	}
	while (i < pad)
	{
		bs_putchar(' ');
		i++;
	}
	if (pf->flag[0] == 0)
	{
		write(1, "0x", 2);
		bs_putstr(str);
	}
	pf->printed += (i + len + 2);
}

void			nbr_prec_print(t_pf *pf, char *str, long long nbr)
{
	int			i;
	int			prec;
	int			len;

	i = 0;
	len = (int)bs_strlen(str);
	prec = (pf->prec > len) ? pf->prec - len : 0;
	while (i < prec)
	{
		bs_putchar('0');
		i++;
	}
	(pf->prec == 0 && nbr == 0) ? bs_putchar(' ') : bs_putstr(str);
}

int				symbol_print(t_pf *pf, int n_nbr)
{
	int			tr;

	tr = 0;
	if (n_nbr == 1)
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

void			deci_print(t_pf *pf, char *str, int n_nbr, long long n)
{
	int			i;
	int			len;
	int			pad;
	int			sym;

	i = 0;
	len = (int)bs_strlen(str);
	pad = (pf->prec > len) ? pf->width - pf->prec : pf->width - len;
	pad -= (n_nbr == 1 || pf->flag[1] == 1 || pf->flag[2] == 1) ? 1 : 0;
	sym = (pf->flag[0] == 1 || (pf->flag[3] == 1 && pad > 0)) ?
			symbol_print(pf, n_nbr) : 0;
	if (pf->flag[0] == 1)
		nbr_prec_print(pf, str, n);
	while (i < pad)
	{
		(pf->flag[3] == 1 && (pf->flag[0] == 0 && pf->prec == -1)) ?
			bs_putchar('0') : bs_putchar(' ');
		i++;
	}
	(sym == 0) ? symbol_print(pf, n_nbr) : 0;
	if (pf->flag[0] == 0)
		nbr_prec_print(pf, str, n);
	pf->printed += (pf->prec > len) ? pf->prec + i : i + len;
}

void			sgn_print(t_pf *pf, long long nbr)
{
	char		*str;
	int			n_nbr;

	n_nbr = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		n_nbr = 1;
	}
	if (nbr == 0 && pf->prec == 0 && pf->width == 0)
		return ;
	(pf->spec == 'd') ? snbase(0, nbr, 10, &str) : snbase(0, nbr, 16, &str);
	(pf->spec == 'd') ? deci_print(pf, str, n_nbr, nbr) : point_print(pf, str);
}
