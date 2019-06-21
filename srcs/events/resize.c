/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 09:23:03 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/06/19 16:02:48 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"
#include "env.h"

void	resize(t_env *env, t_sdl *sdl, int flag)
{
	if (flag == 1)
	{
		env->w = env->sdl.event.window.data1;
		env->h = env->sdl.event.window.data2;
		if (env->w < 500 || env->h < 500)
		{
			SDL_SetWindowSize(sdl->win, 500, 500);
			env->w = 500;
			env->h = 500;
		}
	}
	free(sdl->pixels);
	SDL_DestroyTexture(sdl->text);
	sdl->text = SDL_CreateTexture(sdl->ren, ARGB, STREAM, env->w, env->h);
	if (!(sdl->pixels = (uint32_t*)malloc(4 * ((env->w + 1) * env->h))))
		return ;
	SDL_WarpMouseInWindow(env->sdl.win, env->w / 2, env->h / 2);
	raycast(env, &env->ray);
}

void	set_fullscreen(t_env *env)
{
	if (env->sdl.set_fs != 0)
		env->sdl.set_fs = 0;
	else
		env->sdl.set_fs = SDL_WINDOW_FULLSCREEN_DESKTOP;
	SDL_SetWindowFullscreen(env->sdl.win, env->sdl.set_fs);
	SDL_GetWindowSize(env->sdl.win, &env->w, &env->h);
	resize(env, &env->sdl, 0);
}

void	enable_mouse(t_mouse *mouse)
{
	mouse->old_time = mouse->curr_time;
	mouse->toggle_mouse *= -1;
	if (mouse->toggle_mouse == 1)
		SDL_ShowCursor(SDL_DISABLE);
	else
		SDL_ShowCursor(SDL_ENABLE);
}
