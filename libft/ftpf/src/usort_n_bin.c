/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsgn_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:20:23 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/03 21:08:52 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				bin_space(char *str, int len)
{
	int			tmp;
	int			space;
	int			i;

	tmp = len;
	space = 0;
	i = 0;
	while (--tmp >= 0)
	{
		if (tmp % 4 == 0 && str[i + 1] != '\0')
			space++;
		i++;
	}
	return (space);
}

void			bin_print(t_pf *pf, char *str, int len)
{
	int			tmp;
	int			i;

	tmp = len;
	i = 0;
	if (pf->flag[2] == 1)
	{
		while (--tmp >= 0)
		{
			bs_putchar(str[i]);
			if (tmp % 4 == 0 && str[i + 1] != '\0')
				bs_putchar(' ');
			i++;
		}
	}
	else
		bs_putstr(str);
}

void			bin_start(t_pf *pf, char *str)
{
	int			i;
	int			len;
	int			pad;
	int			a_s;

	i = 0;
	len = (int)bs_strlen(str);
	pad = pf->width - len;
	a_s = (pf->flag[2] == 1) ? bin_space(str, len) : 0;
	pad -= a_s;
	(pf->flag[0] == 1) ? bin_print(pf, str, len) : 0;
	while (i < pad)
	{
		bs_putchar(' ');
		i++;
	}
	(pf->flag[0] == 0) ? bin_print(pf, str, len) : 0;
	pf->printed += i + a_s + len;
}

void			sort_unsgn(t_pf *pf, char *str, unsigned long long nbr)
{
	(pf->spec == 'b') ? bin_start(pf, str) : 0;
	(pf->spec == 'o') ? oct_print(pf, str, nbr) : 0;
	(pf->spec == 'u') ? unsgn_print(pf, str) : 0;
	(pf->spec == 'x' || pf->spec == 'X') ? hex_print(pf, str, nbr) : 0;
}

void			unsgn_start(t_pf *pf, unsigned long long nbr)
{
	char		*str;

	str = NULL;
	if (nbr == 0 && pf->prec == 0 &&
			(pf->spec != 'x' && pf->spec != 'X' && pf->spec != 'o'))
		return ;
	if (pf->spec == 'b')
		unsnbase(0, nbr, 2, &str);
	else if (pf->spec == 'o')
		unsnbase(0, nbr, 8, &str);
	else if (pf->spec == 'u')
		unsnbase(0, nbr, 10, &str);
	else if (pf->spec == 'x')
		unsnbase(0, nbr, 16, &str);
	else if (pf->spec == 'X')
		unsnbase(1, nbr, 16, &str);
	sort_unsgn(pf, str, nbr);
}
