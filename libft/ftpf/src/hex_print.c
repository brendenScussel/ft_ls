/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:53:25 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/03 21:14:42 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				x_pad(t_pf *pf, int i, int pad)
{
	while (i < pad)
	{
		(pf->flag[3] == 1 && (pf->flag[0] == 0 && pf->prec == -1)) ?
			bs_putchar('0') : bs_putchar(' ');
		i++;
	}
	return (i);
}

void			x_nbr(t_pf *pf, char *str, int len, unsigned long long nbr)
{
	int			i;
	int			prec;

	i = 0;
	prec = (pf->prec > len) ? pf->prec - len : 0;
	while (i < prec)
	{
		bs_putchar('0');
		i++;
	}
	(nbr == 0 && pf->prec == 0) ? 0 : bs_putstr(str);
}

void			hex_print(t_pf *pf, char *str, unsigned long long nbr)
{
	int			i;
	int			len;
	int			pad;
	int			prefix;

	i = 0;
	len = (pf->prec == 0 && nbr == 0) ? 0 : (int)bs_strlen(str);
	pad = (pf->prec > len) ? pf->width - pf->prec : pf->width - len;
	prefix = (pf->flag[4] == 1 && nbr > 0) ? 1 : 0;
	pad -= (prefix == 1) ? 2 : 0;
	if (prefix == 1 && (pf->flag[3] == 1 || pf->flag[0] == 1))
		(pf->spec == 'X') ? bs_putstr("0X") : bs_putstr("0x");
	(pf->flag[0] == 1) ? x_nbr(pf, str, len, nbr) : 0;
	i = x_pad(pf, i, pad);
	if (prefix == 1 && pf->flag[0] == 0 && pf->flag[3] == 0)
		(pf->spec == 'X') ? bs_putstr("0X") : bs_putstr("0x");
	(pf->flag[0] == 0) ? x_nbr(pf, str, len, nbr) : 0;
	pf->printed += (pf->prec > len) ? pf->prec + i : i + len;
	pf->printed += (prefix == 1) ? 2 : 0;
}
