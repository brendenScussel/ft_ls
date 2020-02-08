/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:36:40 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/03 21:14:19 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_memset(t_pf *pf)
{
	int			i;

	i = -1;
	while (++i < 5)
		pf->flag[i] = 0;
	pf->width = 0;
	pf->prec = 0;
	pf->length = 0;
	pf->spec = '\0';
	pf->index = 0;
	pf->printed = 0;
	pf->format = NULL;
}

static void		reset_flags(t_pf *pf)
{
	int			i;

	i = 0;
	while (i < 5)
	{
		pf->flag[i] = 0;
		++i;
	}
	pf->width = 0;
}

static void		parse_arg(t_pf *pf)
{
	if (pf->format[0] == '%' && pf->format[1] == '\0')
	{
		bs_putchar('\0');
		pf->index++;
		return ;
	}
	flag_type(pf, pf->format);
	minimum_width(pf, pf->format);
	precision(pf, pf->format);
	length_conversion(pf, pf->format);
	specifier(pf, pf->format);
}

int				std_print(const char *format)
{
	bs_putchar(*format);
	return (1);
}

int				ft_printf(const char *format, ...)
{
	t_pf		*pf;
	int			len;

	pf = (t_pf *)malloc(sizeof(t_pf));
	pf_memset(pf);
	va_start(pf->arg, format);
	pf->format = (char *)format;
	while (*pf->format)
	{
		if (*pf->format != '%')
			pf->printed += std_print(pf->format++);
		else if (*pf->format == '%')
		{
			parse_arg(pf);
			pf->format += pf->index;
			reset_flags(pf);
		}
	}
	va_end(pf->arg);
	len = pf->printed;
	free(pf);
	pf = NULL;
	return (len);
}
