/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers_fpb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:49:03 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/13 15:00:51 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	ft_modify_oux(long long nb, t_printf *t)
{
	if (!(t->mod1))
		return ((int)nb);
	if (!(t->mod2) && (t->mod1 == 'h'))
		return ((unsigned short)nb);
	if (t->mod2 == 'h')
		return ((unsigned char)nb);
	if (!(t->mod2) && (t->mod1 == 'l'))
		return ((unsigned long)nb);
	if (t->mod2 == 'l')
		return ((unsigned long long)nb);
	if (t->mod1 == 'j')
		return ((uintmax_t)nb);
	if (t->mod1 == 'z')
		return ((size_t)nb);
	return (nb);
}

char				*ft_handlep(va_list args, t_printf *t)
{
	long long		nb;

	(void)t;
	nb = va_arg(args, long long);
	t->hash = '1';
	if (nb == 0 && t->prec == -1)
		return (ft_strdup(""));
	return (ft_lltoa_base((long long)nb,
				"0123456789abcdef"));
}

char				*ft_handle_b(va_list args, t_printf *t)
{
	unsigned long long		nb;

	(void)t;
	nb = va_arg(args, unsigned long long);
	nb = ft_modify_oux(nb, t);
	if (t->mod1 == 'j')
		return (ft_llutoa_base(nb, "01"));
	else if ((nb <= MAX_INT))
		return (ft_itoa_base((int)nb, "01"));
	else if (nb <= MAX_UINT || !(t->mod1))
		return (ft_ltoa_base((long)nb, "01"));
	else if (nb <= MAX_LONG)
		return (ft_lltoa_base((long long)nb, "01"));
	else if (nb > MAX_LONG)
	{
		return (ft_llutoa_base((unsigned long long)nb, "01"));
	}
	return (NULL);
}

char				*ft_handle_colors(char *str, int *len)
{
	char	*tmp;

	if (!ft_charinset('{', str))
		return (str);
	tmp = ft_strreplace(str, "{red}", RED);
	free(str);
	str = ft_strreplace(tmp, "{green}", GREEN);
	free(tmp);
	tmp = ft_strreplace(str, "{yellow}", YELLOW);
	free(str);
	str = ft_strreplace(tmp, "{blue}", BLUE);
	free(tmp);
	tmp = ft_strreplace(str, "{magenta}", MAGENTA);
	free(str);
	str = ft_strreplace(tmp, "{cyan}", CYAN);
	free(tmp);
	tmp = ft_strreplace(str, "{eoc}", EOC);
	free(str);
	*len = ft_strlen(tmp);
	return (tmp);
}

char				*ft_handle_float(va_list args, t_printf *t)
{
	double		nb;

	nb = va_arg(args, double);
	if (!t->prec)
		return (ft_ftoa(nb, 6));
	return (ft_ftoa(nb, t->prec));
}
