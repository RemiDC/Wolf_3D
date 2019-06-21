/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:50:58 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/19 15:46:50 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include <wolf3d.h>

int		free_parse(char *row, char **coords, t_env *env, int code)
{
	if (code > 1)
		free_split(coords);
	if (code > 0)
		free(row);
	if (code < 3)
		free_switch(env, code);
	return (1);
}

int		free_switch(t_env *env, int code)
{
	int	y;

	if (!(y = 0) && code)
	{
		if (env->height > 1)
		{
			while (y < env->height)
				free(env->map[y++]);
			free(env->map);
		}
	}
	free(env);
	return (1);
}

void	free_split(char **coords)
{
	int	y;

	y = 0;
	while (coords[y])
		free(coords[y++]);
	free(coords);
}

void	free_sdl(t_env *env, int state, char *error, int code)
{
	int	i;

	i = -1;
	if (state > 1)
		SDL_DestroyWindow(env->sdl.win);
	if (state > 2)
		SDL_DestroyRenderer(env->sdl.ren);
	if (state > 3)
		SDL_DestroyTexture(env->sdl.text);
	if (state > 4)
	{
		free(env->sdl.pixels);
		while (++i < 4)
			SDL_FreeSurface(env->sdl.surf[i]);
	}
	SDL_Quit();
	free_switch(env, 1);
	(state == 6 ? exit(code) : ft_print_error(error, code));
}
