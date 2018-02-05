/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:51:13 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/19 16:36:26 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_hdl_cstd(va_list args, t_printf *t)
{
	if (t->flag == 'c')
		return (ft_handle_char(args, t));
	if (t->flag == 'C')
		return (ft_handle_wchar(args, t));
	if (t->flag == 's')
		return (ft_handle_str(args, t));
	if (t->flag == 'S')
		return (ft_handle_wstr(args, t));
	if (t->flag == 't')
		return (ft_handle_percent(args, t));
	if (t->flag == 'd' || t->flag == 'i')
		return (ft_handleint(args, t));
	if (t->flag == 'D')
		return (ft_handle_int(args, t));
	if (t->flag == 'f')
		return (ft_handle_float(args, t));
	if (t->flag == 'F')
		return (ft_handle_float(args, t));
	if (t->flag == 'p')
		return (ft_handlep(args, t));
	return (NULL);
}

static char		*ft_hdl_oux(va_list args, t_printf *t)
{
	if (t->flag == 'o')
		return (ft_handleoctal(args, t));
	if (t->flag == 'O')
		return (ft_handle_octal(args, t));
	if (t->flag == 'x')
		return (ft_handlehex(args, t));
	if (t->flag == 'X')
		return (ft_handle_hex(args, t));
	if (t->flag == 'u')
		return (ft_handleuint(args, t));
	if (t->flag == 'U')
		return (ft_handle_uint(args, t));
	if (t->flag == 'b')
		return (ft_handle_b(args, t));
	return (NULL);
}

char			*ft_handle_wrong(va_list args, t_printf *t)
{
	char	*str;

	(void)args;
	str = ft_strnew(1);
	str[0] = t->flag;
	return (str);
}

char			*ft_charargs(t_printf *t, va_list args)
{
	char	*str;

	str = NULL;
	if (ft_charinset(t->flag, "sScCtidDfFp"))
		str = ft_hdl_cstd(args, t);
	else if (ft_charinset(t->flag, "oOuUxXb"))
		str = ft_hdl_oux(args, t);
	else
		str = ft_handle_wrong(args, t);
	if (!str)
		return (NULL);
	t->neg = (str && str[0] == '-') ? '1' : t->neg;
	str[0] = (t->neg && t->prec > (int)ft_strlen(str)) ? '0' : str[0];
	if (t->prec == -1 && !ft_charinset(t->flag, "tp") && str[0] == '0')
	{
		free(str);
		return ("");
	}
	return (str);
}
