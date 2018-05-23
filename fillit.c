/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rscott <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:09:53 by rscott            #+#    #+#             */
/*   Updated: 2018/05/23 13:30:44 by rscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <stdio.h>

/*
** [line 112]	called from main.
** makevalidcombos uses strcpy to place the hardcoded strings of valid
** tetromino shapes into the validcombos 2d array.
*/

void	makevalidcombos(char validcombos[20][15])
{
	ft_strcpy(validcombos[0], "###...#");
	ft_strcpy(validcombos[1], ".#...#..##");
	ft_strcpy(validcombos[2], "#...###");
	ft_strcpy(validcombos[3], "##..#...#");
	ft_strcpy(validcombos[4], "###.#");
	ft_strcpy(validcombos[5], "##...#...#");
	ft_strcpy(validcombos[6], "..#.###");
	ft_strcpy(validcombos[7], "#...#...##");
	ft_strcpy(validcombos[8], "###..#");
	ft_strcpy(validcombos[9], ".#..##...#");
	ft_strcpy(validcombos[10], ".#..###");
	ft_strcpy(validcombos[11], "#...##..#");
	ft_strcpy(validcombos[12], ".##.##");
	ft_strcpy(validcombos[13], "#...##...#");
	ft_strcpy(validcombos[14], "##..##");
	ft_strcpy(validcombos[15], "#...#...#...#");
	ft_strcpy(validcombos[16], "####");
	ft_strcpy(validcombos[17], ".#..##..#");
	ft_strcpy(validcombos[18], "##...##");
}

/*
** [line 113]	called from main
** tetriread() returns the number of valid tetrominos found in the input
** [lines 65-73]	fd stores the file descriptor returned from open();
** fd stores the file descriptor returned from running open() on the input.
** buf[ft_strlen(buf)] = '\0'; null terminates the string.
** closes the input.
** [line 74-84]		calls shapecheck() [inputchecker.c:50??]
** shapecheck(char *buf, int i, int widthcount, int heightcount)
** buf is the input, i is -1 due to pre-incrementation in shapecheck's loop,
** i, widthcount and heightcount are not declared in shapecheck due to
** keep the function within 25 lines in length.
** if shapecheck or countvalidtetris return 0 then the input is invalid
** and an error is thrown.
*/

int	tetriread(char *argv[], char *buf)
{
	int fd;
	int validtetrisfound;

	validtetrisfound = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("error\n");
		exit(1);
	}
	read(fd, buf, 526);
	buf[ft_strlen(buf)] = '\0';
	close(fd);
	if (shapecheck(buf, -1, 0, 0) == 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	validtetrisfound = countvalidtetris(buf);
	if (validtetrisfound == 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	else
		return (validtetrisfound);
}

/*
** [line 102]	char validcombos[20][15]; this will store the valid tetrimino
** shapes as strings. there are 19 shapes with a max length of 15.
** [line 103]	char buf[526]; this will store the input as a string.
** 26 tetriminos is the max input, so 26 * 21 characters + 1 for \0.
** [line 112]	makevalidcombos uses strcpy to place the hardcoded strings into
** the validcombos 2d array
** [lines 113-123]	reads the input, stores the # of valid tetrominos found.
** throws an error if the input is invalid.
** passes the 2d array of valid tetrominos to solver.
*/

int		main(int argc, char *argv[])
{
	char	validcombos[20][15];
	char	buf[526];
	char	**checkedtetris;
	int		numberoftetris;

	if (argc != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (0);
	}
	makevalidcombos(validcombos);
	numberoftetris = tetriread(argv, buf);
	if (numberoftetris != 0)
	{
		if (!(checkedtetris = inputchecker(buf,
						numberoftetris, validcombos, -1)))
		{
			ft_putstr("error\n");
			return (0);
		}
		else
			solver(checkedtetris, numberoftetris);
	}
	return (0);
}
