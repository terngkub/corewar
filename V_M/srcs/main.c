/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:18:27 by arobion           #+#    #+#             */
/*   Updated: 2018/02/15 18:09:04 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		opc_nb_cycle2(int opc)
{
	if (opc == 10)
		return (25);
	if (opc == 11)
		return (25);
	if (opc == 12)
		return (800);
	if (opc == 13)
		return (10);
	if (opc == 14)
		return (50);
	if (opc == 15)
		return (1000);
	if (opc == 16)
		return (2);
	return (1);
}

int		opc_nb_cycle(int opc)
{
	if (opc == 1)
		return (10);
	if (opc == 2)
		return (5);
	if (opc == 3)
		return (5);
	if (opc == 4)
		return (10);
	if (opc == 5)
		return (10);
	if (opc == 6)
		return (6);
	if (opc == 7)
		return (6);
	if (opc == 8)
		return (6);
	if (opc == 9)
		return (20);
	return (opc_nb_cycle2(opc));
}

int		main(int argc, char **argv)
{
	t_arena			arn;
	int				nb_players;
	int				i;
	unsigned int	dump;

	i = 1;
	dump = 0;
	if (!(nb_players = parse_champs(argc, argv, &i, &dump)))
		return (0);
	if (!(arn.mem = (char*)malloc(sizeof(char) * MEM_SIZE)))
		exit(0);
	if (!(load_champs(arn, argv, nb_players, i)))
		return (0);
	init_arena(&arn, nb_players, argv, i);
//	print_arena(arn);
	run_cycle(&arn);
//	print_arena(arn);
	//print_mem(arn.mem, MEM_SIZE);
	return (0);
}
