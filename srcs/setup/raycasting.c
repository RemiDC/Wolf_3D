/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 22:47:01 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/13 16:42:19 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "env.h"
#include "wolf3d.h"

void	setup_raycasting(t_cam *cam, t_ray *ray, int width)
{
	if (cam->angle >= 330)
		ray->angle = radians(cam->angle - 330);
	else
		ray->angle = radians(cam->angle + 30);
	ray->step = radians(cam->fov / width);
}

void	setup_slice(t_ray *ray, t_cam *cam, int x, t_env *env)
{
	double	angle;

	angle = radians(cam->angle) - ray->angle;
	ray->distance = smallest_distance(ray, env->data, cam->coord) * cos(angle);
	ray->wall.size = ceil((CELL / ray->distance) * cam->distance);
	ray->wall.start.x = x;
	ray->wall.start.y = (env->h / 2) - (ray->wall.size / 2) + cam->offset;
	ray->wall.end.x = x;
	ray->wall.end.y = (ray->wall.start.y + ray->wall.size);
}
