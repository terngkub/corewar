/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:25:39 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/15 20:51:16 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_read_bis(char *str, int *len)
{
	if (!str && *len == -1)
		return (0);
	else if (*len == -1)
		return (0);
	return (1);
}

char			*ft_readf(const char *fmt, va_list args, char *buff, int *len)
{
	int			idx;
	int			i;

	i = -1;
	idx = 0;
	while (fmt[++i])
	{
		if (fmt[i] == '%')
		{
			buff = ft_strmjoin(buff, fmt, *len, i);
			fmt += i + 1;
			*len += i;
			idx = ft_strspn(fmt, " #+-.0123456789hljz");
			if (!fmt[idx])
				break ;
			buff = ft_handler(buff, (char*)fmt, args, len);
			if ((i = -1) && (fmt += idx + 1) && !ft_read_bis(buff, len))
				return (NULL);
		}
	}
	if (!fmt[0] && fmt[-1] == '%')
		return (buff);
	buff = ft_strmjoin(buff, fmt, *len, i);
	*len += (fmt[i - 1] != '%') ? i : 0;
	return (buff);
}

int				ft_vfprintf(int fd, const char *format, va_list ap)
{
	char		*str;
	int			len;
	char		*buff;

	if (!format)
		return (-1);
	if (!(buff = ft_strnew(0)))
		return (0);
	len = 0;
	if (!(str = ft_readf(format, ap, buff, &len)))
	{
		if (len != -1)
			free(buff);
		return (-1);
	}
	str = ft_handle_colors(str, &len);
	str = ft_rep(str, -1, 0);
	write(fd, str, len);
	free(str);
	return (len);
}

int				ft_printf(const char *format, ...)
{
	va_list		args;
	int			len;

	va_start(args, format);
	len = ft_vfprintf(1, format, args);
	va_end(args);
	return (len);
}
