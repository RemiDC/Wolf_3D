/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:33:37 by reda-con          #+#    #+#             */
/*   Updated: 2019/06/19 13:11:23 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "wolf3d.h"
#include "env.h"

void	upload_image(t_env *env, int i)
{
	raycast(env, &env->ray);
	crosshair(&env->sdl, env);
	if (i == 1 && env->w > WIDTH / 2 && env->h > HEIGHT / 2)
		minimap(env);
	if (SDL_UpdateTexture(env->sdl.text, 0, env->sdl.pixels, env->w * 4) < 0)
		free_sdl(env, 5, ERR_UPDATE, 17);
	if (SDL_RenderCopy(env->sdl.ren, env->sdl.text, 0, 0) < 0)
		free_sdl(env, 5, ERR_COPY, 18);
	SDL_RenderPresent(env->sdl.ren);
}
