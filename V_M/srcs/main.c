/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:18:27 by arobion           #+#    #+#             */
/*   Updated: 2018/02/14 17:36:03 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

t_process	*lst_new_process(int opc, int cycle, int pc)
{
	t_process	*lst;
	int			i;

	i = 0;
	if (!(lst = (t_process*)malloc(sizeof(t_process))))
		exit(0);
	lst->opc = opc;
	lst->cycle_to_wait = cycle;
	lst->pc = pc;
	lst->carry = 0;
	if (!(lst->regs = (char**)malloc(sizeof(char*) * (REG_NUMBER))))
		exit(0);
	while (i < REG_NUMBER)
	{
		if (!(lst->regs[i] = (char*)malloc(sizeof(char) * REG_SIZE)))
			exit(0);
		i++;
	}
	lst->next = NULL;
	return (lst);
}

void	lst_pushfront_process(t_process **begin_list, int opc, int cycle, int pc)
{
	t_process	*lst;

	if (*begin_list)
	{
		lst = lst_new_process(opc, cycle, pc);
		lst->next = *begin_list;
		*begin_list = lst;
	}
	else
		*begin_list = lst_new_process(opc, cycle, pc);
}

void	load_one_champ(t_arena arn, char *champ, int p)
{
	int		fd;
	char	*l;
	int		i;

	i = 0;
	if (!(l = ft_strnew(1)))
		exit(0);
	fd = open(champ, O_RDONLY);
	while (read(fd, l, 1))
	{
		i++;
		if (i > PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
		{
			arn.mem[p] = l[0];
			p++;
		}
	}
	close(fd);
}

int		start_of_input(int i, int nb_players)
{
	int		sizeof_one_player;
	int		ret;

	sizeof_one_player = MEM_SIZE / nb_players;
	ret = (i - 1) * sizeof_one_player;
	return (ret);
}


void	load_champs(t_arena arn, char **argv, int nb_players)
{
	int		i;

	i = 1;
	while (i <= nb_players)
	{
		load_one_champ(arn, argv[i], start_of_input(i, nb_players));
		i++;
	}
}

t_player	create_one_player(char *champ)
{
	t_player	player;
	int			fd;
	int			i;
	char		*l;
	int			j;

	if (!(l = ft_strnew(1)))
		exit(0);
	if (!(player.name = ft_strnew(PROG_NAME_LENGTH)))
		exit(0);
	if (!(player.comment = ft_strnew(COMMENT_LENGTH)))
		exit(0);
	fd = open(champ, O_RDONLY);
	i = -1;
	j = 0;
	while (++i < 4)
		read(fd, l, 1);
	while (i < 4 + PROG_NAME_LENGTH)
	{
		read(fd, l, 1);
		player.name[j++] = l[0];
		i++;
	}
	i = -1;
	j = 0;
	while (++i < 8)
		read(fd, l, 1);
	while (i < 8 + COMMENT_LENGTH)
	{
		read(fd, l, 1);
		player.comment[j++] = l[0];
		i++;
	}
	player.nb_live = 0;
	player.last_live = 0;
	free(l);
	close(fd);
	return (player);
}

void	init_players(t_player *players, int nb_players, char **argv)
{
	int		i;

	i = 0;
	while (i < nb_players)
	{
		players[i] = create_one_player(argv[i + 1]);
		i++;
	}
}

void	init_process(t_arena arn, t_process **begin_list)
{
	int			i;
	int			start;

	i = 0;
	while (i < arn.nb_players)
	{
		start = start_of_input(i + 1, arn.nb_players);
		lst_pushfront_process(begin_list, arn.mem[start], opc_nb_cycle(arn.mem[start]), start);
		i++;
	}
}

void	init_arena(t_arena *arn, int nb_players, char **argv)
{
	(*arn).nb_cycle = 0;
	(*arn).nb_players = nb_players;
	(*arn).nb_checks = 0;
	if (!((*arn).players = (t_player*)malloc(sizeof(t_player) * nb_players)))
		exit(0);
	init_players((*arn).players, nb_players, argv);
	(*arn).process = NULL;
	init_process(*arn, &(arn->process));
}

int		main(int argc, char **argv)
{
	t_arena	arn;
	int		nb_players;

	if (argc - 1 > MAX_PLAYERS || argc == 1)
	{
		write(1, "error\n", 6);
		return (0);
	}
	nb_players = argc - 1;
	if (!(arn.mem = (char*)malloc(sizeof(char) * MEM_SIZE)))
		exit(0);
	load_champs(arn, argv, nb_players);
	init_arena(&arn, nb_players, argv);
	print_arena(arn);
//	print_mem(arn.mem, MEM_SIZE);
	return (0);
}
