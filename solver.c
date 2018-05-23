/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscott <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:11:11 by rscott            #+#    #+#             */
/*   Updated: 2018/05/23 13:33:22 by rscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	[line 124] called from cycle()
**	removes a tetromino from the map
*/

void	deletetetri(char **grid, char *tetri, int row, int col)
{
	char	ch;
	int		i;

	ch = getletter(tetri);
	i = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			if (i == 4)
				return ;
			if (grid[row][col] == ch)
			{
				i++;
				grid[row][col] = '.';
			}
			col++;
		}
		row++;
	}
}

/*
**	[line 120] called from cycle()
**	places a tetromino on the map
*/

void	puttetri(char **map, char *tetri, int x, int y)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (tetri[i])
	{
		if (c == 4)
		{
			x++;
			c = 0;
			y -= 4;
		}
		if (tetri[i] >= 'A' && tetri[i] <= 'Z')
			map[x][y] = tetri[i];
		i++;
		c++;
		y++;
	}
}

/*
**	[line 118] called from cycle()
**	checks for an available spot on the map to place a single tetromino
*/

int		checkspot(char **map, char *tetri, int x, int y)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (tetri[i])
	{
		if (c == 4)
		{
			x++;
			c = 0;
			y = y - 4;
		}
		if (tetri[i] >= 'A' && tetri[i] <= 'Z' && map[x][y] != '.')
			return (0);
		i++;
		c++;
		y++;
	}
	return (1);
}

/*
**	[line 150] called from solver()
**	recursive function that checks for the first open spot on the map then
**	places a tetromino. then checks if the next tetromino will fit [line 121],
**	and if not, deletes the previously placed tetromino and tries to place it
**	in the next available spot, then returns to place the next tetromino
*/

int		cycle(char **map, char **tetri, int x, int y)
{
	if (*tetri == 0)
		return (1);
	while (map[x])
	{
		while (map[x][y])
		{
			if (checkspot(map, *tetri, x, y))
			{
				puttetri(map, *tetri, x, y);
				if (cycle(map, (tetri + 1), 0, 0))
					return (1);
				else
					deletetetri(map, *tetri, x, y);
			}
			y++;
		}
		x++;
		y = 0;
	}
	return (0);
}

/*
**	[fillit.c:126] called from main()
**	[line 146-149] sets the size of the map then makes the map
**	[line 150-157] if cycle returns 0 then the tetrominos can't fit,
**			so the map is remade one size larger
*/

int		solver(char **separatedtetris, int numberoftetris)
{
	char	**map;
	int		mapside;

	mapside = setsidesize(numberoftetris);
	map = makemap(mapside, 0, -1);
	if (!map)
		return (0);
	while (!cycle(map, separatedtetris, 0, 0))
	{
		freemap(map, mapside);
		mapside++;
		map = makemap(mapside, 0, -1);
		if (!map)
			return (0);
	}
	printmap(map, mapside);
	return (0);
}
