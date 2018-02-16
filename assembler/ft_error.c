/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:15:05 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/16 18:56:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	ft_error_line(char *str, int line_nb)
{
	ft_dprintf(2, "%+kERROR%k, line %d : %s\n", LRED, RESET, line_nb, str);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	ft_dprintf(2, "%+kERROR%k: %s\n", LRED, RESET, str);
	exit(EXIT_FAILURE);
}

int		ft_error_return(char *str, int ret)
{
	ft_dprintf(2, "%+kERROR%k: %s\n", LRED, RESET, str);
	return (ret);
}
