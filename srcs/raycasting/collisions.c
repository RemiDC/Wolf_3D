/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:16:08 by kibotrel          #+#    #+#             */
/*   Updated: 2019/05/29 01:21:56 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

void			y_collisions(t_ray *ray, t_cam cam)
{
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->hit_y.y = floor(cam.coord.y / CELL) * CELL - 0.0000001;
	else
		ray->hit_y.y = floor(cam.coord.y / CELL) * CELL + CELL;
	ray->gap_y.y = CELL;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->gap_y.y *= -1;
	ray->hit_y.x = cam.coord.x + (cam.coord.y - ray->hit_y.y) / tan(ray->angle);
	ray->gap_y.x = -(CELL / tan(ray->angle));
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->gap_y.x *= -1;
}

void			x_collisions(t_ray *ray, t_cam cam, t_data data)
{
	if (ray->angle > data.north && ray->angle < data.south)
		ray->hit_x.x = floor(cam.coord.x / CELL) * CELL - 0.0000001;
	else
		ray->hit_x.x = floor(cam.coord.x / CELL) * CELL + CELL;
	ray->gap_x.x = CELL;
	if (ray->angle > data.north && ray->angle < data.south)
		ray->gap_x.x *= -1;
	ray->hit_x.y = cam.coord.y + (cam.coord.x - ray->hit_x.x) * tan(ray->angle);
	ray->gap_x.y = -(CELL * tan(ray->angle));
	if (ray->angle > data.north && ray->angle < data.south)
		ray->gap_x.y *= -1;
}

static void		check_bounds(double *x, double *y, int max_x, int max_y)
{
	if (*x > (max_x - 1) * CELL)
		*x = (max_x - 1) * CELL;
	else if (*x < 0)
		*x = 0;
	if (*y > (max_y - 1) * CELL)
		*y = (max_y - 1) * CELL;
	else if (*y < 0)
		*y = 0;
}

void			check_collisions(t_ray *ray, int **map, int height, int width)
{
	t_pos	hit;

	hit.x = 0;
	hit.y = 0;
	while (hit.x == 0 || hit.y == 0)
	{
		if (hit.x == 0)
			check_bounds(&ray->hit_x.x, &ray->hit_x.y, width, height);
		if (hit.y == 0)
			check_bounds(&ray->hit_y.x, &ray->hit_y.y, width, height);
		if (map[(int)ray->hit_x.y / CELL][(int)ray->hit_x.x / CELL] == 1)
			hit.x = 1;
		else if (hit.x == 0)
		{
			ray->hit_x.x += ray->gap_x.x;
			ray->hit_x.y += ray->gap_x.y;
		}
		if (map[(int)ray->hit_y.y / CELL][(int)ray->hit_y.x / CELL] == 1)
			hit.y = 1;
		else if (hit.y == 0)
		{
			ray->hit_y.x += ray->gap_y.x;
			ray->hit_y.y += ray->gap_y.y;
		}
	}
}
