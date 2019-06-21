/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:07:29 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/19 13:07:01 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

#include <stdio.h>

void	player_position(t_env *env, t_pos *player)
{
	player->x = env->cam.coord.x / 64 - floor(env->cam.coord.x / 64);
	player->y = env->cam.coord.y / 64 - floor(env->cam.coord.y / 64);
	player->x = (int)(map(player->x, fill_data(0, 1, 0, (4 * env->factor))));
	player->y = (int)(map(player->y, fill_data(0, 1, 0, (4 * env->factor))));
	player->x += (floor(env->cam.coord.x / 64) * (4 * env->factor)) + 16;
	player->y += (floor(env->cam.coord.y / 64) * (4 * env->factor)) + 16;
}

void	objects(t_env *env)
{
	t_pos	pos;
	t_pos	wall;
	t_pos	limit;

	pos.y = -1;
	while (++pos.y < env->height)
	{
		pos.x = -1;
		while (++pos.x < env->width)
		{
			wall.y = pos.y * (4 * env->factor) + 15;
			limit.y = wall.y + (4 * env->factor);
			limit.x = pos.x * (4 * env->factor) + (4 * env->factor) + 15;
			if (env->map[(int)pos.y][(int)pos.x] == 1)
				walls(env, wall, limit, pos.x);
			else if (env->map[(int)pos.y][(int)pos.x] == 9)
				spawn(env, wall, limit, pos.x);
			else if (env->map[(int)pos.y][(int)pos.x] == 5)
				end(env, wall, limit, pos.x);
		}
	}
}

void	fov(t_env *env, t_pos player)
{
	int		x;
	t_pos	limit;
	double	angle;
	double	step;

	if (env->cam.angle >= 330)
		angle = radians(env->cam.angle + 330);
	else
		angle = radians(env->cam.angle - 30);
	step = radians(env->cam.fov / RAYS);
	x = -1;
	while (++x < RAYS)
	{
		limit.x = player.x + floor(DISTANCE * cos(angle));
		limit.y = player.y - floor(DISTANCE * sin(angle));
		draw_line(player, limit, env);
		angle += step;
		if (angle >= env->data.two_pi)
			angle -= env->data.two_pi;
	}
}

int		map_size(int height, int width)
{
	if (height <= 16 && width <= 16)
		return (8);
	if (height <= 32 && width <= 32)
		return (4);
	if (height <= 64 && width <= 64)
		return (2);
	return (0);
}

void	minimap(t_env *env)
{
	t_pos	map;
	t_pos	player;
	t_pos	pos;

	if ((env->factor = map_size(env->height, env->width)))
	{
		player_position(env, &player);
		map.y = -1;
		pos.y = player.y - (1 + env->factor / 2);
		while (++map.y < env->height * (4 * env->factor) + 33)
		{
			map.x = -1;
			while (++map.x < env->width * (4 * env->factor) + 33)
				env->sdl.pixels[(int)(map.x + map.y * env->w)] = 0;
		}
		objects(env);
		fov(env, player);
		while (++pos.y < player.y + (1 + env->factor / 2))
		{
			pos.x = player.x - (1 + env->factor / 2);
			while (++pos.x < player.x + (1 + env->factor / 2))
				env->sdl.pixels[(int)(pos.x + pos.y * env->w)] = 0xff0000;
		}
	}
}
