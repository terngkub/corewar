/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_hexlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 20:18:17 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/12 20:34:43 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	disp_hexlen(int fd, size_t size, int len)
{
	unsigned char	*tmp;
	int				i;

	i = len;
	if (!(tmp = (unsigned char*)ft_memalloc(i * sizeof(unsigned char))))
		return ;
	while (size && i > 0)
	{
		tmp[--i] = size % 256;
		size /= 256;
	}
	write(fd, tmp, len);
	free(tmp);
}
