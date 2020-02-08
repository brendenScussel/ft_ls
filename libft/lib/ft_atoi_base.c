/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:36:42 by bscussel          #+#    #+#             */
/*   Updated: 2020/02/02 22:00:42 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	convert ASCII numeric characters into an interger value with
**	specified base (up to 16)
*/

int			value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

/*
**	compare the current character to the list of valid ones
*/

int			is_valid(char c, int base)
{
	char	*valid1;
	char	*valid2;

	valid1 = (char *)ft_memalloc(sizeof(char) * 17);
	valid2 = (char *)ft_memalloc(sizeof(char) * 17);
	valid1 = "0123456789ABCDEF";
	valid2 = "0123456789abcdef";
	if (c == 'x')
		return (1);
	while (base--)
	{
		if (valid1[base] == c || valid2[base] == c)
			return (1);
	}
	return (0);
}

/*
**	ft_atoi_base operates similar to the standard ft_atoi function.
**	the first character of "str" is read, and if a "-", the sign is set to -1
**	while the current character is "blank", it is skipped over
**	if there's a second "+" or "-", it is also skipped
**	while the current character is valid
**	result = current value of result * the base umber + the
**	value of the character
*/

int			ft_atoi_base(const char *str, int str_base)
{
	int		result;
	int		sign;

	result = 0;
	sign = (*str == '-') ? -1 : 1;
	while (*str <= 32)
		str++;
	(*str == '-' || *str == '+') ? ++str : 0;
	while (is_valid(*str, str_base))
		result = result * str_base + value_of(*str++);
	return (result * sign);
}
