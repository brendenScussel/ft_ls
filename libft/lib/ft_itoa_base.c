/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 22:01:31 by bscussel          #+#    #+#             */
/*   Updated: 2020/02/02 22:01:34 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_itoa_base(int up, long long nbr, int base, char **res)
{
	long long	size;
	long long	tmp;
	char		*str;
	char		*case_tab;

	size = 1;
	case_tab = (up == 1) ? ("0123456789ABCDEF") : ("0123456789abcdef");
	tmp = nbr;
	while (tmp /= base)
		size++;
	str = (char *)malloc(sizeof(char) * (size + tmp + 1));
	if (str == NULL)
		return ;
	str[size] = '\0';
	while (size-- > tmp)
	{
		str[size] = case_tab[ft_absol(nbr % base)];
		nbr /= base;
	}
	*res = str;
	str = NULL;
	free(str);
}
