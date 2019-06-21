/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:30:34 by nde-jesu          #+#    #+#             */
/*   Updated: 2019/06/19 15:55:29 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "env.h"
#include "wolf3d.h"

static int		get_color(SDL_Surface *surf, int x, int y)
{
	uint8_t		*p;
	t_color		clr;

	p = surf->pixels + y * surf->pitch - x * surf->format->BytesPerPixel;
	SDL_GetRGB(*p, surf->format, &clr.r, &clr.g, &clr.b);
	return (clr.r << 16 | clr.g << 8 | clr.b);
}

static int		draw_wall(t_pos start, t_pos end, t_env *env, t_pos *current)
{
	int			i;
	int			tex;
	int			color;

	if (env->tex_on == 1)
	{
		i = (current->y - env->cam.offset) * 256 - (env->h) * 128\
			+ env->ray.wall.size * 128;
		tex = (i * CELL / env->ray.wall.size / 256) + 1;
		color = get_color(env->sdl.surf[env->ray.which_wall],
				env->ray.offset, tex);
	}
	else
	{
		if (current->y <= start.y + 5 || current->y >= end.y - 5\
				|| env->ray.offset < 2 || env->ray.offset > 63)
			color = 0x000000;
		else
			color = env->sdl.colors[env->ray.which_wall];
	}
	return (color);
}

static void		draw_slice(t_pos start, t_pos end, t_env *env)
{
	t_pos		current;
	int			color;

	current.x = start.x;
	current.y = -1;
	while (++current.y < env->h)
	{
		if (current.y <= start.y)
			if (env->tex_on == 1)
				color = SKY_HITLER;
			else
				color = SKY;
		else if (current.y > start.y && current.y < end.y)
			color = draw_wall(start, end, env, &current);
		else
		{
			if (env->tex_on == 1)
				color = FLOOR_HITLER;
			else
				color = FLOOR;
		}
		env->sdl.pixels[(int)(current.x + (current.y * (env->w)))] = color;
	}
}

void			raycast(t_env *env, t_ray *ray)
{
	int		x;

	x = -1;
	setup_raycasting(&env->cam, &env->ray, env->w);
	while (++x < env->w)
	{
		y_collisions(ray, env->cam);
		x_collisions(ray, env->cam, env->data);
		check_collisions(ray, env->map, env->height, env->width);
		setup_slice(ray, &env->cam, x, env);
		draw_slice(ray->wall.start, ray->wall.end, env);
		ray->angle -= ray->step;
		if (env->ray.angle >= env->data.two_pi)
			env->ray.angle -= env->data.two_pi;
	}
}
