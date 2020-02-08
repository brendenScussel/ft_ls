/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 22:49:47 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/03 21:24:16 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						snbase(size_t uplo, long long nbr, size_t base,
		char **rn)
{
	long long				len;
	long long				tmp;
	char					*str;
	char					*tab;

	len = 1;
	tab = (uplo == 1) ? ("0123456789ABCDEF") : ("0123456789abcdef");
	tmp = nbr;
	while (tmp /= base)
		len++;
	str = (char*)malloc(sizeof(char) * (tmp + len + 1));
	str[len] = '\0';
	while (len-- > tmp)
	{
		str[len] = tab[bs_absol(nbr % base)];
		nbr /= base;
	}
	*rn = str;
	free(str);
	str = NULL;
}

void						unsnbase(size_t uplo, unsigned long long nbr,
		size_t base, char **rn)
{
	unsigned long long		len;
	unsigned long long		tmp;
	char					*str;
	char					*tab;

	len = 1;
	tab = (uplo == 1) ? ("0123456789ABCDEF") : ("0123456789abcdef");
	tmp = nbr;
	while (tmp /= base)
		len++;
	str = (char*)malloc(sizeof(char) * (tmp + len + 1));
	str[len] = '\0';
	while (len-- > tmp)
	{
		str[len] = tab[bs_absol(nbr % base)];
		nbr /= base;
	}
	*rn = str;
	free(str);
	str = NULL;
}
