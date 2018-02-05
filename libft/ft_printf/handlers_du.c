/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers_uUpjz.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 11:34:39 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/12 16:09:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_modify_di(long long nb, t_printf *t)
{
	if (!(t->mod1))
		return ((int)nb);
	if (!(t->mod2) && (t->mod1 == 'h'))
		return ((short)nb);
	if (t->mod2 == 'h')
		return ((signed char)nb);
	if (!(t->mod2) && (t->mod1 == 'l'))
		return ((long)nb);
	if (t->mod2 == 'l')
		return ((long long)nb);
	if (t->mod1 == 'j')
		return ((intmax_t)nb);
	if (t->mod1 == 'z')
		return ((size_t)nb);
	return ((unsigned int)nb);
}

char		*ft_handleuint(va_list args, t_printf *t)
{
	unsigned long long		nb;

	nb = va_arg(args, unsigned long long);
	if (t->mod2 == 'h' && nb > 255)
		return (ft_llutoa(nb % 256));
	if (!t->mod1)
		return (ft_llutoa((unsigned int)nb));
	return (ft_llutoa(nb));
}

char		*ft_handle_uint(va_list args, t_printf *t)
{
	unsigned long long		nb;

	(void)t;
	nb = va_arg(args, unsigned long long);
	return (ft_llutoa(nb));
}

char		*ft_handleint(va_list args, t_printf *t)
{
	long long		nb;

	nb = va_arg(args, long long);
	if (nb < 0)
		t->neg = '1';
	nb = ft_modify_di(nb, t);
	if (nb >= MIN_INT && nb <= MAX_INT)
		return (ft_itoa((int)nb));
	else if (nb >= MIN_UINT && nb <= MAX_UINT)
		return (ft_ltoa((long)nb));
	else if (nb >= MIN_LONG && nb <= MAX_LONG)
		return (ft_lltoa((long long)nb));
	else if (nb < MIN_LONG || t->flag == 'j')
		return (ft_strjoinclr("-", ft_llutoa((unsigned long long)nb), 2));
	else if (nb > MAX_LONG)
		return (ft_llutoa((unsigned long long)nb));
	return (NULL);
}

char		*ft_handle_int(va_list args, t_printf *t)
{
	long long		nb;

	nb = va_arg(args, long long);
	if (nb >= MIN_INT && nb <= MAX_INT)
		return (ft_itoa((int)nb));
	else if (nb >= MIN_UINT && nb <= MAX_UINT)
		return (ft_ltoa((long)nb));
	else if (nb >= MIN_LONG && nb <= MAX_LONG)
		return (ft_lltoa((long long)nb));
	else if (nb < MIN_LONG || t->flag == 'j')
		return (ft_strjoinclr("-", ft_llutoa((unsigned long long)nb), 2));
	else if (nb > MAX_LONG)
		return (ft_llutoa((unsigned long long)nb));
	return (NULL);
}
