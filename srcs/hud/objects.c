/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:54:51 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/19 13:07:02 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wolf3d.h"

void	walls(t_env *env, t_pos wall, t_pos limit, int x)
{
	while (++wall.y <= limit.y)
	{
		wall.x = x * (4 * env->factor) + 15;
		while (++wall.x <= limit.x)
			env->sdl.pixels[(int)(wall.x + wall.y * env->w)] = 0xffffff;
	}
}

void	spawn(t_env *env, t_pos wall, t_pos limit, int x)
{
	while (++wall.y <= limit.y)
	{
		wall.x = x * (4 * env->factor) + 15;
		while (++wall.x <= limit.x)
			env->sdl.pixels[(int)(wall.x + wall.y * env->w)] = 0xffff00ff;
	}
}

void	end(t_env *env, t_pos wall, t_pos limit, int x)
{
	while (++wall.y <= limit.y)
	{
		wall.x = x * (4 * env->factor) + 15;
		while (++wall.x <= limit.x)
			env->sdl.pixels[(int)(wall.x + wall.y * env->w)] = 0xff7fffff;
	}
}
