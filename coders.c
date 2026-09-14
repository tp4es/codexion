/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 06:04:32 by tide-oli          #+#    #+#             */
/*   Updated: 2026/09/15 01:51:49 by tide-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

typedef struct s_thread_data
{
	int	id;
	int	n_compile;
}	t_thread_data;

void	*coder_routine(void *arg)
{
	t_thread_data	*data;
	int				i;

	data = (t_thread_data *)arg;
	i = 0;
	while (i <= data->n_compile)
	{
		printf("Coder %d: %d\n", data->id, i);
		i++;
	}
	free(data);
	pthread_exit(NULL);
}

void	coder_act(int n_coders, int n_compile)
{
	pthread_t	*coders;
	t_thread_data	*thread_data;
	int			i;

	coders = malloc(sizeof(pthread_t) * n_coders);
	if (!coders)
		return ;
	i = 0;
	while (i < n_coders)
	{
		thread_data = malloc(sizeof(t_thread_data));
		if (!thread_data)
			return ;
		thread_data->id = i;
		thread_data->n_compile = n_compile;
		pthread_create(&coders[i], NULL, coder_routine, thread_data);
		i++;
	}
	i = 0;
	while (i < n_coders)
	{
		pthread_join(coders[i], NULL);
		i++;
	}
	free(coders);
}