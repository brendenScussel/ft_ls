/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfunc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:24:45 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 03:32:26 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t				bs_size_nbr(long n)
{
	size_t			i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n /= 10)
		i++;
	return (i);
}

int					bs_itoa(int n)
{
	char			*str;
	size_t			len;
	size_t			len2;
	unsigned int	temp;

	len = bs_size_nbr((long)n);
	len2 = len;
	temp = n;
	if (n < 0)
		temp = -n;
	str = (char *)malloc(sizeof(char) * len + 1);
	str[len] = '\0';
	str[--len] = temp % 10 + '0';
	while (temp /= 10)
		str[--len] = temp % 10 + '0';
	if (n < 0)
		*(str + 0) = '-';
	bs_putstr(str);
	free(str);
	str = NULL;
	return (len2);
}

long long			bs_pow(int x, unsigned int y)
{
	int				i;
	long long		nbr;

	i = -1;
	nbr = 1;
	while (++i < (int)y)
		nbr *= x;
	return (nbr);
}
