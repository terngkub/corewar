/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:28:09 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/15 21:55:22 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			hex_to_dec(char *str, int len)
{
	int		sum;

	sum = 0;
	while (len--)
		sum = sum * 256 + (unsigned char)*str++;
	return (sum);
}

int			x_char_to_int(char *str, int len)
{
	long long	ret;
	int			i;

	i = 0;
	ret = 0;
	while (i < len - 1)
	{
		ret = ret ^ str[i];
		ret = ret << 8;
		i++;
	}
	ret = ret ^ str[i];
	return ((int)ret);
}

void		int_to_x_char(char *str, int len, int value)
{
	int		i;
	int		byte;

	i = 0;
	while (i < len)
	{
		byte = value << (i * 8);
		byte = byte >> ((len - 1) * 8);
		str[i] = byte;
		i++;
	}
}
