/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 09:50:08 by tide.oli          #+#    #+#             */
/*   Updated: 2026/09/27 14:02:31 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

static int	numbers[4];
static int	father;
static int	left;
static int	right;
static int	tmp;
static int	i;

void	heap_queue(int **test)
{
	int	ordered;
	
	ordered = 0;
	while (ordered == 0)
	{
		i = 1;
		ordered = 1;
		while(number[i])
		{
			father = ((i - 1) / 2);
			if (number[i] > number[father])
			{
				ordered = 1;
				tmp = number[i];
				number[i] = number[father];
				number[father] = tmp;
			}
			i++;
		}		
	}
}

void	heap_pop(int **numbers, int size)
{
	int	*c_number;
	int	*temp;

	c_number = malloc(sizeof(int) * (size - 1));
	if (!c_number)
		return ;
	temp = (*number + 1);
	memcpy(c_number, temp);
	*number = c_number;
	heap_queue(numbers);
	free(c_number);
}

void	heap_add(int **numbers, int size, int n_number)
{
	int	*c_number;

	c_number = malloc(sizeof(int) * (size + 1));
	memcpy(c_number, *numbers);
	c_number[size] = n_number;
	*numbers = malloc(sizeof(int) * (size + 1));
	*number = c_number;
	heap_queue(numbers);
	free(c_number);
}
