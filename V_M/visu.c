/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 14:19:36 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/19 14:38:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu_vm.h"

SDL_Rect		**init_rect(void)
{
	SDL_Rect	**rect;
	int		i;
	int		y;
	int		x;

	i = -1;
	x = 10;
	y = 10;
	rect = NULL;
	if (!(rect = (SDL_Rect**)malloc(4096 * sizeof(SDL_Rect*))))
		return (0);
	while (++i < 4096)
	{
		if (!(rect[i] = (SDL_Rect*)malloc(sizeof(SDL_Rect))))
			return (0);
		if ((i % 64) == 0 && i != 0)
		{
			x = 10;
			y += 20;
		}
		(rect[i])->x = x;
		(rect[i])->y = y;
		x += 20;
	}
	return (rect);
}

void	update_renderer(t_env *env, char *str, SDL_Color color, int i)
{
	int				textW = 0;
	int				textH = 0;

	env->surface = TTF_RenderText_Solid(env->font, str, color);
	env->texture[i] = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	SDL_QueryTexture(env->texture[i], NULL, NULL, &textW, &textH);
	(env->rect[i])->h = textH;
	(env->rect[i])->w = textW;
	SDL_FreeSurface(env->surface);
	SDL_RenderCopy(env->renderer, env->texture[i], NULL, (env->rect[i]));
	SDL_DestroyTexture(env->texture[i]);
}

void	init_SDL(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		ft_dprintf(stderr, "Erreur d'initialisation de la SDL");
		exit(EXIT_FAILURE);
	}
	if (TTF_Init() == -1)
	{
		ft_dprintf(stderr, "Erreur d'initialisation de TTF");
		exit(EXIT_FAILURE);
	}
	if (!(env->texture = (SDL_Texture**)malloc(4096 * sizeof(SDL_Texture*))))
		return (0);
	env->rect = init_rect();
	env->font = TTF_OpenFont("./arial.ttf", 14);
	env->window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

void	display_cycle(t_env *env)
{
	int		end;
	int		i;

	end = 0;
	if (env->window && env->font)
	{
		env->renderer = SDL_CreateRenderer(env.window, -1, SDL_RENDERER_ACCELERATED);
		while (!end)
		{
			SDL_WaitEvent(&env->event);
			if (env->event.type == SDL_QUIT)
				end++;
			SDL_RenderClear(env->renderer);
			i = -1;
			while (++i < 4096)
			{
				update_renderer(&env, "ff", color, i);
			}
			SDL_RenderPresent(env->renderer);
		}
		SDL_DestroyWindow(env->window);
	}
	else
		ft_dprintf(stderr, "ERROR CREATE WINDOW : %s\n", SDL_GetError());
}

void	close_SDL(void)
{
	SDL_Quit();
	TTF_Quit();
}

int		main(void)
{
	SDL_Color		color = {255, 0, 0, 100};
	t_env			env;
	int 			end = 0;
	int				i;

	i = -1;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		ft_dprintf(stderr, "Erreur d'initialisation de la SDL");
		exit(EXIT_FAILURE);
	}
	if (TTF_Init() == -1)
	{
		ft_dprintf(stderr, "Erreur d'initialisation de TTF");
		exit(EXIT_FAILURE);
	}
	if (!(env.texture = (SDL_Texture**)malloc(4096 * sizeof(SDL_Texture*))))
		return (0);
	env.rect = init_rect();
	env.font = TTF_OpenFont("./arial.ttf", 14);
	env.window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//init_SDL(&env);
	if (env.window && env.font)
	{
		env.renderer = SDL_CreateRenderer(env.window, -1, SDL_RENDERER_ACCELERATED);
		while (!end)
		{
			SDL_WaitEvent(&env.event);
			if (env.event.type == SDL_QUIT)
				end++;
			SDL_RenderClear(env.renderer);
			i = 0;
			while (++i < 4096)
			{
				update_renderer(&env, "ff", color, i);
			}
			SDL_RenderPresent(env.renderer);
		}
		SDL_DestroyWindow(env.window);
	}
	else
		ft_dprintf(stderr, "ERROR CREATE WINDOW : %s\n", SDL_GetError());
	//display_cycle(&env);
	SDL_Quit();
	TTF_Quit();
	//close_SDL(void);
	return (EXIT_SUCCESS);
}
