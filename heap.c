#include "codexion.h"

static int	before(t_sim *sim, int first, int second)
{
	long long	one;
	long long	two;

	if (!sim->cfg.edf)
		return (sim->heap[first].order < sim->heap[second].order);
	one = sim->heap[first].coder->last_compile + sim->cfg.burnout;
	two = sim->heap[second].coder->last_compile + sim->cfg.burnout;
	if (one == two)
		return (sim->heap[first].order < sim->heap[second].order);
	return (one < two);
}

int	heap_push(t_sim *sim, t_coder *coder)
{
	int	index;
	int	parent;

	index = sim->heap_size++; sim->heap[index].coder = coder;
	sim->heap[index].order = sim->sequence++;
	while (index)
	{
		parent = (index - 1) / 2;
		if (before(sim, parent, index)) break ;
		sim->heap[index] = sim->heap[parent]; sim->heap[parent] = (t_request){coder, sim->sequence - 1};
		index = parent;
	}
	return (0);
}

void	heap_pop(t_sim *sim)
{
	int	index;
	int	child;
	t_request	last;

	last = sim->heap[--sim->heap_size]; index = 0;
	while (index * 2 + 1 < sim->heap_size)
	{
		child = index * 2 + 1;
		if (child + 1 < sim->heap_size && before(sim, child + 1, child)) child++;
		if (before(sim, child, sim->heap_size)) sim->heap[index] = sim->heap[child];
		else break ;
		index = child;
	}
	sim->heap[index] = last;
}

int	heap_first(t_sim *sim, t_coder *coder)
{
	return (sim->heap_size && sim->heap[0].coder == coder);
}
