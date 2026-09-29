#include "codexion.h"

static int	available(t_sim *sim, t_coder *coder)
{
	int	left;
	int	right;

	left = coder->id; right = (coder->id + 1) % sim->cfg.coders;
	return (!sim->dongles[left] && !sim->dongles[right]
		&& sim->ready[left] <= now_ms() && sim->ready[right] <= now_ms());
}

static int	take_dongles(t_coder *coder)
{
	t_sim	*sim;
	int	left;
	int	right;

	sim = coder->sim; left = coder->id; right = (left + 1) % sim->cfg.coders;
	pthread_mutex_lock(&sim->lock); heap_push(sim, coder);
	while (!sim->stopped && (!heap_first(sim, coder) || !available(sim, coder)))
	{
		pthread_mutex_unlock(&sim->lock);
		usleep(500);
		pthread_mutex_lock(&sim->lock);
	}
	if (!sim->stopped)
	{
		sim->dongles[left] = 1; sim->dongles[right] = 1; heap_pop(sim);
		coder->last_compile = now_ms();
	}
	pthread_mutex_unlock(&sim->lock);
	return (sim->stopped);
}

static void	release_dongles(t_coder *coder)
{
	t_sim	*sim;
	int	left;
	int	right;

	sim = coder->sim; left = coder->id; right = (left + 1) % sim->cfg.coders;
	pthread_mutex_lock(&sim->lock); sim->dongles[left] = 0; sim->dongles[right] = 0;
	sim->ready[left] = now_ms() + sim->cfg.cooldown;
	sim->ready[right] = sim->ready[left]; pthread_cond_broadcast(&sim->changed);
	pthread_mutex_unlock(&sim->lock);
}

static int	work(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	if (take_dongles(coder)) return (1);
	log_state(sim, coder->id, "has taken a dongle");
	log_state(sim, coder->id, "has taken a dongle");
	log_state(sim, coder->id, "is compiling"); ms_sleep(sim->cfg.compile);
	release_dongles(coder); log_state(sim, coder->id, "is debugging");
	ms_sleep(sim->cfg.debug); log_state(sim, coder->id, "is refactoring");
	ms_sleep(sim->cfg.refactor); return (0);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = arg;
	while (coder->compiled < coder->sim->cfg.required && !work(coder))
		coder->compiled++;
	pthread_mutex_lock(&coder->sim->lock);
	if (!coder->sim->stopped && coder->compiled == coder->sim->cfg.required)
		pthread_cond_broadcast(&coder->sim->changed);
	pthread_mutex_unlock(&coder->sim->lock);
	return (NULL);
}
