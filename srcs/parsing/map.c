/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:16:20 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/13 12:33:20 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "wolf3d.h"

static void	expand_map(int **map, t_env *env)
{
	int		y;
	int		x;

	y = -1;
	while (++y < env->height - 1)
	{
		x = -1;
		while (++x < env->width)
			map[y][x] = env->map[y][x];
		free(env->map[y]);
	}
	free(env->map);
}

static void	array_to_map(char **coords, t_env *env)
{
	int		y;
	int		x;
	int		**map;

	limits(coords, env);
	if (!(map = (int**)malloc(sizeof(int*) * env->height)))
	{
		free_switch(env, 0);
		ft_print_error("ERR_MALLOC", 5);
	}
	y = -1;
	while (++y < env->height)
		if (!(map[y] = (int*)malloc(sizeof(int) * (env->width))))
		{
			free_switch(env, 1);
			ft_print_error("ERR_MALLOC", 5);
		}
	if (env->height - 1 > 0)
		expand_map(map, env);
	x = -1;
	while (++x < env->width)
		map[y - 1][x] = ft_atoi(coords[x]);
	env->map = map;
}

static void	build_map(const int fd, char *row, t_env *env)
{
	char	**coords;

	while (ft_get_next_line(fd, &row))
	{
		check_row(row, env);
		if (!(coords = ft_strsplit(row, ' ')))
			ft_print_error(ERR_SPLIT, 8);
		if (env->height == 1)
			env->width = size(coords);
		else if (size(coords) != env->width)
			ft_print_error(ERR_WIDTH, 9);
		array_to_map(coords, env);
		free_parse(row, coords, env, 3);
	}
	if (!env->height)
		ft_print_error(ERR_EMPTY_FILE, 10);
}

void		parse_file(char *file, t_env *env)
{
	int		fd;
	char	*row;

	env->height = 0;
	row = NULL;
	if (!ft_isvalidname(file, ".w3d") && free_switch(env, 0))
		ft_print_error(ERR_FILENAME, 2);
	if ((fd = open(file, O_RDONLY)) < 0 && free_switch(env, 0))
		ft_print_error(ERR_OPEN, 3);
	build_map(fd, row, env);
	if (close(fd) && free_switch(env, 1))
		ft_print_error(ERR_CLOSE, 4);
	bottom_border(env);
}
