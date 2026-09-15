/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 06:04:32 by tide-oli          #+#    #+#             */
/*   Updated: 2026/09/15 20:47:56 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"
# include <sys/time.h>

static long long		g_start_time;

static long long	current_time_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	log_action(t_coder *coder, char *action)
{
	long long timestamp;

	if (g_start_time == 0)
		g_start_time = current_time_ms();
	timestamp = current_time_ms() - g_start_time;
	printf("%lld Coder %d: %s\n", timestamp, coder->id, action);
}

void	*coder_routine(void *arg)
{
    t_coder	*coder;

    coder = (t_coder *)arg;
    while (coder->n_compile > 0)
    {
		pthread_mutex_lock(&g_start_mutex);
        log_action(coder, "Compile");
        usleep(coder->time_tc * 1000);
        log_action(coder, "Debug");
        usleep(coder->time_tdb * 1000);
        log_action(coder, "Refactor");
        usleep(coder->time_trf * 1000);
        coder->n_compile--;
		pthread_mutex_unlock(&g_start_mutex);
    }
    free(coder);
    return (NULL);
}

void	coder_load(t_coder *coder, t_config parameters, int id, t_dongle *dongle)
{
	coder->id = id;
	coder->state = 0;
	coder->time_bo = parameters.time_bo;
	coder->time_tc = parameters.time_tc;
	coder->time_tdb = parameters.time_tdb;
	coder->time_trf = parameters.time_trf;
	coder->n_compile = parameters.n_compile;
	coder->dongle = dongle[0];
}

void	coder_act(t_config parameters, t_dongle *dongles)
{
	pthread_t	*coders;
	t_coder		*coder;
	int			i;

	coders = malloc(sizeof(pthread_t) * parameters.n_coders);
	if (!coders)
		return ;
	i = 0;
	while (i < parameters.n_coders)
	{
		coder = malloc(sizeof(*coder));
		if (!coder)
			return ;
		coder_load(coder, parameters, i, dongles);
		pthread_create(&coders[i], NULL, coder_routine, coder);
		i++;
	}
	i = 0;
	while (i < parameters.n_coders)
	{
		pthread_join(coders[i], NULL);
		i++;
	}
	free(coders);
}