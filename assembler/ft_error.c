/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:15:05 by nkamolba          #+#    #+#             */
/*   Updated: 2018/03/07 19:02:03 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	ft_error_line(char *str, int line_nb)
{
	ft_dprintf(2, "%+kerror%k: %+kline %k%d%k : %s\n",
		LRED, RESET, EOC, LGREEN, line_nb, RESET, str);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	ft_dprintf(2, "%+kerror%k: %s\n", LRED, RESET, str);
	exit(EXIT_FAILURE);
}

int		ft_error_return(char *str, int ret)
{
	ft_dprintf(2, "%+kerror%k: %s\n", LRED, RESET, str);
	return (ret);
}
