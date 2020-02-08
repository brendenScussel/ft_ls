/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 00:58:23 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 03:24:47 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			percent_symbol(t_pf *pf)
{
	int			i;
	int			pad;

	i = 0;
	pad = pf->width - 1;
	(pf->flag[0] == 1) ? bs_putchar('%') : 0;
	while (i < pad)
	{
		(pf->flag[3] == 1 && pf->flag[0] == 0) ?
			bs_putchar('0') : bs_putchar(' ');
		i++;
	}
	(pf->flag[0] == 0) ? bs_putchar('%') : 0;
	pf->printed += 1 + i;
}

void			null_char(t_pf *pf)
{
	int			i;
	int			pad;

	i = 0;
	pad = pf->width - 1;
	if (pf->spec == 'c')
	{
		(pf->flag[0] == 1) ? bs_putchar('\0') : 0;
		while (i < pad)
		{
			bs_putchar(' ');
			i++;
		}
		(pf->flag[0] == 0) ? bs_putchar('\0') : 0;
		pf->printed += i + 1;
	}
	else
	{
		while (i++ < pf->width)
			bs_putchar(' ');
		pf->printed += pf->width;
	}
}

/*
**	should the string arguement be NULL the string "(null)" will be printed
**	padding is applied as normal
**	if precission is 0 nothing no string is printed
**	else if the precission is not -1, NULL is printed to the .prec value or 6
*/

void			null_str(t_pf *pf)
{
	int			i;
	int			pad;
	int			nlen;

	i = 0;
	nlen = (pf->prec == -1) ? 6 : pf->prec;
	(nlen > 6) ? nlen = 6 : 0;
	pad = (pf->width > 0) ? pf->width - nlen : 0;
	(pf->flag[0] == 1 && pf->prec != 0) ? write(1, NSTR, nlen) : 0;
	while (i < pad)
	{
		bs_putchar(' ');
		i++;
	}
	(pf->flag[0] == 0 && pf->prec != 0) ? write(1, NSTR, nlen) : 0;
	pf->printed += (i > 0) ? i + nlen : nlen;
}

static void		arg_print(char *arg, t_pf *pf)
{
	int			i;
	int			len;
	int			pad;

	i = 0;
	len = (int)bs_strlen(arg);
	pad = (pf->prec >= 0 && pf->spec == 's' && pf->prec < len) ?
		(pf->width - pf->prec) : (pf->width - len);
	if (pf->flag[0] == 1)
		(pf->prec >= 0 && pf->spec == 's' && pf->prec < len) ?
			write(1, arg, pf->prec) : write(1, arg, len);
	while (i < pad)
	{
		bs_putchar(' ');
		i++;
	}
	if (pf->flag[0] == 0)
		(pf->prec >= 0 && pf->spec == 's' && pf->prec < len) ?
			write(1, arg, pf->prec) : write(1, arg, len);
	pf->printed += (pf->prec >= 0 && pf->spec == 's' && pf->prec < len) ?
		(i + pf->prec) : (i + len);
}

void			character_print(t_pf *pf)
{
	char		*arg;

	if (pf->spec == '%')
		percent_symbol(pf);
	else if (pf->spec == 's')
	{
		arg = va_arg(pf->arg, char*);
		if (arg == NULL)
			null_str(pf);
		else if (arg[0] == '\0')
			null_char(pf);
		else
			arg_print(arg, pf);
	}
	else
	{
		arg = (char*)malloc(sizeof(char) * 2);
		arg[0] = va_arg(pf->arg, int);
		arg[1] = '\0';
		(arg[0] == '\0') ? null_char(pf) : arg_print(arg, pf);
		free(arg);
		arg = NULL;
	}
}
