/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:35:46 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/03 21:57:09 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_type(t_pf *pf, char *frm)
{
	int		i;

	i = 1;
	while (frm[i] == '-' || frm[i] == '+' || frm[i] == ' ' ||
			frm[i] == '0' || frm[i] == '#')
	{
		(frm[i] == '-') ? pf->flag[0] = 1 : 0;
		(frm[i] == '+') ? pf->flag[1] = 1 : 0;
		(frm[i] == ' ') ? pf->flag[2] = 1 : 0;
		(frm[i] == '0') ? pf->flag[3] = 1 : 0;
		(frm[i] == '#') ? pf->flag[4] = 1 : 0;
		i++;
	}
	pf->index = i;
}

void		minimum_width(t_pf *pf, char *frm)
{
	int		i;
	int		j;
	char	n[21];

	i = pf->index;
	j = 0;
	if (frm[i] == '*')
	{
		pf->width = (int)va_arg(pf->arg, int);
		i++;
	}
	else if (frm[i] >= '0' && frm[i] <= '9')
	{
		while (frm[i] >= '0' && frm[i] <= '9')
			n[j++] = frm[i++];
		n[j] = '\0';
		pf->width = bs_atoi(n);
	}
	pf->index = i;
}

void		precision(t_pf *pf, char *frm)
{
	int		i;
	int		j;
	char	n[21];

	i = pf->index;
	j = 0;
	pf->prec = -1;
	if (frm[i] == '.' && frm[i + 1] == '*')
	{
		pf->prec = (int)va_arg(pf->arg, int);
		i += 2;
	}
	else if (frm[i] == '.')
	{
		i++;
		while (frm[i] >= '0' && frm[i] <= '9')
			n[j++] = frm[i++];
		n[j] = '\0';
		pf->prec = bs_atoi(n);
	}
	pf->index = i;
}

void		length_conversion(t_pf *pf, char *frm)
{
	int		i;

	i = pf->index;
	if (frm[i] == 'h' && frm[i + 1] != 'h')
		pf->length = 1;
	else if (frm[i] == 'h' && frm[i + 1] == 'h')
		pf->length = 2;
	else if (frm[i] == 'l' && frm[i + 1] != 'l')
		pf->length = 3;
	else if (frm[i] == 'l' && frm[i + 1] == 'l')
		pf->length = 4;
	else if (frm[i] == 'L')
		pf->length = 5;
	if (pf->length == 2 || pf->length == 4)
		pf->index += 2;
	else if (pf->length == 1 || pf->length == 3 || pf->length == 5)
		pf->index += 1;
}

void		specifier(t_pf *pf, char *frm)
{
	int		i;
	int		x;
	char	*tab;

	i = pf->index;
	x = 13;
	tab = ("0%cspbdifouxX");
	while ((--x) > 0 && frm[i] != tab[x])
		;
	pf->spec = (frm[i] == tab[x]) ? tab[x] : tab[0];
	(pf->spec == 'i') ? pf->spec = 'd' : 0;
	if (pf->spec == '0')
	{
		if (frm[i + 1] != '\0')
			bum_spec(pf);
		else
			return ;
	}
	else if (pf->spec == 'c' || pf->spec == 's' || pf->spec == '%')
		character_print(pf);
	else
		number_setup(pf);
	pf->index++;
}
