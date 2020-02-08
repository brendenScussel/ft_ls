/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 19:33:31 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 03:28:11 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				oct_pad(t_pf *pf, int i, int pad)
{
	while (i < pad)
	{
		(pf->flag[3] == 1 && (pf->flag[0] == 0 && pf->prec == -1)) ?
			bs_putchar('0') : bs_putchar(' ');
		i++;
	}
	return (i);
}

void			o_nbr(t_pf *pf, char *str, unsigned long long nbr, int prefix)
{
	int			i;
	int			len;
	int			prec;

	i = 0;
	len = (pf->prec == 0 && nbr == 0) ? 0 : (int)bs_strlen(str);
	prec = (pf->prec > len) ? pf->prec - len : 0;
	if (prec <= len && prefix == 1)
		bs_putchar('0');
	else
	{
		while (i < prec)
		{
			bs_putchar('0');
			i++;
		}
	}
	((nbr == 0 && prefix == 1) || (nbr == 0 && pf->prec == 0))
		? 0 : bs_putstr(str);
}

void			oct_print(t_pf *pf, char *str, unsigned long long nbr)
{
	int			i;
	int			len;
	int			pad;
	int			prefix;

	i = 0;
	len = (pf->prec == 0 && nbr == 0) ? 0 : (int)bs_strlen(str);
	pad = (pf->prec > len) ? pf->width - pf->prec : pf->width - len;
	prefix = (pf->flag[4] == 1 &&
			(pf->prec <= len && pf->flag[3] == 0)) ? 1 : 0;
	pad -= prefix;
	if (nbr == 0 && pf->width == 0 && pf->prec == -1 && prefix == 1)
	{
		bs_putchar('0');
		pf->printed += 1;
	}
	else
	{
		(pf->flag[0] == 1) ? o_nbr(pf, str, nbr, prefix) : 0;
		i = oct_pad(pf, i, pad);
		(pf->flag[0] == 0) ? o_nbr(pf, str, nbr, prefix) : 0;
		pf->printed += (pf->prec > len) ?
			pf->prec + i + prefix : i + len + prefix;
	}
}
