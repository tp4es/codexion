#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_config { int coders; int burnout; int compile; int debug; int refactor; int required; int cooldown; int edf; } t_config;
typedef struct s_coder { int id; int compiled; long long last_compile; struct s_sim *sim; } t_coder;
typedef struct s_request { t_coder *coder; long long order; } t_request;
typedef struct s_sim { t_config cfg; t_coder *coders; pthread_t *threads; t_request *heap; int heap_size; int *dongles; long long *ready; long long started; long long sequence; int stopped; int lock_ready; int print_ready; int cond_ready; pthread_mutex_t lock; pthread_mutex_t print; pthread_cond_t changed; } t_sim;

void	*ft_calloc(size_t count, size_t size);
long long	now_ms(void);
int	ms_sleep(long long duration);
void	log_state(t_sim *sim, int id, char *state);
int	parse_config(int argc, char **argv, t_config *cfg);
int	init_sim(t_sim *sim, t_config cfg);
void	destroy_sim(t_sim *sim);
int	heap_push(t_sim *sim, t_coder *coder);
void	heap_pop(t_sim *sim);
int	heap_first(t_sim *sim, t_coder *coder);
void	*coder_routine(void *arg);
void	*monitor_routine(void *arg);
int	run_simulation(t_sim *sim);

#endif
