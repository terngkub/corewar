/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 16:15:05 by nkamolba          #+#    #+#             */
/*   Updated: 2018/02/09 18:11:12 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	ft_error_line(char *str, int line_nb)
{
	ft_fprintf(2, "ERROR, line %d : %s\n", line_nb, str); 
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	ft_fprintf(2, "ERROR: %s\n", str);
	exit(EXIT_FAILURE);
}
