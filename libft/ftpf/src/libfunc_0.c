/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfunc_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 03:32:10 by bscussel          #+#    #+#             */
/*   Updated: 2019/12/04 03:32:17 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		bs_absol(long long x)
{
	x = (x < 0) ? (x * 1) : x;
	return (x);
}

void			bs_putchar(char c)
{
	write(1, &c, 1);
}

void			bs_putstr(const char *s)
{
	char		*cpy;

	cpy = (char *)s;
	while (*cpy)
		write(1, cpy++, 1);
}

size_t			bs_strlen(const char *s)
{
	size_t		len;

	len = 0;
	while (s[len++] != '\0')
		;
	return (len - 1);
}

int				bs_atoi(const char *str)
{
	int			result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}
