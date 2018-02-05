/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_alt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 23:30:46 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/15 20:45:29 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_fprintf(int fd, const char *format, ...)
{
	va_list		args;
	int			len;

	va_start(args, format);
	len = ft_vfprintf(fd, format, args);
	va_end(args);
	return (len);
}

int			ft_sprintf(char **str, const char *format, ...)
{
	va_list		args;
	int			len;
	char		*buff;

	if (!format)
		return (-1);
	if (!(buff = ft_strnew(0)))
		return (0);
	len = 0;
	va_start(args, format);
	if (!(*str = ft_readf(format, args, buff, &len)))
	{
		if (len != -1)
			free(buff);
		return (-1);
	}
	va_end(args);
	*str = ft_handle_colors(*str, &len);
	*str = ft_rep(*str, -1, 0);
	return (len);
}
