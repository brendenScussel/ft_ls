/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:52:11 by bscussel          #+#    #+#             */
/*   Updated: 2020/02/02 21:55:52 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t			ft_strlen(const char *s)
{
	size_t		len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}
