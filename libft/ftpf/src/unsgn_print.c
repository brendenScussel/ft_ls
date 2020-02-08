/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsgn_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:08:01 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/03 21:17:32 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			u_nbr(t_pf *pf, char *str, int len)
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
	bs_putstr(str);
}

void			unsgn_print(t_pf *pf, char *str)
{
	int			i;
	int			len;
	int			pad;

	i = 0;
	len = (int)bs_strlen(str);
	pad = (pf->prec > len) ? pf->width - pf->prec : pf->width - len;
	(pf->flag[0] == 1) ? u_nbr(pf, str, len) : 0;
	while (i < pad)
	{
		(pf->flag[3] == 1 && (pf->flag[0] == 0 && pf->prec == -1)) ?
			bs_putchar('0') : bs_putchar(' ');
		i++;
	}
	(pf->flag[0] == 0) ? u_nbr(pf, str, len) : 0;
	pf->printed += (pf->prec > len) ? pf->prec + i : i + len;
}
