/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers_sSdD.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:46:33 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/12 17:40:34 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_strmmjoin(char *s1, char *s2, int len1, int len2)
{
	char	*new;
	int		i;
	int		y;

	if (!(new = ft_strnew(len1 + len2)))
		return (NULL);
	i = -1;
	while (++i < len1)
		new[i] = s1[i];
	y = -1;
	while (++y < len2)
		new[i++] = s2[y];
	free(s1);
	free(s2);
	return (new);
}

char	*ft_handle_str(va_list args, t_printf *t)
{
	char	*str;

	(void)t;
	if (t->mod1 == 'l')
		return (ft_handle_wstr(args, t));
	str = va_arg(args, char*);
	if (str)
		return (ft_strdup(str));
	return (ft_strdup("(null)"));
}

char	*ft_handle_char(va_list args, t_printf *t)
{
	char	*str;
	int		c;

	(void)t;
	if (t->mod1 == 'l')
		return (ft_handle_wchar(args, t));
	c = va_arg(args, int);
	if (c > 255)
		return (NULL);
	if (!(str = ft_strnew(1)))
		return (NULL);
	if (c == 0)
		c = -1;
	str[0] = c;
	return (str);
}

char	*ft_handle_percent(va_list args, t_printf *t)
{
	char	*str;

	(void)t;
	(void)args;
	if (!(str = ft_strnew(1)))
		return (NULL);
	str[0] = '%';
	return (str);
}
