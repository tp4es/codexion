#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_sim		sim;
	int		status;

	if (parse_config(argc, argv, &config))
		return (printf("Invalid arguments\n"), 1);
	if (init_sim(&sim, config))
		return (fprintf(stderr, "Allocation failure\n"), 1);
	status = run_simulation(&sim);
	destroy_sim(&sim);
	return (status);
}
