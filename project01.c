#include <unistd.h>
#include <stdlib.h>

#define SIZE 4 

void	square_grid(int grid[SIZE][SIZE])
{
	int	c;
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			c = '0' + grid[i][j];
			write(1, &c, 1);
			write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	checkrow(int grid[][SIZE], int row, int value)
{
	int	j;

	j = 0;
	while (j < SIZE)
	{
		if (grid[row][j] == value)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

int	checkcol(int grid[][SIZE], int col, int value)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (grid[i][col] == value)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_view(int *line, int expected)
{
	int	max_height;
	int	count;
	int	i;

	max_height = 0;
	count = 0;
	i = 0;
	while (i < SIZE)
	{
		if (line[i] > max_height)
		{
			count++;
			max_height = line[i];
		}
		i++;
	}
	return (count == expected);
}

int	is_valid(int grid[SIZE][SIZE], int constraints[16])
{
	int	i;
	int	j;
	int	temp[SIZE * 4];

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			temp[j] = grid[j][i];
			temp[SIZE + j] = grid[SIZE - 1 - j][i];
			temp[2 * SIZE + j] = grid[i][j];
			temp[3 * SIZE + j] = grid[i][SIZE - 1 - j];
			j++;
		}
		if (!check_view(temp, constraints[i])
			|| !check_view(temp + SIZE, constraints[4 + i])
			|| !check_view(temp + 2 * SIZE, constraints[8 + i])
			|| !check_view(temp + 3 * SIZE, constraints[12 + i]))
			return (0);
		i++;
	}
	return (1);
}

int	solve(int grid[SIZE][SIZE], int constraints[16], int row, int col)
{
	int	num;

	if (row == SIZE)
		return (is_valid(grid, constraints));
	if (col == SIZE)
		return (solve(grid, constraints, row + 1, 0));
	num = 1;
	while (num <= SIZE)
	{
		if (!checkrow(grid, row, num) && !checkcol(grid, col, num))
		{
			grid[row][col] = num;
			if (solve(grid, constraints, row, col + 1))
				return (1);
			grid[row][col] = 0;
		}
		num++;
	}
	return (0);
}

void	set_constraints(int *constraints, char *input)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (!input[i * 2] || input[i * 2] < '1' || input[i * 2] > '4')
		{
			write(1, "Error\n", 6);
			free(constraints);
			exit(1);
		}
		constraints[i] = input[i * 2] - '0';
		i++;
	}
}

void	initialize_grid(int grid[SIZE][SIZE])
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
			grid[i][j++] = 0;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	*constraints;
	int	grid[SIZE][SIZE];

	if (argc != 2)
		return (write(1, "Error\n", 6), 1);
	constraints = malloc(16 * sizeof(int));
	if (!constraints)
		return (1);
	set_constraints(constraints, argv[1]);
	initialize_grid(grid);
	if (solve(grid, constraints, 0, 0))
		square_grid(grid);
	else
		write(1, "Error\n", 6);
	free(constraints);
	return (0);
}