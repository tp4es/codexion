/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 13:01:37 by tide.oli          #+#    #+#             */
/*   Updated: 2026/09/16 15:47:39 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"
# include <limits.h>
# include <sys/time.h>

static long long	current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_value(char *value)
{
	return (atoi(value));
}

int	setup(char **input, t_config *load)
{
	int	i;
	int	*values[7];

	i = 0;
	values[0] = &load->n_coders;
	values[1] = &load->time_bo;
	values[2] = &load->time_tc;
	values[3] = &load->time_tdb;
	values[4] = &load->time_trf;
	values[5] = &load->n_compile;
	values[6] = &load->dongle_cd;
	while (i < 7)
	{
		if (!strcmp(input[i], "0"))
			*values[i] = 0;
		else
		{
			*values[i] = get_value(input[i]);
			if (!*values[i] || *values[i] < 0 || *values[i] > INT_MAX || *values[i] < INT_MIN)
				return (1);
		}
		i++;
	}
	if (!strcmp(input[i], "FIFO") || !strcmp(input[i], "EDF"))
		load->schedule = input[i];
	else
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	load;
	t_dongle	*dongles;
	int			i;
	long long	g_start_time;
	
	if (argc != 9)
		return (1);
	if (setup((argv + 1), &load))
		return(1);
	dongles = malloc(sizeof(*dongles) * load.n_coders);
	if (!dongles)
		return (1);
	g_start_time = current_time_ms();
	create_dongles(load, dongles);
	coder_act(load, dongles, g_start_time);
	i = 0;
	while (i < load.n_coders)
	{
		pthread_mutex_destroy(&dongles[i].d_mutex);
		pthread_cond_destroy(&dongles[i].d_condition);
		i++;
	}
	free(dongles);
	return(0);
}
