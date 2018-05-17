/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscott <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:11:11 by rscott            #+#    #+#             */
/*   Updated: 2018/05/17 13:39:20 by rscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
