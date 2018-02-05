/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:48:29 by fbabin            #+#    #+#             */
/*   Updated: 2017/12/01 19:06:40 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf		*ft_plst_init(void)
{
	t_printf	*t;

	if ((t = (t_printf*)malloc(sizeof(t_printf))) == NULL)
		return (NULL);
	ft_bzero(t, sizeof(t_printf));
	return (t);
}
