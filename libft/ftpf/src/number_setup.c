/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:33:57 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/03 21:15:17 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					floating_nbr(t_pf *pf)
{
	long double			nbr;

	nbr = 0;
	if (pf->length == 5)
		nbr = (long double)va_arg(pf->arg, long double);
	else
		nbr = (long double)va_arg(pf->arg, double);
	floating_point(pf, nbr);
}

void					u_ll_nbr(t_pf *pf)
{
	unsigned long long	nbr;

	nbr = 0;
	if (pf->length == 1)
		nbr = (unsigned short)va_arg(pf->arg, int);
	else if (pf->length == 2)
		nbr = (unsigned char)va_arg(pf->arg, int);
	else if (pf->length == 3)
		nbr = va_arg(pf->arg, unsigned long);
	else if (pf->length == 4)
		nbr = va_arg(pf->arg, unsigned long long);
	else
		nbr = va_arg(pf->arg, unsigned int);
	unsgn_start(pf, nbr);
}

void					ll_nbr(t_pf *pf)
{
	long long			nbr;

	nbr = 0;
	if (pf->length == 1 && pf->spec != 'p')
		nbr = (short)va_arg(pf->arg, int);
	else if (pf->length == 2 && pf->spec != 'p')
		nbr = (signed char)va_arg(pf->arg, int);
	else if (pf->length == 3 && pf->spec != 'p')
		nbr = va_arg(pf->arg, long);
	else if (pf->length == 4 || pf->spec == 'p')
		nbr = va_arg(pf->arg, long long);
	else
		nbr = va_arg(pf->arg, int);
	sgn_print(pf, nbr);
}

void					number_setup(t_pf *pf)
{
	if (pf->spec == 'd' || pf->spec == 'p')
		ll_nbr(pf);
	else if (pf->spec == 'b' || pf->spec == 'o' || pf->spec == 'u' ||
			pf->spec == 'x' || pf->spec == 'X')
		u_ll_nbr(pf);
	else if (pf->spec == 'f')
		floating_nbr(pf);
}
