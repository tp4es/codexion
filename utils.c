#include "codexion.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	if (size && count > ((size_t)-1) / size)
		return (NULL);
	memory = malloc(count * size);
	if (!memory)
		return (NULL);
	memset(memory, 0, count * size);
	return (memory);
}

long long	now_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ms_sleep(long long duration)
{
    long long	chunk;

    while (duration > 0)
    {
        chunk = duration;
        if (chunk > 1000)
            chunk = 1000;
        if (usleep((useconds_t)chunk * 1000) != 0)
            return (1);
        duration -= chunk;
    }
    return (0);
}

void	log_state(t_sim *sim, int id, char *state)
{
	pthread_mutex_lock(&sim->print);
	pthread_mutex_lock(&sim->lock);
	if (!sim->stopped || !strcmp(state, "burnedout"))
		printf("%lld %d %s\n", now_ms() - sim->started, id + 1, state);
	pthread_mutex_unlock(&sim->lock);
	pthread_mutex_unlock(&sim->print);
}
