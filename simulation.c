#include "codexion.h"

static int	allocate_arrays(t_sim *sim)
{
	int	count;

	count = sim->cfg.coders;
	sim->coders = ft_calloc(count, sizeof(*sim->coders));
	sim->threads = ft_calloc(count, sizeof(*sim->threads));
	sim->heap = ft_calloc(count, sizeof(*sim->heap));
	sim->dongles = ft_calloc(count, sizeof(*sim->dongles));
	sim->ready = ft_calloc(count, sizeof(*sim->ready));
	if (!sim->coders || !sim->threads || !sim->heap || !sim->dongles || !sim->ready)
		return (1);
	return (0);
}

int	init_sim(t_sim *sim, t_config cfg)
{
	memset(sim, 0, sizeof(*sim));
	sim->cfg = cfg;
	if (allocate_arrays(sim))
		return (free(sim->coders), free(sim->threads), free(sim->heap), free(sim->dongles), free(sim->ready), 1);
	if (pthread_mutex_init(&sim->lock, NULL)) return (destroy_sim(sim), 1);
	sim->lock_ready = 1;
	if (pthread_mutex_init(&sim->print, NULL)) return (destroy_sim(sim), 1);
	sim->print_ready = 1;
	if (pthread_cond_init(&sim->changed, NULL)) return (destroy_sim(sim), 1);
	sim->cond_ready = 1;
	return (0);
}

void	destroy_sim(t_sim *sim)
{
	free(sim->coders); free(sim->threads); free(sim->heap);
	free(sim->dongles); free(sim->ready);
	if (sim->cond_ready) pthread_cond_destroy(&sim->changed);
	if (sim->print_ready) pthread_mutex_destroy(&sim->print);
	if (sim->lock_ready) pthread_mutex_destroy(&sim->lock);
}

static void	join_threads(t_sim *sim, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		pthread_join(sim->threads[index], NULL);
		index++;
	}
}

int	run_simulation(t_sim *sim)
{
	pthread_t	monitor;
	int	index;

	sim->started = now_ms(); index = 0;
	while (index < sim->cfg.coders)
	{
		sim->coders[index].id = index; sim->coders[index].sim = sim; sim->coders[index].last_compile = sim->started;
		if (pthread_create(&sim->threads[index], NULL, coder_routine, sim->coders + index)) break ;
		index++;
	}
	if (index == sim->cfg.coders) pthread_create(&monitor, NULL, monitor_routine, sim);
	pthread_mutex_lock(&sim->lock); sim->stopped = index != sim->cfg.coders; pthread_cond_broadcast(&sim->changed); pthread_mutex_unlock(&sim->lock);
	join_threads(sim, index);
	if (index == sim->cfg.coders) pthread_join(monitor, NULL);
	return (index != sim->cfg.coders);
}
