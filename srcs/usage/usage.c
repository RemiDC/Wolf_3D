/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-jesu <nde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:30:44 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/20 09:38:09 by nde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	file_format(void)
{
	ft_putendl("\n\033[0m\033[32;1mFile format:\033[0m\033[36m");
	ft_putendl("\n\tThe map's name must be followed by \".w3d\" and should");
	ft_putendl("\tlook like the following :\n");
	ft_putendl("\t1 1 1 1 1 1 1 1 1");
	ft_putendl("\t1 0 0 0 0 0 0 0 1");
	ft_putendl("\t1 0 0 0 1 0 0 0 1");
	ft_putendl("\t1 0 1 1 1 1 1 0 1");
	ft_putendl("\t1 0 0 1 1 9 0 0 1");
	ft_putendl("\t1 1 1 1 1 1 1 1 1");
	ft_putendl("\n\tThe map must be bounded by walls which are represented by");
	ft_putendl("\tthe value 1. The folowing values are handled in parsing :");
	ft_putendl("\n\t- Empty cell in which you can move (0)");
	ft_putendl("\t- Walls that you can't go through (1)");
	ft_putendl("\t- Spawnpoint (9)");
}

static void	error_handling(void)
{
	ft_putendl("\n\033[0m\033[32;1mError handling:\033[0;36m");
	ft_putendl("\n\tEach following error code are handled by the program...");
	ft_putendl("\n\t- Wrong directory (1)\n\t- Wrong filename (2)");
	ft_putendl("\t- Can't open file (3)\n\t- Can't close file (4)");
	ft_putendl("\t- Can't allocate memory (5)\n\t- Empty line (6)");
	ft_putendl("\t- Incorrect format (7)\n\t- Can't retrieve line infos (8)");
	ft_putendl("\t- Uneven width (9)\n\t- Empty file (10)");
	ft_putendl("\t- Unbounded map (11)");
	ft_putendl("\n\tUse \"echo $?\" to know the last process returned value.");
}

static void	keyboard_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mKeyboard controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in window :");
	ft_putendl("\n\t- Moving in the map (W / A / S / D)");
	ft_putendl("\t- Rotate the camera's angle (< / >)");
	ft_putendl("\t- Modify camera's height (Page_Up / Page_Down)");
	ft_putendl("\t- Respawn in player's spawnpoint (R)");
	ft_putendl("\t- Toggle the minimap (Tab)");
	ft_putendl("\t- Enable fullscreen (F)");
	ft_putendl("\t- Pause the game (P)");
	ft_putendl("\t- Toggle sprint (LShift)");
}

static void	mouse_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mMouse controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in window :");
	ft_putendl("\n\t- Move the camera with the mouse");
	ft_putendl("\t- Resize the window (While pause is activated)");
}

void		usage(void)
{
	ft_putendl("\n\033[32;1musage: ./wolf3d \'map.w3d\'\033[0;36m");
	ft_putendl("\n\tmap.w3d : array of values.");
	file_format();
	error_handling();
	keyboard_controls();
	mouse_controls();
	ft_putendl("\n\033[0m\033[32;1mCredits:\033[0;36m");
	ft_putendl("\n\tMade by kibotrel, reda-con and nde-jesu.\n\033[0m");
}
