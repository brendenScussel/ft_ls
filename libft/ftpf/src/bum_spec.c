/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bum_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:35:07 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 03:20:48 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	conditions for undefined specifier
**	returns a '%' followed by the flags, width and precission
*/

static int			flag_check(int *flag)
{
	int				printed;

	printed = 0;
	if (flag[4] == 1)
	{
		bs_putchar('#');
		printed++;
	}
	if (flag[1] == 1)
	{
		bs_putchar('+');
		printed++;
	}
	if (flag[0] == 1)
	{
		bs_putchar('-');
		printed++;
	}
	return (printed);
}

void				bum_spec(t_pf *pf)
{
	int				str_len;

	str_len = 0;
	bs_putchar('%');
	pf->printed += 1 + flag_check(pf->flag);
	if (pf->width > 0)
		str_len = bs_itoa(pf->width);
	if (pf->prec > -1)
	{
		bs_putchar('.');
		str_len++;
		str_len += bs_itoa(pf->prec);
	}
	pf->printed += str_len;
}
