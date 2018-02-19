/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_vm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:43:20 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/18 17:32:21 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_VM_H
# define VISU_VM_H

/*
** --------------------------------- INCLUDES -------------------------------
*/

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "/Users/pnardozi/.brew/include/SDL2/SDL.h"
# include "/Users/pnardozi/.brew/include/SDL2/SDL_ttf.h"
# define  WIDTH 1920
# define  HEIGHT 1380


/*
** -------------------------------- STRUCTURES -------------------------------
*/

typedef struct			s_env
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Texture		**texture;
	SDL_Rect		**rect;
	TTF_Font		*font;
	int				quit;
}						t_env;



/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/


#endif
