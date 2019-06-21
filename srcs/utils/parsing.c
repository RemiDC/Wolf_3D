/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:24:06 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 12:12:57 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "wolf3d.h"

int		size(char **coords)
{
	int	y;

	y = 0;
	while (coords[y])
		y++;
	return (y);
}

void	bottom_border(t_env *env)
{
	int	y;
	int	x;

	y = env->height - 1;
	x = -1;
	while (++x < env->width)
		if (env->map[y][x] != 1)
			ft_print_error(ERR_MAP, 11);
}

void	check_row(char *row, t_env *env)
{
	int	i;

	i = -1;
	env->height++;
	if (!row)
		ft_print_error(ERR_EMPTY_ROW, 6);
	while (row[++i])
		if (!ft_isdigit(row[i]) && row[i] != ' ')
			ft_print_error(ERR_FORMAT, 7);
}

void	limits(char **coords, t_env *env)
{
	int	y;
	int	end;
	int	flag;

	y = -1;
	end = size(coords) - 1;
	if (!(flag = 0) && env->height == 1)
	{
		while (coords[++y] && flag != 1)
			if (coords[y][0] != '1' || (coords[y][0] == '1' && coords[y][1]))
				flag = 1;
	}
	else if (coords[0][0] != '1' || (coords[0][0] == '1' && coords[0][1])
		|| coords[end][0] != '1' || (coords[end][0] == '1' && coords[end][1]))
		flag = 1;
	if (flag == 1)
		ft_print_error(ERR_MAP, 11);
}
