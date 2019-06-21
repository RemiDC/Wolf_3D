/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:07:35 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/19 13:01:27 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "wolf3d.h"

void	negative(unsigned int *pixel)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	color;

	color = *pixel;
	r = (color & 0xff0000) >> 16;
	g = (color & 0xff00) >> 8;
	b = (color & 0xff);
	color = 0xff << 24 | (r ^ 0xff) << 16 | (g ^ 0xff) << 8 | (b ^ 0xff);
	*pixel = color;
}

void	crosshair(t_sdl *sdl, t_env *env)
{
	int	x;
	int	y;

	y = env->h / 2 - 21;
	while (++y < env->h / 2 + 21)
	{
		x = env->w / 2 - 2;
		while (++x < env->w / 2 + 2)
			negative(&sdl->pixels[x + y * env->w]);
	}
	y = env->h / 2 - 2;
	while (++y < env->h / 2 + 2)
	{
		x = env->w / 2 - 21;
		while (++x < env->w / 2 + 21)
			if (x < env->w / 2 - 1 || x > env->w / 2 + 1)
				negative(&sdl->pixels[x + y * env->w]);
	}
}
