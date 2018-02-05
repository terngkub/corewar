/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 23:01:07 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/12 14:24:35 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_wstrlen(wchar_t *wstr)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (wstr[++i])
	{
		if (ft_wcharlen(wstr[i]) == 0)
			return (-1);
		len += ft_wcharlen(wstr[i]);
	}
	return (len);
}

static char		*ft_getwstr(wchar_t *wstr)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	if (!(str = ft_strnew(ft_wstrlen(wstr))))
		return (NULL);
	while (wstr[++i])
	{
		tmp = ft_getwchar(wstr[i]);
		ft_strcat(str, tmp);
		free(tmp);
	}
	return (str);
}

char			*ft_handle_wstr(va_list args, t_printf *t)
{
	wchar_t		*tmp;
	int			i;
	int			y;

	(void)t;
	i = -1;
	y = 0;
	tmp = va_arg(args, wchar_t*);
	if (!tmp)
		return (ft_strdup("(null)"));
	if (ft_wstrlen(tmp) == -1)
		return (NULL);
	while (tmp[++i])
	{
		if ((y + ft_wcharlen(tmp[i])) > t->prec)
			break ;
		else
			y += ft_wcharlen(tmp[i]);
	}
	t->prec = (t->prec != -1) ? y : t->prec;
	return (ft_getwstr(tmp));
}
