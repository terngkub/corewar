/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers_wcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 21:30:56 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/12 18:44:06 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcharlen(wchar_t wc)
{
	int		i;

	i = 0;
	if (wc < 0 || (wc >= 0xd800 && wc < 0xe000))
		return (0);
	if (MB_CUR_MAX == 1 && wc > 255)
		return (0);
	if ((wc <= 127 && MB_CUR_MAX >= 1) || (wc <= 255 && MB_CUR_MAX == 1))
		i = 1;
	else if (wc <= 2047 && MB_CUR_MAX >= 2)
		i = 2;
	else if (wc <= 65535 && MB_CUR_MAX >= 3)
		i = 3;
	else if (wc <= 1114111 && MB_CUR_MAX >= 4)
		i = 4;
	return (i);
}

char	*ft_getwchar(wchar_t wc)
{
	char	*str;

	if (!(str = ft_strnew(ft_wcharlen(wc))))
		return (NULL);
	if ((wc <= 127 && MB_CUR_MAX >= 1) || (wc <= 255 && MB_CUR_MAX == 1))
		str[0] = wc;
	else if (wc <= 2047 && MB_CUR_MAX >= 2)
	{
		str[0] = (wc >> 6) | 0xC0;
		str[1] = (wc & 0x3F) | 0x80;
	}
	else if (wc <= 65535 && MB_CUR_MAX >= 3)
	{
		str[0] = (wc >> 12) | 0xE0;
		str[1] = (wc >> 6 & 0x3F) | 0x80;
		str[2] = (wc & 0x3F) | 0x80;
	}
	else if (wc <= 1114111 && MB_CUR_MAX >= 4)
	{
		str[0] = (wc >> 18) | 0xF0;
		str[1] = (wc >> 12 & 0x3F) | 0x80;
		str[2] = (wc >> 6 & 0x3F) | 0x80;
		str[3] = (wc & 0x3F) | 0x80;
	}
	return (str);
}

char	*ft_handle_wchar(va_list args, t_printf *t)
{
	wchar_t		tmp;

	(void)t;
	tmp = va_arg(args, wchar_t);
	if (ft_wcharlen(tmp) == 0)
		return (NULL);
	if (tmp == 0)
		tmp = -1;
	return (ft_getwchar(tmp));
}
