/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers_ioOxX.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 12:32:30 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/12 00:35:01 by fbabin           ###   ########.fr       */
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

char				*ft_handleoctal(va_list args, t_printf *t)
{
	unsigned long long		nb;

	(void)t;
	nb = va_arg(args, unsigned long long);
	nb = ft_modify_oux(nb, t);
	if (t->mod1 == 'j')
		return (ft_llutoa_base(nb, "01234567"));
	else if ((nb <= MAX_INT))
		return (ft_itoa_base((int)nb, "01234567"));
	else if (nb <= MAX_UINT)
		return (ft_ltoa_base((long)nb, "01234567"));
	else if (nb <= MAX_LONG)
		return (ft_lltoa_base((long long)nb, "01234567"));
	else if (nb > MAX_LONG)
	{
		if (ft_charinset(t->mod1, "lz"))
			return (ft_llutoa_base((unsigned long long)nb, "01234567"));
		else
			return (ft_ltoa_base((long)nb, "01234567"));
	}
	return (NULL);
}

char				*ft_handle_octal(va_list args, t_printf *t)
{
	(void)t;
	return (ft_lltoa_base(va_arg(args, long long), "01234567"));
}

char				*ft_handlehex(va_list args, t_printf *t)
{
	unsigned long long		nb;

	(void)t;
	nb = va_arg(args, unsigned long long);
	nb = ft_modify_oux(nb, t);
	if (t->mod1 == 'j')
		return (ft_llutoa_base(nb, "0123456789abcdef"));
	else if ((nb <= MAX_INT))
		return (ft_itoa_base((int)nb, "0123456789abcdef"));
	else if (nb <= MAX_UINT || !(t->mod1))
		return (ft_ltoa_base((long)nb, "0123456789abcdef"));
	else if (nb <= MAX_LONG)
		return (ft_lltoa_base((long long)nb, "0123456789abcdef"));
	else if (nb > MAX_LONG)
	{
		return (ft_llutoa_base((unsigned long long)nb, "0123456789abcdef"));
	}
	return (NULL);
}

char				*ft_handle_hex(va_list args, t_printf *t)
{
	unsigned long long		nb;

	(void)t;
	nb = va_arg(args, unsigned long long);
	nb = ft_modify_oux(nb, t);
	if (t->mod1 == 'j')
		return (ft_llutoa_base(nb, "0123456789ABCDEF"));
	else if ((nb <= MAX_INT))
		return (ft_itoa_base((int)nb, "0123456789ABCDEF"));
	else if (nb <= MAX_UINT || !(t->mod1))
		return (ft_ltoa_base((long)nb, "0123456789ABCDEF"));
	else if (nb <= MAX_LONG)
		return (ft_lltoa_base((long long)nb, "0123456789ABCDEF"));
	else if (nb > MAX_LONG)
	{
		return (ft_llutoa_base((unsigned long long)nb, "0123456789ABCDEF"));
	}
	return (NULL);
}
