#include "codexion.h"

static int	finished(t_sim *sim)
{
	int	index;

	index = 0;
	while (index < sim->cfg.coders)
	{
		if (sim->coders[index].compiled < sim->cfg.required)
			return (0);
		index++;
	}
	return (1);
}

static int	burned(t_sim *sim, int *id)
{
	int	index;

	index = 0;
	while (index < sim->cfg.coders)
	{
		if (now_ms() - sim->coders[index].last_compile > sim->cfg.burnout)
			return (*id = index, 1);
		index++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		id;

	sim = arg;
	while (1)
	{
		pthread_mutex_lock(&sim->lock);
		if (finished(sim) || burned(sim, &id))
		{
			if (finished(sim)) id = -1;
			sim->stopped = 1;
			pthread_cond_broadcast(&sim->changed);
			pthread_mutex_unlock(&sim->lock);
			if (id >= 0)
				log_state(sim, id, "burnedout");
			return (NULL);
		}
		pthread_mutex_unlock(&sim->lock); usleep(500);
	}
}
