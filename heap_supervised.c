/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_supervised.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 09:50:08 by tide.oli          #+#    #+#             */
/*   Updated: 2026/09/27 14:01:59 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>

static void swap(int *first, int *second)
{
	int temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

static void sift_up(int *numbers, int index)
{
	int father;

	while (index > 0)
	{
		father = (index - 1) / 2;
		if (numbers[father] <= numbers[index])
			break ;
		swap(&numbers[father], &numbers[index]);
		index = father;
	}
}

static void sift_down(int *numbers, int size, int index)
{
	int left;
	int right;
	int smallest;

	while (1)
	{
		left = index * 2 + 1;
		right = index * 2 + 2;
		smallest = index;
		if (left < size && numbers[left] < numbers[smallest])
			smallest = left;
		if (right < size && numbers[right] < numbers[smallest])
			smallest = right;
		if (smallest == index)
			break ;
		swap(&numbers[index], &numbers[smallest]);
		index = smallest;
	}
}

void heap_queue(int *numbers, int size)
{
	int i;

	i = size / 2 - 1;
	while (i >= 0)
	{
		sift_down(numbers, size, i);
		i--;
	}
}

int heap_add(int **numbers, int *size, int value)
{
	int *resized;

	resized = realloc(*numbers, sizeof(**numbers) * (*size + 1));
	if (!resized)
		return (1);
	* numbers = resized;
	(*numbers)[*size] = value;
	sift_up(*numbers, *size);
	(*size)++;
	return (0);
}

int heap_pop(int **numbers, int *size, int *value)
{
	int *resized;

	if (*size == 0)
		return (1);
	*value = (*numbers)[0];
	(*size)--;
	if (*size > 0)
	{
		(*numbers)[0] = (*numbers)[*size];
		sift_down(*numbers, *size, 0);
	}
	resized = realloc(*numbers, sizeof(**numbers) * *size);
	if (resized || *size == 0)
		* numbers = resized;
	return (0);
}

